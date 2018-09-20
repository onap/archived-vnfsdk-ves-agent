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
 * Implementation of EVEL functions relating to the notification.
 *
 ****************************************************************************/

#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "evel_throttle.h"

/**************************************************************************//**
 * Create a new notification event.
 *
 * @note    The mandatory fields on the notification must be supplied to this
 *          factory function and are immutable once set.  Optional fields have
 *          explicit setter functions, but again values may only be set once
 *          so that the notification has immutable properties.
 *
 * @param event_name  Unique Event Name confirming Domain AsdcModel Description
 * @param event_id    A universal identifier of the event for: troubleshooting correlation, analysis, etc
 * @param interface     The card or port name of the reporting entity.
 *
 * @returns pointer to the newly manufactured ::EVENT_NOTIFICATION.  If the
 *          event is not used it must be released using
 *          ::evel_free_notification
 * @retval  NULL  Failed to create the event.
 *****************************************************************************/
EVENT_NOTIFICATION * evel_new_notification(const char* ev_name,
                                           const char *ev_id,
                                           const char * const changeIdentifier,
                                           const char * const changeType)
{
  EVENT_NOTIFICATION * notification = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(changeIdentifier != NULL);
  assert(changeType != NULL);

  /***************************************************************************/
  /* Allocate the notification.                                              */
  /***************************************************************************/
  notification = malloc(sizeof(EVENT_NOTIFICATION));
  if (notification == NULL)
  {
    log_error_state("Out of memory");
    goto exit_label;
  }
  memset(notification, 0, sizeof(EVENT_NOTIFICATION));
  EVEL_DEBUG("New notification is at %lp", notification);

  /***************************************************************************/
  /* Initialize the header & the notification fields.  Optional string       */
  /* values are uninitialized (NULL).                                        */
  /***************************************************************************/
  evel_init_header_nameid(&notification->header,ev_name,ev_id);
  notification->header.event_domain = EVEL_DOMAIN_NOTIFICATION;
  notification->major_version = EVEL_NOTIFICATION_MAJOR_VERSION;
  notification->minor_version = EVEL_NOTIFICATION_MINOR_VERSION;
  notification->changeIdentifier = strdup(changeIdentifier);
  notification->changeType = strdup(changeType);

  /****** Optional Parameters  ******/
  evel_init_option_state(&notification->new_state);
  evel_init_option_state(&notification->old_state);
  evel_init_option_string(&notification->changeContact);
  evel_init_option_string(&notification->state_interface);
  dlist_initialize(&notification->arrayOfNamedHashMap);
  notification->additional_fields = ht_create();

exit_label:
  EVEL_EXIT();
  return notification;
}

/**************************************************************************//**
 * Free a notification.
 *
 * Free off the notification supplied.  Will free all the contained allocated
 * memory.
 *
 * @note It does not free the notification itself, since that may be part of a
 * larger structure.
 *****************************************************************************/
void evel_free_notification(EVENT_NOTIFICATION * const notification)
{
  HASHTABLE_T *ht;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.  As an internal API we don't allow freeing NULL    */
  /* events as we do on the public API.                                      */
  /***************************************************************************/
  assert(notification != NULL);
  assert(notification->header.event_domain == EVEL_DOMAIN_NOTIFICATION);

  /***************************************************************************/
  /* Free all internal strings then the header itself.                       */
  /***************************************************************************/
  ht = notification->additional_fields;
  if( ht != NULL )
  {
     ht_destroy(ht);
  }

  ht = dlist_pop_last(&notification->arrayOfNamedHashMap);
  while (ht != NULL)
  {
    EVEL_DEBUG("Freeing Notification arrayOfNamedHashMap");
    ht_destroy(ht);
    ht = dlist_pop_last(&notification->arrayOfNamedHashMap);
  }

  evel_free_option_string(&notification->state_interface);
  evel_free_option_string(&notification->changeContact);
  evel_free_header(&notification->header);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Event Type property of the notification.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param notification  Pointer to the ::EVENT_NOTIFICATION.
 * @param type          The Event Type to be set. ASCIIZ string. The caller
 *                      does not need to preserve the value once the function
 *                      returns.
 *****************************************************************************/
void evel_notification_type_set(EVENT_NOTIFICATION * const notification,
                                const char * const type)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions and call evel_header_type_set.                      */
  /***************************************************************************/
  assert(notification != NULL);
  assert(notification->header.event_domain == EVEL_DOMAIN_NOTIFICATION);
  evel_header_type_set(&notification->header, type);

  EVEL_EXIT();
}

