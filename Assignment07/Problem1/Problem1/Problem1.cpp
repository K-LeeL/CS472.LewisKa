// Assignment 07: Backtracking and Helping Your Favorite Aunt
// Due : Wed Apr 10 , 2024 11 : 59pm
// Kaylee Lewis

// Problem 1: There are n coins placed in a row. The goal is to form n/2 pairs of them by a sequence of
// moves On each move a single coin can jump right or left over two coins adjacent to it ( i.e. , over either
// two single coins or one previously formed pair ) to land on the next single coin; no triples are allowed.
// Any empty space between adjacent coins is ignored.Determine all the values of n for which the puzzle
// has a solution and devise an algorithm that solves the puzzle in the minimum number of moves for
// any even value of n.
// You may use backtracking to find the minimum number of coins for which the problem has a solution.
// Note that the problem statement automatically rejects any odd value of n.
//
// www.geeksforgeeks.org/coin-puzzle-find-minimum-number-of-coins
// Algorithmic Puzzles By Anany Levitin , Maria Levitin
// https://www.youtube.com/watch?v=NNcN5X1wsaw
// https://www.youtube.com/watch?v=hhVNvi_M-dA

#include <iostream>
#include <vector>

// Function to solve the puzzle
std::vector<int> solvePuzzle ( int n , std::vector<std::vector<int>> &moves )
{
     // Check if n is a multiple of 4
     if ( n % 4 != 0 )
     {
          // If not, print a message indicating no solution exists
          std::cout << "No solution exists for n = " << n << ". Please provide an even number that is a multiple of 4." << std::endl;
          return {};
     }

     // Initialize a vector representing the initial state of the puzzle
     std::vector<int> puzzle;
     for ( int i = 1; i <= n; ++i )
     {
          puzzle.push_back ( i );
     }

     // Store the original arrangement of coins
     moves.push_back ( puzzle );

     // Perform the first set of operations
     for ( int i = 1; i < n / 4; ++i )
     {
          // Find the rightmost single coin
          int rightmostSingle = puzzle.back ( );
          puzzle.pop_back ( );

          // Find the coin to its left with i coins between them
          int targetIndex = puzzle.size ( ) - i;
          puzzle.insert ( puzzle.begin ( ) + targetIndex , rightmostSingle );

          // Store the current arrangement of coins after the move
          moves.push_back ( puzzle );
     }

     // Perform the second set of operations
     for ( int i = n / 4; i < n / 2; ++i )
     {
          // Find the leftmost single coin
          int leftmostSingle = puzzle.front ( );
          puzzle.erase ( puzzle.begin ( ) );

          // Jump it over i coins to the right
          int targetIndex = n / 2 + i - 1;
          puzzle.insert ( puzzle.begin ( ) + targetIndex , leftmostSingle );

          // Store the current arrangement of coins after the move
          moves.push_back ( puzzle );
     }

     return puzzle;
}

int main ( )
{
     int n = 8;
     std::vector<std::vector<int>> moves;

     // Solve the puzzle for the given value of n
     std::vector<int> solution = solvePuzzle ( n , moves );
     if ( !solution.empty ( ) )
     {
          // If a solution exists, print the original arrangement of coins
          std::cout << "Original arrangement of coins: ";
          for ( int coin : moves.front ( ) )
          {
               std::cout << coin << " ";
          }
          std::cout << std::endl;

          // Print each move made during the puzzle solving process
          for ( size_t i = 1; i < moves.size ( ); ++i )
          {
               std::cout << "Move " << i << ": ";
               for ( int coin : moves [ i - 1 ] )
               {
                    std::cout << coin << " ";
               }
               std::cout << " -> ";
               for ( int coin : moves [ i ] )
               {
                    std::cout << coin << " ";
               }
               std::cout << std::endl;
          }

          // Print the final arrangement of coins
          std::cout << "Final arrangement of coins: ";
          for ( int coin : solution )
          {
               std::cout << coin << " ";
          }
          std::cout << std::endl;
     }
     return 0;
}