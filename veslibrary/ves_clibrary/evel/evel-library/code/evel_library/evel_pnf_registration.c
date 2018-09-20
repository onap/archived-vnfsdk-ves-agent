/*************************************************************************//**
 *
 * Copyright © 2017 AT&T Intellectual Property. All rights reserved.
 *
 * Unless otherwise specified, all software contained herein is
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
 *
 ****************************************************************************/
/**************************************************************************//**
 * @file
 * Implementation of EVEL functions relating to the PNF Registration.
 *
 ****************************************************************************/

#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "evel_throttle.h"

/**************************************************************************//**
 * Create a new PNF Registration event.
 *
 * @note    The mandatory fields on the PNF Registration must be supplied to the
 *          factory function and are immutable once set.  Optional fields have
 *          explicit setter functions, but again values may only be set once
 *          so that the State Change has immutable properties.
 *
 * @param event_name  Unique Event Name confirming Domain AsdcModel Description
 * @param event_id    A universal identifier of the event for: troubleshooting correlation, analysis, etc
 *
 * @returns pointer to the newly manufactured ::EVENT_PNF_REGISTRATION. If the
 *          event is not used it must be released using
 *          ::evel_free_pnf_registration
 * @retval  NULL  Failed to create the event.
 *****************************************************************************/
EVENT_PNF_REGISTRATION * evel_new_pnf_registration(const char* ev_name, const char *ev_id )
{
  EVENT_PNF_REGISTRATION * pnf_registration = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Allocate the PNF Registration.                                          */
  /***************************************************************************/
  pnf_registration = malloc(sizeof(EVENT_PNF_REGISTRATION));
  if (pnf_registration == NULL)
  {
    log_error_state("Out of memory");
    goto exit_label;
  }
  memset(pnf_registration, 0, sizeof(EVENT_PNF_REGISTRATION));
  EVEL_DEBUG("New PNF Registration is at %lp", pnf_registration);

  /***************************************************************************/
  /* Initialize the header & the PNF Registration fields. Optional string    */
  /* values are uninitialized (NULL).                                        */
  /***************************************************************************/
  evel_init_header_nameid(&pnf_registration->header,ev_name,ev_id);
  pnf_registration->header.event_domain = EVEL_DOMAIN_PNF_REGISTRATION;
  pnf_registration->major_version = EVEL_PNF_REGISTRATION_MAJOR_VERSION;
  pnf_registration->minor_version = EVEL_PNF_REGISTRATION_MINOR_VERSION;

  evel_init_option_string(&pnf_registration->last_service_date);
  evel_init_option_string(&pnf_registration->mac_address);
  evel_init_option_string(&pnf_registration->manufacture_date);
  evel_init_option_string(&pnf_registration->model_number);
  evel_init_option_string(&pnf_registration->oam_v4_ipaddress);
  evel_init_option_string(&pnf_registration->oam_v6_ipaddress);
  evel_init_option_string(&pnf_registration->serial_number);
  evel_init_option_string(&pnf_registration->sw_version);
  evel_init_option_string(&pnf_registration->unit_family);
  evel_init_option_string(&pnf_registration->unit_type);
  evel_init_option_string(&pnf_registration->vendor_name);
  pnf_registration->additional_fields = ht_create();

exit_label:
  EVEL_EXIT();
  return pnf_registration;
}

/**************************************************************************//**
 * Free a PNF Registration.
 *
 * Free off the PNF Registration supplied. Will free all contained allocated
 * memory.
 *
 * @note It does not free the PNF Registration itself, since that may be part 
 * of a larger structure.
 *****************************************************************************/
