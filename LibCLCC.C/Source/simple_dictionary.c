#include "../Headers/simple_dictionary.h"
#include "stdlib.h"

bool LibCLCC_dictionary_int32_comparator(void *L, void *R)
{
    return *(int32_t *)L == *(int32_t *)R;
}
simple_dict *LibCLCC_CreateSimpleDictionary()
{
    return LibCLCC_CreateSimpleDictionaryWB(DEFAULT_NON_SHRINK_LIST_BLOCK_SIZE);
}
simple_dict *LibCLCC_CreateSimpleDictionaryWB(NON_SHRINK_LIST_INT block_size)
{
    return LibCLCC_CreateSimpleDictionaryWB_WC(block_size, LibCLCC_dictionary_int32_comparator);
}
simple_dict *LibCLCC_CreateSimpleDictionaryWB_WC(NON_SHRINK_LIST_INT block_size,
                                                 LibCLCC_dictionary_comparator comparator)
{
    non_shrink_list *ValueList = LibCLCC_CreateNonShrinkList(block_size);
    if (ValueList == NULL)
    {
        return NULL;
    }
    non_shrink_list *KeyList = LibCLCC_CreateNonShrinkList(block_size);
    if (KeyList == NULL)
    {
        LibCLCC_DestroyNonShrinkList(ValueList);
        return NULL;
    }
    simple_dict *dict = (simple_dict *)malloc(sizeof(simple_dict));
    if (dict == NULL)
    {
        return NULL;
    }
    dict->key = *KeyList;
    dict->value = *ValueList;
    dict->key_comparator = comparator;
    return dict;
}
typedef struct __LibCLCC_simple_dictionary_query_state
{
    simple_dict *dict;
    void *key;
    NON_SHRINK_LIST_INT *innerID;
} __LibCLCC_simple_dictionary_query_state;
static bool QueryList(void *element, void *ptr, NON_SHRINK_LIST_INT id)
{
    __LibCLCC_simple_dictionary_query_state *state = ptr;
    if (state->dict->key_comparator(element, state->key))
    {
        state->innerID[0] = id;
        return true;
    }
    return false;
}
void *LibCLCC_GetValue(simple_dict *dict, void *key)
{
    NON_SHRINK_LIST_INT id = -1;
    __LibCLCC_simple_dictionary_query_state state;
    state.dict = dict;
    state.key = key;
    state.innerID = &id;
    LibCLCC_EnumerateNonShrinkList(&dict->key, QueryList, &state);
    if (id == -1)
    {
        return NULL;
    }
    return dict->value.head[id];
}
bool LibCLCC_RemoveKey(simple_dict *dict, void *key)
{
    NON_SHRINK_LIST_INT id = -1;
    __LibCLCC_simple_dictionary_query_state state;
    state.dict = dict;
    state.key = key;
    state.innerID = &id;
    LibCLCC_EnumerateNonShrinkList(&dict->key, QueryList, &state);
    if (id == -1)
    {
        return false;
    }
    LibCLCC_RemoveElementFromNonShrinkList(&dict->key, id);
    LibCLCC_RemoveElementFromNonShrinkList(&dict->value, id);
    return true;
}
bool LibCLCC_RemoveKeyWD(simple_dict *dict, void *key,
                         LibCLCC_non_shrink_destructor key_destructor,
                         LibCLCC_non_shrink_destructor value_destructor)
{

    NON_SHRINK_LIST_INT id = -1;
    __LibCLCC_simple_dictionary_query_state state;
    state.dict = dict;
    state.key = key;
    state.innerID = &id;
    LibCLCC_EnumerateNonShrinkList(&dict->key, QueryList, &state);
    if (id == -1)
    {
        return false;
    }
    key_destructor(key);
    value_destructor(dict->value.head[id]);
    LibCLCC_RemoveElementFromNonShrinkList(&dict->key, id);
    LibCLCC_RemoveElementFromNonShrinkList(&dict->value, id);
    return true;
}
bool LibCLCC_SetValue(simple_dict *dict, void *key, void *value)
{

    NON_SHRINK_LIST_INT id = -1;
    __LibCLCC_simple_dictionary_query_state state;
    state.dict = dict;
    state.key = key;
    state.innerID = &id;
    LibCLCC_EnumerateNonShrinkList(&dict->key, QueryList, &state);
    if (id == -1)
    {
        LibCLCC_AddElementToNonShrinkList(&dict->key, key);
        LibCLCC_AddElementToNonShrinkList(&dict->value, value);
    }
    else
    {
        dict->value.head[id] = value;
        return true;
    }
    return false;
}
void *LibCLCC_DestorySimpleDictionary(simple_dict *dict)
{
    LibCLCC_DestroyNonShrinkList(&dict->key);
    LibCLCC_DestroyNonShrinkList(&dict->value);
    free(dict);
}
void *LibCLCC_DestorySimpleDictionaryWD(simple_dict *dict,
                                        LibCLCC_non_shrink_destructor key_destructor,
                                        LibCLCC_non_shrink_destructor value_destructor)
{
    LibCLCC_DestroyNonShrinkListWD(&dict->key, key_destructor);
    LibCLCC_DestroyNonShrinkListWD(&dict->value, value_destructor);
    free(dict);
}