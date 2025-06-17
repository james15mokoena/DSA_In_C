#ifndef _DYNAMIC_ARRAYS_H
#define _DYNAMIC_ARRAYS_H

#include <stdlib.h>
#include <string.h>

/**
 * 
 * @brief A generic doubly linked list node.
 * @param alias The name used when declaring variables of this struct type.
 * @param elem_type The type of data to be stored in the struct.
 */
#define CREATE_DLL_STRUCT(alias,elem_type) \
    typedef struct {               \
        elem_type data;                             \
        void* next_node;     \
        void* prev_node;     \
    } alias;                          

typedef struct name{
    char* f_name;
    char* m_name;
    char* l_name;
} name;


/**
 * @brief Allocates space dynamically for an array of "num_elements" of
 * type with the specified size "type_size".
 * @param num_elements The number of elements to be stored in the array.
 * @param type_size The size in bytes that is required to store each element.
 * @return A pointer to the memory allocated.
 */
void* alloc_array(int num_elements, size_t type_size){
    
    void* arr_ptr = calloc(num_elements,type_size);
    return arr_ptr;
}

/**
 * @brief Deallocates the space allocated to the array pointed to by this pointer.
 * @param ptr The pointer whose array is to be deallocated.
 */
void dealloc_array(void* ptr){
    free(ptr);
    ptr = NULL;    
}

/**
 * @brief Inserts the new element pointed to by the pointer.
 * @param idx The index at which to insert the new element.
 * @param arr_ptr A pointer to the array to insert into.
 * @param new_el_ptr A pointer to the new element to be inserted.
 * @param elem_size The size of the object/element in bytes.
 * @return 1 if successfully inserted other 0.
 */
int insert_at(int idx, void* arr_ptr , void* new_el_ptr, size_t elem_size){

    if(memcpy((char*)arr_ptr + (idx * elem_size), new_el_ptr, elem_size) != NULL)
        return 1;
    
    return 0;
}

/**
 * @brief Prints the elements of the array pointed to by the pointer.
 * @param arr_ptr A pointer to the array.
 * @param len The number of elements in the array to print.
 */
void print_array(void* arr_ptr, int len){

    for(int i=0; i<len; ++i)
        printf("%c",((char*) arr_ptr)[i]);
}

#endif //_DYNAMIC_ARRAYS_H