
//  Author: Your Glorious Instructor
//            Changes made by Kaylee Lewis
//  Purpose:
//  Modify the adjacency matrix implementation to use an extra stack
//  where you push a new node id onto the stack when adding a node to minimize the initialization effort.
//  Do that by scanning the stack to see if a node id has already been plugged into the adjacency matrix.
//  Explain in comments how this reduces the effort of initializing a new graph away from quadratic behavior.
//  https://www.geeksforgeeks.org/search-an-element-in-a-linked-list-iterative-and-recursive/
//  https://www.geeksforgeeks.org/implementing-sets-without-c-stl-containers/

//  File: AdjMatrixGraph.hpp

#pragma once

#include "C:\Users\Kaylee\Documents\GitHub\CS472.LewisKa\Assignment01\include\Graph.hpp"
#include <map>
#include <stack>
#include <queue>
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <functional>
#include <unordered_map>

template <class N>
class AdjMatrixGraph final : public Graph<N>
{
private:
    // Create a struct to store the node and its index
    class NodeEntry
    {
    public:
        N node; 
        int index; 
    };

    // Maximum number of nodes
    const static int maxSize = 10;
    bool adjMatrix[maxSize][maxSize];
    NodeEntry *nodes[maxSize];

    // Adding the stack to store the node ids
    std::stack<N> nodeStack; 

    int numNodes = 0;

    // Function to find a node in the matrix
    int findNodeInMatrix(N x)
    {
         // Check if the nodes array is properly initialized
         if ( nodes == nullptr )
         {
              // Handle the case where nodes array is not properly initialized
              return -1;
         }

        // Temporary stack to preserve the original order
        for (int j=0; j < numNodes; ++j)
        {
             // Check array bounds and node initialization
             if ( j < maxSize && nodes [ j ] != nullptr && x == nodes [ j ]->node )
             {
                  // Check array bounds and node initialization
                  return j;
             }
        }
        return -1;
    }

    // Function to scan the stack and check if a node id is already in the matrix
    int findNodeInStack ( N x ) 
    {
         // Temporary stack to preserve the original order
         std::stack<N> tempStack; 
         int index = -1; 

         // Scan the stack
         while ( !nodeStack.empty ( ) ) 
         {
              // If the node is found, return the index
              if ( nodeStack.top ( ) == x )
              {
                   index = numNodes - nodeStack.size ( );
              }

              // Push the node id onto the temporary stack
              tempStack.push ( nodeStack.top ( ) );

              // Pop the node id off the main stack
              nodeStack.pop ( );
         }

         // Restore the original order in the main stack
         while ( !tempStack.empty ( ) )
         {
              // Push the node id onto the main stack
              nodeStack.push ( tempStack.top ( ) );

              // Pop the node id off the temporary stack
              tempStack.pop ( );
         }

         return index;
    }

public:
    // Default constructor, create empty
    AdjMatrixGraph()
    {
         // Initialize the adjacency matrix
        for(int i = 0; i < maxSize; i++)
        {
            // Initialize the node entry
            nodes [ i ] = nullptr;

            // Scan the matrix
            for (int j=0; j < maxSize; j++) 
            {
                // Set the adjacency matrix to false
                adjMatrix[i][j] = false;
            }
        }
    }

    // Add the nodes in the list to graph
    AdjMatrixGraph(std::vector<N> newNodes, std::vector<std::pair<N,N>> newEdges)
    {
        // Temporary stack to preserve the original order
        adjMatrix = new NodeEntry[maxSize][maxSize];

        // Scan the stack
        for (typename std::vector<N>::const_iterator it = newNodes.begin(); it < newNodes.end();
             ++it)
        {
            // Create a new node entry
            NodeEntry ne = new NodeEntry();

            // Set the node id
            ne.node = *it;

            // Set the index
            ne.index = numNodes;

            // Push the node id onto the stack
            nodes[numNodes] = ne; 
            nodeStack.push ( *it );

            // Increment the number of nodes
            numNodes++; 
        }

        // Scan the stack
        for (typename std::vector<std::pair<N,N>>::const_iterator it = newEdges.begin(); 
             it < newEdges.end(); ++it) 
        {
            // Create a new node entry
            std::pair<N,N> edge = *it;
             
            // Find the source node
            const int sourceIndex = findNodeInMatrix(edge.first);

            // Find the destination node
            const int destIndex = findNodeInMatrix(edge.second); 

            // If the source node is found
            if (sourceIndex != -1) 
            {
                // If the destination node is found
                if (destIndex != -1) 
                {
                    // Add the edge
                    adjMatrix[sourceIndex][destIndex] = true; 
                }
            }
        }
    }

    // Clean up behind ourselves
    ~AdjMatrixGraph() override = default;

