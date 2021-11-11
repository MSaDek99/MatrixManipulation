/* A C program to scan a matrix from a file with a certain size and manipulate it                      */
/* - Getting the trace in case of a square matrix                     */
/* - Getting the determinant if a square or 1x1 matrix is scanned                                                */
/* - Extracting A Submatrix                     */
/* Written by Mohammed Elsayed                                                       */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
struct matrix
{
char name; // to hold the 1 character name of the matrix
int mValues[10][10]; // to hold the values in the matrix, up to 10 rows x 10 columns
int nrows; // to hold the number of rows used in mValues
int ncols; // to hold the number of columns used in mValues
};
void matrixInput(struct matrix *mat); /* to input the size (number of rows and
columns) of the matrix, the name of the matrix, and read in the values from the file into the 2D
array that makes up the matrix */
void matrixDisplay(struct matrix mat); /* to display the name of the matrix and
the values in the 2D array that makes up the matrix*/
void matrixTrace(struct matrix mat, int *trace); /*to find the trace of the
original matrix; this function does not display either mat , or the trace */
void matrixDeterminant(struct matrix m1, struct matrix *m2, int *determinant); /* to find the determinant of m2, where m2 is a 2x2 subset matrix of m1
this function does not display either m1 or m2 , or the determinant*/
void subMatrix(struct matrix m1, struct matrix *m2); /* to input one or more
row numbers and one or more column numbers to remove from m1 to form submatrix m2
this function does not display m1 or m2*/
int selectingindex(int index ,int array[],int size); /*to select the rows and columns that the user wants to have in the new matrix after deleting the unwanted rows and columns */
int main()
{
    int traceA,deter,choice; // Defining Trace of square matrices , determinant and the choice of the user whether to continue and repeat the program or to exit the program
    struct matrix originalmat ; // Defining Original matrix
    struct matrix determat ; // Defining the 2x2 matrix extracted
    struct matrix submat ; // Defining the submatrix that the user will extract from the original matrix
    matrixInput(&originalmat); // Calling the function that prompt the user to scan the matrix in the size the user wants
    matrixDisplay(originalmat); // Printing the desired matrix to the screen
    if(originalmat.nrows == originalmat.ncols) // In Case of a square matrix
    {
        matrixTrace( originalmat, &traceA); // Calling the function to get the trace of the square matrix
        printf("The trace of matrix %c is %d\n",originalmat.name,traceA); // Printing the Trace of the Matrix to the screen
    }
    else // In Case of non square matrices
    {
        printf("Trace only exists for non-square matrices\n"); // Printing that no Trace can be calculated
    }
    printf("Finding the determinant now!\n");
    matrixDeterminant( originalmat, &determat, &deter); // Calling the function to Extract a 2x2 submatrix and Calculate the determinant of the n x n matrices
    printf("\nThe determinant is %d for\n",deter); // Printing The determinant to the screen
    matrixDisplay(determat); // Printing the 2x2 submatrix to the screen
    printf("\n");
    if((originalmat).nrows== 1 && (originalmat).ncols==1)// If matrix is 1x1 no submatrix can be extracted
     {
         printf("The Matrix is 1x1,no submatrix can be extracted\n");
     }
     else
     {
         subMatrix( originalmat,&submat); // Calling the submatrix function that prompt the user to extract a submatrix from the original matrix
         matrixDisplay(submat); // Printing the submatrix to the screen
     }
    do
    {   // Calling the main again to make the program loop until the user decides to exit
        do
        {
        fflush(stdin); // to empty the buffer of the scanf
        printf("Would you like to input another matrix? (type 1 for yes or for 0 no) "); // Detecting the user choice to loop or not
        scanf("%d",&choice);
        }
        while((choice < 0) || (choice > 1));
        if(choice == 1)
        {
            matrixInput(&originalmat);
            matrixDisplay(originalmat);
            if(originalmat.nrows == originalmat.ncols)
            {
                matrixTrace( originalmat, &traceA);
                printf("The trace of matrix %c is %d\n\n",originalmat.name,traceA);
            }
            else
            {
                printf("Trace only exists for non-square matrices\n");
            }
            printf("Finding the determinant now!\n");
            matrixDeterminant( originalmat, &determat, &deter);
            printf("\nThe determinant is %d for\n",deter);
            matrixDisplay(determat);
            printf("\n");
            if((originalmat).nrows== 1 && (originalmat).ncols==1)
             {
                 printf("The Matrix is 1x1,no submatrix can be extracted\n");
             }
            else
            {
                 subMatrix( originalmat,&submat);
                 matrixDisplay(submat);
            }
        }
          else // If 0 exit the program
          {
           return ;
          }
    }
     while (1 <2 );

}

