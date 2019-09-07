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
 * Implementation of EVEL functions relating to Other domain.
 *
 *****************************************************************************/

#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "evel.h"
#include "evel_internal.h"
#include "evel_throttle.h"

/**************************************************************************//**
 * Create a new Other event.
 *
 * @note    The mandatory fields on the Other must be supplied to this factory
 *          function and are immutable once set.  Optional fields have explicit
 *          setter functions, but again values may only be set once so that the
 *          Other has immutable properties.
 * @returns pointer to the newly manufactured ::EVENT_OTHER.  If the event is
 *          not used (i.e. posted) it must be released using ::evel_free_other.
 * @retval  NULL  Failed to create the event.
 *****************************************************************************/
EVENT_OTHER * evel_new_other(const char* ev_name, const char *ev_id)
{
  EVENT_OTHER * other = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/

  /***************************************************************************/
  /* Allocate the Other.                                                     */
  /***************************************************************************/
  other = malloc(sizeof(EVENT_OTHER));
  if (other == NULL)
  {
    log_error_state("Out of memory");
    goto exit_label;
  }
  memset(other, 0, sizeof(EVENT_OTHER));
  EVEL_DEBUG("New Other is at %lp", other);

  /***************************************************************************/
  /* Initialize the header & the Other fields.  Optional string values are   */
  /* uninitialized (NULL).                                                   */
  /***************************************************************************/
  evel_init_header_nameid(&other->header,ev_name,ev_id);
  other->header.event_domain = EVEL_DOMAIN_OTHER;
  other->major_version = EVEL_OTHER_EVENT_MAJOR_VERSION;
  other->minor_version = EVEL_OTHER_EVENT_MINOR_VERSION;

  other->hashMap = ht_create();
  dlist_initialize(&other->jsonobjects);
  dlist_initialize(&other->arrayOfNamedHashMap);

exit_label:
  EVEL_EXIT();
  return other;
}

/**************************************************************************//**
 * Set the Event Type property of the Other.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param other       Pointer to the Other.
 * @param type        The Event Type to be set. ASCIIZ string. The caller
 *                    does not need to preserve the value once the function
 *                    returns.
 *****************************************************************************/
void evel_other_type_set(EVENT_OTHER * other,
                         const char * const type)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions and call evel_header_type_set.                      */
  /***************************************************************************/
  assert(other != NULL);
  assert(other->header.event_domain == EVEL_DOMAIN_OTHER);
  evel_header_type_set(&other->header, type);

  EVEL_EXIT();
}


/**************************************************************************//**
 * Add a json object to jsonObject list.
 *
 * The name and value are null delimited ASCII strings.  The library takes
 * a copy so the caller does not have to preserve values after the function
 * returns.
 *
 * @param other         Pointer to the Other.
 * @param size          size of hashtable
 *****************************************************************************/
void evel_other_field_add_hashmap(EVENT_OTHER * other, char * name, char *value)
{
  char *nam=NULL;
  char *val=NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(other != NULL);
  assert(other->header.event_domain == EVEL_DOMAIN_OTHER);

  assert(name != NULL);
  assert(value != NULL);

  EVEL_DEBUG("Adding values to hashMap");
      
  EVEL_DEBUG("Adding name=%s value=%s", name, value);

  nam = strdup(name);
  val = strdup(value);

  ht_insert(other->hashMap, nam, val);

  EVEL_EXIT();
}

HASHTABLE_T * evel_other_add_new_hashmap_to_hmarray(EVENT_OTHER * const other,
                                                    const char * const name)
{
  HASHTABLE_T *ht;
  char *nam=NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(other != NULL);
  assert(other->header.event_domain == EVEL_DOMAIN_OTHER);
  assert(name != NULL);

  nam = strdup(name);
  EVEL_DEBUG("Adding HashMap to array of hashmap - %s", nam);

  ht = nht_create(nam);

  if (ht != NULL)
  {
    dlist_push_last(&other->arrayOfNamedHashMap, ht);
  }

  EVEL_EXIT();

  return ht;
}

/**************************************************************************//**
 * Add a field name/value pair to the Other.
 *
 * The name and value are null delimited ASCII strings.  The library takes
 * a copy so the caller does not have to preserve values after the function
 * returns.
 *
 * @param ht        Pointer to the hasmap array.
 * @param name      ASCIIZ string with the field's name.  The caller does not
 *                  need to preserve the value once the function returns.
 * @param value     ASCIIZ string with the field's value.  The caller does not
 *                  need to preserve the value once the function returns.
 *****************************************************************************/
