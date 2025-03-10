/* Copyright JS Foundation and other contributors, http://js.foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ECMA_ARRAY_OBJECT_H
#define ECMA_ARRAY_OBJECT_H

#include "ecma-globals.h"

/** \addtogroup ecma ECMA
 * @{
 *
 * \addtogroup ecmaarrayobject ECMA Array object related routines
 * @{
 */

/**
 * Maximum number of new array holes in a fast mode access array.
 * If the number of new holes exceeds this limit, the array is converted back
 * to normal property list based array.
 */
#define ECMA_FAST_ARRAY_MAX_NEW_HOLES_COUNT 32

/**
 * Bitshift index for fast array hole count representation
 */
#define ECMA_FAST_ARRAY_HOLE_SHIFT 8

/**
 * This number represents 1 array hole in underlying buffer of a fast acces mode array
 */
#define ECMA_FAST_ARRAY_HOLE_ONE (1 << ECMA_FAST_ARRAY_HOLE_SHIFT)

/**
 * Maximum number of array holes in a fast access mode array
 */
#define ECMA_FAST_ARRAY_MAX_HOLE_COUNT (1 << 24)

/**
 * Flags for ecma_op_array_object_set_length
 */
typedef enum
{
  ECMA_ARRAY_OBJECT_SET_LENGTH_FLAG_IS_THROW = 1u << 0, /**< is_throw flag is set */
  ECMA_ARRAY_OBJECT_SET_LENGTH_FLAG_REJECT = 1u << 1, /**< reject later because the descriptor flags
                                                       *   contains an unallowed combination */
  ECMA_ARRAY_OBJECT_SET_LENGTH_FLAG_WRITABLE_DEFINED = 1u << 2, /**< writable flag defined
                                                                 *   in the property descriptor */
  ECMA_ARRAY_OBJECT_SET_LENGTH_FLAG_WRITABLE = 1u << 3, /**< writable flag enabled
                                                         *   in the property descriptor */
} ecma_array_object_set_length_flags_t;

ecma_object_t *
ecma_op_new_array_object (uint32_t length);

ecma_object_t *
ecma_op_new_fast_array_object (uint32_t length);

bool
ecma_op_object_is_fast_array (ecma_object_t *object_p);

bool
ecma_op_array_is_fast_array (ecma_extended_object_t *array_p);

uint32_t
ecma_fast_array_get_hole_count (ecma_object_t *obj_p);

ecma_value_t *
ecma_fast_array_extend (ecma_object_t *object_p, uint32_t new_lengt);

bool
ecma_fast_array_set_property (ecma_object_t *object_p, uint32_t index, ecma_value_t value);

void
ecma_array_object_delete_property (ecma_object_t *object_p, ecma_string_t *property_name_p,
                                   ecma_property_value_t *prop_value_p);

uint32_t
ecma_delete_fast_array_properties (ecma_object_t *object_p, uint32_t new_length);

ecma_collection_t *
ecma_fast_array_get_property_names (ecma_object_t *object_p, uint32_t opts);

void
ecma_fast_array_convert_to_normal (ecma_object_t *object_p);

ecma_value_t
ecma_op_create_array_object (const ecma_value_t *arguments_list_p, uint32_t arguments_list_len,
                             bool is_treat_single_arg_as_length);

#if ENABLED (JERRY_ESNEXT)
ecma_value_t
ecma_op_array_species_create (ecma_object_t *original_array_p,
                              uint32_t length);

ecma_value_t
ecma_op_create_array_iterator (ecma_object_t *obj_p,
                               ecma_array_iterator_type_t type);
#endif /* ENABLED (JERRY_ESNEXT) */

ecma_value_t
ecma_op_array_object_set_length (ecma_object_t *object_p, ecma_value_t new_value, uint32_t flags);

ecma_value_t
ecma_op_array_object_define_own_property (ecma_object_t *object_p, ecma_string_t *property_name_p,
                                          const ecma_property_descriptor_t *property_desc_p);

uint32_t ecma_array_get_length (ecma_object_t *array_p);

void
ecma_op_array_list_lazy_property_names (ecma_object_t *obj_p,
                                        uint32_t opts,
                                        ecma_collection_t *main_collection_p,
                                        ecma_collection_t *non_enum_collection_p);

/**
 * @}
 * @}
 */

#endif /* !ECMA_ARRAY_OBJECT_H */
