#include "fatal.h"
#include "hashquad.h"
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

        #define MinTableSize (10)

        enum KindOfEntry { Legitimate, Empty, Deleted };

        struct HashEntry
        {
            enum KindOfEntry Info;
            ElementType      Element;
        };

        typedef struct HashEntry Cell;
        // Integer to keep record of Collisions
        int ccount = 0;

        /* Cell *TheCells will be an array of */
        /* HashEntry cells, allocated later */
        struct HashTbl
        {
            int TableSize;
            Cell *TheCells;
        };


        static int
        NextPrime( int N )
        {
            int i;

            if( N % 2 == 0 )
                N++;
            for( ; ; N += 2 )
            {
                for( i = 3; i * i <= N; i += 2 )
                    if( N % i == 0 )
                        goto ContOuter;  /* Sorry about this! */
                return N;
              ContOuter: ;
            }
        }

        /* Hash function for ints */
        Index
        Hash( int Key, int TableSize )
        {
            return Key % TableSize;
        }

/* START: fig5_15.txt */
        HashTable
        InitializeTable( int TableSize )
        {
            HashTable H;
            int i;

/* 1*/      if( TableSize < MinTableSize )
            {
/* 2*/          Error( "Table size too small" );
/* 3*/          return NULL;
            }

            /* Allocate table */
/* 4*/      H = malloc( sizeof( struct HashTbl ) );
/* 5*/      if( H == NULL )
/* 6*/          FatalError( "Out of space!!!" );

/* 7*/      H->TableSize = NextPrime( TableSize );

            /* Allocate array of Cells */
/* 8*/      H->TheCells = malloc( sizeof( Cell ) * H->TableSize );
/* 9*/      if( H->TheCells == NULL )
/*10*/          FatalError( "Out of space!!!" );

/*11*/      for( i = 0; i < H->TableSize; i++ )
            {
                H->TheCells[ i ].Info       = Empty;
                H->TheCells[ i ].Element.ID = 0;
                sprintf(H->TheCells[ i ].Element.Name, "%c", '\0');
                sprintf(H->TheCells[ i ].Element.City, "%c", '\0');
                H->TheCells[ i ].Element.Service = '\0';
            }
/*13*/      return H;
        }
/* END */

/* START: fig5_16.txt */
        Position
        Find( int Key, HashTable H )
        {
            Position CurrentPos;
            int CollisionNum;

/* 1*/      CollisionNum = 0;
//printf("key = %d.\n", Key);
/* 2*/      CurrentPos = Hash( Key, H->TableSize );
/* 3*/      while( H->TheCells[ CurrentPos ].Info != Empty &&
                   H->TheCells[ CurrentPos ].Element.ID != Key )
                            /* Probably need strcmp!! */
            {
                // For Each iteration, if there exists a collision in Quadratic Probing
                // Therefore, increment the collision counter(ccount) on each iteration.
                ccount++;
/* 4*/          CurrentPos += 2 * ++CollisionNum - 1;
/* 5*/          if( CurrentPos >= H->TableSize )
/* 6*/              CurrentPos -= H->TableSize;
            }
//            printf("Last.\n");
/* 7*/      return CurrentPos;
        }
/* END */

/* START: fig5_17.txt */
        void
        Insert( int Key, char Name[], char City[], char Service, HashTable H )
        {
            Position Pos;
            // Find the Position where records are to be inserted.
            Pos = Find( Key, H );
            if( H->TheCells[ Pos ].Info != Legitimate )
            {
                /* OK to insert here */
                H->TheCells[ Pos ].Info = Legitimate;
                H->TheCells[ Pos ].Element.ID = Key;
                sprintf(H->TheCells[ Pos ].Element.Name, "%s", Name);
                sprintf(H->TheCells[ Pos ].Element.City, "%s", City);
                H->TheCells[ Pos ].Element.Service = Service;
                         /* Probably need strcpy! */
            }
            printf("Key %d Inserted at Position %d.\n", Key, Pos);
            printf("Index[%d] ->\t", Pos);
            printf("ID = %d,\t",        H->TheCells[Pos].Element.ID);
            printf("Name = %s,\t",      H->TheCells[Pos].Element.Name);
            printf("City = %s,\t",      H->TheCells[Pos].Element.City);
            printf("Service = %c\n",    H->TheCells[Pos].Element.Service);
        }
/* END */

/* START: fig5_22.txt */
        HashTable
        Rehash( HashTable H )
        {
            int i, OldSize;
            Cell *OldCells;

/* 1*/      OldCells = H->TheCells;
/* 2*/      OldSize  = H->TableSize;

            /* Get a new, empty table */
/* 3*/      H = InitializeTable( 2 * OldSize );

            /* Scan through old table, reinserting into new */
/* 4*/      for( i = 0; i < OldSize; i++ )
/* 5*/          if( OldCells[ i ].Info == Legitimate )
/* 6*/              Insert( OldCells[ i ].Element.ID, OldCells[ i ].Element.Name, OldCells[ i ].Element.City, OldCells[ i ].Element.Service, H );

/* 7*/      free( OldCells );

/* 8*/      return H;
        }