void evel_free_pnf_registration(EVENT_PNF_REGISTRATION * const pnf_registration)
{
  HASHTABLE_T *ht;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.  As an internal API we don't allow freeing NULL    */
  /* events as we do on the public API.                                      */
  /***************************************************************************/
  assert(pnf_registration != NULL);
  assert(pnf_registration->header.event_domain == EVEL_DOMAIN_PNF_REGISTRATION);

  /***************************************************************************/
  /* Free all internal strings then the header itself.                       */
  /***************************************************************************/
  ht = pnf_registration->additional_fields;
  if( ht != NULL )
  {
     ht_destroy(ht);
  }

  evel_free_option_string(&pnf_registration->last_service_date);
  evel_free_option_string(&pnf_registration->mac_address);
  evel_free_option_string(&pnf_registration->manufacture_date);
  evel_free_option_string(&pnf_registration->model_number);
  evel_free_option_string(&pnf_registration->oam_v4_ipaddress);
  evel_free_option_string(&pnf_registration->oam_v6_ipaddress);
  evel_free_option_string(&pnf_registration->serial_number);
  evel_free_option_string(&pnf_registration->sw_version);
  evel_free_option_string(&pnf_registration->unit_family);
  evel_free_option_string(&pnf_registration->unit_type);
  evel_free_option_string(&pnf_registration->vendor_name);

  evel_free_header(&pnf_registration->header);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Add an additional field name/value pair to the PNF Registration 
 *
 * The name and value are null delimited ASCII strings.  The library takes
 * a copy so the caller does not have to preserve values after the function
 * returns.
 *
 * @param pnf_registration  Pointer to the ::EVENT_PNF_REGISTRATION.
 * @param name          ASCIIZ string with the attribute's name.  The caller
 *                      does not need to preserve the value once the function
 *                      returns.
 * @param value         ASCIIZ string with the attribute's value.  The caller
 *                      does not need to preserve the value once the function
 *                      returns.
 *****************************************************************************/
void evel_pnf_registration_addl_field_add(
                             EVENT_PNF_REGISTRATION * const pnf_registration,
                             const char * const name,
                             const char * const value)
{
  char *nam=NULL;
  char *val=NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(pnf_registration != NULL);
  assert(pnf_registration->header.event_domain == EVEL_DOMAIN_PNF_REGISTRATION);
  assert(name != NULL);
  assert(value != NULL);

  EVEL_DEBUG("Adding name=%s value=%s", name, value);

  nam = strdup(name);
  val = strdup(value);

  ht_insert(pnf_registration->additional_fields, nam, val);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Encode the PNF Registration as a JSON PNF Registration
 *
 * @param jbuf              Pointer to the ::EVEL_JSON_BUFFER to encode into.
 * @param pnf_registration  Pointer to the ::EVENT_PNF_REGISTRATION to encode.
 *****************************************************************************/
void evel_json_encode_pnf_registration(EVEL_JSON_BUFFER * jbuf,
                               EVENT_PNF_REGISTRATION * pnf_registration)
{
  HASHTABLE_T *ht;
  ENTRY_T *entry;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(pnf_registration != NULL);
  assert(pnf_registration->header.event_domain == EVEL_DOMAIN_PNF_REGISTRATION);

  evel_json_encode_header(jbuf, &pnf_registration->header);
  evel_json_open_named_object(jbuf, "pnfRegistrationFields");

  /***************************************************************************/
  /* Optional fields.                                                        */
  /***************************************************************************/
  evel_enc_kv_opt_string(jbuf, "lastServiceDate", &pnf_registration->last_service_date);
  evel_enc_kv_opt_string(jbuf, "macAddress", &pnf_registration->mac_address);
  evel_enc_kv_opt_string(jbuf, "manufactureDate", &pnf_registration->manufacture_date);
  evel_enc_kv_opt_string(jbuf, "modelNumber", &pnf_registration->model_number);
  evel_enc_kv_opt_string(jbuf, "oamV4IpAddress", &pnf_registration->oam_v4_ipaddress);
  evel_enc_kv_opt_string(jbuf, "oamV6IpAddress", &pnf_registration->oam_v6_ipaddress);
  evel_enc_kv_opt_string(jbuf, "serialNumber", &pnf_registration->serial_number);
  evel_enc_kv_opt_string(jbuf, "softwareVersion", &pnf_registration->sw_version);
  evel_enc_kv_opt_string(jbuf, "unitFamily", &pnf_registration->unit_family);
  evel_enc_kv_opt_string(jbuf, "unitType", &pnf_registration->unit_type);
  evel_enc_kv_opt_string(jbuf, "vendorName", &pnf_registration->vendor_name);

  evel_json_checkpoint(jbuf);
  ht = pnf_registration->additional_fields;
  if( ht != NULL )
  {
    bool added = false;
    if( ht->size > 0)
    {
      evel_json_checkpoint(jbuf);
      if (evel_json_open_opt_named_object(jbuf, "additionalFields"))
      {

        for(unsigned int idx = 0; idx < ht->size; idx++ )
        {
          /*****************************************************************/
          /* Get the first entry of a particular Key and loop through the  */
          /* remaining if any. Then proceed to next key.                   */
          /*****************************************************************/
          entry =  ht->table[idx];
          while( entry != NULL && entry->key != NULL)
          {
            EVEL_DEBUG("Encoding heartBeatFields %s %s",(char *) (entry->key), entry->value);
            if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                              "additionalFields",
                                              entry->key))
            {
              //evel_json_open_object(jbuf);
              evel_enc_kv_string(jbuf, entry->key, entry->value);
              //evel_json_close_object(jbuf);
              added = true;
            }
            entry = entry->next;
          }
        }
      }
    }
    evel_json_close_object(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!added)
    {
      evel_json_rewind(jbuf);
    }
  }

  evel_enc_version(jbuf,
        "pnfRegistrationFieldsVersion",
         pnf_registration->major_version, pnf_registration->minor_version);

  evel_json_close_object(jbuf);

  EVEL_EXIT();
}