void evel_other_set_hashmap_in_hmarray(
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

  EVEL_DEBUG("Adding name=%s value=%s", name, value);

  nam = strdup(name);
  val = strdup(value);

  ht_insert(ht, nam, val);

  EVEL_EXIT();
}
/**************************************************************************//**
 * Add a json object to jsonObject list.
 *
 * The name and value are null delimited ASCII strings.  The library takes
 * a copy so the caller does not have to preserve values after the function
 * returns.
 *
 * @param other     Pointer to the Other.
 * @param jsonobj   Pointer to json object
 *****************************************************************************/
void evel_other_field_add_jsonobj(EVENT_OTHER * other, EVEL_JSON_OBJECT *jsonobj)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(other != NULL);
  assert(other->header.event_domain == EVEL_DOMAIN_OTHER);
  assert(jsonobj != NULL);

  EVEL_DEBUG("Adding jsonObject");

  dlist_push_last(&other->jsonobjects, jsonobj);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Encode the Other in JSON according to AT&T's schema for the event type.
 *
 * @param jbuf          Pointer to the ::EVEL_JSON_BUFFER to encode into.
 * @param event         Pointer to the ::EVENT_HEADER to encode.
 *****************************************************************************/
void evel_json_encode_other(EVEL_JSON_BUFFER * jbuf,
                            EVENT_OTHER * event)
{
  EVEL_JSON_OBJECT * jsonobjp = NULL;
  DLIST_ITEM * other_field_item = NULL;
  EVEL_JSON_OBJECT_INSTANCE * jsonobjinst = NULL;
  DLIST_ITEM * jsobj_field_item = NULL;
  EVEL_INTERNAL_KEY * keyinst = NULL;
  DLIST_ITEM * keyinst_field_item = NULL;
  HASHTABLE_T *ht = NULL;
  ENTRY_T *entry = NULL;
  DLIST_ITEM *dlist_item;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(event != NULL);
  assert(event->header.event_domain == EVEL_DOMAIN_OTHER);

  evel_json_encode_header(jbuf, &event->header);
  evel_json_open_named_object(jbuf, "otherFields");

  evel_json_checkpoint(jbuf);
  ht = event->hashMap;
  if( ht != NULL )
  {
    bool added = false;
    if( ht->size > 0)
    {
      evel_json_checkpoint(jbuf);
      if (evel_json_open_opt_named_object(jbuf, "hashMap"))
      {
        unsigned int idx = 0;
        for(; idx < ht->size; idx++ )
        {
          /*****************************************************************/
          /* Get the first entry of a particular Key and loop through the  */
          /* remaining if any. Then proceed to next key.                   */
          /*****************************************************************/
          entry =  ht->table[idx];
          while( entry != NULL && entry->key != NULL)
          {
            EVEL_DEBUG("Encoding Other Fields %s %s",(char *) (entry->key), entry->value);
            if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                              "hashMap",
                                              entry->key))
            {

             // evel_json_open_object(jbuf);
              evel_enc_kv_string(jbuf, entry->key, entry->value);
             // evel_json_close_object(jbuf);
              added = true;
            }
            entry = entry->next;
          }
        }
        evel_json_close_object(jbuf);
      }
    }

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!added)
    {
      evel_json_rewind(jbuf);
    }
  }

  evel_json_checkpoint(jbuf);
  if(evel_json_open_opt_named_list(jbuf, "jsonObjects"))
  {
  bool item_added = false;
  other_field_item = dlist_get_first(&event->jsonobjects);
  while (other_field_item != NULL)
  {
    jsonobjp = (EVEL_JSON_OBJECT *) other_field_item->item;
    if(jsonobjp != NULL)  //;
    {
     evel_json_open_object(jbuf);

       if( evel_json_open_opt_named_list(jbuf, "objectInstances"))
       {
	bool item_added2 = false;
        jsobj_field_item = dlist_get_first(&jsonobjp->jsonobjectinstances);
	while (jsobj_field_item != NULL)
	{
	   jsonobjinst = (EVEL_JSON_OBJECT_INSTANCE *) jsobj_field_item->item;
	   if( jsonobjinst != NULL )
	   {
              evel_json_open_object(jbuf);
              evel_enc_kv_object(jbuf, "objectInstance", jsonobjinst->jsonstring);
              evel_enc_kv_opt_ull(jbuf, "objectInstanceEpochMicrosec", &jsonobjinst->objinst_epoch_microsec);
  //evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "objectKeys"))
  {
//    bool item_added3 = false;

    keyinst_field_item = dlist_get_first(&jsonobjinst->object_keys);
    while (keyinst_field_item != NULL)
    {
      keyinst = (EVEL_INTERNAL_KEY *)keyinst_field_item->item;
      if(keyinst != NULL)
      {
        evel_json_open_object(jbuf);
        evel_enc_kv_string(jbuf, "keyName", keyinst->keyname);
        evel_enc_kv_opt_int(jbuf, "keyOrder", &keyinst->keyorder);
        evel_enc_kv_opt_string(jbuf, "keyValue", &keyinst->keyvalue);
        evel_json_close_object(jbuf);
//	item_added3 = false;
      }
      keyinst_field_item = dlist_get_next(keyinst_field_item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    //if (!item_added3)
    //{
    //  evel_json_rewind(jbuf);
    //}
  }
	       evel_json_close_object(jbuf);
	    }
	    item_added2 = true;
            jsobj_field_item = dlist_get_next(jsobj_field_item);
	}
        evel_json_close_list(jbuf);
	if( !item_added2 )
	{
	  evel_json_rewind(jbuf);
	}
       }

    evel_enc_kv_string(jbuf, "objectName", jsonobjp->object_name);
    evel_enc_kv_opt_string(jbuf, "objectSchema", &jsonobjp->objectschema);
    evel_enc_kv_opt_string(jbuf, "objectSchemaUrl", &jsonobjp->objectschemaurl);
    evel_enc_kv_opt_string(jbuf, "nfSubscribedObjectName", &jsonobjp->nfsubscribedobjname);
    evel_enc_kv_opt_string(jbuf, "nfSubscriptionId", &jsonobjp->nfsubscriptionid);
    evel_json_close_object(jbuf);
    item_added = true;
  }
  other_field_item = dlist_get_next(other_field_item);
  }
  evel_json_close_list(jbuf);

  if (!item_added)
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

    dlist_item = dlist_get_first(&event->arrayOfNamedHashMap);
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
          unsigned int idx = 0;
          for(; idx < ht->size; idx++ )
          {
            /*****************************************************************/
            /* Get the first entry of a particular Key and loop through the  */
            /* remaining if any. Then proceed to next key.                   */
            /*****************************************************************/
            entry =  ht->table[idx];
            while( entry != NULL && entry->key != NULL)
            {
              EVEL_DEBUG("Encoding OtherFields %s %s",(char *) (entry->key), entry->value);
              if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                               "arrayOfNamedHashMap",
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

  evel_enc_version(jbuf, "otherFieldsVersion", event->major_version,event->minor_version);

  evel_json_close_object(jbuf);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Free an Other.
 *
 * Free off the Other supplied.  Will free all the contained allocated memory.
 *
 * @note It does not free the Other itself, since that may be part of a
 * larger structure.
 *****************************************************************************/
void evel_free_other(EVENT_OTHER * event)
{
  HASHTABLE_T *ht;
  EVEL_JSON_OBJECT * jsonobjp = NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.  As an internal API we don't allow freeing NULL    */
  /* events as we do on the public API.                                      */
  /***************************************************************************/
  assert(event != NULL);
  assert(event->header.event_domain == EVEL_DOMAIN_OTHER);

  /***************************************************************************/
  /* Free all internal strings then the header itself.                       */
  /***************************************************************************/
  ht = event->hashMap;
  if( ht != NULL )
  {
     ht_destroy(ht);
  }
 
  ht = dlist_pop_last(&event->arrayOfNamedHashMap);
  while (ht != NULL)
  {
    EVEL_DEBUG("Freeing Other arrayOfNamedHashMap");
    ht_destroy(ht);
    ht = dlist_pop_last(&event->arrayOfNamedHashMap);
  }
 
  jsonobjp = dlist_pop_last(&event->jsonobjects);
  while (jsonobjp != NULL)
  {
    evel_free_jsonobject( jsonobjp );

    jsonobjp = dlist_pop_last(&event->jsonobjects);
  }

  evel_free_header(&event->header);

  EVEL_EXIT();
}
