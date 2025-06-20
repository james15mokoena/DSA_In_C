/**
 * @brief This general_tree.h file contains the structures and interfaces
 * for implementing a general tree, whose nodes can have as many children
 * as necessary and does not enforce any rules for insertion or deletion
 * of elements. When a position is removed all its children are removed with
 * it, the same way the contents of a folder get deleted when the folder is
 * deleted in the file system.
 * 
 * @author Pheello James Mokoena
 * @date 19 June 2025
 * 
 */

#ifndef _DSA_GENERAL_TREE_H
#define _DSA_GENERAL_TREE_H


#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define DEFAULT_NUM_CHILDREN 5


/**
 * @brief A position of a general tree, that can have many children and only
 * one parent position.
 */
typedef struct gt_pos{

    /// @brief A pointer to the data that is stored in this position.
    void* data_ptr;

    /// @brief A pointer to a general tree position that is the parent of this position.
    struct gt_pos* parent;

    /// @brief An array of pointers to general tree positions that are children of this position.
    struct gt_pos** children;

    /// @brief The number of children of this position.
    unsigned int num_children;

    /**
     * @brief The maximum number of children that this current array of pointers to the children of this
     * can stored.
     * */
    unsigned int num_children_cap;
    
    /// @brief Stores the next available slot to store a pointer to a child of this position.
    unsigned int next_slot;

} gt_pos;


/**
 * @brief A general tree ADT, implemented as a linked data structure.
 */
typedef struct g_tree{
    
    /// @brief The root position of the tree.
    struct gt_pos* root;

    /// @brief The number of elements stored in the tree.
    unsigned int size;
} g_tree;

/**
 * @brief Creates and initializes a general tree.
 * @return a pointer to the newly created general tree.
 */
g_tree* init_gt();

/**
 * @brief Creates and initializes a general tree position.
 * @param data_ptr A pointer to the data that is to be stored in this position.
 * @return The new created and initializes general tree position.
 */
gt_pos* init_gt_pos(void* data_ptr);

/**
 * 
 * @brief Reallocates more memory for the children of this general tree position.
 * @param pos A pointer to the general tree position whose array of children is to be expanded.
 * @return the address of the newly allocated array of pointers to the children of this position
 * or null is if expansion failed.
 */
gt_pos* expand_gt_pos(gt_pos* pos);

/**
 * 
 * @brief Reallocates less memory for the children of this general tree position.
 * @param pos A pointer to the general tree position whose array of children is to be shrinked.
 * @return the address of the newly allocated array of pointers to the children of this position
 * or null is if expansion failed.
 */
gt_pos* shrink_gt_pos(gt_pos* pos);


/**
 * @brief Frees the memory that is allocated to the position, which automatically results in freeing
 * the memory allocated to its children.
 * @param pos A general tree position that is to be deallocated.
 * @param tree A general tree.
 * @return true is the position was deallocated successfully, otherwise false.
 */
gt_pos* free_gt_pos(gt_pos* pos,g_tree* tree);

/**
 * @brief Checks if a position has at least one child.
 * @param pos A general tree position.
 * @return true if it has at least one child, otherwise false.
 */
bool is_internal(gt_pos* pos);

/**
 * @brief Checks if a position does not have children.
 * @param pos A general tree position.
 * @return true if it does not have children, otherwise false.
 */
bool is_external(gt_pos* pos);

/**
 * @brief Removes a pointer to a general tree position's child.
 * @return true if it is removed, otherwise false.
 */
bool unlink_gt_pos_child(gt_pos* parent, gt_pos* child);

/**
 * @brief Checks if a position if the root position of the tree.
 * @param pos A general tree position.
 * @param tree A general tree.
 * @return true if it is the root position, otherwise false.
 */
bool is_root(gt_pos* pos, g_tree* tree);

/**
 * @brief Gets the root position of the general tree.
 * @param tree A general tree.
 * @return the root position of the general tree.
 */
gt_pos* get_root(g_tree* tree);

/**
 * @brief Returns the parent of this general tree position in the tree.
 * @param pos A general tree position.
 * @param tree A general tree.
 * @return the parent of this general tree position.
 */
gt_pos* get_parent(gt_pos* pos, g_tree* tree);

/**
 * @brief Returns a pointer to an array of pointers to the children of this general tree
 * position.
 * @param pos A general tree position.
 * @return an array of pointers to the children of this general tree position.
 */
gt_pos** get_children(gt_pos* pos);

/**
 * @brief Shifts the pointers to the children of a general tree backwards after a
 * former child's address is removed.
 * @param pos A general tree position whose children are to be shifted backwards.
 * @param start_index The index towards which all the addresses stored in the indices
 * following it are to be shifted.
 */
void shift_back(gt_pos* pos, int start_index);

/**
 * @brief Returns the number of children of this general tree position.
 * @param pos A general tree position.
 * @return the number of children of this general tree position.
 */
int get_num_children(gt_pos* pos);

/**
 * @brief Checks if a general tree has a root position.
 * @param tree A general tree.
 * @return true if the tree has a root position, otherwise false.
 */
bool has_root(g_tree* tree);

/**
 * @brief Creates and initializes the root position for this general tree.
 * @param tree A general tree.
 * @param data A pointer to the data to be stored in the root position.
 * @return the root position of the tree.
 */
gt_pos* add_root(g_tree* tree, void* data);

/**
 * @brief Creates a new general tree position that stores the data and is a child of the parent
 * position.
 * @param data A pointer to the data to be stored in the position.
 * @param parent A pointer to the parent position of the newly created position.
 * @param tree A general tree to which the new position is added.
 * @return the newly created general tree position.
 */
gt_pos* add_child(void* data, gt_pos* parent, g_tree* tree);

/**
 * @brief Returns the number of elements stored in the general tree.
 * @param tree A general tree.
 * @return the number of elements stored in the general tree.
 */
unsigned int get_size(g_tree* tree);

/**
 * @brief Deallocates the memory that was allocated to a general tree.
 * @param tree A general tree.
 * @return NULL if the tree is successfully deleted, or the address of the tree.
 */
g_tree* delete_gt(g_tree* tree);

/**
 * @brief Returns the next available index to store the address of the next child of this
 * position.
 * @param pos A general tree position.
 * @return the next available slot to store the address of the next child of this position.
 */
int get_next_slot(gt_pos* pos);

/**
 * @brief Checks if the array of pointers to the children of this general tree position is expandable
 * based on the load factor, which must be at least 80% or 0.8 for expansion to take place.
 * @param pos A general tree position.
 * @return true if the position's array of pointers to children needs expansion, otherwise false.
 */
bool is_expandable(gt_pos* pos);

/**
 * @brief Checks if a general tree is empty.
 * @param tree A general tree.
 * @return true if the tree is empty otherwise false.
 */
bool is_empty(g_tree* tree);

/**
 * @brief Sets the parent of a general tree position.
 * @param pos A general tree position.
 * @param parent A general tree position that is to be the parent of the position.
 * @return true if "parent" was set successfully as the parent of "pos".
 */
bool set_parent(gt_pos* pos, gt_pos* parent);

#endif // _DSA_GENERAL_TREE_H