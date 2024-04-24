// Exam 2: Programming
// Started: Mar 20 at 6:15pm
// Kaylee Lewis

// Problem 2:
// A kitchen counter is made of fancy tiles is divided into three rows and n columns.
// We have boxes of red , white , and blue tiles , each with n tiles in the box.
// We to arrange the tiles so that we have tiles of each of the three colors in every column.
// The only thing you can so swap tiles in the same row.
//
// Note how this is a decrease - and -conquer problem , as the solution is trivial if there is one column.
// Going forward , we rearrange the counters so that the three counters are three different colors ,
// and repeating this process for boards of decreasing size

// https://www.geeksforgeeks.org/tiling-problem-using-divide-and-conquer-algorithm/

#include <iostream>
#include <vector>

#include <iostream>
#include <vector>

// Function to swap tiles in the same row
void swapTiles ( std::vector<std::vector<char>> &counter , int row , int col1 , int col2 )
{
     char temp = counter [ row ] [ col1 ];
     counter [ row ] [ col1 ] = counter [ row ] [ col2 ];
     counter [ row ] [ col2 ] = temp;
}

// Function to check the validity of the counter
bool isValid ( const std::vector<std::vector<char>> &counter , int n )
{
     // Count the number of tiles of each color
     int redCount = 0 , whiteCount = 0 , blueCount = 0;
     for ( int row = 0; row < 3; ++row )
     {
          for ( int col = 0; col < n; ++col )
          {
               if ( counter [ row ] [ col ] == 'R' )
                    redCount++;
               else if ( counter [ row ] [ col ] == 'W' )
                    whiteCount++;
               else if ( counter [ row ] [ col ] == 'B' )
                    blueCount++;
          }
     }
     // Check if each color has an equal representation overall
     return redCount == whiteCount && whiteCount == blueCount;
}

// Recursive function to rearrange the counter
bool rearrangeCounter ( std::vector<std::vector<char>> &counter , int n , int col )
{
     // if all columns are arranged, check if the arrangement is valid
     if ( col == n )
     {
          return isValid ( counter , n );
     }

     //  Try all possible swaps in the current column
     for ( int i = 0; i < 3; ++i )
     {
          for ( int j = i + 1; j < 3; ++j )
          {
               // Swap tiles in the same row
               swapTiles ( counter , i , col , j );

               // Recur for the next column
               if ( rearrangeCounter ( counter , n , col + 1 ) )
               {
                    return true; // If a valid arrangement is found, return true
               }

               // Undo the swap to backtrack
               swapTiles ( counter , i , col , j );
          }
     }

     // If no valid arrangement is found for this column, return false
     return false;
}

// Function to fill the counter with tiles of each color
void fillCounter ( std::vector<std::vector<char>> &counter , int n )
{
     for ( int i = 0; i < 3; ++i )
     {
          for ( int j = 0; j < n; ++j )
          {
               counter [ i ] [ j ] = ( i == 0 ) ? 'R' : ( ( i == 1 ) ? 'W' : 'B' );
          }
     }
}

// Function to print the counter
void printCounter ( const std::vector<std::vector<char>> &counter , int n )
{
     for ( int i = 0; i < 3; ++i )
     {
          for ( int j = 0; j < n; ++j )
          {
               std::cout << counter [ i ] [ j ] << " ";
          }
          std::cout << std::endl;
     }
}

// Function to handle the main logic
void handleCounter ( int n )
{
     // Create the counter
     std::vector<std::vector<char>> counter ( 3 , std::vector<char> ( n ) );

     // Fill the counter with tiles of each color
     fillCounter ( counter , n );

     // Rearrange the counter
     if ( rearrangeCounter ( counter , n , 0 ) )
     {
          std::cout << "Valid arrangement found:" << std::endl;
          // Print the counter
          printCounter ( counter , n );
     } else
     {
          std::cout << "No valid arrangement possible." << std::endl;
     }
}

// Main function
int main ( )
{
     int n;
     std::cout << "Enter the number of columns: ";
     std::cin >> n;

     // Check if the number of columns is divisible by 3
     if ( n % 3 != 0 )
     {
          std::cout << "Number of columns must be divisible by 3." << std::endl;
          return 1;
     }

     // Handle the counter
     handleCounter ( n );

     return 0;
}