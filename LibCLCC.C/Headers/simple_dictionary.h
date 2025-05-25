#ifndef __LIBCLCC_SIMPLE_DICTIONARY__
#define __LIBCLCC_SIMPLE_DICTIONARY__

#include "non_shrink_list.h"

/// @brief First void* is the
typedef bool (*LibCLCC_dictionary_comparator)(void *, void *);

typedef struct simple_dict
{
    non_shrink_list key;
    non_shrink_list value;
    LibCLCC_dictionary_comparator key_comparator;
} simple_dict;

simple_dict *LibCLCC_CreateSimpleDictionary();
simple_dict *LibCLCC_CreateSimpleDictionaryWB(NON_SHRINK_LIST_INT block_size);
simple_dict *LibCLCC_CreateSimpleDictionaryWB_WC(NON_SHRINK_LIST_INT block_size,
                                                 LibCLCC_dictionary_comparator comparator);
bool LibCLCC_dictionary_int32_comparator(void *L, void *R);
void *LibCLCC_GetValue(simple_dict *dict, void *key);
bool LibCLCC_RemoveKey(simple_dict *dict, void *key);
bool LibCLCC_RemoveKeyWD(simple_dict *dict, void *key,
                         LibCLCC_non_shrink_destructor key_destructor,
                         LibCLCC_non_shrink_destructor value_destructor);
bool LibCLCC_SetValue(simple_dict *dict, void *key, void *value);
void LibCLCC_DestorySimpleDictionary(simple_dict *dict);
void LibCLCC_DestorySimpleDictionaryWD(simple_dict *dict,
                                        LibCLCC_non_shrink_destructor key_destructor,
                                        LibCLCC_non_shrink_destructor value_destructor);

#endif