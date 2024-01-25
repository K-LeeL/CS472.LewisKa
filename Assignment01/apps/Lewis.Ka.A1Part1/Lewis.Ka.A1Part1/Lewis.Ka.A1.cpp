
//  Author: Kaylee Lewis

//  Assignment 01: Let's Play With Graphs:
//  Due: Wed Jan 24 , 2024 11 : 59pm

//  1. Create directed graphs to test programs.Implement the following functions:
//  AdjListGraph & generateAdjListGraph(int numberOfNodes, double edgeProbability);
//  AdjMatrixGraph &generateAdjMatrixGraphGraph ( int numberOfNodes , double edgeProbability);
//
//  Each function will return a reference to a Graph containing the specified number of nodes
//  with edges existing between each pair of nodes having the specified probability.
//  This means that when you add a node to the graph, that there is an edgeProbability chance
//  that you need to add an edge from the new node to each of existing nodes in the graph.
//  Note that the probability test must occur for each existing node in the graph.
//  for numberOfNodes times, you will add a new node to the list and then loop through
//  the nodes currently in the graph.
//  In this loop, use the random number functions to generate a number in the range
//  [0\ldots 1).
//  If that number is greater than the edgeProbability, then you need to add an edge
//  from your new node to the node you are examining.
//
//  Hint: call super class method in C++
//
// 2. Use the program you just created to guess the performance of the depth first
//  search of a graph represented in an adjacency matrix.
//  Generate graphs with sizes of 2, 8, 64, 256, and 1024 nodes, each with a random
//  number of edges, with edge probability of 0.5.
//  Report how long (in seconds) it takes for your program to execute the search.
//
//  Assumptions:
//  Assume that the base graph type is a directed graph.
//    Un-directed graphs can be represented by a pair of directional edges from/to each
//    node pair in the graph.
//  Note that you will need to keep a separate vector or list in your data structures to keep
//  track of the information stored with each node.
//    The adjacency list and adjacency matrix representations will store references to the data in this list.
//  You may use your favorite programming language to solve the problems in this assignment.
//    Note that one of the requirements for this assignment is that your code be reusable (users of scripting
//    languages such as Ruby, Python, or Javascript take note that this means you need to write more than a
//    single program).
//  You can not use the Boost libraries for this assignment if you are using C++.
//

//  https://stackoverflow.com/questions/5056645/sorting-stdpairvector
//  https://stackoverflow.com/questions/686353/random-float-number-generation
//  https://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
//  https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
//  https://www.thealgorists.com/Algo/DFS
//  https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/
//  https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/

//  File: Lewis.Ka.A1.cpp

#include "C:\Users\Kaylee\Documents\GitHub\CS472.LewisKa\Assignment01\include\AdjMatrixGraph.hpp"
#include "C:\Users\Kaylee\Documents\GitHub\CS472.LewisKa\Assignment01\include\AdjListGraph.hpp"
#include <iostream>
#include <utility>
#include <chrono>
#include <ctime>
#include <cstdlib>

// Function to generate an adjacency list graph with random edges
template <class N>
AdjListGraph<N>* generateAdjListGraph ( int numberOfNodes , double edgeProbability )
{
     // Seed the random number generator
     srand ( static_cast< unsigned >( time ( nullptr ) ) );

     // Create a new graph
     AdjListGraph<N>* graph = new AdjListGraph<N> ( );

     // Add the nodes to the graph
     for ( int i = 0; i < numberOfNodes; ++i )
     {
          // Create a new node
          N newNode = static_cast< N >( i );

          // Add the node to the graph
          graph->addNode ( newNode );

          // Loop through the nodes in the graph
          for ( int j = 0; j < graph->getNumNodes ( ); ++j )
          {
               // If the random number is less than the edge probability, add an edge
               if ( rand ( ) / static_cast< double >( RAND_MAX ) < edgeProbability )
               {
                    // Get the existing node
                    N existingNode = graph->getNode ( j );

                    // Add the edge
                    graph->addEdge ( newNode , existingNode );
               }
          }
     }

     return graph;
}

// Function to generate an adjacency matrix graph with random edges
template <class N>
AdjMatrixGraph<N>* generateAdjMatrixGraph ( int numberOfNodes , double edgeProbability )
{
     // Seed the random number generator
     srand ( static_cast< unsigned >( time ( nullptr ) ) );

     // Create a new graph
     AdjMatrixGraph<N>* graph = new AdjMatrixGraph<N> ( );

     // Add the nodes to the graph
     for ( int i = 0; i < numberOfNodes; ++i )
     {
          // Create a new node
          N newNode = static_cast< N >( i );

          // Add the node to the graph
          graph->addNode ( newNode );

          // Loop through the nodes in the graph
          for ( int j = 0; j < graph->getNumNodes ( ); ++j )
          {
               // If the random number is less than the edge probability, add an edge
               if ( rand ( ) / static_cast< double >( RAND_MAX ) < edgeProbability )
               {
                    // Get the existing node
                    N existingNode = graph->getNode ( j );

                    // Add the edge
                    graph->addEdge ( newNode , existingNode );
               }
          }
     }

     return graph;
}

// Function to measure the time it takes to perform DFS on a graph
template <class N , class GraphType>
void measureDFSTime ( GraphType &graph , N startNode )
{

     // Start the timer
     const auto startTime = std::chrono::high_resolution_clock::now ( );

     // Perform DFS on the graph
     graph->dfs ( startNode , [ ] ( N node ) 
          {
               // Print the node
               std::cout << node << std::endl;
          } );

     // Stop the timer
     const auto endTime = std::chrono::high_resolution_clock::now ( );

     // Calculate the execution time
     const auto ms = std::chrono::duration_cast< std::chrono::milliseconds >( endTime - startTime );

     // Print the execution time
     std::cout << "DFS time: " << ms.count ( ) << " ms" << std::endl;
}

void testGraph ( int numberOfNodes , const double edgeProbability )
{
     // Generate and measure DFS for an adjacency matrix graph
     std::cout << "Testing graph with " << numberOfNodes << " nodes and edge probability of " << edgeProbability << std::endl;

     // Generate and measure DFS for an adjacency matrix graph
     std::cout << "DFS on Adjacency Matrix Graph:" << std::endl;
     AdjMatrixGraph<int>* matrixGraph;
     matrixGraph = generateAdjMatrixGraph<int> ( numberOfNodes , edgeProbability );
     measureDFSTime ( matrixGraph , 0 );

     // Generate and measure DFS for an adjacency list graph
     std::cout << "DFS on Adjacency List Graph:" << std::endl;
     AdjListGraph<int> *listGraph = generateAdjListGraph<int> ( numberOfNodes , edgeProbability );
     measureDFSTime ( listGraph , 0 );

     std::cout << std::endl;
}

int main ( )
{
     const double edgeProbability = 0.5;
     //Generate graphs with sizes of 2, 8, 64, 256, and 1024 nodes, each with a random number of edges, with edge probability of 0.5.

     std::vector<int> sizes { 2, 8, 64, 256, 1024 };

     for ( int s : sizes )
     {
          testGraph ( s , 0.5 );
     }

     system ( "pause" );

     return 0;
}