// A simple program to create a file with random observations.
// Kaylee Lewis

//https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution

#include <iostream>
#include <fstream>
#include <random>

int main ( )
{
     // Define the range of x and y coordinates
     const int minX = 0 , maxX = 1000;
     const int minY = 0 , maxY = 1000;

     // Number of observations
     const int numObservations = 100;

     // Create a random number generator
     std::random_device rd;
     std::mt19937 gen ( rd ( ) );
     std::uniform_int_distribution<int> distribX ( minX , maxX );
     std::uniform_int_distribution<int> distribY ( minY , maxY );

     // Create and open the file
     std::ofstream outfile ( "observations.txt" );
     if ( !outfile.is_open ( ) )
     {
          std::cerr << "Error: Unable to open the file for writing.\n";
          return 1;
     }

     // Generate random observations and write them to the file
     for ( int i = 0; i < numObservations; ++i )
     {
          int x = distribX ( gen );
          int y = distribY ( gen );
          outfile << x << " " << y << std::endl;
     }

     // Close the file
     outfile.close ( );

     std::cout << "Observations file created successfully.\n";
     return 0;
}