    // Function to check if two nodes are adjacent
    bool adjacent(N x, N y) override
    {
        // Initialize the result
        bool result = false;

        // Find the nodes in the matrix
        const int xIndex = findNodeInMatrix(x);
        const int yIndex = findNodeInMatrix(y);

        // If the nodes are found
        if ((xIndex != -1) && (yIndex != -1))
        {
            // Check if the nodes are adjacent
            const bool xy = adjMatrix[xIndex][yIndex];
            const bool yx = adjMatrix[yIndex][xIndex];

            // If both are true, then the nodes are adjacent
            result = xy && yx;
        }

        return(result);
    }

    // Function to find a node in the matrix
    std::vector<N> neighbors(N x) override
    {
        // Create a vector to store the neighbors
        std::vector<N> *v = new std::vector<N>();

        // Find the node in the matrix
        const int xIndex = findNodeInMatrix(x);

        // If the node is found
        if (xIndex != -1)
        {
            // Scan the matrix
            for (int i=0; i < numNodes; ++i) 
            {
                 // If the node is found
                if (adjMatrix[xIndex][i] == true) 
                {
                     // Add the node to the vector
                    v->push_back(nodes[i]->node);
                }
            }
        }

        // Return the vector
        return *v;
    }

    // Function to add a node to the graph
    void addNode(N node) override
    {
        // Find the node in the matrix
        NodeEntry *ne = new NodeEntry();

        // Set the node id
        ne->node = node;

        // Set the index
        ne->index = numNodes;

        // Push the node id onto the stack
        nodes[numNodes] = ne;

        // Increment the number of nodes
        numNodes++;

    }

    // Function to add an edge to the graph
    void addEdge(N x, N y) override
    {
        const int xIndex = findNodeInMatrix(x);
        const int yIndex = findNodeInMatrix(y);
        if ((xIndex != -1) && (yIndex != -1))
        {
            adjMatrix[xIndex][yIndex] = true;
        }
    }

    // Function to delete an edge from the graph
    void deleteEdge(N x, N y) override
    {
        const int xIndex = findNodeInMatrix(x);
        const int yIndex = findNodeInMatrix(y);
        adjMatrix[xIndex][yIndex] = false;
    }

    // Traversals
     // Depth first search
    void dfs(N startNode, std::function<void(N)> visit) override
    {
        // Create a map to store the visited nodes
        std::map<N, bool> visited;

        // Scan the stack
        for (int i = 0; i < numNodes; ++i)
        {
            // Set the visited flag to false
            visited[nodes[i]->node] = false;
        }

        // Create a stack to store the nodes
        std::stack<N> s;

        // Push the start node onto the stack
        s.push(startNode);

        // Scan the stack
        while (!s.empty()) 
        {
            // Get the top node
            N currentNode = s.top();

            // Pop the top node off the stack
            s.pop();

            // Get the visited flag
            const bool beenVisited = visited[currentNode];

            // If the node has not been visited
            if (!beenVisited) 
            {
                // Visit the node
                visit(currentNode);

                // Set the visited flag to true
                visited[currentNode] = true;
            }

            // Get the neighbors of the node
            std::vector<N> neighVec = neighbors(currentNode);

            // Scan the neighbors
            for (auto neighbor: neighVec ) 
            {
                 // If the neighbor has not been visited
                 // push the neighbor onto the stack
                if (!visited[neighbor]) { s.push(neighbor); } 
            }
        }
    }

     // Breadth first search
    void bfs(N startNode, std::function<void(N)> visit) override
    {
        // Create a map to store the visited nodes
        std::map<N, bool> visited;

        // Scan the stack
        for (int i = 0; i < numNodes; ++i)
        {
            // Set the visited flag to false
            visited[nodes[i]->node] = false;
        }

        // Create a queue to store the nodes
        std::queue<N> q;

        // Push the start node onto the queue
        q.push(startNode);

        // Scan the queue
        while (!q.empty()) 
        {
            // Get the top node
            N currentNode = q.front();

            // Pop the top node off the queue
            q.pop();

            // Get the visited flag
            const bool beenVisited = visited[currentNode];

            // If the node has not been visited
            if (!beenVisited) 
            {
                // Visit the node
                visit(currentNode);

                // Set the visited flag to true
                visited[currentNode] = true;
            }

            // Get the neighbors of the node
            std::vector<N> neighVec = neighbors(currentNode);

            // Scan the neighbors
            for (auto neighbor: neighVec) 
            {
                 // If the neighbor has not been visited
                 // push the neighbor onto the queue
                 if (!visited[neighbor]) { q.push(neighbor); }
            }
        }
    }

    // Function to get the number of nodes in the graph
    size_t getNumNodes ( ) const override
    {
         // Return the number of nodes
         return numNodes;
    }

    // Function to get a node from the graph
    N getNode ( int index ) const override
    {
         if ( nodes == nullptr || index < 0 || index >= maxSize || nodes [ index ] == nullptr )
         {
              // Handle the case where nodes array is not properly initialized or index is out of bounds
              // Return a default value 
              return N ( );  
         }

         // Return the node at the specified index
         return nodes [ index ]->node;
    }
};
