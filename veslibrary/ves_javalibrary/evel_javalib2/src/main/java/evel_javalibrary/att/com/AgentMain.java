
package evel_javalibrary.att.com;

/**************************************************************************//**
 * @file
 * Header for EVEL library
 *
 * This file implements the EVEL library which is intended to provide a
 * simple wrapper around the complexity of AT&T's Vendor Event Listener API so
 * that VNFs can use it without worrying about details of the API transport.
 *
 * License
 * -------
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

import org.apache.log4j.Logger;
import org.apache.log4j.Level;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.ConnectException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.io.UnsupportedEncodingException;
import java.net.URL;
import java.nio.channels.InterruptedByTimeoutException;
import java.security.KeyStore;
import java.time.Duration;

import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.KeyManagerFactory;
import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSession;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;
import javax.net.ssl.TrustManagerFactory;

import org.apache.log4j.BasicConfigurator;

/**
 * @author Gokul Singaraju
 */


public class AgentMain {

    /**************************************************************************//**
     * Error codes
     *
     * Error codes for EVEL low level interface
     *****************************************************************************/
    public enum EVEL_ERR_CODES {
        EVEL_SUCCESS,                   /** The operation was successful.          */
        EVEL_ERR_GEN_FAIL,              /** Non-specific failure.                  */
        EVEL_CURL_LIBRARY_FAIL,         /** A cURL library operation failed.       */
        EVEL_PTHREAD_LIBRARY_FAIL,      /** A Posix threads operation failed.      */
        EVEL_OUT_OF_MEMORY,             /** A memory allocation failure occurred.  */
        EVEL_EVENT_BUFFER_FULL,         /** Too many events in the ring-buffer.    */
        EVEL_EVENT_HANDLER_INACTIVE,    /** Attempt to raise event when inactive.  */
        EVEL_NO_METADATA,               /** Failed to retrieve OpenStack metadata. */
        EVEL_BAD_METADATA,              /** OpenStack metadata invalid format.     */
        EVEL_BAD_JSON_FORMAT,           /** JSON failed to parse correctly.        */
        EVEL_JSON_KEY_NOT_FOUND,        /** Failed to find the specified JSON key. */
        EVEL_MAX_ERROR_CODES            /** Maximum number of valid error codes.   */
    }

    private static final Logger logger = Logger.getLogger(AgentMain.class);

    private static String url = null;
    private static URL vesurl = null;
    private static URL vesbatchurl = null;
    private static HttpURLConnection con = null;
    private static String userpass = null;
    private static String keystorePath = null;
    private static String jksPassw = null;
    private static String keyPassw = null;
    private static String version = "7";
    
    
    
    private static String userpass2 = null;
    private static String keystorePath2 = null;
    private static String jksPassw2 = null;
    private static String keyPassw2 = null;
    private static String url2 = null;
    private static URL vesurl2 = null;
    private static URL vesbatchurl2 = null;
    private static HttpURLConnection con2 = null;

    /* RingBuffer to forward messages on sending AgentDispatcher thread */
    private static RingBuffer ringb = new RingBuffer(100);
    private static volatile boolean shouldStop = false;

    private static Thread thr;

    /* AgentDispatcher loops on messages in RingBuffer and POSTs them
     * to external Collector
     */
    private static class AgentDispatcher  implements Runnable {
    	public static int httpResponse = 0;
    	public static int httpResponse2 = 0;
        private void sendObject(EvelObject tosend){
        	while(true) {        		
        		httpResponse = AgentMain.sendObjectWithReturn(tosend);        		
        	if((httpResponse  >= 200 && httpResponse  < 299) || httpResponse == 400) {           		        		
        		return;        		
        	}        	  
        	httpResponse2 = AgentMain.sendObjectWithReturn2(tosend);
        	if((httpResponse2 >= 200 && httpResponse2 < 299) || httpResponse2 == 400) {             	       		     		       		
        		return;
        	}
        	else {
        		
        	 	try {
                   	Thread.sleep(120000);                                                          
                   	}catch(Exception ee) {                   		
                   	}
        	}
        	}            
        }

