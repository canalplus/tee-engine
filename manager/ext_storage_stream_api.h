/*****************************************************************************
** Copyright (C) 2015 Intel                                                 **
**                                                                          **
** Licensed under the Apache License, Version 2.0 (the "License");          **
** you may not use this file except in compliance with the License.         **
** You may obtain a copy of the License at                                  **
**                                                                          **
**      http://www.apache.org/licenses/LICENSE-2.0                          **
**                                                                          **
** Unless required by applicable law or agreed to in writing, software      **
** distributed under the License is distributed on an "AS IS" BASIS,        **
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. **
** See the License for the specific language governing permissions and      **
** limitations under the License.                                           **
*****************************************************************************/

#ifndef EMULATOR_MANAGER_EXT_STORAGE_BLOB_API_H_
#define EMULATOR_MANAGER_EXT_STORAGE_BLOB_API_H_

#include <stdint.h>
#include "tee_storage_common.h"

/* checks that storage blob is not illegal */
#define IS_VALID_STORAGE_BLOB(a) (a != 0 && a != 0xFFFFFFFF)

/* !brief
 * returns valid storage id on success 0x0 on fail
 */
uint32_t ext_object_id_to_storage_id(char *objectid, size_t objectid_len);

/* !brief
 * returns valid storage id on success 0x0 on fail,
 * should only be called once for object if
 */
uint32_t ext_open_storage_blob(char *objectID, size_t objectIDlen, bool create_if_not_exist);

/* !brief
 * closes valid storage id,
 * should only be called once for object
 */
void ext_close_storage_blob(uint32_t storage_blob_id);


/* !brief
 * closes and deletes valid storage id,
 * should only be called once for object
 */
void ext_delete_storage_blob(uint32_t storage_blob_id, void *objectID, size_t objectIDLen);

/* !brief
 * returns the size of storage id,
 */
size_t ext_get_storage_blob_size(uint32_t storage_blob_id);


/* ! brief atomic operation to change object id of storage blob
 *  storage id remains same for the new object id
 */
bool ext_change_object_ID(uint32_t storage_blob_id,
			  void *objectID, size_t objectIDLen,
			  void *new_objectID, size_t new_objectIDLen);

/* !brief reads datalen amount of bytes from offset of storage_blob return bytes read
 *
 */
uint32_t ext_read_stream(uint32_t storage_blob_id, uint32_t offset, void *data, size_t datalen);

/* !brief writes datalen amount of bytes from offset of storage_blob, returns bytes written
 *
 */
uint32_t ext_write_stream(uint32_t storage_blob_id, uint32_t offset, void *data, size_t datalen);

/* !brief truncates the file, if size grows, added bytes are 0
 *
 */
TEE_Result ext_truncate_storage_blob(uint32_t storage_blob_id, uint32_t size);

/*
 * !brief allocs storage blob enumerator, return true on success and id in uint32_t reference
 */
bool ext_alloc_for_enumerator(uint32_t *ID);

/*
 * !brief frees storage blob enumerator
 */
void ext_free_enumerator(uint32_t free_enum_ID);

/*
 * !brief resets storage blob enumerator
 */
void ext_reset_enumerator(uint32_t reset_enum_ID);

/*
 * !brief starts storage blob enumerator, returns true on success
 */
bool ext_start_enumerator(uint32_t start_enum_ID);

/*
 * !brief gets next storage blob from enumerator,
 * returns true on success, meta data of storage object in reference.
 * recv_data_to_caller must be valid pointer
 */
bool ext_get_next_obj_from_enumeration(uint32_t get_next_ID,
				       struct storage_obj_meta_data *recv_data_to_caller);

#endif /* EMULATOR_MANAGER_EXT_storage_blob_API_H_ */
