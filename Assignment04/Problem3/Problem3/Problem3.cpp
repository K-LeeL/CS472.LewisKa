// Assignment 04: Divide and Conquer
// Due: Wed Feb 28, 2024 11:59pm
// Problem 3:
// At some time in our life, we are introduced to the game of dominoes.
// The term “domino” comes from the fact that the playing piece in the game has only two cells.
// Consider the next level of tromino :
// a playing piece that can contain three possible cells.
// Ignoring rotations and reflections, there are only two possible shapes a tromino can take :
//   an “I” shape and an “L” shape.
// Consider the following tiling problem :
// we have a game board that is an n by n array of unit squares wheremn ≥ 4 and is some positive power of 2.
// There is one randomly selected square that is a forbidden square;
// i.e. , no tromino can be placed in that square.
// Write a program that will output a tiling of the array that satisfies the following conditions:
//   • Every unit square other than the forbidden square is covered by a tromnio.
//   • No tromnio covers the forbidden square.
//   • No two tromnios overlap.
//   • No tromnio extends beyond the board.
// Write a program in your favorite programming language that solves this tiling problem
// Hint: Write the algorithm before you start trying to sling code

//Algorithm:
// Input:
// Ask for the size of the board as n ( has to be divisible by 2 and greater than or equal to 4 ).
// Ask for the coordinates of the forbidden square ( x , y ).
// 
// Create the Board :
// Create a n x n 2D array to represent the board.
// Mark the forbidden square
// 
// Tiling Function :
// Define a recursive function tileBoard ( the board , n , x , y , forbidden X , and forbidden Y ) to tile the board.
//         The base case is:
//              If n == 2 , place a tromino to cover the remaining area except for the forbidden square.
//                   Return.
//                   Recursive Case :
//              Divide the board into four quadrants.
//                   For each quadrant :
//              If the quadrant doesn't contain the forbidden square:
//                   Recursively tile that quadrant.
//                   Increment the tromino number for each recursive call.
// 
//              Print the completed tiling of the board.

// www.geeksforgeeks.org/tiling-problem-using-divide-and-conquer-algorithm/
// https://www.codingninjas.com/studio/library/tiling-problem-using-divide-and-conquer-algorithm
// https://www3.cs.stonybrook.edu/~rezaul/Fall-2017/CSE548/CSE548-lecture-2.pdf

#include <iostream>
#include <vector>

// Function to print the board
void printBoard ( std::vector<std::vector<int>> &board , int n )
{
     // Loop through the rows
     for ( int i = 0; i < n; i++ ) 
     {
          // Loop through the columns
          for ( int j = 0; j < n; j++ )
          {
               // Forbidden square
               if ( board [ i ] [ j ] == -1 )
                    // Print X for forbidden square
                    std::cout << "X ";
               else
                    // Print the value of the square
                    std::cout << board [ i ] [ j ] << " ";
          }
          std::cout << std::endl;
     }
}

// Function to tile the board
void tileBoard ( std::vector<std::vector<int>> &board , int n , int x , int y , int forbiddenX , int forbiddenY )
{
     if ( n == 2 )
     {
          int tromino = 1;

          // Loop through the rows
          for ( int i = x; i < x + n; i++ )
          {
               // Loop through the columns
               for ( int j = y; j < y + n; j++ )
               {
                    // If the square is the forbidden square
                    if ( i == forbiddenX && j == forbiddenY )
                         continue;
                    // Tile the board
                    board [ i ] [ j ] = tromino;
               }
          }
          return;
     }

     int tromino = 1;

     // Loop through the rows
     for ( int i = x; i < x + n; i += n / 2 )
     {
          // Loop through the columns
          for ( int j = y; j < y + n; j += n / 2 )
          {
               // If the forbidden square is in the first quadrant
               if ( !( i <= forbiddenX && forbiddenX < i + n / 2 && j <= forbiddenY && forbiddenY < j + n / 2 ) )
               {
                    // Tile the board
                    tileBoard ( board , n / 2 , i , j , i + n / 2 - 1 , j + n / 2 - 1 );
               }
               // If the forbidden square is in the second quadrant
               tromino++;
          }
     }
}

int main ( )
{
     int n , forbiddenX , forbiddenY;

     // Get the dimensions
     std::cout << "Enter the size of the board (n): ";
     std::cin >> n;
     std::cout << "Enter the coordinates of the forbidden square (x y): ";
     std::cin >> forbiddenX >> forbiddenY;

     // Create the board
     std::vector<std::vector<int>> board ( n , std::vector<int> ( n , 0 ) );

     // Mark forbidden square
     board [ forbiddenX ] [ forbiddenY ] = -1;

     // Tile the board
     tileBoard ( board , n , 0 , 0 , forbiddenX , forbiddenY );

     // Print the board
     printBoard ( board , n );

     return 0;
}