        public void run() {

            String datatosend=null;
            while (!shouldStop){
                EvelObject tosend = ringb.take();
                if( tosend != null && ((datatosend = (String) tosend.datastr) != null))
                {
                    sendObject(tosend);
                }
                else
                {
                    logger.trace(url + "Waiting for events");
                    try {
                        Thread.sleep(5);
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                        logger.trace("Interrupted on "+url);
                        
                        
                    }
                }
            }//end while

            logger.trace("Caught stop event, emptying buffer before exiting");

            while (!ringb.isEmpty()){
                EvelObject tosend = ringb.take();
                if( tosend != null && ((datatosend = (String) tosend.datastr) != null))
                {
                    sendObject(tosend);
                }
            }
            logger.trace("Send buffer is empty, shutting down");
        }//end run
    }//end AgentDispatcher

    public static int doPost(HttpURLConnection con, String dataToSend) throws IOException {
              OutputStream os = con.getOutputStream();
              BufferedWriter writer = new BufferedWriter(
                  new OutputStreamWriter(os, "UTF-8"));
              //Call writer POST
              writer.write(dataToSend);
              writer.flush();
              writer.close();
              os.close();
              //Handle the response code for POST request
              return con.getResponseCode();
        }

    private static String readStream(InputStream stream) throws IOException {
        StringBuilder builder = new StringBuilder();
        try (BufferedReader in = new BufferedReader(new InputStreamReader(stream))) {
            String line;
            while ((line = in.readLine()) != null) {
                builder.append(line); // + "\r\n"(no need, json has no line breaks!)
            }
            in.close();
        }
        logger.error("Resp: " + builder.toString());
        
        return builder.toString();
    }

    // Create a trust manager that does not validate certificate chains
    private static TrustManager[] trustAllCerts = new TrustManager[] {
        new X509TrustManager() {
            public java.security.cert.X509Certificate[] getAcceptedIssuers() {
                return new java.security.cert.X509Certificate[0];
            }
            public void checkClientTrusted(
                java.security.cert.X509Certificate[] certs, String authType) {
            }
            public void checkServerTrusted(
                java.security.cert.X509Certificate[] certs, String authType) {
            }
        }
    };
    
