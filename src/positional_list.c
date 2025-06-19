/**
 * @brief This positional_list.c file contains the implementations of the
 * functions that access and manipulate the "pl_pos" and "p_list" structs.
 * 
 * @author Pheello James Mokoena
 * @date 17 June 2025
 */


#include "../include/positional_list.h"

////////////////////// POSITION FUNCTIONS //////////////////////

void* get_element(pl_pos* pos){    
    return pos->data_ptr;
}

pl_pos* get_next(pl_pos* pos){
    return pos->next_ptr;
}

pl_pos* get_prev(pl_pos* pos){
    return pos->prev_ptr;
}

////////////////////// END OF POSITION FUNCTIONS //////////////////////


////////////////////// POSITIONAL LIST FUNCTIONS //////////////////////

p_list* init_p_list(){
    
    // allocate space for this positional list.
    p_list* list = malloc(sizeof(p_list));
    list->header = malloc(sizeof(pl_pos));    
    list->trailer = malloc(sizeof(pl_pos));

    // initialize the header position.    
    (list->header)->data_ptr = NULL;
    (list->header)->next_ptr = list->trailer;     // points to the trailer
    (list->header)->prev_ptr = NULL;    
    
    // initialize the trailer position.    
    (list->trailer)->data_ptr = NULL;
    (list->trailer)->prev_ptr = list->header;     // points to the header.
    (list->trailer)->next_ptr = NULL;    

    // initialize the number of elements in the list.
    list->num_elements = 0;

    // check if enough space is allocated before returning the list.
    if(list != NULL && list->header != NULL && list->trailer != NULL)
        return list;

    return NULL;
}

p_list* destroy_p_list(p_list* list){

    if(list != NULL && is_empty(list) == FALSE){

        // get the first position in the list.
        pl_pos* curr_pos = get_header(list)->next_ptr;

        pl_pos* next_pos = NULL;

        while(curr_pos != NULL){

            // move the next position
            next_pos = after(curr_pos,list);

            // delete this position
            delete(curr_pos,list);

            // update curr_pos to reference the next position
            curr_pos = next_pos;
        }

        // delete the header sentinel
        free(list->header);
        // delete the trailer sentinel
        free(list->trailer);
        list->header = list->trailer = NULL;
        list->num_elements = 0;
        // delete the list
        free(list);
        list = NULL;                
    }

    return NULL;
}

BOOL is_header(pl_pos* pos, p_list* list){
    if(pos != NULL && list != NULL && list->header == pos)
        return TRUE;

    return FALSE;
}

BOOL is_trailer(pl_pos* pos, p_list* list){
    if(pos != NULL && list != NULL && list->trailer == pos)
        return TRUE;

    return FALSE;
}

pl_pos* get_header(p_list* list){
    return list != NULL ? list->header : NULL;
}

pl_pos* get_trailer(p_list* list){
    return list != NULL ? list->trailer : NULL;
}

pl_pos* first(p_list* list){
        
    if(is_empty(list) == FALSE)
        return (list->header)->next_ptr;
    
    return NULL;
}

pl_pos* last(p_list* list){

    if(is_empty(list) == FALSE)
        return (list->trailer)->prev_ptr;

    return NULL;
}

pl_pos* before(pl_pos* pos, p_list* list){
    
    if(pos != NULL && list != NULL && is_header(pos,list) == FALSE)
        return pos->prev_ptr;

    return NULL;
}

pl_pos* after(pl_pos* pos, p_list* list){

    if(pos != NULL && list != NULL && is_trailer(pos,list) == FALSE)
        return pos->next_ptr;

    return NULL;
}

BOOL is_empty(p_list* list){
    return (list != NULL && (list->num_elements) > 0) ? FALSE : TRUE;
}

uint size(p_list* list){    
    return (list != NULL) ? list->num_elements : 0;
}

pl_pos* add_first(void* elem_ptr,p_list* list){
    
    if(elem_ptr != NULL && list != NULL){

        // create a new position
        pl_pos* new_pos = malloc(sizeof(pl_pos));        
        pl_pos* header = get_header(list);
        
        // check if memory is allocated
        if(new_pos != NULL){

            // get the current position that the header is pointing to.
            pl_pos* next_pos = header->next_ptr;            
            new_pos->data_ptr = elem_ptr;
            new_pos->next_ptr = next_pos;
            new_pos->prev_ptr = header;
            next_pos->prev_ptr = new_pos;
            header->next_ptr = new_pos;            
            ++(list->num_elements);
            return new_pos;
        }                    
    }
    
    return NULL;
}

pl_pos* add_last(void* elem_ptr, p_list* list){

    if(elem_ptr != NULL && list != NULL){

        pl_pos* trailer = get_trailer(list);
        pl_pos* new_pos = malloc(sizeof(pl_pos));

        if(new_pos != NULL){

            // get the current last position.
            pl_pos* prev_pos = trailer->prev_ptr;
            new_pos->data_ptr = elem_ptr;
            new_pos->next_ptr = trailer;
            new_pos->prev_ptr = prev_pos;
            prev_pos->next_ptr = new_pos;
            trailer->prev_ptr = new_pos;
            ++(list->num_elements);
            return new_pos;
        }
    }

    return NULL;
}