void matrixInput(struct matrix *mat)
{
    int rowindex,columnindex,length;// Declaring the row index and column index of the matrix the user wants to get from the file and the length of the user to make sure it's one chracter
    char string[20];
    FILE *fin ;
    fin = fopen("matrix.txt", "r"); // Opening the file
    do
    {
        fflush(stdin);// To remove the clear the buffer so the scanf just see the input
        printf("please enter a one character name for the  matrix e.g. A,B,etc: ");//Prompt the user to enter only one character as the name of the matrix
        scanf("%s",string);// scanning the input from the user
        printf("\n");
        length=strlen(string);// Getting the length of the input to check whether it's only one character
    }
    while( ((string[0])>'Z' && (string[0])<'a') || ((string[0])<'A') || ((string[0])>'z') || (length>1) );
     ((*mat).name)=string[0];// Equating the name of the matrix with the input string as it fits the criteria
    do
    {   // Scanning the Number of Rows
       fflush(stdin);
       printf("Enter # rows of the matrix(<10): \n");
       scanf("%d" ,&((*mat).nrows));
       printf("\n");
    }
    while(((*mat).nrows)<1 || ((*mat).nrows)>10 );// Checking the that the number of rows is within the range
    do // Scanning the Number of Columns
    {
       fflush(stdin);
       printf("Enter # columns of the matrix(<10): \n");// Checking the that the number of columns is within the range
       scanf("%d" ,&((*mat).ncols));
       printf("\n");

    }
    while(((*mat).ncols)<1 || ((*mat).ncols)>10);

      if (fin != NULL)//Checking if the file is existing
    {
         for(rowindex=0; rowindex<(*mat).nrows; rowindex++)
         {
                  for(columnindex=0; columnindex<(*mat).ncols; columnindex++)
                  {
                        fscanf(fin,"%d",&((*mat).mValues[rowindex][columnindex]));//Scanning the matrix row by row
                  }
         }

    }

      else
    {
            printf( "The file could not be opened - program aborting\n" );
    }

}
void matrixDisplay(struct matrix mat)// Defining the function that displays a matrix on the screen

{
    int rowindex,columnindex;// Declaring the row index and column index of the matrix the user wants to get from the file
    printf("Matrix %c:\n",(mat.name));
    for(rowindex=0; rowindex<mat.nrows; rowindex++)
    {
        printf("Row %d:\t\t",rowindex);
        for(columnindex=0; columnindex<mat.ncols; columnindex++)
        {
            printf("%d\t",mat.mValues[rowindex][columnindex]);
        }
        printf("\n");
    }

}
void matrixTrace(struct matrix mat, int *trace)
{// Getting the trace of a n x n matrix
    int rowindex;// Doesn't differ whether it's a row or column index
    *trace=0;
    for(rowindex=0; rowindex<mat.nrows; rowindex++)
    {
        *trace=*trace+ mat.mValues[rowindex][rowindex];// Trace is the sum of the diagonal elements
    }
}
void matrixDeterminant(struct matrix m1, struct matrix *m2, int *determinant)
{//Getting the Determinant of the matrix
    int rowindex,columnindex,startingrow,startingcol,length,x=0,y=0;
    char string[20];
    if((m1.nrows)>=2 && (m1.ncols)>=2)
    {
    (*m2).nrows=2;
    (*m2).ncols=2;
              do
              {
                    fflush(stdin);// To remove the clear the buffer so the scanf just see the input
                    printf("please enter a one character name for the  matrix e.g. A,B,etc: ");//Prompt the user to enter only one character as the name of the matrix
                    scanf("%s",string);// scanning the input from the user
                    printf("\n");
                    length=strlen(string);// Getting the length of the input to check whether it's only one character
              }
            while( ((string[0])>'Z' && (string[0])<'a') || ((string[0])<'A') || ((string[0])>'z') || (length>1) );
            ((*m2).name)=string[0];// Equating the name of the matrix with the input string as it fits the criteria
            do
            {
                 if(m1.nrows==2)
                {
                    printf("Starting row of the determinant matrix must be 0\n");
                    startingrow=0;
                }
                else
                {
                   printf("Enter row number where to start the 2x2 matrix,number needs to be between 0 and %d:\n",m1.nrows-2);
                   scanf("%d" ,&startingrow);
                   printf("\n");
                }
            }
            while(startingrow<0 || startingrow>(m1.nrows-2));

            do
            {
                if(m1.ncols==2)
                {
                    printf("Starting column of the determinant matrix must be 0\n");
                    startingcol=0;
                }
                else
                    {
               printf("Enter column number where to start the 2x2 matrix,number needs to be between 0 and %d:\n",m1.ncols-2);
               scanf("%d" ,&startingcol);
               printf("\n");
                    }

            }
            while(startingcol<0 || startingcol>(m1.ncols-2));

            for(rowindex=startingrow; rowindex<(startingrow+2) ; rowindex++,x++,y=y-2)//x,y are the row and column index of the 2x2 matrix , y must be reset to 0 for the second row
            {
                    for(columnindex=startingcol ;columnindex<(startingcol+2); columnindex++)
                    {
                        (*m2).mValues[x][y]=(m1).mValues[rowindex][columnindex] ;
                        y++;
                    }
            }

            *determinant = (*m2).mValues[0][0]*(*m2).mValues[1][1] - (*m2).mValues[1][0]*(*m2).mValues[0][1];//Normal formula for determinant
    }
    else {
            if((m1.nrows)== 1 && (m1.ncols)==1)//If the rows and columns are equal then the determinant is equal tot he element
            {
              do
              {
                    fflush(stdin);// To remove the clear the buffer so the scanf just see the input
                    printf("please enter a one character name for the  matrix e.g. A,B,etc: ");//Prompt the user to enter only one character as the name of the matrix
                    scanf("%s",string);// scanning the input from the user
                    printf("\n");
                    length=strlen(string);// Getting the length of the input to check whether it's only one character
              }
            while( ((string[0])>'Z' && (string[0])<'a') || ((string[0])<'A') || ((string[0])>'z') || (length>1) );
            ((*m2).name)=string[0];// Equating the name of the matrix with the input string as it fits the criteria

                    (*m2).nrows=1;
                    (*m2).ncols=1;
                 *determinant= m1.mValues[0][0] ;
                  printf("The determinant is the same as the element\n");
                  (*m2).mValues[0][0] = (m1).mValues[0][0] ;
            }
            else
                {
                    printf("No 2x2 submatrix can be extracted\n");
                }
         }
}

