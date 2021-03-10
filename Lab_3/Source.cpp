#include <iostream>
#include <cmath>
#include<bits/stdc++.h>
#include <map>
using namespace std;
struct data {
	float x;
	float y;
	float z;
};
/*
Bubble sort
*/
void bubble_sort(data *arr,size_t size) {
	int i,j;
	float length[size+2];
	for (i=0; i<size-1; i++) {
		length[i]=sqrt(arr[i].x*arr[i].x+arr[i].y*arr[i].y+arr[i].z*arr[i].z);
		for (j=i+1; j<size; j++) {
			length[j]=sqrt(arr[j].x*arr[j].x+arr[j].y*arr[j].y+arr[j].z*arr[j].z);
			if (length[j]<length[i]) {
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
void quickSort(data *arr, int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
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
void mergesort(data *A, data * temp, int low, int high,int N)
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
Auto Merge Sort
*/



/*
Print
*/
void print(data *arr,size_t size) {
	for (int i=0; i<size; i++) {
		cout << arr[i].x << " "<<arr[i].y << " "<<arr[i].z << endl;
	}
}
void generation(data* A, int n){
	 for (int i = 0; i < n; i++) {
        A [i].x = (rand() % 100);
        A [i].y = (rand() % 100);
        A [i].z = (rand() % 100);
    }
} 
void generation_plus_copy(data* A, data* temp, int n){
	 for (int i = 0; i < n; i++) {
        temp[i].x = A[i].x = (rand() % 50);
        temp[i].y = A[i].y = (rand() % 50);
        temp[i].z = A[i].z = (rand() % 50);
    }
}

int main() {
	data my_array[5]= {{1,2,3},{12,12,23},{12,65,23},{23,65,32},{12,23,4}};
	bubble_sort(my_array, 5);
	print(my_array, 5);
	cout << endl;
	
	data arr[5]= {{1,2,3},{12,12,23},{12,65,23},{23,65,32},{12,23,4}};
	quickSort(arr, 0, 4);
	print(arr, 5);
	cout << endl;
	
	int numb_of_merge=10;
	data A[numb_of_merge], temp[numb_of_merge];
    // generate random input of integers
    generation_plus_copy(A,temp,numb_of_merge);
 
    cout << "Original array: " << endl;
    print(A,numb_of_merge);
    cout << endl;
 
    // sort array `A[0…N-1]` using a temporary array temp
    mergesort(A, temp, 0, numb_of_merge-1, numb_of_merge);
 
    print(A,numb_of_merge);
	
	return 0;
}


