#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "hashquad.h"

int main()
{
    // Array Structure to store file data into Array
    typedef struct Array
    {
        ElementType Arrx;
    }Arr;

    // Variables to measure Time Consumed and Array to store the number of records present in the file
    LARGE_INTEGER start_time, end_time, elapsed_time, frequency;
    QueryPerformanceFrequency(&frequency);
	char size_of_array[2][10];
	// FILE pointer to store the file
    FILE *fileptr;

    int x = 0;
    fileptr = fopen("data_10.txt", "r");

    if (fileptr == NULL)
    {
        printf("Error in Loading File.\n");
        exit(1);
    }
    else
    {
        printf("File Loaded.\n");
    }


    // Stores the number of records present in the file in an array.
    for (int a = 0; a < 2; a++)
    {
        fscanf(fileptr, "%s", size_of_array[a]);
    }

    // sizex stores the number of records in the file
    int sizex = atoi(size_of_array[1]);
    printf("size = %d.\n", sizex);

    // file_contents stores the records in the file
    Arr *file_contents = malloc( sizex * sizeof( Arr ) );
    if( file_contents == NULL )
            FatalError( "Out of space!!!" );


    // arr1 will be used later for sorting purposes.
    int *arr1 = malloc( sizex * sizeof ( int ) );
    if( arr1 == NULL )
        FatalError( "Out of space!!!" );


    QueryPerformanceCounter(&start_time); //start time
   // Stores the Records present in the file in the array.

    while(!feof(fileptr))
    {
        fscanf(fileptr, "%d", &file_contents[x].Arrx.ID);
        fscanf(fileptr, "%s", file_contents[x].Arrx.Name);
        fscanf(fileptr, "%s", file_contents[x].Arrx.City);
        fscanf(fileptr, "%s", &file_contents[x].Arrx.Service);
        x++;
    }

    QueryPerformanceCounter(&end_time); // end time
    elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	printf("\nThe Run Time of Storing Contents of File in Array is: %g\n\n", (((double) elapsed_time.QuadPart) / frequency.QuadPart));

	// Close the file
    fclose(fileptr);

    // Declare and Initialize the HashTabe
    HashTable H;
    H = InitializeTable(sizex+2);

    QueryPerformanceCounter(&start_time); //start time

    // Insert the Records into the HashTable and Also store the ID in the array for sorting purpose.
    printf("Inserting Records into the HashTable........\n");
    for (int a = 0; a < sizex; a++)
        {
            Insert(file_contents[a].Arrx.ID, file_contents[a].Arrx.Name, file_contents[a].Arrx.City, file_contents[a].Arrx.Service, H);
            arr1[a] = file_contents[a].Arrx.ID;
        }
    printf("No. of Collisions = %d.\n", GetCollisions());
    printf("Memory Used For Inserting is %d bytes.", GetMemory( H ) );
    QueryPerformanceCounter(&end_time); // end time
    elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	printf("\n\nThe Run Time of Insertion and Storing ID in the Array is: %g\n\n", (((double) elapsed_time.QuadPart) / frequency.QuadPart));

	printf("Printing The HashTable........\n");
    Print_HashTable(H);

    QueryPerformanceCounter(&start_time); //start time
    // Insert the Records into the HashTable and Also store the ID in the array for sorting purpose.
    printf("Finding Records in the HashTable........\n");
    for (int a = 0; a < sizex; a++)
        {
            if (a%2 == 0) Find_Record(file_contents[a].Arrx.ID, H);
        }
    printf("Memory Used For Finding is %d bytes.", GetMemory( H ) );
    QueryPerformanceCounter(&end_time); // end time
    elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	printf("\n\nThe Run Time of Finding Records in the HashTable is: %g\n\n", (((double) elapsed_time.QuadPart) / frequency.QuadPart));

    QueryPerformanceCounter(&start_time); //start time
    printf("Deleting Records from the HashTable........\n");
    // Delete Half of the Records from the HashTable
    for (int a = 0; a < sizex; a++)
    {
        if(a%2 != 0)
        {
            Delete(file_contents[a].Arrx.ID, H);
            arr1[a] = NULL;
        }
    }
    printf("Memory Used For Deleting is %d bytes.", GetMemory( H ) );
    QueryPerformanceCounter(&end_time); // end time
    elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	printf("\n\nThe Run Time of Deletion of Records in HashTable is: %g\n\n", (((double) elapsed_time.QuadPart) / frequency.QuadPart));

    QueryPerformanceCounter(&start_time); //start time
    // Print the HashTable and number.
    Print_HashTable(H);
    QueryPerformanceCounter(&end_time); // end time
    elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
	printf("\n\nThe Run Time of Printing HashTable is: %g\n", (((double) elapsed_time.QuadPart) / frequency.QuadPart));

	QueryPerformanceCounter(&start_time); //start time
	// Sort The Array, and Print the HashTable in a sorted manner.
	printf("Sorted Traversal of the HashTable........\n");
    Sorted_Traversal(H, arr1, sizex);
    int size_arr = sizex*sizeof(*arr1);
    printf("Memory Used For Sorted Traversal is %d bytes.", (GetMemory( H ) + size_arr) );
    QueryPerformanceCounter(&end_time); // end time
    elapsed_time.QuadPart = end_time.QuadPart - start_time.QuadPart;
    // Destroy the HashTable.
    DestroyTable(H);
    free(file_contents);
    free(arr1);
	printf("\n\nThe Run Time of Sorting Array and Traversing HashTable in Sorted Order is: %g\n", (((double) elapsed_time.QuadPart) / frequency.QuadPart));

    printf("\n\nProgram Terminated Successfully.\n");
    return 0;
}
