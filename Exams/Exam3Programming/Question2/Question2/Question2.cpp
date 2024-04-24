// Exam 3 - Programming
// Started: Apr 24 at 5 : 46pm
// Kaylee Lewis
//
// Question 2: Primality testing is a important task in cryptography.
// Due to the computational complexity of such tasks, we often find ourselves dealing with approximation
// algorithms that tells that a number is composite or maybe prime.
//
// Implement the following algorithm for determining if a number is a composite number :
//
     // Let n be the number under test.
     // Check successive integers from 2 to
     // 
     // as possible divisors of n
     // If the divisor being checked divides n evenly , return true
     // Return false as no divisor divided n evenly
// 
// Note the tendency is to think this algorithm is O ( n ) but the number in test is not an correct measure
// of problem size. Rather it is the number of bits in the binary expansion of n.
//

#include <iostream>

// Function to test if a number is composite
bool isComposite ( int n )
{
     // 1 and negative numbers are not considered composite
     if ( n <= 1 ) return false;

     // Check for factors from 2 to n/2
     for ( int i = 2; i <= n / 2; ++i )
     {
          // If n is divisible by i, then n is composite
          if ( n % i == 0 )
          {
               // n is composite
               return true; 
          }
     }

     // n is prime
     return false; 
}

int main ( )
{
     int n;

     std::cout << "Enter a number to test for primality: ";
     std::cin >> n;

     // Test if n is composite
     if ( isComposite ( n ) )
     {
          std::cout << n << " is composite." << std::endl;
     } else
     {
          std::cout << n << " is prime." << std::endl;
     }

     return 0;
}

// Explain why that means this algorithm is an exponential algorithm and thus not a member of the complexity
// class P.
// HINT : Given an integer, how do we determine how many binary bits will be in that integers binary
// representation ?

// The algorithm has a time complexity of O(n) when considering 'n' as the number under test.
// If the number of bits 'k' is the size of the problem then the complexity becomes O(2^k).
// This is because 'n' is proportional to 2^k. This algorithm is exponential in 'k'.
// An algorithm is in the complexity class P if it can be solved by polynomial time in terms
// of the size of the input. Since this algorithm is exponential in terms of the size of the input
// (the number of bits), it is not in P.