    //Second Collector return object
    public static final int sendObjectWithReturn2(EvelObject tosend){
        String datatosend = (String) tosend.datastr;
        //process data
        logger.trace(url2 + "Got an event size second collector "+datatosend.length());
        logger.trace(datatosend);
        int respCode = 0;
        Duration timeout = Duration.ofSeconds(2000);
        try {

            if( tosend.type == false)
            	
                con2 = (HttpURLConnection) vesurl2.openConnection();
            
            else
                con2 = (HttpURLConnection) vesbatchurl2.openConnection();

            if (con2 instanceof HttpsURLConnection) {
            	
                HttpsURLConnection httpsConnection = (HttpsURLConnection) con2;

                try {

                    SSLContext sc = SSLContext.getInstance("TLSv1.2");
                    /* Get the JKS contents */
                    if( !keystorePath2.isEmpty() && !jksPassw2.isEmpty() && !keyPassw2.isEmpty() )
                    {
                        final KeyStore keyStore = KeyStore.getInstance("JKS");
                        try (final InputStream is = new FileInputStream(keystorePath2)) {
                            keyStore.load(is, jksPassw2.toCharArray());
                        }
                        final KeyManagerFactory kmf = KeyManagerFactory.getInstance(KeyManagerFactory
                                .getDefaultAlgorithm());
                        kmf.init(keyStore, keyPassw2.toCharArray());
                        final TrustManagerFactory tmf = TrustManagerFactory.getInstance(TrustManagerFactory
                                .getDefaultAlgorithm());
                        tmf.init(keyStore);
                        sc.init(kmf.getKeyManagers(), tmf.getTrustManagers(), new java.security.SecureRandom());
                    }
                    else
                    {
                        // Init the SSLContext with a TrustManager[] and SecureRandom()
                        sc.init(null, trustAllCerts, new java.security.SecureRandom());
                    }
                    httpsConnection.setDefaultHostnameVerifier(new HostnameVerifier()
                    {
                    public boolean verify(String hostname, SSLSession session)
                    {
                        return true;
                    }
                    });
                    httpsConnection.setSSLSocketFactory(sc.getSocketFactory());
                    con2  = httpsConnection;
                    
                    
                }
                
                catch (final Exception exc) {
                    logger.error("SSL/TLS connection error");
                }
            }
            
            //add reuqest header
            con2.setRequestMethod("POST");
            // No caching, we want the real thing.
           
            con2.setUseCaches (false);
            // Specify the content type.
           
            con2.setRequestProperty("Content-Type", "application/json");
            con2.setInstanceFollowRedirects( false );
           
            //Basic username password authentication
            String basicAuth = "Basic " + javax.xml.bind.DatatypeConverter.printBase64Binary(userpass2.getBytes("UTF-8"));
            con2.setRequestProperty ("Authorization", basicAuth);
            
            con2.setReadTimeout(15000 /* milliseconds */);
            
            con2.setConnectTimeout(15000 /* milliseconds */);
            
            // Send post request
            con2.setDoOutput(true);
            con2.setDoInput(true);
            
            con2.setFixedLengthStreamingMode(datatosend.length());
            
            
        
            try {
            	respCode = AgentMain.doPost(con2, datatosend);
              }catch (ConnectException ie) { 
                /* Handle the interruption. Or ignore it. */ 
            	  
           
              }
              catch (InterruptedByTimeoutException ee) { 
                /* Handle the error. Or ignore it. */ 
            	  
           
              }
              catch (IOException te) { 
                /* Handle the timeout. Or ignore it. */ 
            	  
              	
              }
            

            
            
                logger.trace(url2 + "Connection HTTP Response code :"+respCode);
                if(respCode < HttpURLConnection.HTTP_OK ) {
                    logger.trace(url2 + " **INFO**");
                }
                else if(respCode >= HttpURLConnection.HTTP_OK && respCode < HttpURLConnection.HTTP_MULT_CHOICE )
                {
                    logger.trace(url2 + " **OK**");
                    
                }
                else if(respCode >= HttpURLConnection.HTTP_MULT_CHOICE  && respCode < HttpURLConnection.HTTP_BAD_REQUEST )
                {
                    logger.warn(url2 + " **REDIRECTION**");
                    
                }
                else if(respCode >= HttpURLConnection.HTTP_BAD_REQUEST )
                {
                    logger.warn(url2 + " **SERVER ERROR**");                    
                    InputStream es = con2.getErrorStream();
                    AgentMain.readStream(es);
                }
            
                
                return respCode;                                            
        } catch (ConnectException e) {
        	
        } catch (IOException e) {
            logger.error("Exception during POST", e);
            
            
            return 0;
        }
        
        return respCode;

    }


