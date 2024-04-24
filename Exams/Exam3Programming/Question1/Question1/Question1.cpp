// Exam 3 - Programming
// Started: Apr 24 at 5 : 46pm
// Kaylee Lewis
// Question 1: We know from our study of the sorting problem that any algorithm that sorts only by comparison of keys can achieve a time efficiency no better than O ( n *log ( n ) ).
// But the problem statement proceeds upon the assumption of no knowledge about the structure of keys other than the act of comparing the two keys.

// Consider the following algorithm for sorting a list of integers.
     // Define a set of ten sublists.
     // Inspect the digits of each number from right to left
     // Place a key into the pile that corresponds to the current digit
     // On each pass , if there are two keys to be placed in same pile , always place the key coming from the leftmost pile in the previous pass to the left of the other key
     // Traverse the list of lists in sequential order , appending each item into a list for the next pass
//

#include <iostream>
#include <vector>
#include <list>

// Function to sort a list of integers using the Radix Sort algorithm
void radixSort ( std::vector<int> &numbers )
{
     // Define ten sublists for each digit (0 to 9)
     std::list<int> sublists [ 10 ];

     // Find the maximum number of digits in the given numbers
     int maxDigits = 0;
     for ( int number : numbers )
     {
          int digits = 0;
          while ( number > 0 )
          {
               number /= 10;
               digits++;
          }
          maxDigits = std::max ( maxDigits , digits );
     }

     // Iterate over each digit position, starting from the rightmost (least significant)
     for ( int digitPosition = 0; digitPosition < maxDigits; digitPosition++ )
     {
          // Distribute numbers into sublists based on the current digit
          for ( int number : numbers )
          {
               int currentDigit = ( number / static_cast< int >( pow ( 10 , digitPosition ) ) ) % 10;
               sublists [ currentDigit ].push_back ( number );
          }

          // Reconstruct the numbers list by appending numbers from the sublists
          int index = 0;
          for ( int i = 0; i < 10; i++ )
          {
               for ( int number : sublists [ i ] )
               {
                    numbers [ index++ ] = number;
               }
               sublists [ i ].clear ( ); 
          }
     }
}

int main ( )
{
     std::vector<int> numbers = { 110, 4, 75, 55, 8, 31, 2, 6 };

     std::cout << "Original Array: ";
     for ( int number : numbers )
     {
          std::cout << number << " ";
     }
     std::cout << std::endl;

     radixSort ( numbers );

     std::cout << "Sorted Array: ";
     for ( int number : numbers )
     {
          std::cout << number << " ";
     }
     std::cout << std::endl;

     return 0;
}