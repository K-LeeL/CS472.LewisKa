// Assignment 02: Battling Big-Oh
// Due: Wed Jan 31 , 2024 11 : 59pmDue : Wed Jan 31 , 2024 11 : 59pm
// Kaylee Lewis
// Q1:  Using the algorithm given:
//   What value is returned by this algorithm, expressed as function of n?
//   What is the 0(n) of this algorithm? Justify your answer.

//  https://www.geeksforgeeks.org/analysis-algorithms-big-o-analysis/

// What is the value returned by this algorithm, expressed as a function of n?
     // The value returned by this algorithm is the number of times the inner loop runs.
     // The inner loop runs i + j times, so the value returned by this algorithm is the sum
     //   of the first i natural numbers.
     // (n*(n+1)*(n+2))/2 is the value returned by this algorithm, expressed as a function of n.

//   What is the 0(n) of this algorithm? Justify your answer.
     // The outer loop runs n times, O(n), the middle loop runs i times, O(n^2), and the inner
     //   loop runs i + j times, O(n^3).
     // So the O(n) of this algorithm is O(n^3).

#include <iostream>

// FunkyIndexes algorithm
//  This algorithm is O(n^3)
int algorithm ( int n )
{
     // r is the result, O(1)
     int r = 0; 

     // The outer loop runs n times, O(n)
     for ( int i = 1; i <= n; ++i ) 
     {
          // The middle loop runs i times O(n^2)
          for ( int j = 1; j <= i; ++j )
          {
               // The inner loop runs i + j times, O(n^3)
               for ( int k = j; k <= i + j; ++k )
               {
                    // r is incremented by 1
                    r += 1; 
                    
               }
          }
     }

     //  The result is returned
     return r;
}

int main ( )
{
     // Example with n = 5
     int n = 5;
     int const result = algorithm ( n );

     // Print the result 
     std::cout << "The result for n = " << n << " is: " << result << std::endl;

     return 0;
}