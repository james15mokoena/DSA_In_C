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
    gt_pos* root = add_root(fam,"Esther");
    
        
    printf("Size: %d\n",get_size(fam));

    return SUCCESS;
}