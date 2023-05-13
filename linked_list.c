#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "fatal.h"

    struct Node
        {
            ElementType Element;
            Position    Next;
        };

        List
        MakeEmpty( List L )
        {
            if( L != NULL )
                DeleteList( L );
            L = malloc( sizeof( struct Node ) );
            if( L == NULL )
                FatalError( "Out of memory!" );
            L->Next = NULL;
            return L;
        }

/* START: fig3_8.txt */
        /* Return true if L is empty */

        int
        IsEmpty( List L )
        {
            return L->Next == NULL;
        }
/* END */

/* START: fig3_9.txt */
        /* Return true if P is the last position in list L */
        /* Parameter L is unused in this implementation */

        int IsLast( Position P, List L )
        {
            return P->Next == NULL;
        }
/* END */

/* START: fig3_10.txt */
        /* Return Position of X in L; NULL if not found */

        Position
        Find( ElementType X, List L )
        {
            Position P;

/* 1*/      P = L->Next;
           //----as my ElementType is not of type "int", thus comparing structs where comparison is needed and calling Rec_compare func which compares two structs------//
/* 2*/      while( P != NULL && !(Rec_compare(&X, &(P->Element))))
/* 3*/          P = P->Next;

/* 4*/      return P;
        }
/* END */

/* START: fig3_11.txt */
        /* Delete from a list */
        /* Cell pointed to by P->Next is wiped out */
        /* Assume that the position is legal */
        /* Assume use of a header node */

        void
        Delete( ElementType X, List L )
        {
            Position P, TmpCell;

            P = FindPrevious( X, L );


            if( !IsLast( P, L ) )  /* Assumption of header use */
            {                      /* X is found; delete it */
                TmpCell = P->Next;
                P->Next = TmpCell->Next;  /* Bypass deleted cell */

                free( TmpCell );

            }
        }
/* END */

//-------following func takes two structs of ElementType and compare them----------//
     int
     Rec_compare(ElementType *X, ElementType *Y)
     {
        // int a, b, c;

       //  a = strcmp(X->name, Y->name);    //-----comparing name, each struct has------//
         //b = strcmp(X->city, Y->city);    //-----comparing city of the structs------//
         //c = strcmp(X->ctg, Y->ctg);      //-----comparing category each struct has------//

         //-----if ids of both structs are equal, checking for the further data i.e. name, city and category, if the strcmp returns 0, it means both strings are equal-----//
         if ((X->id == Y->id) ){
            return 1;    //--------Returning the function value as True if above condition is True-----//
         }
         else{
            return 0;      //--------Returning the function value as False if above condition is False------//
         }
     }

/* START: fig3_12.txt */
        /* If X is not found, then Next field of returned value is NULL */
        /* Assumes a header */

        Position
        FindPrevious( ElementType X, List L )
        {
            Position P;

/* 1*/      P = L;
/* 2*/      while( P->Next != NULL && !(Rec_compare(&X, &(P->Next->Element)))) //----comparing the X and Next of P element structs by calling Rec_compare func----//
/* 3*/          P = P->Next;

/* 4*/      return P;
        }
/* END */

/* START: fig3_13.txt */
        /* Insert (after legal position P) */
        /* Header implementation assumed */
        /* Parameter L is unused in this implementation */

    void
        Insert(ElementType X, List L, Position P )
        {
            Position TmpCell;

/* 1*/      TmpCell = malloc( sizeof( struct Node ) );
/* 2*/      if( TmpCell == NULL )
/* 3*/          FatalError( "Out of space!!!" );

/* 4*/      TmpCell->Element = X;
/* 5*/      TmpCell->Next = P->Next;
/* 6*/      P->Next = TmpCell;

        }
/* END */