/****************************************************************//**
 * Set the last service date
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once. However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param pnfRegistration     Pointer to the pnfRegistration
 * @param last_service_date   The last service date to be set. ASCIIZ
 *                            string. The caller does not need to preserve
 *                            the value once the function returns.
*********************************************************************/
void evel_pnfRegistration_last_service_date_set(EVENT_PNF_REGISTRATION * pnfRegistration, const char * const last_service_date)
{
  EVEL_ENTER();


/***************************************************************************/
/* Check preconditions.                                                    */
/***************************************************************************/
  assert(pnfRegistration != NULL);
  assert(pnfRegistration->header.event_domain == EVEL_DOMAIN_PNF_REGISTRATION);
  assert(last_service_date != NULL);

  evel_set_option_string(&pnfRegistration->last_service_date, last_service_date, "Last Service Date");
  EVEL_EXIT();
}
/************************************************************************//**
 * Set the Mac Address
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries
 *        to overwrite, just ignoring the update instead.
 *
 * @param pnfRegistration     Pointer to the pnfRegistration
 * @param mac_address   The mac address to be set. ASCIIZ string. The
 *                      caller does not need to preserve the value once
 *                      the function returns.
***************************************************************************/
void evel_pnfRegistration_mac_address_set(EVENT_PNF_REGISTRATION * pnfRegistration, const char * const mac_address)
{
  EVEL_ENTER();

/***************************************************************************/
/* Check preconditions.                                                    */
/***************************************************************************/
  assert(pnfRegistration != NULL);
  assert(pnfRegistration->header.event_domain == EVEL_DOMAIN_PNF_REGISTRATION);
  assert(mac_address != NULL);

  evel_set_option_string(&pnfRegistration->mac_address, mac_address, "MAC Address");
  EVEL_EXIT();
}
/***********************************************************************//**
 * Set the Manufacture Date
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries
 *        to overwrite, just ignoring the update instead.
 *
 * @param pnfRegistration     Pointer to the pnfRegistration
 * @param manufacture_date    The manufacture date to be set. ASCIIZ string.
 *                            The caller does not need to preserve the value
 *                            once the function returns.
***************************************************************************/
void evel_pnfRegistration_manufacture_date_set(EVENT_PNF_REGISTRATION * pnfRegistration, const char * const manufacture_date)
 {
  EVEL_ENTER();

/***************************************************************************/
/* Check preconditions.                                                    */
/***************************************************************************/
  assert(pnfRegistration != NULL);
  assert(pnfRegistration->header.event_domain == EVEL_DOMAIN_PNF_REGISTRATION);
  assert(manufacture_date != NULL);

  evel_set_option_string(&pnfRegistration->manufacture_date, manufacture_date, "Manufacture Date");
  EVEL_EXIT();
}

