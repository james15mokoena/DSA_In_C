#include <stdio.h>
#include "../include/positional_list.h"


/// @brief Indicates that the program terminated successfully.
#define SUCCESS 0

// from positional_list.h

void test_pl_pos();
void test_p_list();

/**
 * @brief The entry point of the program.
 * @param argc The number of command line arguments passed to the
 * program.
 * @param argv An array of pointers to arguments passed to the program.
 * @return A status code indicating whether the program terminated successfully
 * or not, with 0 indicating successful termination and any other integer indicating
 * something went wrong before/during termination.
 */
int main(int argc, string argv[]){

    test_p_list();

    printf("Done!!\n");
    
    return SUCCESS;
}

void test_pl_pos(){

    pl_pos p1;
    char* n = "James Mokoena";
    p1.data_ptr = n;

    pl_pos p2;
    string n1 = "Michael Mokoena";
    p2.data_ptr = n1;

    pl_pos p3;
    string n2 = "Julia Mokoena";
    p3.data_ptr = n2;

    pl_pos p4;
    string n3 = "Esther Mokoena";
    p4.data_ptr = n3;

    pl_pos p5;
    string n4 = "Meshack Mokoena";
    p5.data_ptr = n4;

    pl_pos p6;
    string n5 = "Joseph Mokoena";
    p6.data_ptr = n5;

    // link
    p6.next_ptr = &p4;  // p6.n -> p4
    p6.prev_ptr = NULL; // start
    p4.prev_ptr = &p6;  // p4.p -> p6
    p4.next_ptr = &p5;  // p4.n -> p5
    p5.prev_ptr = &p4;  // p5.p -> p4
    p5.next_ptr = &p3;  // p5.n -> p3
    p3.prev_ptr = &p5;  // p3.p -> p5
    p3.next_ptr = &p2;  // p3.n -> p2
    p2.prev_ptr = &p3;  // p2.p -> p3
    p2.next_ptr = &p1;  // p2.n -> p1
    p1.prev_ptr = &p2;  // p1.p -> p2
    p1.next_ptr = NULL; // end

    pl_pos* curr = &p1;

    while(curr != NULL){

        string p = (string) get_element(curr);
        printf("%s\n",p);
        curr = get_prev(curr);
    }
}

void test_p_list(){
    
    p_list* list = init_p_list();
    
    if(list != NULL){

        // testing insert operations
        string i1 = "Pheello";
        pl_pos* y1 = add_first(&i1,list);  

        string i2 = "Pastor Chris";
        pl_pos* y2 = add_after(y1,&i2,list);

        string i3 = "Mish";
        pl_pos* y3 = add_after(y2,&i3,list);

        string i4 = "Precious";
        pl_pos* y4 = add_last(&i4,list);

        printf("List size: %d\n",size(list));

        print_p_list(list,str_print);

        string i = "Ben 10";
        pl_pos* p1 = str_search(i1,list);

        if(p1 != NULL){
            string s = (string) p1->data_ptr;
            printf("Found: %s\n",s);
        }            
        else{
            string s = (string) p1->data_ptr;
            printf("Not found: %s\n",s);
        }
            

        list = destroy_p_list(list);

        if(list == NULL)
            printf("Positional list deleted successfully!!\n");
        else
            printf("Size = %d\n",size(list));
        
    }        
    else
        fprintf(stderr,"%s\n","Failed to create the positional list.");

}