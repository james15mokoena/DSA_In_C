#include <stdio.h>
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

    t_pos p;
    char* m = "Esther";
    p.data_ptr = m;

    t_pos p1;
    char* me = "Pheello";
    p1.data_ptr = me;

    t_pos p2;
    char* ju = "Julia";
    p2.data_ptr = ju;

    t_pos p3;
    char* te = "Teboho";
    p3.data_ptr = te;

    printf("%s\n",(char*)p.data_ptr);



    
    return SUCCESS;
}