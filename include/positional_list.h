/**
 * @brief This positional_list.h file contains the data structures and functions
 * that implement the Positional List ADT with a Doubly Linked List. The Position
 * struct of the list is named "pl_pos" which stands for "Positional List Position" 
 * and the positional list struct that represents the positional list is named "p_list",
 * which stands for "Positional List".
 * 
 * @note This file only contains the interfaces, no implementation.
 * 
 * @authors Pheello James Mokoena
 * @date 17 June 2025
 */

#ifndef _DSA_POSITIONAL_LIST_H
#define _DSA_POSITIONAL_LIST_H

#include <stdlib.h>
#include <stdio.h>


////////////////////// AUXILLIARY STRUCTURES //////////////////////

typedef unsigned int uint;
typedef char* string;

/**
 * Boolean constants.
 */
typedef enum BOOL{
    FALSE = 0,
    TRUE
} BOOL;


////////////////////// END OF AUXILLIARY STRUCTURE //////////////////////


////////////////////// POSITION STRUCTURE //////////////////////

/**
 * @brief A generic positional list "position" or node. This position stores a reference to an
 * object/data of any type through the member variable "data_ptr". The member "next_ptr"
 * stores the address of the next node in the list, whereas member "prev_ptr" stores the
 * address of the previous node in the positional list.
 */
typedef struct pl_pos{

    /// @brief A pointer to the data stored in the node.
    void* data_ptr;

    /// @brief A pointer to the next node in the list.
    struct pl_pos* next_ptr;

    /// @brief A pointer to the previous node in the list.
    struct pl_pos* prev_ptr;

} pl_pos;

////////////////////// END OF POSITION STRUCTURE //////////////////////


////////////////////// POSITIONAL LIST STRUCTURE //////////////////////

/**
 * @brief A generic Positional List implemented with a doubly linked list.
 * @author Pheello James Mokoena
 * @date 17 June 2025
 */
typedef struct p_list{

    /**
     * @brief A sentinel pointer that points to the first node in the list.
     * @note It does not store any data.
     */ 
    pl_pos* header;

    /**
     * @brief A sentinel pointer that points to the last node in the list.
     * @note It does not store any data.
     */ 
    pl_pos* trailer;

    /// @brief Stores the number of elements in the list.
    uint num_elements;

} p_list;

////////////////////// END OF POSITIONAL LIST STRUCTURE //////////////////////


////////////////////// POSITION FUNCTIONS //////////////////////

/**
 * @brief Returns a pointer to the element stored at this position.
 * @param pos The position storing the element to be returned.
 * @return a pointer to the element stored in this position.
 */
void* get_element(pl_pos* pos);

/**
 * @brief Returns a pointer to the position that is immediately after this position.
 * @param pos The position whose next neighbor is to be returned.
 * @return the immediate next neighbor of this position.
 */
pl_pos* get_next(pl_pos* pos);

/**
 * @brief Returns a pointer to the position that is immediately before this position.
 * @param pos The position whose previous neighbor is to be returned.
 * @return the immediate previous neighbor of this position.
 */
pl_pos* get_prev(pl_pos* pos);

////////////////////// END OF POSITION FUNCTIONS //////////////////////


////////////////////// FUNCTION POINTERS //////////////////////

/**
 * @brief Stores a pointer to a function that searches for that element in 
 * in a positional list.
 * @param elem_ptr A pointer to the element to search for.
 * @param list A positional list to be searched for the element.
 * @return the position storing the element or null if the element is not found.
 */
typedef pl_pos* (*ptr_search)(void* elem_ptr, p_list* list);

/**
 * @brief Stores a reference to a function that prints the values stored in a positional
 * list.
 * @param list A positional list whose elements are to be printed.
 */
typedef void (*ptr_print)(p_list* list);

////////////////////// END OF FUNCTION POINTERS //////////////////////


////////////////////// POSITIONAL LIST FUNCTIONS //////////////////////

/**
 * @brief Creates and initializes a positional list.
 * @return the address of the newly created positional list.
 */
p_list* init_p_list();

/**
 * @brief Deallocates the memory that was allocated to this positional list.
 * @param list A positional list.
 * @return a null value indicating that the list is successfully deleted.
 */
p_list* destroy_p_list(p_list* list);

/**
 * @brief Checks if the position is the header sentinel of the list.
 * @param pos The position to be checked.
 * @param list A positional list containing this position.
 * @return true if the position is the header.
 */
