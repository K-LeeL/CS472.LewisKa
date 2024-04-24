// Assignment 06: A Greedy Exercise in File Compression
// Due: Fri Mar 22 , 2024 11 : 59pm
// Kaylee Lewis
// Problem 2 Part B:
// A file decompressor that converts the Huffman encoded compressed file back to the original

// www.techiedelight.com/huffman-coding/
// www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
// www.geeksforgeeks.org/huffman-decoding/
// https://www.codeconvert.ai/free-converter

// Decompressor.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

// NodeTree class to represent the nodes of the Huffman tree
class NodeTree
{
public:
     char data;
     NodeTree *left;
     NodeTree *right;

     NodeTree ( char data , NodeTree *left = nullptr , NodeTree *right = nullptr )
          : data ( data ) , left ( left ) , right ( right )
     {
     }

     ~NodeTree ( )
     {
          delete left;
          delete right;
     }

     bool isLeaf ( ) const
     {
          return left == nullptr && right == nullptr;
     }
};


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

// Function to read the Huffman tree from binary data
NodeTree *readHuffmanTree ( std::ifstream &inFile )
{
     char bit;
     if ( !inFile.get ( bit ) )
     {
          std::cerr << "Error: Corrupted Huffman tree data (unexpected end)\n";
          return nullptr;
     }

     if ( bit == '1' )
     {
          char data;
          if ( !inFile.get ( data ) )
          {
               std::cerr << "Error: Corrupted Huffman tree data (unexpected end)\n";
               return nullptr;
          }
          return new NodeTree ( data );
     } else if ( bit == '0' )
     {
          NodeTree *left = readHuffmanTree ( inFile );
          NodeTree *right = readHuffmanTree ( inFile );
          if ( !left || !right )
          {
               return nullptr;
          }
          return new NodeTree ( '\0' , left , right );
     } else
     {
          std::cerr << "Error: Corrupted Huffman tree data (invalid bit)\n";
          return nullptr;
     }
}

// Function to decompress a file using Huffman encoding
void decompressFile ( const std::string &inputFile , const std::string &outputFile )
{
     // Open input file
     std::ifstream inFile ( inputFile , std::ios::binary );
     if ( !inFile )
     {
          std::cerr << "Error: Unable to open input file" << std::endl;
          return;
     }

     // Read header information
     int totalEncodedChars , totalEncodedBytes , originalChars;
     inFile.read ( reinterpret_cast< char * >( &totalEncodedChars ) , sizeof ( totalEncodedChars ) );
     inFile.read ( reinterpret_cast< char * >( &totalEncodedBytes ) , sizeof ( totalEncodedBytes ) );
     inFile.read ( reinterpret_cast< char * >( &originalChars ) , sizeof ( originalChars ) );
     

     std::cout << "Total Chars: " << totalEncodedChars << std::endl;
     std::cout << "Encoding Size: " << totalEncodedBytes << std::endl;
     std::cout << "Original Chars: " << originalChars << std::endl;

     // Reconstruct Huffman tree from encoded data
     NodeTree *root = readHuffmanTree ( inFile );
     if ( !root )
     {
          std::cerr << "Error: Failed to decode Huffman tree" << std::endl;
          inFile.close ( );
          return;
     }

     // Decompress the encoded data
     std::ofstream outFile ( outputFile , std::ios::binary );
     if ( !outFile )
     {
          std::cerr << "Error: Unable to open output file" << std::endl;
          inFile.close ( );
          delete root; // Clean up Huffman tree before returning
          return;
     }

     int decodedChars = 0; // Track the number of characters decoded
     NodeTree *currentNode = root;
     char byte;
     while ( inFile.read ( &byte , sizeof ( byte ) ) && decodedChars < originalChars )
     {
          // Process each bit in the byte
          for ( int i = 7; i >= 0 && decodedChars < originalChars; --i )
          {
               // Extract the bit
               bool bit = ( byte >> i ) & 1;

               // Traverse the Huffman tree
               currentNode = bit ? currentNode->right : currentNode->left;

               // If we've reached a leaf node, write the character to the output file
               if ( currentNode->isLeaf ( ) )
               {
                    outFile.put ( currentNode->data );

                    // Debugging: Print decoded character and current count
                    std::cout << "Decoded Character[" << decodedChars << "]: " << currentNode->data << std::endl;

                    currentNode = root;
                    ++decodedChars;

               }
          }
     }

     // Check if the number of decoded characters matches the expected count
     if ( decodedChars != originalChars )
     {
          std::cerr << "Error: Unexpected number of characters after decompression" << std::endl;
          inFile.close ( );
          outFile.close ( );
          delete root;
          return;
     }

     // Close files and clean up memory
     inFile.close ( );
     outFile.close ( );
     delete root;

     std::cout << "File decompressed successfully.\n";
}

int main ( )
{
     std::string compressedFile = "compressed.bin";
     std::string decompressedFile = "decompressed.txt";
     decompressFile ( compressedFile , decompressedFile );
     return 0;
}