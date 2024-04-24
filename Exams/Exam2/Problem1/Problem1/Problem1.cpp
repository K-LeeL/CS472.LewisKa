// Exam 2: Programming
// Started: Mar 20 at 6:15pm
// Kaylee Lewis

// Problem 1:   
// You  have the opportunity to assist Wonka in solving a clean-up problem in one of his warehouses.  
// An Oompa-Loompa tripped and spilled a pallet of chocolate coins onto the floor of an empty warehouse.   
// Wonka asks you to design and implement an algorithm so that an Ooompa-Loompa robot can be programmed to 
// clean up the coins.
// The floor tiles in the warehouse form an n by m grid with no more than one chocolate coin on each floor tile. 
// The robotic Ooompa-Loompa starts in the upper left floor tile and told to collect as many coins as possible and 
// bring them to the bottom right cell of the grid.   
// At any point in time, the robot can only move one tile to the right or one tile down from its current location. 
// If the robotic Oompa-Loompa always picks up a coin if it finds one on a tile, design and implement an algorithm 
// that will find the path that the robotic Oompa-Loompa needs to take to find the largest number of the chocolate 
// coins.
// If F (i, j) is the largest number of coins the robot can collect and bring to tile and assuming no adjacent tiles 
// above the first row, and to the left of the first column,  then given that ci,j is the value of the coin at tile 
// (i,j), then:
//      F(0, j) = 0, ∀1 ≤ j ≤ m
//      F(i, 0) = 0, ∀1 ≤ i ≤ n
//      F (i, j) = (max F(i-l, j), F(i, j-1)) + ci,j, ∀1 ≤ i ≤ n and ∀1 ≤ j ≤ m 
// Given an input of an array C[0...n-1, 0...m-1]
// when entries equal to 1 when a coin is on that floor tile or 0 other wise,  design and implement a dynamic 
// programming solution to Wonka's problem and provide an analysis of the O(n) of your algorithm.

// https://leetcode.com/problems/minimum-path-sum/
// https://www.geeksforgeeks.org/maximum-path-sum-matrix/
// https://www.geeksforgeeks.org/count-possible-paths-top-left-bottom-right-nxm-matrix/

#include <iostream>
#include <vector>
#include <algorithm>

// Function to find the maximum number of coins collected
int maxCoins ( std::vector<std::vector<int>> &floorGrid )
{
     // Get the number of rows and columns in the grid
     int numRows = floorGrid.size ( );
     if ( numRows == 0 ) return 0;
     int numColumns = floorGrid [ 0 ].size ( );

     // Create a table to store the maximum number of coins
     std::vector<std::vector<int>> maxCoins ( numRows , std::vector<int> ( numColumns , 0 ) );

     // Initialize the first row and first column
     for ( int i = 0; i < numRows; ++i )
     {
          // Initialize the first column
          for ( int j = 0; j < numColumns; ++j )
          {
               // Update the DP table
               if ( i == 0 && j == 0 )
               {
                    maxCoins [ i ] [ j ] = floorGrid [ i ] [ j ];
               } else if ( i == 0 )
               {
                    maxCoins [ i ] [ j ] = maxCoins [ i ] [ j - 1 ] + floorGrid [ i ] [ j ];
               } else if ( j == 0 )
               {
                    maxCoins [ i ] [ j ] = maxCoins [ i - 1 ] [ j ] + floorGrid [ i ] [ j ];
               } else
               {
                    maxCoins [ i ] [ j ] = std::max ( maxCoins [ i - 1 ] [ j ] , maxCoins [ i ] [ j - 1 ] ) + floorGrid [ i ] [ j ];
               }
          }
     }

     // Return the maximum number of coins collected at the bottom right corner
     return maxCoins [ numRows - 1 ] [ numColumns - 1 ];
}

int main ( )
{
     // Testing the function with a sample grid
     std::vector<std::vector<int>> floorGrid =
     {
         {0, 1, 0, 0},
         {0, 0, 1, 0},
         {1, 1, 0, 1},
         {0, 0, 0, 1}
     };

     std::cout << "The maximum number of coins that were collected is: " << maxCoins ( floorGrid ) << std::endl;

     return 0;
}

// Analysis of the O(n) of the algorithm:
// The table requires visiting each cell once so the time complexity of the algorithm is O(n*m) (n is the number of
// rows and m is the number of columns of the table)
// The best and worst case time complexity is O(n x m).if n=m, it becomes O(n^2)
