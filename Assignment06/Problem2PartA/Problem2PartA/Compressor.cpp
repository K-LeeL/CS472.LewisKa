// Assignment 06: A Greedy Exercise in File Compression
// Due: Fri Mar 22 , 2024 11 : 59pm
// Kaylee Lewis
// Problem 2 Part A:
// Create a file compressor that Huffman encodes a text file

// // www.techiedelight.com/huffman-coding/
// www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
// www.geeksforgeeks.org/huffman-decoding/
// https://www.codeconvert.ai/free-converter

// Compressor.cpp

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <algorithm>
#include <bitset>

class NodeTree 
{
public:
    char data;
    NodeTree* left;
    NodeTree* right;

    NodeTree(char data, NodeTree* left = nullptr, NodeTree* right = nullptr)
        : data(data), left(left), right(right) {}

    ~NodeTree() {
        delete left;
        delete right;
    }

    bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
};

// Function to create a code tree for huffman encoding
std::unordered_map<char , std::string> huffmanCodeTree ( NodeTree *node , std::string binString )
{
     std::unordered_map<char , std::string> codeMap;
     if ( node == nullptr )
     {
          std::cout << "Reached nullptr node." << std::endl;
          return codeMap;
     }
     if ( node->isLeaf ( ) )
     {
          std::cout << "Leaf node found: " << node->data << std::endl;
          codeMap [ node->data ] = binString;
     } else
     {
          std::cout << "Traversing left child." << std::endl;
          auto leftMap = huffmanCodeTree ( node->left , binString + "0" );
          codeMap.insert ( leftMap.begin ( ) , leftMap.end ( ) );

          std::cout << "Traversing right child." << std::endl;
          auto rightMap = huffmanCodeTree ( node->right , binString + "1" );
          codeMap.insert ( rightMap.begin ( ) , rightMap.end ( ) );
     }
     return codeMap;
}

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

          std::cout << "Creating parent node." << std::endl;
          nodePtrs.push_back ( new NodeTree ( '\0' , left , right ) );
     }
     return nodePtrs [ 0 ];
}

void encodeHuffmanTree(NodeTree *node, std::ofstream &out)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->isLeaf())
    {
        std::cout << "Leaf node found: " << node->data << std::endl;
        out.put('1');
        out.put(node->data);
    }
    else
    {
        std::cout << "Internal node found." << std::endl;
        out.put('0');
        encodeHuffmanTree(node->left, out);
        encodeHuffmanTree(node->right, out);
    }
}

void writeHeader(std::ofstream& outFile, int totalChars, int encodingSize, int originalChars, NodeTree* root) {
    outFile.write(reinterpret_cast<const char*>(&totalChars), sizeof(totalChars));
    std::cout << "Total Chars: " << totalChars << std::endl;

    outFile.write(reinterpret_cast<const char*>(&encodingSize), sizeof(encodingSize));
    std::cout << "Encoding Size: " << encodingSize << std::endl;

    outFile.write(reinterpret_cast<const char*>(&originalChars), sizeof(originalChars));
     std::cout << "Original Chars: " << originalChars << std::endl;

    encodeHuffmanTree(root, outFile);

    std::cout << "Header written" << std::endl;
}

void compressFile ( const std::string &inputFile , const std::string &outputFile )
{
     int originalChars = 0;
     std::ifstream inFile ( inputFile , std::ios::binary );
     if ( !inFile.is_open ( ) )
     {
          std::cerr << "Error: Unable to open input file" << std::endl;
          return;
     }

     std::unordered_map<char , int> freq;

     char ch;
     while ( inFile.get ( ch ) )
     {
          // Debugging output: Print characters being read
          std::cout << "Read character: " << ch << std::endl;

          // Increment character frequency
          freq [ ch ]++;
          originalChars++;
     }

     // Debugging output: Print character frequencies
     std::cout << "Character Frequencies:" << std::endl;
     for ( const auto &pair : freq )
     {
          std::cout << "'" << pair.first << "': " << pair.second << std::endl;
     }

     // Construct Huffman tree and generate Huffman codes
     std::vector<std::pair<char , int>> freqVec ( freq.begin ( ) , freq.end ( ) );
     NodeTree *root = makeTree ( freqVec );
     std::unordered_map<char , std::string> encoding = huffmanCodeTree ( root , "" );

     std::cout << "Huffman Codes:" << std::endl;
     for ( const auto &pair : encoding )
     {
          std::cout << "'" << pair.first << "': " << pair.second << std::endl;
     }

     // Calculate total characters after encoding
     size_t totalEncodedChars = 0;
     for ( const auto &pair : freqVec )
     {
          totalEncodedChars += pair.second * encoding [ pair.first ].length ( );
          std::cout << "Encoded character: '" << pair.first << "' (" << pair.second << " times) - " << encoding [ pair.first ] << std::endl;
     }

     // Calculate original characters (in bytes)
     int totalEncodedBytes = totalEncodedChars / 8 + ( totalEncodedChars % 8 != 0 ? 1 : 0 );

     // Debugging output: Print compression statistics
     std::cout << "Total characters in original text: " << originalChars << std::endl;
     std::cout << "Total characters after encoding: " << totalEncodedChars << std::endl;
     std::cout << "Encoded characters (in bytes): " << totalEncodedBytes << std::endl;
     std::cout << "Total unique characters: " << freq.size ( ) << std::endl;

     // Write compressed data to output file
     std::ofstream outFile ( outputFile , std::ios::binary );
     if ( !outFile.is_open ( ) )
     {
          std::cerr << "Error: Unable to open output file" << std::endl;
          delete root; // Free allocated memory before returning
          return;
     }

     // Write header information to output file
     writeHeader ( outFile , totalEncodedChars , totalEncodedBytes , originalChars , root );

     // Reset the input file stream to the beginning
     inFile.clear ( );
     inFile.seekg ( 0 , std::ios::beg );

     // Write the compressed data to the output file
     std::string buffer;
     while ( inFile.get ( ch ) )
     {
          buffer += encoding [ ch ];
          while ( buffer.size ( ) >= 8 )
          {
               std::bitset<8> bits ( buffer.substr ( 0 , 8 ) );
               buffer = buffer.substr ( 8 );
               char byte = static_cast< char >( bits.to_ulong ( ) );
               outFile.put ( byte );
          }
     }
     if ( !buffer.empty ( ) ) // Write the remaining bits, if any
     {
          std::bitset<8> bits ( buffer );
          char byte = static_cast< char >( bits.to_ulong ( ) );
          outFile.put ( byte );
     }

     // Close input and output files
     inFile.close ( );
     outFile.close ( );

     // Free allocated memory
     delete root;
}

int main ( )
{
     std::string inputFile = "input.txt";
     std::string compressedFile = "compressed.bin";
     compressFile ( inputFile , compressedFile );
     std::cout << "File compressed successfully." << std::endl;
     return 0;
}