/***********************************************************************//**
 * Set the Model Number
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries
 *        to overwrite, just ignoring the update instead.
 *
 * @param pnfRegistration     Pointer to the pnfRegistration
 * @param model_number   The model Number to be set. ASCIIZ string. The caller
 *                       does not need to preserve the value once the
 *                       function returns.
***************************************************************************/
void evel_pnfRegistration_model_number_set(EVENT_PNF_REGISTRATION * pnfRegistration, const char * const model_number)
{
  EVEL_ENTER();


/***************************************************************************/
/* Check preconditions.                                                    */
/***************************************************************************/
  assert(pnfRegistration != NULL);
  assert(pnfRegistration->header.event_domain == EVEL_DOMAIN_PNF_REGISTRATION);
  assert(model_number != NULL);

  evel_set_option_string(&pnfRegistration->model_number, model_number, "Model Number");
  EVEL_EXIT();
}

/***********************************************************************//**
 * Set the OAM v4 ipaddress
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries
 *        to overwrite, just ignoring the update instead.
 *
 * @param pnfRegistration     Pointer to the pnfRegistration
 * @param oam_v4_ipaddress    Set the oam IP address. ASCIIZ string.
 *                            The caller does not need
 *                            preserve the value once the function returns.
*************************************************************************/
void evel_pnfRegistration_oam_v4_ipaddress_set(EVENT_PNF_REGISTRATION * pnfRegistration, const char * const oam_v4_ipaddress)
{
  EVEL_ENTER();


/***************************************************************************/
/* Check preconditions.                                                    */
/***************************************************************************/
  assert(pnfRegistration != NULL);
  assert(pnfRegistration->header.event_domain == EVEL_DOMAIN_PNF_REGISTRATION);
  assert(oam_v4_ipaddress != NULL);

  evel_set_option_string(&pnfRegistration->oam_v4_ipaddress, oam_v4_ipaddress, "OAM V4 IP Address");
  EVEL_EXIT();
}

/**********************************************************************//**
 * Set the oam v6 ipaddress
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries
 *        to overwrite, just ignoring the update instead.
 *
 * @param pnfRegistration     Pointer to the pnfRegistration
 * @param oam_v6_ipaddress    Set the oam IP address. ASCIIZ string.
 *                            The caller does not need
 *                            preserve the value once the function returns.
**************************************************************************/
void evel_pnfRegistration_oam_v6_ipaddress_set(EVENT_PNF_REGISTRATION * pnfRegistration, const char * const oam_v6_ipaddress)
{
  EVEL_ENTER();


/***************************************************************************/
/* Check preconditions.                                                    */
/***************************************************************************/
  assert(pnfRegistration != NULL);
  assert(pnfRegistration->header.event_domain == EVEL_DOMAIN_PNF_REGISTRATION);
  assert(oam_v6_ipaddress != NULL);

  evel_set_option_string(&pnfRegistration->oam_v6_ipaddress, oam_v6_ipaddress, "OAM V6 IP Address");
  EVEL_EXIT();
}

/**********************************************************************//**
 * Set the Serial Number
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries
 *        to overwrite, just ignoring the update instead.
 *
 * @param pnfRegistration     Pointer to the pnfRegistration
 * @param serial_number   The serial number to be set. ASCIIZ string.
 *                        The caller does not need to preserve the
 *                        value once the function returns.
**************************************************************************/
void evel_pnfRegistration_serial_number_set(EVENT_PNF_REGISTRATION * pnfRegistration, const char * const serial_number)
{
  EVEL_ENTER();


/***************************************************************************/
/* Check preconditions.                                                    */
/***************************************************************************/
  assert(pnfRegistration != NULL);
  assert(pnfRegistration->header.event_domain == EVEL_DOMAIN_PNF_REGISTRATION);
  assert(serial_number != NULL);

  evel_set_option_string(&pnfRegistration->serial_number, serial_number, "SerialNumber");
  EVEL_EXIT();
}

