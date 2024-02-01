// Assignment 02: Battling Big-Oh
// Due: Wed Jan 31 , 2024 11 : 59pmDue : Wed Jan 31 , 2024 11 : 59pm
// Kaylee Lewis
//
// Q5: Test the order of library sort
//
// Use the sort routine provided by the language to sort randomly generated
//        data sets of 5 , 10 , 50 , 100 , 500 , 1000 , 5000 , and 10 , 000 integers.
// Sort at least 10 or more random data sets for each data set size.
// Implement an algorithm that looks like this
//    Output: A data set of run times for each data set size
//     for size ∈ [ 5 , 10 , 50 , 100 , 500 , 1000 , 5000 , 100000 ] do
//        Set totalRunTime ← 0;
//        for runNumber ∈ [ 0 ..NumberOfRuns) do
//             GenerateRandomDataSet ( dataSet , size );
//             Note start time;
//             Sort ( dataSet );
//             Note end time;
//             Set elapsed time to difference between end and start times;
//             Add elapsed time to totalRunTime;
//        Set averageRunTime = totalRunTime / NumberOfRuns;
// The function GenerateRandomDataSet(dataSet, size) needs to generate a random set of integers
//        of whatever size is passed into the function as an input.
// Create a graph at graphs data set size versus the average run time for each size.
// Include a plot of data set size versus f ( n ) = n ∗ lg ( n ) as well.
// 1-3 paragraph) analysis of the results

// https://www.geeksforgeeks.org/time-complexities-of-all-sorting-algorithms/'
// https://www.geeksforgeeks.org/time-and-space-complexity-analysis-of-selection-sort/
// https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
// https://www.geeksforgeeks.org/generating-random-number-range-c/
// https://www.geeksforgeeks.org/stdmt19937-class-in-cpp/?ref=header_search
// https://builtin.com/machine-learning/fastest-sorting-algorithm

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>

#include <C:\Python\Python312\include\Python.h>
#include "matplotlibcpp.h"

// Function to generate a random data set
void generateRandomDataSet ( std::vector<int> &dataSet , int size )
{
     //  Clear the vector and reserve space for the new data set
     dataSet.clear ( );

     //  Reserve space for the new data set
     dataSet.reserve ( size );

     //  Generate a random data set
     std::random_device rd;

     //  Use the Mersenne Twister 19937 generator
     std::mt19937 gen ( rd ( ) );

     //  Use a uniform distribution for the random numbers
     std::uniform_int_distribution<> dis ( 0 , size - 1 );

     //  Generate the random data set
     for ( int i = 0; i < size; ++i )
     {
          //  Add a random number to the data set
          dataSet.push_back ( dis ( gen ) );
     }
}

// Function to measure the sorting time
double measureSortingTime ( const std::vector<int> &dataSet , int numberRuns )
{
     //  Total run time for all runs
     double totalRunTime = 0.0; 

     //  Sort the data set multiple times
     for ( int runNumber = 0; runNumber < numberRuns; ++runNumber )
     {
          //  Make a copy of the data set
          std::vector<int> dataCopy = dataSet; 

          //  Start the timer
          auto startTime = std::chrono::high_resolution_clock::now ( ); 

          //  Sort the data set
          std::sort ( dataCopy.begin ( ) , dataCopy.end ( ) );

          //  Stop the timer
          auto endTime = std::chrono::high_resolution_clock::now ( );

          //  Calculate the elapsed time
          auto elapsedTime = std::chrono::duration_cast< std::chrono::microseconds >( endTime - startTime ).count ( );
          totalRunTime += elapsedTime;
     }

     //  Return the average run time
     return totalRunTime / numberRuns;
}

int main ( )
{
     //  random generated data set sizes
     const std::vector<int> dataSetSizes = { 5, 10, 50, 100, 500, 1000, 5000, 10000 };

     //  Number of runs for each data set size
     const int numberRuns = 10;

     //  Average run times and f(n) values
     std::vector<double> averageRunTimes;

     //  f(n) = n * lg(n)
     std::vector<double> fnvalues;

     //  Generate the data sets and measure the run times
     std::cout << "Data set size\tAverage run time (ms)   f(n) = n * lg(n)" << std::endl;


     //  Generate the data sets and measure the run times
     for (const int size : dataSetSizes )
     {
          //  Generate a random data set
          std::vector<int> dataSet;

          //  Generate a random data set
          generateRandomDataSet ( dataSet , size ); 


          //  Measure the average run time
          double averageRunTime = measureSortingTime ( dataSet , numberRuns );

          //  Add the average run time to the list
          averageRunTimes.push_back ( averageRunTime );

          //  Calculate f(n) = n * lg(n)
          double fn = size * log2 ( size );

          //  Add the f(n) value to the list
          fnvalues.push_back ( fn );

          //  Output the data set size, average run time, and f(n) value
          std::cout << size << "\t\t" << averageRunTime <<  "\t\t\t" << fn << std::endl;
     }

     //  Create a graph of data set size versus the average run time
      matplotlibcpp::plot ( dataSetSizes , averageRunTimes , "o-" , "label='Average Run Time'" );

     //  Create a graph of data set size versus f(n) = n * lg(n)
      matplotlibcpp::plot ( dataSetSizes , fnvalues , "o-" , "label='f(n) = n * log(n)'" );

     //  Set the x and y axis labels
      matplotlibcpp::xlabel ( "Data Set Size" );

     //  Set the x and y axis labels
      matplotlibcpp::ylabel ( "Time (microseconds)" );

     //  Set the title of the graph
      matplotlibcpp::title ( "Data Set Size vs. Average Run Time" );

     //  Display the legend
      matplotlibcpp::legend ( );

     //  Show the graph
      matplotlibcpp::show ( );

     return 0;
}