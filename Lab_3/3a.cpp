#include <iostream>
#include <algorithm>
#include <cmath>
#include<bits/stdc++.h>
#include <map>
#include <ctime>
using namespace std;
struct data {
	float x;
	float y;
	float z;
	//for sort;
	float length = 0 ;
};
/*
Bubble sort
*/
void bubble_sort(data *arr,size_t size) {
	int i,j;
	for (i=0; i<size-1; i++) {
		arr[i].length=sqrt(arr[i].x*arr[i].x+arr[i].y*arr[i].y+arr[i].z*arr[i].z);
		for (j=i+1; j<size; j++) {
			arr[j].length=sqrt(arr[j].x*arr[j].x+arr[j].y*arr[j].y+arr[j].z*arr[j].z);
			if (arr[i].length>arr[j].length) {
				data temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
}
/*
Quick sort
*/
int partition(data* arr, int low, int high) 
{ 
    float pivot = sqrt(arr[high].x*arr[high].x+arr[high].y*arr[high].y+arr[high].z*arr[high].z);    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than or 
        // equal to pivot 
        float length=sqrt(arr[j].x*arr[j].x+arr[j].y*arr[j].y+arr[j].z*arr[j].z);
        if (length <= pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(arr[i], arr[j]); 
        } 
    } 
    swap(arr[i + 1], arr[high]); 
    return (i + 1); 
} 
void quick_sort(data *arr, int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quick_sort(arr, low, pi - 1); 
        quick_sort(arr, pi + 1, high); 
    } 
}
/*
Merge Sort
*/
int min(int x, int y) {
    return (x < y) ? x : y;
}
 
// Merge two sorted subarrays `A[from…mid]` and `A[mid+1…to]`
void merge(data *arr1, data* temp, int from, int mid, int to,int N)
{
		double length[N];
 	for(int i=from; i<=to;i++)
 		length[i]=sqrt(arr1[i].x*arr1[i].x+arr1[i].y*arr1[i].y+arr1[i].z*arr1[i].z);
	 
	 
    int k = from, i = from, j = mid + 1;
 	
    // loop till no elements are left in the left and right runs
    while (i <= mid && j <= to)
    {
        if (length[i] < length[j]) {
            temp[k].x = arr1[i].x;
            temp[k].y = arr1[i].y;
            temp[k].z = arr1[i].z;
            k++;
            i++;
        }
        else {
            temp[k].x = arr1[j].x;
            temp[k].y = arr1[j].y;
            temp[k].z = arr1[j].z;
            k++;
            j++;
        }
    }
    // copy remaining elements
    while (i < N && i <= mid) {
        temp[k].x = arr1[i].x;
        temp[k].y = arr1[i].y;
        temp[k].z = arr1[i].z;
        k++;
        i++;
    }
    for (int i = from; i <= to; i++) {
        arr1[i].x = temp[i].x;
        arr1[i].y = temp[i].y;
        arr1[i].z = temp[i].z;
        
    }
}
 
// Iteratively sort subarray `A[low…high]` using a temporary array
void merge_sort(data *A, data * temp, int low, int high,int N)
{
    // divide the array into blocks of size `m`
    // m = [1, 2, 4, 8, 16…]
    for (int m = 1; m <= high - low; m = 2*m)
    {
        for (int i = low; i < high; i += 2*m)
        {
            int from = i;
            int mid = i + m - 1;
            int to = min(i + 2*m - 1, high);
 
            merge(A, temp, from, mid, to, N);
        }
    }
}
/*
Auto Sort
*/


/*
Print
*/
void print(data *arr,size_t size) {
	for (int i=0; i<size; i++) {
		cout << arr[i].x << " "<<arr[i].y << " "<<arr[i].z << endl;
	}
	cout << endl;
}
/*
Generation and copy
*/
void generation(data* A, int n){
	 for (int i = 0; i < n; i++) {
        A [i].x = (rand() % 100);
        A [i].y = (rand() % 100);
        A [i].z = (rand() % 100);
    }
} 
void generation_one(data *A, int n){
	for (int i = 0; i < n; i++) {
        A [i].x = 1;
        A [i].y = 1;
        A [i].z = 1;
    }
}
void generation_plus_copy(data* A, data* temp, int n){
	 for (int i = 0; i < n; i++) {
        temp[i].x = A[i].x = (rand() % 50);
        temp[i].y = A[i].y = (rand() % 50);
        temp[i].z = A[i].z = (rand() % 50);
    }
}
void generation_plus_copy_one(data* A, data* temp, int n){
	 for (int i = 0; i < n; i++) {
        temp[i].x = A[i].x = 1;
        temp[i].y = A[i].y = 1;
        temp[i].z = A[i].z = 1;
    }
}
data* copy_array_loop(data* arr, int size) {
	data* result = new data[size];
	for(std::size_t i = 0; i< size; i++) {
		result[i].x = arr[i].x;
		result[i].y = arr[i].y;
		result[i].z = arr[i].z;
	}
	return result;
	delete[] result;
}
/*
Demonstration mode
*/
void benchmark_mode(){
	int size_of_array;
	cout << "Enter the size of the array: "<<endl;
	cin >> size_of_array;
	data* A=new data[size_of_array], *temp=new data[size_of_array];
	//generation_plus_copy_one(A,temp,size_of_array);
	generation_plus_copy(A,temp,size_of_array);
	unsigned int start=0, end=0, dif=0;
	data* A1=new data[size_of_array];
	A1=copy_array_loop(A,size_of_array);
	data* A2=new data[size_of_array];
	A2=copy_array_loop(A,size_of_array);
	
	cout << "Bubble sort: ";
	start=clock();
	bubble_sort(A,size_of_array);
	end=clock();
	//print(A, size_of_array);
	cout << end-start << " ms"<<endl;
	
	cout << "Quick sort: ";
	start=clock();
	quick_sort(A1,0,size_of_array-1);
	end=clock();
	//print(A1, size_of_array);
	cout << end-start << " ms"<<endl;
	
	cout << "Merge sort: " ;
	start=clock();
	merge_sort(A2, temp, 0, size_of_array-1, size_of_array);
	end=clock();
	//print(A2, size_of_array);
	cout << end-start << " ms"<<endl;
	
	delete[] A1,A2,A,temp;
	
}

int main() {
	int global_mode=0;
	cout << "Select the operating mode: 1 Demonstration mode, 2 Benchmark mode, 9 EXIT: "<<endl;
	cin >> global_mode;
	switch (global_mode)
	{
	case 1:
	//	demo_mode();
		break;
	case 2:
		benchmark_mode()
		break;
	case 9:
		return 0;
	default:
		cerr << "Error data!"<<endl;
		break;
	}
	
	return 0;
}