/***********************************************************************//**
 * Set the Software Version
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries
 *        to overwrite, just ignoring the update instead.
 *
 * @param pnfRegistration     Pointer to the pnfRegistration
 * @param sw_version  The SW Version to be set. ASCIIZ string. The caller does
 *                   not need to preserve the value once the function returns.
****************************************************************************/
void evel_pnfRegistration_sw_version_set(EVENT_PNF_REGISTRATION * pnfRegistration, const char * const sw_version)
{
  EVEL_ENTER();

/***************************************************************************/
/* Check preconditions.                                                    */
/***************************************************************************/
  assert(pnfRegistration != NULL);
  assert(pnfRegistration->header.event_domain == EVEL_DOMAIN_PNF_REGISTRATION);
  assert(sw_version != NULL);

  evel_set_option_string(&pnfRegistration->sw_version, sw_version, "Software Version");
  EVEL_EXIT();
}

/***********************************************************************//**
 * Set the Unit Family
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries
 *        to overwrite, just ignoring the update instead.
 *
 * @param pnfRegistration     Pointer to the pnfRegistration
 * @param unit_family   The unit family to be set. ASCIIZ string. The caller
 *                      does not need to preserve the value once the function
 *                      returns.
***************************************************************************/
void evel_pnfRegistration_unit_family_set(EVENT_PNF_REGISTRATION * pnfRegistration, const char * const unit_family)
{
  EVEL_ENTER();


/***************************************************************************/
/* Check preconditions.                                                    */
/***************************************************************************/
  assert(pnfRegistration != NULL);
  assert(pnfRegistration->header.event_domain == EVEL_DOMAIN_PNF_REGISTRATION);
  assert(unit_family != NULL);

  evel_set_option_string(&pnfRegistration->unit_family, unit_family, "Unit Family");
  EVEL_EXIT();
}

/**********************************************************************//**
 * Set the Unit type
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries
 *        to overwrite, just ignoring the update instead.
 *
 * @param pnfRegistration     Pointer to the pnfRegistration
 * @param unit_type   The unit type to be set. ASCIIZ string. The caller does
 *                   not need to preserve the value once the function returns.
****************************************************************************/
void evel_pnfRegistration_unit_type_set(EVENT_PNF_REGISTRATION * pnfRegistration, const char * const unit_type)
{
  EVEL_ENTER();


/***************************************************************************/
/* Check preconditions.                                                    */
/***************************************************************************/
  assert(pnfRegistration != NULL);
  assert(pnfRegistration->header.event_domain == EVEL_DOMAIN_PNF_REGISTRATION);
  assert(unit_type != NULL);

  evel_set_option_string(&pnfRegistration->unit_type, unit_type, "Unit Type");
  EVEL_EXIT();
}

/***********************************************************************//**
 * Set the Vendor name
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries
 *        to overwrite, just ignoring the update instead.
 *
 * @param pnfRegistration     Pointer to the pnfRegistration
 * @param vendor_name   The vendor name to be set. ASCIIZ string. The
 *                      caller does not need to preserve the value once
 *                      the function returns.
***************************************************************************/
void evel_pnfRegistration_vendor_name_set(EVENT_PNF_REGISTRATION * pnfRegistration, const char * const vendor_name)
{
  EVEL_ENTER();


/***************************************************************************/
/* Check preconditions.                                                    */
/***************************************************************************/
  assert(pnfRegistration != NULL);
  assert(pnfRegistration->header.event_domain == EVEL_DOMAIN_PNF_REGISTRATION);
  assert(vendor_name != NULL);

  evel_set_option_string(&pnfRegistration->vendor_name, vendor_name, "Vendor Name");
  EVEL_EXIT();
}
