// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include<limits>
#include<cstdlib>
#include<ctime>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for(int i = 1; i < data.size(); ++i){
	int ele = data[i];
	int j = i - 1;
	for(; j >= 0 && ele < data[j]; --j){	
	    data[j + 1] = data[j];
 	}
	data[j + 1] = ele;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    srand(time(NULL));
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if(low < high){
	int middle = Partition(data, low, high);
	QuickSortSubVector(data, low, middle - 1);
	QuickSortSubVector(data, middle + 1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171 
    int random = rand() % (high - low + 1) + low;
    swap(data[random], data[high]);
    int x = data[high];
    int i = low - 1;
    for(int j = low; j < high; ++j){
	if(data[j] <= data[high]){
	    ++i;
	    swap(data[i], data[j]);
	}
    }
    swap(data[i + 1], data[high]);
    return i + 1;	  
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low < high){
 	int middle1 = (low + high)/2;
 	int middle2 = middle1 + 1;
	MergeSortSubVector(data, low, middle1);
	MergeSortSubVector(data, middle2, high);
	if(data[middle1] > data[middle2]){
	    Merge(data, low, middle1, middle2, high);
	}
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int leftIndex = 0; // index into left subvector              
    int rightIndex = 0; // index into right subvector         
    vector<int> leftvec(middle2-low+1);  
    vector<int> rightvec(high-middle2+2);
    int i = low;
    for(; i < middle2; ++i)
	leftvec[i-low] = data[i];
    leftvec[leftvec.size() - 1] = (std::numeric_limits<int>::max());
    for(i = middle2; i < high+1; ++i)
	rightvec[i - middle2] = data[i];
    rightvec[rightvec.size() - 1] = (std::numeric_limits<int>::max());
    for(i = low; i <= high; ++i){
        if(leftvec[leftIndex] <= rightvec[rightIndex]){
            data[i] = leftvec[leftIndex];
            ++leftIndex;
        }	
        else{
	    data[i] = rightvec[rightIndex];
            ++rightIndex;
        }	
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; --i) {
        swap(data[0],data[i]);
        --heapSize;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int l = 2*(root+1) - 1;
    int r = 2*(root+1);
    int max = root;
    if(l < heapSize && data[l] > data[root])
	max = l;
    if(r < heapSize && data[r] > data[max])
	max = r;
    if(max != root){
	swap(data[root], data[max]);
	MaxHeapify(data, max);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i = heapSize/2 - 1; i >= 0; --i)
	MaxHeapify(data, i);
}
