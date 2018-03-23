
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
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.security.KeyStore;

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
	private static String keystore_pth = null;
	private static String jks_passw = null;
        private static String key_passw = null;
	private static String version = "5";
	
	/* RingBuffer to forward messages on sending AgentDispatcher thread */
	private static RingBuffer ringb = new RingBuffer(100);
	
	Thread thr;
	
	/* AgentDispatcher loops on messages in RingBuffer and POSTs them
	 * to external Collector
	 */
    private static class AgentDispatcher  implements Runnable {
    	
    	private String readStream(InputStream stream) throws Exception {
    	    StringBuilder builder = new StringBuilder();
    	    try (BufferedReader in = new BufferedReader(new InputStreamReader(stream))) {
    	        String line;
    	        while ((line = in.readLine()) != null) {
    	            builder.append(line); // + "\r\n"(no need, json has no line breaks!)
    	        }
    	        in.close();
    	    }
    	    logger.error("Resp: " + builder.toString());
    	    //System.out.println("Resp: " + builder.toString());
    	    return builder.toString();
    	}

	// Create a trust manager that does not validate certificate chains
	TrustManager[] trustAllCerts = new TrustManager[] { 
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
    	
      public void run() {
 
      String datatosend=null;  
      for(;;){
    	  EvelObject tosend = ringb.take();
    	  if( tosend != null && ((datatosend = (String) tosend.datastr) != null))
    	  {
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
    	            	if( !keystore_pth.isEmpty() && !jks_passw.isEmpty() && !key_passw.isEmpty() )
    	            	{
    	                  final KeyStore keyStore = KeyStore.getInstance("JKS"); 
    	                  try (final InputStream is = new FileInputStream(keystore_pth)) { 
    	            	    keyStore.load(is, jks_passw.toCharArray()); 
    	                  } 
    	                  final KeyManagerFactory kmf = KeyManagerFactory.getInstance(KeyManagerFactory 
    	            	     .getDefaultAlgorithm()); 
    	                  kmf.init(keyStore, key_passw.toCharArray()); 
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
    	            	   exc.printStackTrace(); 
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
    	        OutputStream os = con.getOutputStream();
	    	    BufferedWriter writer = new BufferedWriter(
	    	                new OutputStreamWriter(os, "UTF-8"));
	    	    //Call writer POST
	    	    writer.write(datatosend);
	    	    writer.flush();
	    	    writer.close();
	    	    os.close();	
	    	    //Handle the response code for POST request
	    	    int respCode = con.getResponseCode();
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
                    readStream(es);
			    }
    	        
				
			  } catch (IOException e) {
				  e.printStackTrace();
			  } catch (Exception e) {
				e.printStackTrace();
			}
    		  
    	  }
    	  else
    	  {
    		  logger.trace(url + "Waiting for events");
    		  try {
				Thread.sleep(5);
			  } catch (InterruptedException e) {
    		                Thread.currentThread().interrupt();
				logger.trace("Interrupted on "+url);
				System.out.println("Interrupted on "+url);
				//e.printStackTrace();
			  }
    	  }
      }//end for
     }//end run
   }//end AgentDispatcher
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
     * @param   event_api_url    The API's URL.
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
    		String event_api_url,
    		int port,
            String path,
            String topic,
            String username,
            String password,
            String keystore_path,
            String jks_password,
            String key_password,
            Level level) throws IOException
    {
    	  EVEL_ERR_CODES rc = EVEL_ERR_CODES.EVEL_SUCCESS;

    	  EVEL_ENTER();

  	  	  BasicConfigurator.configure();

    	  /***************************************************************************/
    	  /* Check assumptions.                                                      */
    	  /***************************************************************************/
    	  assert(event_api_url != null);
    	  assert(port > 1024);
    	  assert(username != null);
    	  
    	  logger.setLevel(level);
    	  
    	  if( !isValidURL(event_api_url) ){
    		  System.out.println("Invalid Event API URL");
    		  logger.error("Invalid Event API URL");
    		  rc = EVEL_ERR_CODES.EVEL_ERR_GEN_FAIL;
    		  System.exit(1);
    	  }
    	  
    	  if(path == null){
    		  path = "";
    	  } else {
    		  version += "/example_vnf";
    	  }
    	  
          keystore_pth = keystore_path;
          jks_passw = jks_password;
          key_passw = key_password;
    	  
  		url = event_api_url+":"+Integer.toString(port)+path+"/eventListener/v"+version;
  		vesurl = null;
		try {
			vesurl = new URL(url);
			vesbatchurl = new URL(url+"/eventBatch");
		} catch (MalformedURLException e) {
			logger.info("Error in url input");
			e.printStackTrace();
			System.exit(1);
		}
  	    userpass = username + ":" + password;

        logger.info("Starting Agent Dispatcher thread");
        Thread t = new Thread(new AgentDispatcher());
        t.start();
    	  
        EVEL_EXIT();
    	return rc; 
    	
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
		String data = obj.evel_json_encode_event().toString();
		EvelObject myobj = new EvelObject(data,false);
    	boolean ret = ringb.put(myobj);
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
		String data = obj.evel_json_encode_event().toString();
		EvelObject myobj = new EvelObject(data,true);
    	boolean ret = ringb.put(myobj);
    	logger.info("Evel Post batch event ret:"+ret);
    	return ret;
    }
	

}
