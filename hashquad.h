/* Interface for quadratic probing hash table */
typedef struct Records ElementType;

/* START: fig5_14.txt */
        #ifndef _HashQuad_H
        #define _HashQuad_H

        typedef unsigned int Index;
        typedef Index Position;

        struct HashTbl;
        typedef struct HashTbl *HashTable;

        struct Records;
        struct Records
        {
            int         ID;
            char        Name[20];
            char        City[4];
            char        Service;
        };


        Index Hash( int Key, int TableSize );
        HashTable InitializeTable( int TableSize );
        void DestroyTable( HashTable H );
        Position Find( int Key, HashTable H );
        void Insert( int Key, char Name[], char City[], char Service, HashTable H );
        int Retrieve( Position P, HashTable H );
        HashTable Rehash( HashTable H );
        void Print_HashTable( HashTable H );
        int GetCollisions ( void );
        void Delete(int Key, HashTable H);
        void selectionSort(int arr[], int n);
        void Swap(int* xp, int* yp);
        void Sorted_Traversal( HashTable H, int Array[], int Size );
        void Find_Record( int Key, HashTable H);
        int GetMemory( HashTable H );

        /* Routines such as Delete are MakeEmpty are omitted */

        #endif  /* _HashQuad_H */

/* END */