BOOL is_header(pl_pos* pos, p_list* list);

/**
 * @brief Checks if the position is the trailer sentinel of the list.
 * @param pos The position to be checked.
 * @param list A positional list containing this position.
 * @return true if the position is the trailer.
 */
BOOL is_trailer(pl_pos* pos, p_list* list);

/**
 * @brief Returns the sentinel header position for the positional list.
 * @param list A positional list.
 * @return the header position.
 */
pl_pos* get_header(p_list* list);

/**
 * @brief Returns the sentinel trailer position for the positional list.
 * @param list A positional list. 
 * @return the trailer position.
 */
pl_pos* get_trailer(p_list* list);


/**
 * @brief Returns the position of the first element in the list, or null is empty.
 * @param list A positional list.
 * @return position of the first element.
 */
pl_pos* first(p_list* list);

/**
 * @brief Returns the position of the last element in the list, or null is empty.
 * @param list A positional list.
 * @return position of the last element.
 */
pl_pos* last(p_list* list);

/**
 * @brief Returns the position of the list immediately before position pos or null
 * if pos is the first position.
 * @param pos The position whose immediate previous neighbor is to be returned.
 * @param list A positional list containing this position.
 * @return the position of the list immediately before position pos
 */
pl_pos* before(pl_pos* pos, p_list* list);

/**
 * @brief Returns the position of the list immediately after position pos or null
 * if pos is the first position.
 * @param pos The position whose immediate next neighbor is to be returned.
 * @param list A positional list containing this position.
 * @return the position of the list immediately after position pos
 */
pl_pos* after(pl_pos* pos, p_list* list);

/**
 * @brief Returns true if the positional list is empty, that is, does not contain any
 * elements.
 * @param list A positional list.
 * @return true if the list is empty, otherwise false.
 */
BOOL is_empty(p_list* list);

/**
 * @brief Returns the number of elements in the positional list.
 * @param list A positional list.
 * @return the number of elements in the positional list.
 */
uint size(p_list* list);

/**
 * @brief Inserts a new element at the front of the list.
 * @param elem_ptr A pointer to the element to be inserted.
 * @param list The list to insert the element into.
 * @return the position of the new element.
 */
pl_pos* add_first(void* elem_ptr,p_list* list);

/**
 * @brief Inserts a new element at the back of the list.
 * @param elem_ptr A pointer to the element to be inserted.
 * @param list The list to insert the element into.
 * @return the position of the new element.
 */
pl_pos* add_last(void* elem_ptr,p_list* list);

/**
 * @brief Inserts a new element e in the list, just before position pos.
 * @param pos A pointer to the position to insert before.
 * @param elem_ptr A pointer to the element to be inserted.
 * @param list The list to insert the element into.
 * @return the position of the new element.
 */
pl_pos* add_before(pl_pos* pos,void* elem_ptr,p_list* list);

/**
 * @brief Inserts a new element e in the list, just after position pos.
 * @param pos A pointer to the position to insert after.
 * @param elem_ptr A pointer to the element to be inserted.
 * @param list The list to insert the element into.
 * @return the position of the new element.
 */
pl_pos* add_after(pl_pos* pos, void* elem_ptr, p_list* list);

/**
 * @brief Replaces the element at position pos with element e.
 * @param pos A pointer to the position whose element is to be replaced.
 * @param elem_ptr A pointer to the new element to be stored in the position.
 * @param list A positional list whose element is to be updated.
 * @return the element formerly stored at position pos.
 */
void* set(pl_pos* pos, void* elem_ptr, p_list* list);

/**
 * @brief Removes and returns the element at position pos in the list, invalidating
 * the position.
 * @param pos A pointer to the position storing the element to be removed.
 * @param list A positional list from which a position is to be removed.
 * @return the element stored in the position.
 */
void* delete(pl_pos* pos, p_list* list);

/**
 * @brief Returns an element that is stored in position pos in the list.
 * @param elem_ptr A pointer to the element to be search for.
 * @param list A position containing this position.
 * @param func A pointer to a function that searches for the element in a
 * positional list.
 * @return the element stored in the position.
 */
void* pl_search(void* elem_ptr, p_list* list, ptr_search func);

/**
 * @brief Prints all the elements of the positional list.
 * @param list a positional list whose elements are to be printed.
 * @param func a pointer to a function that prints the elements stored
 * in the positional list.
 */
void print_p_list(p_list* list, ptr_print func);

