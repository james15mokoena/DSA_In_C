#include "../include/general_tree.h"

g_tree* init_gt(){
    g_tree* new_tree = malloc(sizeof(g_tree));
    new_tree->root = NULL;
    new_tree->size = 0;
    return new_tree;
}

gt_pos* init_gt_pos(void* data_ptr){
    
    if(data_ptr != NULL){
        gt_pos* new_pos = malloc(sizeof(gt_pos));
        new_pos->num_children_cap = DEFAULT_NUM_CHILDREN;
        new_pos->data_ptr = data_ptr;
        new_pos->parent = NULL;
        new_pos->next_slot = 0;
        new_pos->children = calloc(new_pos->num_children_cap,sizeof(gt_pos*));
        for(int i=0; i<new_pos->num_children_cap; ++i)
            new_pos->children[i] = NULL;
        return new_pos;
    }
    
    return NULL;
}

gt_pos* expand_gt_pos(gt_pos* pos){
    
    if(pos != NULL && is_internal(pos)){

        if(is_expandable(pos)){

            gt_pos** temp = pos->children;
            pos->children = calloc(pos->num_children_cap * 2,sizeof(gt_pos*));

            // copy the current children into the new array.
            for(int i=0; i<pos->num_children; ++i){
                if(temp[i] != NULL){
                    pos->children[i] = temp[i];
                }
                else
                    pos->children[i] = NULL;
            }

            // update the capacity to the new capacity.
            pos->num_children_cap = pos->num_children_cap * 2;
            
            // deallocate the old array of pointers to the children of this position.
            free(temp);
            temp = NULL;

            return pos;
        }        
    }

    return pos;
}

gt_pos* shrink_gt_pos(gt_pos* pos){

    if(pos != NULL){

        float temp_children = pos->num_children;
        float temp_cap = pos->num_children_cap;
        float loadFactor = temp_children/temp_cap;

        //printf("Shrink load factor: %.2f\n",loadFactor);

        if(loadFactor <= 0.2){

            gt_pos** tmp = pos->children;
            pos->children = calloc(pos->num_children_cap/2,sizeof(gt_pos*));
            
            // copy the addresses of the positions to the new array of pointers.
            for(int i=0; i<pos->num_children; ++i){
                if(tmp[i] != NULL)
                    pos->children[i] = tmp[i];
                else
                    pos->children[i] = NULL;
            }

            // update the capacity
            pos->num_children_cap = pos->num_children_cap/2;
            // free the memory allocated to the old array of pointers.
            free(tmp);
            tmp = NULL;
            return pos;
        }
    }

    return pos;
}

gt_pos* free_gt_pos(gt_pos* pos, g_tree* tree){

    if(pos != NULL && tree != NULL){

        // free the memory occupied by the data.
        free(pos->data_ptr);        
        pos->data_ptr = NULL;

        if(!is_root(pos,tree)){
            // un-link the position from its parent.
            if(unlink_gt_pos_child(pos->parent,pos))
                pos->parent = NULL;
            else
                fprintf(stderr,"%s\n","Failed to unlink the child position from its parent.");
        }
        
        // delete its children.
        if(is_internal(pos)){

            for(int i=0; i<pos->num_children; ++i){
                free(pos->children[i]);
                pos->children[i] = NULL;
            }
        }

        pos->num_children = 0;
        pos->num_children_cap = 0;
        return pos = NULL;
    }

    return NULL;
}

bool is_internal(gt_pos* pos){
    return (pos != NULL && pos->num_children > 0) ? true : false;
}

bool is_external(gt_pos* pos){
    return (pos != NULL && pos->num_children == 0) ? true : false;
}

bool unlink_gt_pos_child(gt_pos* parent, gt_pos* child){

    if(parent != NULL && is_internal(parent) && child != NULL){

        bool is_unlinked = false;
        int index = -1;

        for(int i=0; i<parent->num_children; ++i){
            if(parent->children[i] == child){
                parent->children[i] = NULL;
                --parent->num_children;
                is_unlinked = true;
                index = i;
                break;
            }                
        }

        if(is_unlinked){
            shift_back(parent,index);
        }

        return is_unlinked;
    }

    return false;
}

bool is_root(gt_pos* pos, g_tree* tree){
    return (pos != NULL && tree != NULL && pos == get_root(tree)) ? true : false;
}

gt_pos* get_root(g_tree* tree){
    return (tree != NULL) ? tree->root : NULL;
}

void shift_back(gt_pos* pos, int start_index){
     
    if(pos != NULL && start_index >= 0 && pos->num_children > 0){

        for(int i=start_index; i<pos->num_children_cap; ++i){
            if(pos->children[i] == NULL){
                pos->children[i] = pos->children[i+1];
                pos->children[i+1] = NULL;

                if(pos->children[i] == NULL && pos->children[i+1] == NULL)
                    break;
            }                            
        }
    }
}

gt_pos* get_parent(gt_pos* pos, g_tree* tree){
    return (pos != NULL && tree != NULL && !is_root(pos,tree)) ? pos->parent : NULL;
}

gt_pos** get_children(gt_pos* pos){
    return (pos != NULL && is_internal(pos)) ? pos->children : NULL;
}

int get_num_children(gt_pos* pos){
    return (pos != NULL && is_internal(pos)) ? pos->num_children: 0;
}

bool has_root(g_tree* tree){
    return (tree != NULL && get_root(tree) != NULL) ? true : false;
}

gt_pos* add_root(g_tree* tree, void* data){

    if(tree != NULL && !has_root(tree) && data != NULL){
        tree->root = init_gt_pos(data);
        ++tree->size;
        return tree->root;
    }

    return NULL;
}


gt_pos* add_child(void* data, gt_pos* parent, g_tree* tree){

    if(data != NULL && parent != NULL){

        if(is_expandable(parent)){
            parent = expand_gt_pos(parent);
            gt_pos* new_pos = init_gt_pos(data);
            new_pos->parent = parent;
            if(get_next_slot(parent) >= 0){
                parent->children[get_next_slot(parent)] = new_pos;   // CONTINUE HERE...
            }
        }
    }
}

unsigned int get_size(g_tree* tree){
    return tree != NULL ? tree->size : 0;
}

g_tree* delete_gt(g_tree* tree){
    return NULL;
}

int get_next_slot(gt_pos* pos){
    return (pos != NULL) ? pos->next_slot : -1;
}

bool is_expandable(gt_pos* pos){
    
    if(pos != NULL && is_internal(pos)){

        float num_children = pos->num_children;
        float cap = pos->num_children_cap;
        float loadFactor = num_children/cap;

        return loadFactor >= 0.8;
    }
    
    return false;
}

bool is_empty(g_tree* tree){
    return (tree != NULL && get_size(tree) == 0) ? true : false;
}

bool set_parent(gt_pos* pos, gt_pos* parent){
    if(pos != NULL && parent != NULL){
        pos->parent = parent;
        return true;
    }

    return false;
}