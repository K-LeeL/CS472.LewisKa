// Assignment 04: Divide and Conquer
// Due: Wed Feb 28, 2024 11:59pm
// Problem 2:
// Mr. Wonka has another problem:
// His version of the LifeSavers candy (those round pieces of hard candy sold in a cylinder) comes in three colors :
// red , white , and blue.
// The problem :
// he wants them placed in the cylinder with red candy first , then white candies , and then blue candies.
// Design and implement ( in your favorite programming language ) an algorithm that runs in linear time that,
// given an input string containing the characters ’r’ , ’w’ , and ’b’ in some random order, returns a new string
// with the characters arranged in the correct order.
//
// www.geeksforgeeks.org/sort-an-array-of-0s-1s-and-2s/

#include <iostream>
#include <string>

std::string arrangeCandies ( std::string candies )
{
     int left = 0; 
     int right = candies.size ( ) - 1; 

     // Move all the red candies to the left
     for ( int i = 0; i <= right;)
     {
          // If the current candy is red, swap it with the candy to the left
          if ( candies [ i ] == 'r' )
          {
               // Swap the current candy with the candy to the left
               std::swap ( candies [ i ] , candies [ left ] );
               left++;
               i++;

               // If the current candy is white, do nothing
          } else if ( candies [ i ] == 'b' )
          {
               // Swap the current candy with the candy to the right
               std::swap ( candies [ i ] , candies [ right ] );
               right--;

               // If the current candy is blue, move to the next candy
          } else
          {
               i++;
          }
     }

     return candies;
}

int main ( )
{
     std::string candies;
     std::cout << "Enter a random order of candies (use 'r' for red, 'w' for white, and 'b' for blue): ";
     std::cin >> candies;

     std::string arrangedCandies = arrangeCandies ( candies );
    std::cout << "Arranged candies: " << arrangedCandies << std::endl;

     return 0;
}