#include "../include/general_tree.h"

/// @brief Indicates that the program terminated successfully.
#define SUCCESS 0

/**
 * @brief The entry point of the program.
 * @param argc The number of command line arguments passed to the
 * program.
 * @param argv An array of pointers to arguments passed to the program.
 * @return A status code indicating whether the program terminated successfully
 * or not, with 0 indicating successful termination and any other integer indicating
 * something went wrong before/during termination.
 */
int main(int argc, char* argv[]){

    g_tree* fam = init_gt();
    gt_pos* root = add_gt_root(fam,"Esther");
    
    gt_pos* c1 = add_gt_child("Tumelo",root, fam);
    gt_pos* c2 = add_gt_child("Julia",root, fam);
    gt_pos* c3 = add_gt_child("Teboho",root, fam);
    gt_pos* c4 = add_gt_child("Pheello",root, fam);

    gt_pos* c21 = add_gt_child("Karabo",c2, fam);
    gt_pos* c22 = add_gt_child("Amahle",c2,fam);

    printf("Tree Size: %d\n",get_size(fam));    
    printf("Root: %s\nNo children: %d\n",(char*) root->data_ptr,get_num_children(root));
    gt_pos_str_print(root);
    gt_pos_str_print(c2);

    return SUCCESS;
}