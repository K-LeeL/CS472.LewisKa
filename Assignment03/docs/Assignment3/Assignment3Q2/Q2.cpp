// Assignment 03: Brute Force Ecology
// Due: Wed Feb 7 , 2024 11 : 59pm
//  Kaylee Lewis

// Problem 2: Assume that we have a tagged population that is living in an area upon which we overlay a 1000 by
// 1000 meter grid. Write a program that reads a collection of observations from a data file ( stored as x - y
// points , one per line , you will need to write a simple program that randomly generates one of these files )
// and determines the home range of the population by reporting the list of points that form the convex
// hull of the observation locations. Use the function from the previous question to find the convex hull.

// https://www.geeksforgeeks.org/convex-hull-using-divide-and-conquer-algorithm/#
// https://www.geeksforgeeks.org/convex-hull-set-1-jarviss-algorithm-or-wrapping/
// https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

// Using the standard template library pair class
using Point = std::pair<int , int>;

// Function to find the cross product of two vectors
int cross_product ( const Point &p , const Point &q , const Point &r )
{
     // Cross product of two vectors pq and pr
     return ( q.first - p.first ) * ( r.second - p.second ) - ( q.second - p.second ) * ( r.first - p.first );
}

// Function to check if the point r lies on the line segment pq
bool lies_on_segment ( const Point &p , const Point &q , const Point &r )
{
     // Check if the point r lies on the line segment pq
     return ( r.first >= std::min ( p.first , q.first ) && r.first <= std::max ( p.first , q.first ) &&
          r.second >= std::min ( p.second , q.second ) && r.second <= std::max ( p.second , q.second ) );
}

// Function to check the orientation
int orientation ( const Point &p , const Point &q , const Point &r )
{
     // Find the orientation 
     int val = cross_product ( p , q , r );

     // If the points are collinear
     if ( val == 0 ) return 0;

     // If the points are clockwise
     return ( val > 0 ) ? 1 : 2;
}

/// Function to find the points
std::vector<Point> convexHull ( std::vector<Point> &points )
{
     // Number of points
     int n = points.size ( );

     // If less than 3
     if ( n < 3 )
     {
          return points;
     }

     // Initialize to store the points
     std::vector<Point> hull;

     // Find the leftmost point
     int leftmost = 0;
     for ( int i = 1; i < n; i++ )
     {
          // If the current point is less than the leftmost point
          if ( points [ i ].first < points [ leftmost ].first )
               leftmost = i;
     }

     // Initialize the current point
     int p = leftmost , q;

     // Iterate through the points
     do
     {
          // Add the current point to the hull
          hull.push_back ( points [ p ] );

          // Find the next point
          q = ( p + 1 ) % n;

          // Iterate through the points
          for ( int i = 0; i < n; i++ )
          {
               // If the point i is more counterclockwise
               if ( orientation ( points [ p ] , points [ i ] , points [ q ] ) == 2 )
                    q = i;
          }
          // Update the current point
          p = q;

     } while ( p != leftmost );

     return hull;
}

int main ( )
{
     // Read observations from file
     std::ifstream infile ( "C:/Users/Kaylee/Documents/GitHub/CS472.LewisKa/Assignment03/docs/Assignment3/CreateObservations/observations.txt" );
     if ( !infile )
     {
          std::cerr << "Error: Unable to open the file." << std::endl;
          return 1;
     }

     std::vector<Point> observations;
     int x , y;
     while ( infile >> x >> y )
     {
          observations.push_back ( { x, y } );
     }
     infile.close ( );

     // Calculate convex hull
     std::vector<Point> hull = convexHull ( observations );

     // Print convex hull points
     std::cout << "Convex Hull Points:\n";
     for ( const auto &point : hull )
     {
          std::cout << "(" << point.first << ", " << point.second << ")" << std::endl;
     }

     return 0;
}