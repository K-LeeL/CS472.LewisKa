// Assignment 06: A Greedy Exercise in File Compression
// Due: Fri Mar 22 , 2024 11 : 59pm
// Kaylee Lewis
// Problem 1:
//  Provide a greedy algorithm for computing the Huffman encoding of a bit - string implementing
//  this algorithm in C++.

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

// NodeTree class to represent the nodes of the Huffman tree
class NodeTree
{
public:
     char data;
     NodeTree *left , *right;

     // Constructor to initialize the NodeTree object
     NodeTree ( char data , NodeTree *left = nullptr , NodeTree *right = nullptr )
          : data ( data ) , left ( left ) , right ( right )
     {
     }

     // Function to return the children of the node
     std::pair<NodeTree * , NodeTree *> children ( )
     {
          return std::make_pair ( left , right );
     }

     // Function to convert the NodeTree object to a string
     std::string toString ( )
     {
          return std::string ( 1 , data );
     }
};

// Function to create the Huffman codes for each character in the input string
std::unordered_map<char , std::string> huffmanCodeTree ( NodeTree *node , std::string binString = "" )
{
     // If the node is a leaf node, return the character and its binary string
     if ( node->left == nullptr && node->right == nullptr )
     {
          return { {node->data, binString} };
     }

     // Recursively call the function on the left and right children of the node
     std::pair<NodeTree * , NodeTree *> children = node->children ( );
     NodeTree *leftChild = children.first;
     NodeTree *rightChild = children.second;

     // Create a map to store the Huffman codes for each character
     std::unordered_map<char , std::string> codeMap;

     auto leftMap = huffmanCodeTree ( leftChild , binString + "0" );
     codeMap.insert ( leftMap.begin ( ) , leftMap.end ( ) );

     auto rightMap = huffmanCodeTree ( rightChild , binString + "1" );
     codeMap.insert ( rightMap.begin ( ) , rightMap.end ( ) );

     return codeMap;
}

// Function to create the Huffman tree from the frequencies of the characters
NodeTree *makeTree ( std::vector<std::pair<char , int>> &nodes )
{
     // Create a node for each character
     std::vector<NodeTree *> nodePtrs ( nodes.size ( ) );
     std::transform ( nodes.begin ( ) , nodes.end ( ) , nodePtrs.begin ( ) , [ ] ( std::pair<char , int> &pair )
          {
               return new NodeTree ( pair.first );
          } );

     // Build the tree
     while ( nodePtrs.size ( ) > 1 )
     {
          // Sort the nodes based on their frequency
          std::sort ( nodePtrs.begin ( ) , nodePtrs.end ( ) , [ ] ( NodeTree *a , NodeTree *b )
               {
                    return a->data > b->data;
               } );

          // Combine the two nodes with the lowest frequency
          NodeTree *left = nodePtrs.back ( ); nodePtrs.pop_back ( );
          NodeTree *right = nodePtrs.back ( ); nodePtrs.pop_back ( );

          // Create a new node with the combined frequency
          nodePtrs.push_back ( new NodeTree ( '\0' , left , right ) );
     }

     // Return the root of the Huffman tree
     return nodePtrs [ 0 ];
}

// Function to print the Huffman codes for each character in the input string
void printHuffmanCodes ( const std::string &input )
{
     // Calculate the frequency of each character in the input string
     std::unordered_map<char , int> freq;
     for ( char c : input )
     {
          freq [ c ]++;
     }

     // Sort the characters based on their frequency
     std::vector<std::pair<char , int>> freqVec ( freq.begin ( ) , freq.end ( ) );
     std::sort ( freqVec.begin ( ) , freqVec.end ( ) , [ ] ( const std::pair<char , int> &x , const std::pair<char , int> &y )
          {
               return x.second > y.second;
          } );

     // Create the Huffman tree and get the Huffman codes for each character
     NodeTree *root = makeTree ( freqVec );
     std::unordered_map<char , std::string> encoding = huffmanCodeTree ( root );

     // Print the Huffman codes for each character
     for ( char c : input )
     {
          std::cout << c << " : " << encoding [ c ] << std::endl;
     }
}

int main ( )
{
     std::string input = "BCAADDDCCACACAC";
     printHuffmanCodes ( input );

     return 0;
}