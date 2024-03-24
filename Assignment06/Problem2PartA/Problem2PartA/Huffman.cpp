// Huffman.cpp

#include "Huffman.h"

// Function to create the Huffman codes for each character in the input string
std::unordered_map<char , std::string> huffmanCodeTree ( NodeTree *node , std::string binString )
{
     std::unordered_map<char , std::string> codeMap;
     if ( node == nullptr )
     {
          return codeMap;
     }
     if ( node->isLeaf ( ) )
     {
          codeMap [ node->data ] = binString;
     } else
     {
          auto leftMap = huffmanCodeTree ( node->left , binString + "0" );
          codeMap.insert ( leftMap.begin ( ) , leftMap.end ( ) );

          auto rightMap = huffmanCodeTree ( node->right , binString + "1" );
          codeMap.insert ( rightMap.begin ( ) , rightMap.end ( ) );
     }
     return codeMap;
}

// Function to create the Huffman tree from the frequencies of the characters
NodeTree *makeTree ( std::vector<std::pair<char , int>> &nodes )
{
     std::vector<NodeTree *> nodePtrs ( nodes.size ( ) );
     std::transform ( nodes.begin ( ) , nodes.end ( ) , nodePtrs.begin ( ) , [ ] ( std::pair<char , int> &pair )
          {
               return new NodeTree ( pair.first );
          } );

     while ( nodePtrs.size ( ) > 1 )
     {
          std::sort ( nodePtrs.begin ( ) , nodePtrs.end ( ) , [ ] ( NodeTree *a , NodeTree *b )
               {
                    return a->data > b->data;
               } );

          NodeTree *left = nodePtrs.back ( );
          nodePtrs.pop_back ( );
          NodeTree *right = nodePtrs.back ( );
          nodePtrs.pop_back ( );
          nodePtrs.push_back ( new NodeTree ( '\0' , left , right ) );
     }
     return nodePtrs [ 0 ];
}

// Function to encode the Huffman tree into binary format and write it to an output stream
void encodeHuffmanTree ( NodeTree *node , std::ofstream &out )
{
     if ( node == nullptr )
     {
          return;
     }
     if ( node->isLeaf ( ) )
     {
          out.put ( '1' );
          out.put ( node->data );
     } else
     {
          out.put ( '0' );
          encodeHuffmanTree ( node->left , out );
          encodeHuffmanTree ( node->right , out );
     }
}