int selectingindex(int index ,int array[],int size)// Function to select the rows and the columns of the submatrix
{
    int i ,count=0;// i is a just a variable for counting the index whether it's row or column index
    for(i=0;i<size;i++)
    {
        if( index != array[i])//checking if the index is not equal to the elements of the array
        {
        count++;//Making sure that the index is not equal to all elements of the array as the count will be equal to the number of elements in the array
        }
    }
        return count ;

}

void subMatrix(struct matrix m1, struct matrix *m2)//Getting a submatrix from the original matrix
{
            int i,j,x,y,length,numdeletedrows,numdeletedcols;//i,j is a variable to index the number of rows and columns of the original matrix while x,y are the same of the submatrix
            char string [20] ;
            printf("Finding a submatrix now!\n");
            printf("Forming a submatrix of matrix %c...\n",m1.name);
            printf("how many rows do you want to delete? (must be between 1 and %d): ",m1.nrows);
            scanf("%d",&numdeletedrows);//Scanning the number of the deleted rows
            printf("\n");
            int deletedrow[numdeletedrows];//Setting the size of the matrix as the number of the number deleted rows
            printf("please enter ,one per row, the number(s) of the %d row(s) you wish to delete\n",numdeletedrows);
            for(i=0; i<(numdeletedrows); i++ )
            {
                printf("\tenter row number to delete (must be between 0 and %d):",(m1.nrows-1));
                scanf("%d",&deletedrow[i]);//Making an array with the number of the rows the user wants to delete
                printf("\n");

            }

            printf("how many columns do you want to delete? (must be between 1 and %d): ",m1.ncols);
            scanf("%d",&numdeletedcols);//Scanning the number of the deleted columns
            int deletedcol[numdeletedcols];//Setting the size of the matrix as the number of the number deleted columns
            printf("please enter ,one per row, the number(s) of the %d column(s) you wish to delete\n",numdeletedcols);
            for(j=0; j<(numdeletedcols); j++ )
            {
                printf("\tenter column number to delete (must be between 0 and %d):",(m1.ncols-1));
                scanf("%d",&deletedcol[j]);//Making an array with the number of the rows the user wants to delete
                printf("\n");
            }

                    (*m2).nrows =m1.nrows - numdeletedrows ;//Setting the number of rows of the submatrix
                    (*m2).ncols =m1.ncols - numdeletedcols ;//Setting the number of columns of the submatrix
              do
              {
                    fflush(stdin);// To remove the clear the buffer so the scanf just see the input
                    printf("please enter a one character name for the  matrix e.g. A,B,etc: ");//Prompt the user to enter only one character as the name of the matrix
                    scanf("%s",string);// scanning the input from the user
                    printf("\n");
                    length=strlen(string);// Getting the length of the input to check whether it's only one character
              }
            while( ((string[0])>'Z' && (string[0])<'a') || ((string[0])<'A') || ((string[0])>'z') || (length>1) );
            ((*m2).name)=string[0];// Equating the name of the matrix with the input string as it fits the criteria

            for(i=0,x=0; i<(m1.nrows) ; i++)
            {
                     if(selectingindex(i,deletedrow,numdeletedrows)== (numdeletedrows))
                        {
                                    for(j=0,y=0;j<(m1.ncols);j++)
                                       {
                                            if(selectingindex(j,deletedcol,numdeletedcols)== (numdeletedcols))

                                                {
                                                    (*m2).mValues[x][y] = (m1).mValues[i][j];
                                                    y++;
                                                }
                                       }
                                       x++;
                        }
            }//Checking whether the row and column is not chosen by the user and copying its elements to the submatrix

}
