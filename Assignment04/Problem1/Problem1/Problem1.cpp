// Assignment 04: Divide and Conquer
// Due: Wed Feb 28, 2024 11:59pm
// Problem 1:
//   A problem that unexpectedly ties back to a binary tree:
//        Mr. Wonka gives you a n × m chocolate bar that he wants to break into n ∗ m 1 × 1 pieces.
//        A bar can only be broken on a straight line and only one bar can be broken at a time.
//        Design an algorithm that solves this problem with a minimum number of bar breaks and
//        explain why properties of a binary tree explains why this is the minimum number.
//
// https://www.geeksforgeeks.org/divide-and-conquer/

#include <iostream>
#include <algorithm>

// Function to break the chocolate bar into 1x1 pieces
void breakChocolate ( int n , int m )
{
     std::cout << "Breaking the chocolate into 1x1 pieces:" << std::endl;

     // Determine whether to prioritize breaking along rows or columns
     if ( n <= m )
     {
          // Break along rows
          for ( int i = 0; i < n; ++i )
          {
               for ( int j = 0; j < m; ++j )
               {
                    std::cout << "(" << i << ", " << j << ") ";
               }
               std::cout << std::endl;
          }
     } else
     {
          // Break along columns
          for ( int j = 0; j < m; ++j )
          {
               for ( int i = 0; i < n; ++i )
               {
                    std::cout << "(" << i << ", " << j << ") ";
               }
               std::cout << std::endl;
          }
     }
}

int main ( )
{
     int n , m;
     std::cout << "Enter the dimensions of the chocolate bar with the number of rows and columns seperated by a space: ";
     std::cin >> n >> m;

     breakChocolate ( n , m );

     return 0;
}

// The code asks the user to enter the dimensions of the chocolate bar.
// It then breaks the chocolate bar into 1x1 pieces by going through each row and column.
// Then it finally prints out the coordinates of each piece.
// The algorithm breaks on the shortest dimension to make the fewest breaks needed.
// Since each piece is broken in half the piece then becomes too small to break again.
// This is similar to a binary tree where each node has two children.