    public static int sendObjectWithReturn(EvelObject tosend){
        String datatosend = (String) tosend.datastr;
        //process data
        logger.trace(url + "Got an event size "+datatosend.length());
        logger.trace(datatosend);

        try {

            if( tosend.type == false)
                con = (HttpURLConnection) vesurl.openConnection();
            else
                con = (HttpURLConnection) vesbatchurl.openConnection();

            if (con instanceof HttpsURLConnection) {
                HttpsURLConnection httpsConnection = (HttpsURLConnection) con;

                try {

                    SSLContext sc = SSLContext.getInstance("TLSv1.2");
                    /* Get the JKS contents */
                    if( !keystorePath.isEmpty() && !jksPassw.isEmpty() && !keyPassw.isEmpty() )
                    {
                        final KeyStore keyStore = KeyStore.getInstance("JKS");
                        try (final InputStream is = new FileInputStream(keystorePath)) {
                            keyStore.load(is, jksPassw.toCharArray());
                        }
                        final KeyManagerFactory kmf = KeyManagerFactory.getInstance(KeyManagerFactory
                                .getDefaultAlgorithm());
                        kmf.init(keyStore, keyPassw.toCharArray());
                        final TrustManagerFactory tmf = TrustManagerFactory.getInstance(TrustManagerFactory
                                .getDefaultAlgorithm());
                        tmf.init(keyStore);
                        sc.init(kmf.getKeyManagers(), tmf.getTrustManagers(), new java.security.SecureRandom());
                    }
                    else
                    {
                        // Init the SSLContext with a TrustManager[] and SecureRandom()
                        sc.init(null, trustAllCerts, new java.security.SecureRandom());
                    }
                    httpsConnection.setDefaultHostnameVerifier(new HostnameVerifier()
                            {
                                public boolean verify(String hostname, SSLSession session)
                    {
                        return true;
                    }
                    });
                    httpsConnection.setSSLSocketFactory(sc.getSocketFactory());
                    con  = httpsConnection;

                }
                catch (final Exception exc) {
                    logger.error("SSL/TLS connection error");
                }
            }

            //add reuqest header
            con.setRequestMethod("POST");
            // No caching, we want the real thing.
            con.setUseCaches (false);
            // Specify the content type.
            con.setRequestProperty("Content-Type", "application/json");
            con.setInstanceFollowRedirects( false );
            //Basic username password authentication
            String basicAuth = "Basic " + javax.xml.bind.DatatypeConverter.printBase64Binary(userpass.getBytes("UTF-8"));
            con.setRequestProperty ("Authorization", basicAuth);

            con.setReadTimeout(15000 /* milliseconds */);
            con.setConnectTimeout(15000 /* milliseconds */);
            // Send post request
            con.setDoOutput(true);
            con.setDoInput(true);

            con.setFixedLengthStreamingMode(datatosend.length());
            int respCode = AgentMain.doPost(con, datatosend);
            logger.trace(url + "Connection HTTP Response code :"+respCode);
            if(respCode < HttpURLConnection.HTTP_OK ) {
                logger.trace(url + " **INFO**");
            }
            else if(respCode >= HttpURLConnection.HTTP_OK && respCode < HttpURLConnection.HTTP_MULT_CHOICE )
            {
                logger.trace(url + " **OK**");
            }
            else if(respCode >= HttpURLConnection.HTTP_MULT_CHOICE  && respCode < HttpURLConnection.HTTP_BAD_REQUEST )
            {
                logger.warn(url + " **REDIRECTION**");
            }
            else if(respCode >= HttpURLConnection.HTTP_BAD_REQUEST )
            {
                logger.warn(url + " **SERVER ERROR**");

                InputStream es = con.getErrorStream();
                AgentMain.readStream(es);
            }

            return respCode;

        } catch (IOException e) {
            logger.error("Exception during POST", e);
            return 0;
        }
    }

    // Validate URL
    public static boolean isValidURL(String urlStr) {
        try {
            URL url = new URL(urlStr);
            return true;
        }
        catch (MalformedURLException e) {
            return false;
        }
    }

    /**************************************************************************//**
     * Library initialization.
     *
     * Initialize the EVEL library.
     *
     * @note  This function initializes the Java EVEL library interfaces.
     *        Validates input parameters and starts the AgentDispatcher thread
     *
     * @param   eventApiUrl    The API's URL.
     * @param   port    The API's port.
     * @param   path    The optional path (may be NULL).
     * @param   topic   The optional topic part of the URL (may be NULL).
     * @param   username  Username for Basic Authentication of requests.
     * @param   password  Password for Basic Authentication of requests.
     * @param   Level     Java Log levels.
     *
     * @returns Status code
     * @retval  EVEL_SUCCESS      On success
     * @retval  ::EVEL_ERR_CODES  On failure.
     *****************************************************************************/
    public static EVEL_ERR_CODES evel_initialize(
            String eventApiUrl,
            int port,
            String path,
            String topic,
            String username,
            String password,
            String evelKeystorePath,
            String evelJksPassword,
            String evelKeyPassword,
            String eventApiUrl2,
            int port2,
            String username2,
            String password2,
            Level level) throws IOException
    {
        EVEL_ERR_CODES rc = EVEL_ERR_CODES.EVEL_SUCCESS;

        EVEL_ENTER();

        BasicConfigurator.configure();

        /***************************************************************************/
        /* Check assumptions.                                                      */
        /***************************************************************************/
        assert(eventApiUrl != null);
        assert(port > 1024);
        assert(username != null);
        
        assert(eventApiUrl2 != null);
        assert(port2 > 1024);
        assert(username2 != null);

        logger.setLevel(level);

        if( !isValidURL(eventApiUrl) ){
            
            logger.error("Invalid Event API URL");
            rc = EVEL_ERR_CODES.EVEL_ERR_GEN_FAIL;
            System.exit(1);
        }
        
        if( !isValidURL(eventApiUrl2) ){
            
            logger.error("Invalid Event API URL");
            rc = EVEL_ERR_CODES.EVEL_ERR_GEN_FAIL;
            System.exit(1);
        }

        if(path == null){
            path = "";
        } else {
            version += "/example_vnf";
        }

        keystorePath = evelKeystorePath;
        jksPassw = evelJksPassword;
        keyPassw = evelKeyPassword;
        
        keystorePath2 = evelKeystorePath;
        jksPassw2 = evelJksPassword;
        keyPassw2 = evelKeyPassword;

        url = eventApiUrl+":"+Integer.toString(port)+path+"/eventListener/v"+version;
        vesurl = null;
        
        url2 = eventApiUrl2+":"+Integer.toString(port2)+path+"/eventListener/v"+version; 
        vesurl2 = null;
        try {
            vesurl = new URL(url);
            vesbatchurl = new URL(url+"/eventBatch");
            
            
            vesurl2 = new URL(url2);
            vesbatchurl2 = new URL(url2+"/eventBatch");
        } catch (MalformedURLException e) {
            logger.info("Error in url input");
            
            System.exit(1);
        }
        userpass = username + ":" + password;
        
        userpass2 = username2 + ":" + password2;

        logger.info("Starting Agent Dispatcher thread");
        thr = new Thread(new AgentDispatcher());
        thr.start();

        EVEL_EXIT();
        return rc;

    }