////////////////////// END OF POSITIONAL LIST FUNCTIONS //////////////////////


////////////////////// SEARCH FUNCTIONS //////////////////////

/**
 * @brief Searches for the element in a positional list storing strings (char*).
 * @param elem_ptr A pointer to the element to be searched for.
 * @param list A positional list to be searched.
 * @return the position storing the element or null if the element is not found.
 */
pl_pos* str_search(string elem_ptr, p_list* list);

/**
 * @brief Searches for the element in a positional list storing long elements.
 * @param elem_ptr A pointer to the element to be searched for.
 * @param list A positional list to be searched.
 * @return the position storing the element or null if the element is not found.
 */
pl_pos* long_search(long* elem_ptr, p_list* list);

/**
 * @brief Searches for the element in a positional list storing double elements.
 * @param elem_ptr A pointer to the element to be searched for.
 * @param list A positional list to be searched.
 * @return the position storing the element or null if the element is not found.
 */
pl_pos* double_search(double* elem_ptr, p_list* list);

/**
 * @brief Searches for the element in a positional list storing float elements.
 * @param elem_ptr A pointer to the element to be searched for.
 * @param list A positional list to be searched.
 * @return the position storing the element or null if the element is not found.
 */
pl_pos* float_search(float* elem_ptr, p_list* list);

/**
 * @brief Searches for the element in a positional list storing integer elements.
 * @param elem_ptr A pointer to the element to be searched for.
 * @param list A positional list to be searched.
 * @return the position storing the element or null if the element is not found.
 */
pl_pos* int_search(int* elem_ptr, p_list* list);

/**
 * @brief Searches for the element in a positional list storing short elements.
 * @param elem_ptr A pointer to the element to be searched for.
 * @param list A positional list to be searched.
 * @return the position storing the element or null if the element is not found.
 */
pl_pos* short_search(short* elem_ptr, p_list* list);

/**
 * @brief A macro that generalizes searching for an element of the type stored in
 * the positional list.
 * @param list A pointer to a positional list to be searched.
 * @param elem_ptr A pointer to the element to be searched for.
 * @param elem_type The data type of the element to be searched for.
 */
#define PL_SEARCH(list,elem_ptr,elem_type)\
    if(elem_ptr != NULL && list != NULL && is_empty(list) == FALSE){\
        pl_pos* curr = get_header(list)->next_ptr;\
        elem_type targ_elem = *elem_ptr;\
        while(curr != get_trailer(list)){\
            elem_type* elem = (elem_type*) curr->data_ptr;\
            if(*elem == targ_elem)\
                return curr;\
            curr = after(curr,list);\
        }\
        printf("\n");\
    }

////////////////////// END OF SEARCH FUNCTIONS //////////////////////


////////////////////// PRINT FUNCTIONS //////////////////////

/**
 * @brief Prints all the string elements stored in a positional list.
 * @param list A positional list whose string elements are to be printed.
 */
void str_print(p_list* list);

/**
 * @brief Prints all the long elements stored in a positional list.
 * @param list A positional list whose long elements are to be printed.
 */
void long_print(p_list* list);

/**
 * @brief Prints all the integer elements stored in a positional list.
 * @param list A positional list whose integer elements are to be printed.
 */
void int_print(p_list* list);

/**
 * @brief Prints all the short elements stored in a positional list.
 * @param list A positional list whose short elements are to be printed.
 */
void short_print(p_list* list);

/**
 * @brief Prints all the double elements stored in a positional list.
 * @param list A positional list whose double elements are to be printed.
 */
void double_print(p_list* list);

/**
 * @brief Prints all the float elements stored in a positional list.
 * @param list A positional list whose float elements are to be printed.
 */
void float_print(p_list* list);

/**
 * @brief A macro that generalizes the functionality for printing the elements
 * of a positional list.
 * @param list A pointer to a positional list whose elements are to be printed.
 * @param type The data type of the elements stored in the positional list.
 * @param format The format used to print the type of elements stored in the list.
 */
#define PRINT_P_LIST(list,type, format)\
    if(list != NULL && is_empty(list) == FALSE){\
        pl_pos* curr = get_header(list)->next_ptr;\
        while(curr != list->trailer){\
            type* elem = (type*) curr->data_ptr;\
            printf(format,*elem);\
            printf("\n");\
            curr = after(curr,list);\
        } \
    }

////////////////////// END OF PRINT FUNCTIONS //////////////////////

#endif //_DSA_POSITIONAL_LIST_H