pl_pos* add_before(pl_pos* pos,void* elem_ptr,p_list* list){

    if(pos != NULL && elem_ptr != NULL && list != NULL && is_header(pos,list) == FALSE){

        pl_pos* new_pos = malloc(sizeof(pl_pos));
        // get the position before this one.
        pl_pos* prev_pos = before(pos,list);

        new_pos->data_ptr = elem_ptr;
        new_pos->next_ptr = pos;
        new_pos->prev_ptr = prev_pos;
        prev_pos->next_ptr = new_pos;
        pos->prev_ptr = new_pos;
        ++(list->num_elements);
        return new_pos;
    }
    else if(is_header(pos,list) == TRUE)
        fprintf(stderr,"%s\n","Cannot add before the header position, use \"add_first(e,list)\" instead.");

    return NULL;
}

pl_pos* add_after(pl_pos* pos,void* elem_ptr,p_list* list){

    if(pos != NULL && elem_ptr != NULL && list != NULL && is_trailer(pos,list) == FALSE){

        pl_pos* new_pos = malloc(sizeof(pl_pos));
        // get the position after this one.
        pl_pos* next_pos = after(pos,list);

        new_pos->data_ptr = elem_ptr;
        new_pos->prev_ptr = pos;
        new_pos->next_ptr = next_pos;
        next_pos->prev_ptr = new_pos;
        pos->next_ptr = new_pos;
        ++(list->num_elements);
        return new_pos;
    }
    else if(is_trailer(pos,list) == TRUE)
        fprintf(stderr,"%s\n","Cannot add after the trailer position, use \"add_last(e,list)\" instead.");

    return NULL;
}

void* set(pl_pos* pos, void* elem_ptr, p_list* list){
    
    if(pos != NULL && list != NULL && is_header(pos,list) == FALSE && is_trailer(pos,list) == FALSE){

        void* old_elem = pos->data_ptr;
        pos->data_ptr = elem_ptr;
        return old_elem;
    }

    return NULL;
}

void* delete(pl_pos* pos, p_list* list){
    
    if(pos != NULL && list != NULL && is_header(pos,list) == FALSE && is_trailer(pos,list) == FALSE){

        // get its previous neighbor
        pl_pos* prev_pos = before(pos,list);        
        // get its next neighbor
        pl_pos* next_pos = after(pos,list);

        prev_pos->next_ptr = next_pos;
        next_pos->prev_ptr = prev_pos;
        pos->next_ptr = NULL;
        pos->prev_ptr = NULL;        
        void* elem_ptr = pos->data_ptr;
        // deallocate the memory allocated to this position.
        pos->data_ptr = NULL;        
        free(pos);
        --(list->num_elements);
        return elem_ptr;
    }
    else if((is_header(pos,list) == TRUE || is_trailer(pos,list) == TRUE) && is_empty(list) == TRUE)
        destroy_p_list(list);
    else if(is_header(pos,list) == TRUE || is_trailer(pos,list) == TRUE)
        fprintf(stderr,"%s\n","Cannot delete a header or trailer position when the list is not empty.");

    return NULL;
}

void* pl_search(void* elem_ptr, p_list* list, ptr_search func){

    if(elem_ptr != NULL && list != NULL && is_empty(list) == FALSE)
        return func(elem_ptr, list);

    return NULL;
}

void print_p_list(p_list* list, ptr_print func){

    if(list != NULL && is_empty(list) == FALSE && func != NULL)
        func(list);
}

////////////////////// END OF POSITIONAL LIST FUNCTIONS //////////////////////


////////////////////// SEARCH FUNCTIONS //////////////////////

pl_pos* str_search(string elem_ptr, p_list* list){

    if(elem_ptr != NULL && list != NULL && is_empty(list) == FALSE){

        // get the first position in the list.
        pl_pos* curr = get_header(list)->next_ptr;
        
        // search until at most we reach the trailer position.
        while(curr != get_trailer(list)){

            string elem = (string) curr->data_ptr;            
            if(elem == elem_ptr)
                return curr;

            curr = after(curr,list);
        }

        printf("\n");
    }

    return NULL;
}

pl_pos* long_search(long* elem_ptr, p_list* list){

    PL_SEARCH(list,elem_ptr,long)

    return NULL;
}

pl_pos* double_search(double* elem_ptr, p_list* list){

    PL_SEARCH(list,elem_ptr,double);

    return NULL;
}

pl_pos* float_search(float* elem_ptr, p_list* list){

    PL_SEARCH(list,elem_ptr,float);

    return NULL;
}

pl_pos* int_search(int* elem_ptr, p_list* list){

    PL_SEARCH(list,elem_ptr,int);

    return NULL;
}

pl_pos* short_search(short* elem_ptr, p_list* list){

    PL_SEARCH(list,elem_ptr,int);

    return NULL;
}

////////////////////// END OF SEARCH FUNCTIONS //////////////////////


////////////////////// PRINT FUNCTIONS //////////////////////

void str_print(p_list* list){
    
    if(list != NULL && is_empty(list) == FALSE){

        // get the first position in the list.
        pl_pos* curr = get_header(list)->next_ptr;
        
        // search until at most we reach the trailer position.
        while(curr != get_trailer(list)){

            string elem = (string) curr->data_ptr;
            printf("%s\n",elem);        
            curr = after(curr,list);
        }

        printf("\n");
    }
}

void long_print(p_list* list){

    PRINT_P_LIST(list,long,"%ld")
}

void int_print(p_list* list){

    PRINT_P_LIST(list,int,"%d")
}

void short_print(p_list* list){

    PRINT_P_LIST(list,short,"%hd")
}

void double_print(p_list* list){

    PRINT_P_LIST(list,double,"%.2f")
}

void float_print(p_list* list){

    PRINT_P_LIST(list,float,"%.2f")
}

////////////////////// END OF PRINT FUNCTIONS //////////////////////