    public static void evel_shutdown() {
        if(shouldStop){
            logger.warn("evel_shutdown was called whilst the agent was already stopping - this has no effect");
        }
        shouldStop = true;
        logger.debug("Called evel_shutdown, will shutdown when the buffer is empty");
    }


    private static void EVEL_EXIT() {
        logger.trace("Exit VES Agent Main");
    }

    private static void EVEL_ENTER() {
        logger.trace("Enter VES Agent Main");
    }

    /**************************************************************************//**
     * Handle user formatted post message
     *
     * @note  This function handles VES 5.x formatted messages from all valid
     *        Domains and stores them in RingBuffer.
     *
     * @param   obj     VES 5.x formatted user messages with common header
     *                  and optional specialized body
     *
     * @retval  boolean    True  On successful acceptance False on failure
     *****************************************************************************/

    public static boolean evel_post_event(EvelHeader obj)
    {
        if (shouldStop){
            logger.error("evel_post_event called whilst agent is shutting down - event will not be posted");
            return false;
        }
        String data = obj.evel_json_encode_event().toString();
        EvelObject myobj = new EvelObject(data,false);
        boolean ret = ringb.put(myobj);
        logger.info("Evel Post event ret:"+ret);
        return ret;
    }

  /**************************************************************************//**
     * Handle user formatted post message, post the event, and return the HTTP error code
     *
     * @note  This function handles VES 5.x formatted messages from all valid
     *        Domains and stores them in RingBuffer.
     *
     * @param   obj     VES 5.x formatted user messages with common header
     *                  and optional specialized body
     *
     * @retval  int    The http code returned when sending the event
     *****************************************************************************/

    public static int evel_post_event_immediate(EvelHeader obj)
    {
        if (shouldStop){
            logger.error("evel_post_event_immediate called while agent is shutting down - event will not be posted");
            return 0;
        }

        String data = obj.evel_json_encode_event().toString();
        EvelObject myobj = new EvelObject(data,false);
        int ret = AgentMain.sendObjectWithReturn(myobj);
        logger.info("Evel Post event ret:"+ret);
        return ret;
    }

    /**************************************************************************//**
     * Handle user formatted post message
     *
     * @note  This function handles VES 5.x formatted messages from all valid
     *        Domains and stores them in RingBuffer.
     *
     * @param   obj     VES 5.x formatted user messages with common header
     *                  and optional specialized body
     *
     * @retval  boolean    True  On successful acceptance False on failure
     *****************************************************************************/

    public static boolean evel_post_event(EvelBatch obj)
    {
        if (shouldStop){
            logger.error("evel_post_event called whilst agent is shutting down - event will not be posted");
            return false;
        }
        String data = obj.evel_json_encode_event().toString();
        EvelObject myobj = new EvelObject(data,true);
        boolean ret = ringb.put(myobj);
        logger.info("Evel Post batch event ret:"+ret);
        return ret;
    }
}
