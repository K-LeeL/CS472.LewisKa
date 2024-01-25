
//  Author: Your Glorious Instructor
//            Changes made by Kaylee Lewis
//  Purpose:
//  Modify the Adjacency List Graph class that replaces the vector of lists used to store 
//  edges with a st::unordered_map object. 
//  https://en.cppreference.com/w/cpp/container/unordered_map
//  https://www.geeksforgeeks.org/unordered_map-in-cpp-stl/
//  https://www.geeksforgeeks.org/print-adjacency-list-for-a-directed-graph/?ref=header_search

//  File: AdjListGraph.hpp

# pragma once
 
#include "C:\Users\Kaylee\Documents\GitHub\CS472.LewisKa\Assignment01\include\Graph.hpp"
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <utility>
#include <functional>
#include <unordered_map>

template <class N>
class AdjListGraph final : public Graph<N>
{
private:
    // Create a type alias for the list of edges
    using Edges = std::list<std::pair<N , N>>;

    // Create a type alias for the vertex map
    std::unordered_map<N , Edges > vertexMap;

public:
    // Default constructor, create empty
    AdjListGraph() : Graph<N>() { }

    // Get the vertex map from the Graph we're copying
    AdjListGraph(const AdjListGraph& other) : Graph<N>()
    {
         // Copy the vertex map
         vertexMap = other.vertexMap;
    }
    
    // Don't forget to overload the assignment operator
    AdjListGraph& operator= (const AdjListGraph &source)
    {
        // Check for self-assignment
        vertexMap = source.vertexMap;
        return *this;
    }
    
    // Add the nodes in the list to graph
    AdjListGraph ( std::vector<N> newNodes , std::vector<std::pair<N , N>> newEdges )
         : Graph<N> ( newNodes , newEdges )
    {
         // Add the nodes to the graph
         for ( const auto &node : newNodes )
         {
              vertexMap [ node ] = Edges ( ); 
         }

         // Add the edges to the graph
         for ( const auto &edge : newEdges )
         {
              vertexMap [ edge.first ].push_back ( edge );
              vertexMap [ edge.second ].push_back ( { edge.second, edge.first } );
         }
    }
    
    // Clean up behind ourselves
    ~AdjListGraph ( ) override = default;

    // Check if two nodes are adjacent
    bool adjacent ( N x , N y ) override
    {
         // Return true if the edge exists
         const Edges &edges = vertexMap.at ( x );

         // Check if the edge exists
         return std::find ( edges.begin ( ) , edges.end ( ) , std::make_pair ( x , y ) ) != edges.end ( );
    }

    // Get the neighbors of a node
    std::vector<N> neighbors ( N x ) override
    {
         // Create a vector to store the neighbors
         std::vector<N> nodes;

         // Get the edges for the node
         const Edges &edges = vertexMap.at ( x );

         // Loop through the edges and add the nodes to the vector
         for ( const auto &edge : edges )
         {
              // Add the node to the vector
              nodes.push_back ( edge.second );
         }

         // Return the vector of nodes
         return nodes;
    }

    // Add a node to the graph
    void addNode ( N node ) override
    {
         // Add the node to the vertex map
         if (vertexMap.find( node ) == vertexMap.end())
         {
              vertexMap [ node ] = Edges ( );
         }
    }

    // Add an edge to the graph
    void addEdge ( N x , N y ) override
    {
         // Add the edge to the vertex map
         vertexMap [ x ].push_back ( { x, y } );
         vertexMap [ y ].push_back ( { y, x } ); 
    }

    // Delete an edge from the graph
    void deleteEdge ( N x , N y ) override
    {
         vertexMap [ x ].remove ( { x, y } );
         vertexMap [ y ].remove ( { y, x } );
    }
    
    // Traversals
    void dfs ( N startNode , std::function<void ( N )> visit ) override
    {
         // Create a stack to store the nodes
         std::unordered_map<N , bool> visited;

         // Create a stack to store the nodes
         std::stack<N> s;

         // Push the start node onto the stack
         s.push ( startNode );

         // Loop while the stack is not empty
         while ( !s.empty ( ) )
         {
              // Get the top node
              N currentNode = s.top ( );

              // Remove the top node
              s.pop ( );

              // If the node has not been visited, visit it and add its neighbors to the stack
              if ( !visited [ currentNode ] )
              {
                   // Visit the node
                   visit ( currentNode );

                   // Mark the node as visited
                   visited [ currentNode ] = true;

                   // Add the neighbors to the stack
                   for ( const auto &neighbor : neighbors ( currentNode ) )
                   {
                        // If the neighbor has not been visited, add it to the stack
                        if ( !visited [ neighbor ] )
                        {
                             // Add the neighbor to the stack
                             s.push ( neighbor );
                        }
                   }
              }
         }
    }

    // Breadth-first search
    void bfs ( N startNode , std::function<void ( N )> visit ) override
    {
        // Create a map to store the visited nodes
        std::unordered_map<N , bool> visited;

        // Create a queue to store the nodes
        std::queue<N> q;

        // Push the start node onto the queue
        q.push ( startNode );

        // Loop while the queue is not empty
        while ( !q.empty ( ) )
        {
             // Get the front node
             N currentNode = q.front ( );

             // Remove the front node
             q.pop ( );

             // If the node has not been visited, visit it and add its neighbors to the queue
             if ( !visited [ currentNode ] )
             {
                  // Visit the node
                  visit ( currentNode );

                  // Mark the node as visited
                  visited [ currentNode ] = true;

                  // Add the neighbors to the queue
                  for ( const auto &neighbor : neighbors ( currentNode ) )
                  {
                       // If the neighbor has not been visited, add it to the queue
                       if ( !visited [ neighbor ] )
                       {
                            // Add the neighbor to the queue
                            q.push ( neighbor );
                       }
                  }
             }
        }
    }

    // Get the number of nodes in the graph
    size_t getNumNodes ( ) const override
    {
         // Return the number of nodes in the graph
         return vertexMap.size ( );
    }

    // Get the node at the specified index
    N getNode ( int index ) const override
    {
         // Create an iterator to the beginning of the vertex map
         auto it = vertexMap.begin ( );

         // Move iterator to the desired index
         std::advance ( it , index );  

         // Return the node at the specified index
         return it->first;  
    }
};