#if 0
/* START: fig3_14.txt */
        /* Incorrect DeleteList algorithm */

        void
        DeleteList( List L )
        {
            Position P;

/* 1*/      P = L->Next;  /* Header assumed */
/* 2*/      L->Next = NULL;
/* 3*/      while( P != NULL )
            {
/* 4*/          free( P );
/* 5*/          P = P->Next;
            }
        }
/* END */
#endif

/* START: fig3_15.txt */
        /* Correct DeleteList algorithm */

        void
        DeleteList( List L )
        {
            Position P, Tmp;

/* 1*/      P = L->Next;  /* Header assumed */
/* 2*/      L->Next = NULL;
/* 3*/      while( P != NULL )
            {
/* 4*/          Tmp = P->Next;
/* 5*/          free( P );
/* 6*/          P = Tmp;
            }
        }
/* END */

        Position
        Header( List L )
        {
            return L;
        }

        Position
        First( List L )
        {
            return L->Next;
        }

        Position
        Advance( Position P )
        {
            return P->Next;
        }

        ElementType
        Retrieve( Position P )
        {
            return P->Element;
        }

     void
      PrintList( const List L ) //------to print the list at any stage for testing code----//
   {
    Position P = Header( L );

    if( IsEmpty( L ))       //-------if list is empty, printing message to user that list is Empty----//
        printf( "Empty list\n" );
    else
    {
        do
        {
            P = Advance(P );
            printf("%d\t%s\t%s\t%s\n", P->Element.id, P->Element.name, P->Element.city, P->Element.ctg);
            //-------printing the id, name,city and category by accessing the field of Element of that Position like we retrieved the data by P->Element --------//
        } while( !IsLast( P, L ) );
        printf( "\n" );
    }
   }

    Position
        GotoIndex( List L, int n )
         {
            int count;
            Position P;
            P = L->Next;
            count = 0;
            while (P != NULL && count != n) {   //------till the list does not end, moving forward the list list till the index equals our variable----//
                P = Advance( P );
                count += 1;
            }
            return P;
        }

       //----------function to swap two positions -----//
    	void Swap(Position P, Position Q)
    	 {
           ElementType temp = P->Element;   //------initializing a new struct of ElementType i.e. Temp and storing first struct to be swapped-------//
           P->Element = Q->Element;     //------putting contents of second struct in first one's position-------//
           Q->Element = temp;           //-----finally putting the contents of first struct which were stored in temp, into second struct's position------//
         }

 //----------func which sorts by taking arguments List , lower index and highest index the records can have--------//
         void Sort(List L, int low, int high)
         {
             if(low < high){               //-------if low is lesser than high, then calling Sort and making left and right sub-sections----//
             int pi = part(L, low, high);
             Sort(L, low, pi - 1);
             Sort(L, pi + 1, high);
             }
         }

//----------------func to get partition sub-section for Quicksort---------------------//
         int part(List L, int low, int high)
         {
             Position A = GotoIndex(L, high);   //-------getting highest index's Position-------//
             int pivot = A->Element.id;         //---------setting the pivot variable to the id of Element at High index position 'A'--------//
             int i = low - 1;
             Position P;
             Position Q, R, S;


             for(int j = low; j <= high - 1; j++){     //------running the loop from low index to one lesser than high index-----//
                Q = GotoIndex(L, j);                //----------getting the jth index in position Q--------//
                if(Q->Element.id <pivot){            //--------if the id of Q is lesser than pivot id then incrementing i and getting its index and swapping it with ith Position--------//
                    i++;
                    P = GotoIndex(L, i);
                    Swap(P, Q);
                }
             }

             R = GotoIndex(L, i+1);      //-----getting index of i+1 ---------//
             S = GotoIndex(L, high);     //-------after above swaps, getting the index of high again------//
             Swap(R, S);                 //-----------swapping the high and i+1------//
             return (i + 1);             //--------returning i+1 integer----------//
         }

         int
         memory_calc()
         {
             int memory = sizeof(struct Node);  //-------calculating memory which was allocated to Elements in struct Node--------//
             return memory;
         }