/* END */



        // Returns the ID stored in the HashTable at current Position
        int
        Retrieve( Position P, HashTable H )
        {
            return H->TheCells[ P ].Element.ID;
        }


        // Destroys the HashTable
        void
        DestroyTable( HashTable H )
        {
            free( H->TheCells );
            free( H );
        }


        // Function to Print the HashTable
        void
        Print_HashTable( HashTable H )
        {
            // Traverse through the HashTable, and Look at the info of each element in TheCells in HashTable
            // If it is Legitimate, Then prints the records. Else if it is Deleted or Empty, then prints it accordingly.
            for (int i = 0; i < H->TableSize; i++)
            {
                if (H->TheCells[i].Info == Legitimate)
                {
                printf("Index[%d] ->\t", i);
                printf("ID = %d,\t",        H->TheCells[i].Element.ID);
                printf("Name = %s,\t",      H->TheCells[i].Element.Name);
                printf("City = %s,\t",      H->TheCells[i].Element.City);
                printf("Service = %c\t",    H->TheCells[i].Element.Service);
                printf("\n");
                }
                else if (H->TheCells[i].Info == Deleted)
                printf("Index[%d] = Deleted\n", i);
                else if (H->TheCells[i].Info == Empty)
                printf("Index[%d] = Empty\n", i);
            }
            printf("\n");
        }

        // Function that returns the number of Collisions occurred in Quadratic Probing
        int
        GetCollisions (void)
        {
            return ccount;
        }

        // Function to Delete an Element from the HashTable
        void
        Delete(int Key, HashTable H)
        {
            // Finds the Position of Given Key in the HashTable and stores in Pos
            Position Pos = Find(Key, H);
            // If Pos is not NULL, means Key is found
            if(Pos != NULL)
            {
                // If the Given Pos in the HashTable is Legitimate and Stores the Key
                // Then make all the records NULL, and change info from Legitimate to Deleted.
                if (H->TheCells[Pos].Info == Legitimate  &&  H->TheCells[Pos].Element.ID == Key)
                {
                    H->TheCells[Pos].Info = Deleted;
                    H->TheCells[ Pos ].Element.ID = 0;
                    sprintf(H->TheCells[ Pos ].Element.Name, "%c", '\0');
                    sprintf(H->TheCells[ Pos ].Element.City, "%c", '\0');
                    H->TheCells[ Pos ].Element.Service = '\0';
                    printf("Deleted Element = %d.\n", Key);
                }
            }
            // If Pos is NULL, Key is not found, or does not exist.
            else
            {
                printf("Key = %d Not Found.\n", Key);
            }

        }

        // Sorts the array
        void
        selectionSort(int arr[], int n)
        {
//            printf("n = %d.\n");
            int i, j, min_idx;

            // One by one move boundary of unsorted subarray
            for (i = 0; i < n - 1; i++) {

                // Find the minimum element in unsorted array
                min_idx = i;
                for (j = i + 1; j < n; j++)
                    if (arr[j] < arr[min_idx])
                        min_idx = j;

                // Swap the found minimum element
                // with the first element
                Swap(&arr[min_idx], &arr[i]);
            }
        }

        // Swaps elements given as argument
        void
        Swap(int* xp, int* yp)
        {
            int temp = *xp;
            *xp = *yp;
            *yp = temp;
        }

        // Function to Print the HashTable
        void
        Sorted_Traversal( HashTable H, int Array[], int Size )
        {
            // Traverse through the HashTable in a sorted order. This is done by storing the ID's of HashTable in an array.
            // Then the array is sorted. Then Position is found.  Elements of Array and ID of HashTable are then compared and if equal, records of HashTable are printed.
            // Since Array is in Sorted Order, HashTable also gets printed in Sorted Order.
            selectionSort(Array, Size);
            for (int i = 0; i < Size; i++)
            {
                Position Pos = Find(Array[i], H);
                if(H->TheCells[Pos].Element.ID == Array[i] && Array[i] != NULL)
                   {
                       printf("Index[%d] ->\t", Pos);
                       printf("ID = %d,\t",        H->TheCells[Pos].Element.ID);
                       printf("Name = %s,\t",      H->TheCells[Pos].Element.Name);
                       printf("City = %s,\t",      H->TheCells[Pos].Element.City);
                       printf("Service = %c\n",    H->TheCells[Pos].Element.Service);
                   }
                else continue;
            }
        }

        // Function to find a given Key/ID in The HashTable
        void
        Find_Record( int Key, HashTable H)
        {
            // Find The Position of the Given Key/ID and print it.
            Position Pos = Find(Key, H);
            {
                printf("Key = %d Found at Position = %d.\n", Key, Pos);
                return;
            }
            // Key/ID not Found.
            printf("Key not Found.\n");
        }


        // Returns the memory used in Bytes
        int
        GetMemory( HashTable H )
        {
            return ( H->TableSize * ( (2*sizeof(int)) + sizeof(H->TheCells->Element) ) );;
        }

