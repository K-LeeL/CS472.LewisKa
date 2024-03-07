// Assignment 05: Greedy Dynamic Programming
// Due : Wed Mar 6 , 2024 11 : 59pm
//
// Problem 2: 
// Both Prim's and Kruskal's algorithms find the minimum spanning tree ( MST ) of a weighted graph.
// They are suited for different scenarios. Prim's algorithm is used for dense graphs or connected components.
// It efficiently grows the MST from an arbitrary starting vertex , making it faster for dense graphs with a
// time complexity of O ( V ^ 2 ) or O ( E log V ).
// 
// Kruskal's algorithm is preferable for sparse graphs or disconnected components. 
// It sorts edges by weight and adds them to the MST without forming cycles.
// It is efficient with a time complexity of O ( E log E ).
// 
// The choice between the two algorithms depends on the graph's density and connectivity. 
// Prim's algorithm is suitable for dense graphs and Kruskal's algorithm is good for sparse graphs or disconnected components.
//
// Problem 3:
// Both the NetworkX and Boost::Graph libraries include implementations of Prim’s and Kruskal’s algorithms.
// But it’s helpful to do it once by hand to understand how things work.
// Implement both algorithms , with adequate testing code in place to show your implementations are behaving correctly.
//
// NOTE: don’t try to use your own implementations of Graphs - Use the libraries.

// https://www.boost.org/doc/libs/1_77_0/libs/graph/doc/prim_minimum_spanning_tree.html
// https://www.boost.org/doc/libs/1_77_0/libs/graph/doc/kruskal_min_spanning_tree.html
// https://www.boost.org/doc/libs/1_77_0/libs/graph/doc/adjacency_list.html
// https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
// https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/


#include <iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/graph_traits.hpp>
#include<boost/graph/prim_minimum_spanning_tree.hpp>
#include<boost/graph/kruskal_min_spanning_tree.hpp>

// Prim's algorithm function
template <typename Graph>
void prim_algorithm ( const Graph &g )
{
     // typedefs for the graph
     typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
     typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;

     // vector to store the minimum spanning tree
     std::vector<Vertex> p ( num_vertices ( g ) );
     prim_minimum_spanning_tree ( g , &p [ 0 ] );

     // print the minimum spanning tree
     std::cout << "Prim's Minimum Spanning Tree: " << std::endl;

     // iterate through the vertices
     for ( std::size_t i = 0; i != p.size ( ); ++i )
     {
          // if the vertex is not equal to itself
          if ( p [ i ] != i )
          {
               // find the edge and print the edge and its weight
               Edge e;

               // check if the edge is found
               bool found;

               // get the edge and its weight
               tie ( e , found ) = edge ( i , p [ i ] , g );

               // if the edge is found
               if ( found )
                    std::cout << "Edge: " << i << " - " << p [ i ] << " Weight: " << get ( boost::edge_weight , g , e ) << std::endl;
          }
     }
}

// Kruskal's algorithm function
template <typename Graph>
void kruskal_algorithm ( const Graph &g )
{
     // typedefs for the graph
     typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;

     // vector to store the minimum spanning tree
     std::vector<Edge> kruskal_tree;
     kruskal_minimum_spanning_tree ( g , std::back_inserter ( kruskal_tree ) );

     std::cout << std::endl;

     // print the minimum spanning tree
     std::cout << "Kruskal's Minimum Spanning Tree: " << std::endl;

     // iterate through the edges
     for ( const auto &e : kruskal_tree )
     {
          std::cout << "Edge: " << source ( e , g ) << " - " << target ( e , g ) << " Weight: " << get ( boost::edge_weight , g , e ) << std::endl;
     }
}

int main ( )
{

     // typedef for the graph
     typedef boost::adjacency_list<boost::vecS , boost::vecS , boost::undirectedS , boost::no_property , boost::property<boost::edge_weight_t , int>> Graph;

     // create a graph
     Graph g;

     // Add edges with weights
     add_edge ( 0 , 1 , 2 , g );
     add_edge ( 0 , 2 , 4 , g );
     add_edge ( 1 , 2 , 1 , g );
     add_edge ( 1 , 3 , 5 , g );
     add_edge ( 2 , 3 , 3 , g );

     // call the prim and kruskal algorithm functions
     prim_algorithm ( g );
     kruskal_algorithm ( g );

     return 0;
}