void evel_notification_changeContact_set(
                               EVENT_NOTIFICATION * const notification,
                               const char * const changeContact)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions                                                     */
  /***************************************************************************/
  assert(notification != NULL);
  assert(notification->header.event_domain == EVEL_DOMAIN_NOTIFICATION);

  assert(changeContact != NULL);

  evel_set_option_string(&notification->changeContact,
                         changeContact,
                         "Change contact");

  EVEL_EXIT();
}

void evel_notification_state_interface_set(
                               EVENT_NOTIFICATION * const notification,
                               const char * const state_interface)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions                                                     */
  /***************************************************************************/
  assert(notification != NULL);
  assert(notification->header.event_domain == EVEL_DOMAIN_NOTIFICATION);

  assert(state_interface != NULL);

  evel_set_option_string(&notification->state_interface,
                         state_interface,
                         "State Interface");

  EVEL_EXIT();
}

void evel_notification_new_state_set(
                               EVENT_NOTIFICATION * const notification,
                               const EVEL_ENTITY_STATE state)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions                                                     */
  /***************************************************************************/
  assert(notification != NULL);
  assert(notification->header.event_domain == EVEL_DOMAIN_NOTIFICATION);

  assert(state < EVEL_MAX_ENTITY_STATES);
  evel_set_option_state(&notification->new_state, state, "New State"); 

  EVEL_EXIT();
}

void evel_notification_old_state_set(
                               EVENT_NOTIFICATION * const notification,
                               const EVEL_ENTITY_STATE state)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions                                                     */
  /***************************************************************************/
  assert(notification != NULL);
  assert(notification->header.event_domain == EVEL_DOMAIN_NOTIFICATION);

  assert(state < EVEL_MAX_ENTITY_STATES);
  evel_set_option_state(&notification->old_state, state, "Old State"); 

  EVEL_EXIT();
}

/**************************************************************************//**
 * Add an additional field name/value pair to the notification.
 *
 * The name and value are null delimited ASCII strings.  The library takes
 * a copy so the caller does not have to preserve values after the function
 * returns.
 *
 * @param notification  Pointer to the ::EVENT_NOTIFICATION.
 * @param name          ASCIIZ string with the attribute's name.  The caller
 *                      does not need to preserve the value once the function
 *                      returns.
 * @param value         ASCIIZ string with the attribute's value.  The caller
 *                      does not need to preserve the value once the function
 *                      returns.
 *****************************************************************************/
void evel_notification_addl_field_add(EVENT_NOTIFICATION * const notification,
                                      const char * const name,
                                      const char * const value)
{
  char *nam=NULL;
  char *val=NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(notification != NULL);
  assert(notification->header.event_domain == EVEL_DOMAIN_NOTIFICATION);
  assert(name != NULL);
  assert(value != NULL);

  EVEL_DEBUG("Adding name=%s value=%s", name, value);

  nam = strdup(name);
  val = strdup(value);

  ht_insert(notification->additional_fields, nam, val);

  EVEL_EXIT();
}

HASHTABLE_T * evel_notification_add_new_named_hashmap(
                                      EVENT_NOTIFICATION * const notification,
                                      const char * const name)
{
  HASHTABLE_T *ht;
  char *nam=NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(notification != NULL);
  assert(notification->header.event_domain == EVEL_DOMAIN_NOTIFICATION);
  assert(name != NULL);

  EVEL_DEBUG("Adding HashMapName=%s", name);

  nam = strdup(name);

  ht = nht_create( nam );

  if (ht != NULL)
  {
    dlist_push_last(&notification->arrayOfNamedHashMap, ht);
  }

  EVEL_EXIT();

  return ht;
}

