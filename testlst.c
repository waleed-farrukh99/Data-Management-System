#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linked_list.h"

int main()
{
    clock_t start, end;

    FILE *fptr;

    int i = 0;
    char size_arr[2][10];
    ElementType *contents = malloc(10*sizeof(ElementType));  //array of ElementType which stores the records of file which is being read


    List L = MakeEmpty(NULL);  //creating the List//

    Position P = Header(L);

    fptr = fopen("data_10.txt", "r");   //reading the file data_10.txt //
    if (fptr == NULL){
        printf("File does not exist");    //if the file pointer is NULL, it means that file does not exist //
        return 1;
    }

    printf("Loading Completed\n");   //will print if file is loaded and exists //

    for(int a = 0; a < 2; a++){
        fscanf(fptr, "%s", size_arr[a]);  //storing the Number of Records a file has, in size_arr array //
    }
    printf("Number of Records are: %d\n", atoi(size_arr[1])); //printing the number of records by converting it to integer value//

    int sizex = atoi(size_arr[1]);      //storing the integer value of Number of Records in integer sizex //
    int mem = (sizex +1)*memory_calc();



           //THE FOLLOWING IS A TRUE PIECE OF CODE FOR PRINTING

    while(!feof(fptr)){      //if the the file has not reached its end, the continue executing following lines//

        fscanf(fptr, "%d\t%[^\t]\t%[^\t]\t%[^\n]\n", &contents[i].id, contents[i].name, contents[i].city, contents[i].ctg);
        //above line reads and stores the contents of file, as fscanf reads only chars, so I have written %d to read id till each tab space and then continue reading characters till each tab space and in the last till the end of line and storing in ith contents relevant field//

        i++;           //incrementing the i variable to continue reading till the end of file//
    }




    fclose(fptr);            //----closing the file------//


   start = clock();   //---starting time to note for Insertion---//
   printf ("\nInsertion started\n");

    for(i = 0; i <sizex; i++){      //---Running the loop till number of records to Insert---//
        Insert(contents[i], L, P);   //---passing arguments to Insert func, first is the ith content in the List created---//
    }
    end = clock();  //---noting the end time of Insertion in end---//
    printf("Runtime for Insertion is: %g seconds\n", ((end - start) / ((double)CLOCKS_PER_SEC))); //---printing the time consumed---//
    mem = (sizex+1)*memory_calc();     //-------multiplying with the size of records plus 1 which is for header node---//
    printf("\nMemory used: %d\n", mem);
    //PrintList(L);        //---used in between to Print and check if working is correct---//

    start = clock();         //---starting the clock to note time for Find---//
    printf("\nFinding data\n");

        for(i = 0; i < sizex; i += 2){ //--Running the loop till size of Records and i += 2 is due to because we want to find even index of records---//
           Find(contents[i], L);    //---passing ith index of contents and List L to func Find---//
           if(i%1000 == 0){
           printf("%d\n", i);    //---used to print the number of records it has found because for file or record 1000000, I wanted to keep track of progress---//
           }
        }
        end = clock();         //---noting end time of function---//
        printf("Runtime for finding is: %g seconds\n", ((end - start) / ((double)CLOCKS_PER_SEC)));
        //------------------calculating run-time of Find func----------------------------------------//
        mem = (sizex + 1)*memory_calc();
        printf("\nMemory used: %d\n", mem);


       start = clock();      //------starting the clock to note start time-----//

     printf("\nSorting started\n\n");
        Sort(L, 0, 9);           //------passing list, low value index i.e. 0, and high index i.e. 9 and not 10 as index is starting from 0 and not 1 for 10000 number of records---//
        end = clock();              //------noting end time by clock----//

        PrintList(L);             //-------printing to check if the list has been sorted correctly------//
        printf("\nSorting done\n");
        printf("Runtime for Sort is: %g seconds\n\n", ((end - start) / ((double)CLOCKS_PER_SEC)));
             //-------------------calculating run-time for Sort function-----------------------------//
        mem = (sizex + 1)*memory_calc();
        printf("\nMemory used: %d\n", mem);


        start = clock();            //------starting the clock to note start time-----//
        printf("\nDelete started\n\n");
        for(i = 0; i<sizex; i++){   //-------loop running till the number of records and going to each struct record and deleting it----//
          if(i % 2 != 0){
        Delete(contents[i], L);
          }
        }
        end = clock();         //--------noting end time by clock---------//
        PrintList(L);          //--------printing the list to make sure it is deleted-------//
        printf("\nRuntime for Delete is: %g seconds\n", ((end - start) / ((double)CLOCKS_PER_SEC)));
        //---------printing the runtime of deletion after calculating it--------//

        mem = (sizex + 1)*(memory_calc()/2);  //------noting time for deleting records----//
        printf("\nMemory used: %d\n", mem);

        free(contents);      //---------freeing the memory which was allocated--------//

       }




