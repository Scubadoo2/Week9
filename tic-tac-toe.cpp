/***********************************************************************
* Program:
*    Lesson 08, Tic-Tac-Toe
* Summary: 
*    This program reads, displays, and writes a Tic-Tac-Toe board
************************************************************************/

#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

#define X 'X'
#define O 'O'
#define B '.'
#define boardSize 3

bool read(         char board[][boardSize][boardSize], const char* fileName);
bool write(  const char board[][boardSize][boardSize], const char* fileName);
void display(const char board[][boardSize][boardSize]);
bool didWin( const char board[][boardSize][boardSize], char turn);

/**********************************************************************
 * Keeps the data and calles the read/display/write functions
 ***********************************************************************/
int main()
{
   char board[boardSize][boardSize][boardSize];

   // read the board
   char fileName[256];
   cout << "Enter source filename: ";
   cin  >> fileName;
   if (!read(board, fileName))
   {
      cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
      return 1;
   }

   // display the board
   display(board);

   // write the board to a file
   cout << "Enter destination filename: ";
   cin  >> fileName;
   if (!write(board, fileName))
   {
      cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
      return 1;
   }

   return 0;
}

/**************************************************************
 * READ
 * Read the board from the specified filename
 *************************************************************/
bool read(char board[][boardSize][boardSize], const char* fileName)
{
   assert(*fileName);

   // open the file
   ifstream fin(fileName);
   if (fin.fail())
      return false;

   // read 9 symbols, hopefully they are . X O
   for (int z = 0; z < boardSize; z++)
      for (int r = 0; r < boardSize; r++)
         for (int c = 0; c < boardSize; c++)
         {
            fin >> board[z][r][c];
            assert(!fin.fail());
            assert(board[z][r][c] == X ||
                  board[z][r][c] == O ||
                  board[z][r][c] == B);
         }
   // close the file
   fin.close();
   return true;
}

/**********************************************************
 * WRITE
 * Write to fileName the board data
 *********************************************************/
bool write(const char board[][boardSize][boardSize], const char* fileName)
{
   assert(fileName[0] != '\0');

   // open the file
   ofstream fout(fileName);
   if (fout.fail())
      return false;

   // write my 9 symbols
   for (int z = 0; z < boardSize; z++)
      for (int r = 0; r < boardSize; r++)
         for (int c = 0; c < boardSize; c++)
            fout << board[z][r][c] << (c == (boardSize - 1) ? '\n' : ' ');

   // close it!
   fout.close();
   cout << "File written\n";
   return true;
}

/*******************************************************
 * DISPLAY
 * Display the contents the the screen
 *****************************************************/
void display(const char board[][boardSize][boardSize])
{
   //Display each layer
   for(int d=0; d < boardSize; d++){
      cout << "Level " << d+1 << endl;

      // loop through each row
      for (int r = 0; r < boardSize; r++)
      {
         // only the first row is not preceeded with the --+-- magic
         if (r != 0)
            cout << "---+---+---\n";

         // now, on each row, do the column stuff
         for (int c = 0; c < boardSize; c++)
         {
            // display a space for the dot
            if (board[d][r][c] == B)
               cout << "   ";
            else
               cout << " " << board[d][r][c] << " ";

            // end with a | or a newline
            cout << (c == (boardSize - 1) ? '\n' : '|');
         }
      }
      
      //A gap in between
      cout << endl;

   }

   // display who won
   if (didWin(board, X))
      cout << "X won!\n";
   if (didWin(board, O))
      cout << "O won!\n";
   
   return;
}

/********************************************
 * DID WIN
 * Did a given player (determined by the "turn"
 * variable) win the game?
 *******************************************/
bool didWin(const char board[][boardSize][boardSize], char turn)
{
   
   bool isGood = true;
   // check layer by layer (treat as 2d tic-tac-toe games)
   for (int z = 0; z < boardSize; z++){
      // check columns for each layer
      for (int r = 0; r < boardSize; r++){
         isGood = true;
         for (int i = 0; i < boardSize; i++){
            if (board[z][r][i] != turn){
               isGood = false;
               break;
            }
         }
         if (isGood)
            return true;
      }
      // check rows
      for (int c = 0; c < boardSize; c++){
         isGood = true;
         for (int i = 0; i < boardSize; i++){
            if (board[z][i][c] != turn){
               isGood = false;
               break;
            }
         }
         if (isGood)
            return true;
      }
      // Diagnal left
      isGood = true;
      for(int i=0; i < boardSize; i++){
         if(board[z][i][i] != turn){
            isGood = false;
            break;
         }
      }
      if(isGood){
         return true;
      }
      // Diagnal right
      isGood = true;
      for(int i=0; i < boardSize; i++){
         if(board[z][i][(boardSize - 1) - i] != turn){
            isGood = false;
            break;
         }
      }
      if(isGood){
         return true;
      }
   }  
   
   // check z-axis columns
   for (int r = 0; r < boardSize; r++){
      for (int c = 0; c < boardSize; c++){
         isGood = true;
         for (int i = 0; i < boardSize; i++){
            if (board[i][r][c] != turn){
               isGood = false;
               break;
            }
         }
         if (isGood)
            return true;
         isGood = true;
         for (int i = 0; i < boardSize; i++)
            if (board[i][i][c] != turn){
               isGood = false;
               break;
            }
         if (isGood)
            return true;
         isGood = true;
         for (int i = 0; i < boardSize; i++)
            if (board[i][r][i] != turn){
               isGood = false;
               break;
            }
         if (isGood)
            return true;
      }
   }

   //Diagnals along the center
   //Top right
   isGood = true;
   for(int i = 0; i < boardSize; i++){
      if(board[i][i][i] != turn){
         isGood = false;
         break;
      }
   }
   if(isGood){
      return true;
   }
   
   //Top left
   isGood = true;
   for(int i = 0; i < boardSize; i++){
      if(board[i][i][(boardSize-1) - i] != turn){
         isGood = false;
         break;
      }
   }
   if(isGood){
      return true;
   }
   
   //Bottom right
   isGood = true;
   for(int i = 0; i < boardSize; i++){
      if(board[i][(boardSize-1) - i][i] != turn){
         isGood = false;
         break;
      }
   }
   if(isGood){
      return true;
   }
   
   //Bottom left
   isGood = true;
   for(int i = 0; i < boardSize; i++){
      if(board[i][(boardSize-1) - i][(boardSize-1) - i] != turn){
         isGood = false;
         break;
      }
   }
   if(isGood){
      return true;
   }
   
   
   return false;
}
