// Exam 1 Question 1
// Kaylee Lewis

// The insertion sort algorithm works on an array that has been partitioned into a sorted
// and unsorted subarrays.
// Each iteration selects one item from the unsorted part and inserts it into the correct position in the sorted part.
// This happens by iterating through the sorted part of the array to find the insertion point.
// This last step is done using a linear search.
// Implement an insertion sort function in your language of choice using the psuedocode below as a guide ,
// remembering to make the code as generic as possible ( i..e. , use templates in C++ , duck typing in Python ).
// Then , implement a second function that implements binary insertion sort where the insertion point in the sorted list
// is found using binary search ( yep , you get to write a binary search function here too ).
// Include a comment in your source code that explains why this has a better time efficiency that regular insertion sort
// ( using Big - Oh ).

// https://www.geeksforgeeks.org/binary-insertion-sort/
// https://www.geeksforgeeks.org/insertion-sort/
// https://www.geeksforgeeks.org/binary-search/
// https://www.geeksforgeeks.org/chrono-in-c/?ref=header_search
// https://www.geeksforgeeks.org/measure-execution-time-function-cpp/

// The binary insertion sort algorithm is an improvement to the regular insertion sort algorithm.
// Efficiency is improved when finding the correct insertion point reducing comparisons from
// linear to logarithmic time complexity (O(n log n)).

#include <iostream>
#include <vector>
#include <chrono>

// Function using regular insertion sort
template<typename T>
void insertionSort(std::vector<T>& arr)
{
    int n = arr.size();

    // for loop to iterate through the array
    for (int i = 1; i < n; i++) 
     {
        int j = i;

        // while loop to find the insertion point
        while (j > 0 && arr[j - 1] > arr[j]) 
        {
            std::swap(arr[j], arr[j - 1]);
            j--;
        }
    }
}

// Function using binary insertion sort
template<typename T>
void binaryInsertionSort(std::vector<T>& arr)
{
    int n = arr.size();

    // for loop to iterate through the array
    for (int i = 1; i < n; i++) 
    {
        T key = arr[i];
        int left = 0;
        int right = i - 1;
        int j = i - 1;

        // while loop to find the insertion point
        while (left <= right) 
        {
            int mid = left + (right - left) / 2;

            // if statement to check if the middle value is greater than the key
            if (arr[mid] > key) 
            {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        // while loop to shift the elements to the right
        while (j >= left) 
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[left] = key;
    }
}

int main()
{
    std::vector<int> arr = {5, 2, 8, 1, 9};
     std::cout << "Array before Insertion: ";
    for ( int num1 : arr )
    {
         std::cout << num1 << " ";
    }
    std::cout << std::endl;
    // Regular Insertion Sort
    auto startRegular = std::chrono::steady_clock::now ( );
    insertionSort ( arr );
    std::cout << "Regular Insertion Sort: ";
    for (int num : arr) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    auto endRegular = std::chrono::steady_clock::now ( );
    std::cout << "Regular Insertion Sort Time: " << std::chrono::duration_cast< std::chrono::microseconds >( endRegular - startRegular ).count ( ) << " microseconds" << std::endl;

     // Binary Insertion Sort
         // Test the speed of Binary Insertion Sort
    std::vector<int> arr2 = { 5, 2, 8, 1, 9 }; // Reset the array
    auto startBinary = std::chrono::steady_clock::now ( );
    binaryInsertionSort(arr2);
    std::cout << "Binary Insertion Sort: ";
    for (int num : arr2) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    auto endBinary = std::chrono::steady_clock::now ( );
    std::cout << "Binary Insertion Sort Time: " << std::chrono::duration_cast< std::chrono::microseconds >( endBinary - startBinary ).count ( ) << " microseconds" << std::endl;

    return 0;
}
