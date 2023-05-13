

/* START: fig3_6.txt */
        #ifndef _List_H
        #define _List_H

        struct Rec_file
        {                    //-------making structure having integer id and char contents and making all struct typedef to ElementType-----//
        int id;
        char name[100];
        char city[50];
        char ctg[10];
        };
        typedef struct Rec_file ElementType;

        struct Node;
        typedef struct Node *PtrToNode;
        typedef PtrToNode List;
        typedef PtrToNode Position;


        List MakeEmpty( List L );
        int IsEmpty( List L );
        int IsLast( Position P, List L );
        Position Find( ElementType X, List L );
        int Rec_compare(ElementType *X, ElementType *Y);
        void Delete( ElementType X, List L );
        Position FindPrevious( ElementType X, List L );
        void Insert(ElementType X, List L, Position P );
        void DeleteList( List L );
        Position Header( List L );
        Position First( List L );
        Position Advance( Position P );
        ElementType Retrieve( Position P );
        void PrintList( const List L );
        Position GotoIndex( List L, int n );
        void Swap(Position P, Position Q);
        void Sort(List L, int low, int high);
        int part(List L, int low, int high);
        int memory_calc();




        #endif    /* _List_H */
/* END */
