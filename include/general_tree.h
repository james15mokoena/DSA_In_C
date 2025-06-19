/**
 * @brief This general_tree.h file contains the structures and interfaces
 * for implementing a general tree, whose nodes can have as many children
 * as necessary and does not enforce any rules for insertion and deletion
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

/**
 * @brief A position of a general tree, that can have many children and only
 * one parent position.
 */
typedef struct t_pos{

    /// @brief A pointer to the data that is stored in this position.
    void* data_ptr;

    /// @brief A pointer to a tree position that is the parent of this position.
    struct t_pos* parent;

    /// @brief An array pointers to tree positions that are children of this position.
    struct t_post* children[];
} t_pos;




#endif // _DSA_GENERAL_TREE_H