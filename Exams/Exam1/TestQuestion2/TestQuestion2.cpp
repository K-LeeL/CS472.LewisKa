// Exam 1 Question 2
// Kaylee Lewis

// The general statement of the closet pair algorithm is given a list of pairs of objects
// and a distance function that gives you a double that is the "distance" between those
// two objects.
// Implement this algorithm as a function in your favorite programming language
// ( remember you have pass in a list of objects and a function ).
// Then provide implementations of distance functions for Euclidian distance
// ( sqrt of the sum of squares of components ) and Hamming distance
// ( number of bit positions that differ between two bit strings ).

// www.geeksforgeeks.org/closest-pair-of-points-using-divide-and-conquer-algorithm/
// www.geeksforgeeks.org/closest-pair-of-points-onlogn-implementation/

#include <iostream>
#include <vector>
#include <cmath>

// Define a structure to represent a pair of objects
struct Pair
{
     // Coordinates of the objects
     int x , y; 
};

// Function to calculate Euclidean distance between two pairs of objects
double euclideanDistance ( const Pair &p1 , const Pair &p2 )
{
     return sqrt ( pow ( p1.x - p2.x , 2 ) + pow ( p1.y - p2.y , 2 ) );
}

// Function to calculate Hamming distance between two pairs of objects
double hammingDistance ( const Pair &p1 , const Pair &p2 )
{
     // Assuming both pairs have same number of bits
     int distance = 0;
     int temp = p1.x ^ p2.x;
     while ( temp )
     {
          distance += temp & 1;
          temp >>= 1;
     }
     temp = p1.y ^ p2.y;
     while ( temp )
     {
          distance += temp & 1;
          temp >>= 1;
     }
     return distance;
}

// Function to find the distance between the two closest points
double closestPairDistance ( const std::vector<Pair> &pairs , double ( *distanceFunction )( const Pair & , const Pair & ) )
{
     // Initialize minDist to infinity
     double minDist = std::numeric_limits<double>::infinity ( ); 
     int n = pairs.size ( );

     for ( int i = 0; i < n - 1; ++i )
     {
          for ( int j = i + 1; j < n; ++j )
          {
               // Calculate distance using the provided function
               double dist = distanceFunction ( pairs [ i ] , pairs [ j ] );

               // Update minDist if necessary
               minDist = std::min ( minDist , dist ); 
          }
     }

     return minDist;
}

int main ( )
{
     // Example usage
     std::vector<Pair> pairs = { {1, 2}, {3, 4}, {5, 6}, {7, 8} }; 

     // Print the pairs
     std::cout << "Pairs:" << std::endl;
     for ( const auto &pair : pairs )
     {
          std::cout << "(" << pair.x << ", " << pair.y << ")" << std::endl;
     }


     double euclideanDist = closestPairDistance ( pairs , euclideanDistance );
     double hammingDist = closestPairDistance ( pairs , hammingDistance );

     std::cout << "Closest pair distance (Euclidean): " << euclideanDist << std::endl;
     std::cout << "Closest pair distance (Hamming): " << hammingDist << std::endl;

     return 0;
}