void evel_notification_named_hashmap_set(
                                      HASHTABLE_T * const ht,
                                      const char * const name,
                                      const char * const value)
{
  char *nam=NULL;
  char *val=NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(ht != NULL);
  assert(name != NULL);
  assert(value != NULL);

  EVEL_DEBUG("Adding name=%s value=%s", name, value);

  nam = strdup(name);
  val = strdup(value);

  ht_insert(ht, nam, val);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Encode the notification as a JSON notification.
 *
 * @param jbuf          Pointer to the ::EVEL_JSON_BUFFER to encode into.
 * @param notification  Pointer to the ::EVENT_NOTIFICATION to encode.
 *****************************************************************************/
void evel_json_encode_notification(EVEL_JSON_BUFFER * jbuf,
                                   EVENT_NOTIFICATION * notification)
{
  HASHTABLE_T *ht;
  ENTRY_T *entry;
  DLIST_ITEM * dlist_item = NULL;

  char * new_state;
  char * old_state;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(notification != NULL);
  assert(notification->header.event_domain == EVEL_DOMAIN_NOTIFICATION);

  new_state = evel_entity_opt_state(&notification->new_state);
  old_state = evel_entity_opt_state(&notification->old_state);

  evel_json_encode_header(jbuf, &notification->header);
  evel_json_open_named_object(jbuf, "notificationFields");

  /***************************************************************************/
  /* Mandatory fields.                                                       */
  /***************************************************************************/
  evel_enc_kv_string(jbuf, "changeIdentifier", notification->changeIdentifier);
  evel_enc_kv_string(jbuf, "changeType", notification->changeType);

  /***************************************************************************/
  /* Optional fields.                                                        */
  /***************************************************************************/
  if (new_state != NULL)
  {
    evel_enc_kv_string(jbuf, "newState", new_state);
  }
  if (old_state != NULL)
  {
    evel_enc_kv_string(jbuf, "oldState", old_state);
  }
  evel_enc_kv_opt_string(jbuf, "changeContact", &notification->changeContact);
  evel_enc_kv_opt_string(jbuf, "stateInterface", &notification->state_interface);
  evel_json_checkpoint(jbuf);
  ht = notification->additional_fields;
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
            EVEL_DEBUG("Encoding notificationFields %s %s",(char *) (entry->key), entry->value);
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

  /***************************************************************************/
  /* Checkpoint, so that we can wind back if all fields are suppressed.      */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "arrayOfNamedHashMap"))
  {
    bool added_array = false;

    dlist_item = dlist_get_first(&notification->arrayOfNamedHashMap);
    while (dlist_item != NULL)
    {
      bool added = false;
      ht = (HASHTABLE_T *) dlist_item->item;
      assert(ht != NULL);

      if((ht->size > 0) && (ht-> n > 0))
      {
        evel_json_checkpoint(jbuf);
        evel_json_open_object(jbuf);
        evel_enc_kv_string(jbuf, "name", ht->hmName);
        if (evel_json_open_opt_named_object(jbuf, "hashMap"))
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
              EVEL_DEBUG("Encoding NotificationFields %s %s",(char *) (entry->key), entry->value);
              if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                                ht->hmName,
                                                entry->key))
              {
                evel_enc_kv_string(jbuf, entry->key, entry->value);
                added = true;
                added_array = true;
              }
              entry = entry->next;
            }
          }
          evel_json_close_object(jbuf);
          if (!added)
          {
            evel_json_rewind(jbuf);
          }
        }
        evel_json_close_object(jbuf);
      }

      dlist_item = dlist_get_next(dlist_item);
    }

    evel_json_close_list(jbuf);

    if (!added_array)
    {
      evel_json_rewind(jbuf);
    }
  }
  evel_enc_version(jbuf,
                   "notificationFieldsVersion",
                   notification->major_version,notification->minor_version);

  evel_json_close_object(jbuf);

  EVEL_EXIT();
}
