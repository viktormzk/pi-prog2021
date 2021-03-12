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
Selection sort
*/
void sel_sort(data arr[],size_t low, size_t size) {
	int i,j;
	for (i=low; i<size-1; i++) {
		for (j=i+1; j<size; j++) {
			if (arr[i].length>arr[j].length) {
				swap(arr[i],arr[j]);
			}
		}
	}
}
/*
Quick sort
*/

int partition(data *arr, int low, int high) 
{ 
    float pivot = arr[high].length;   
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than or 
        // equal to pivot 
        if (arr[j].length <= pivot) 
        { 
            i++;    
            swap(arr[i], arr[j]); 
        } 
    } 
    swap(arr[i + 1], arr[high]); 
    return (i + 1); 
} 

void quick_sort(data* arr, int low, int high) 
{ 
    if (low < high) 
    { 
        
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
void merge(data* arr1, data* temp, int from, int mid, int to,int N)
{
    int k = from, i = from, j = mid + 1;
 	
    // loop till no elements are left in the left and right runs
    while (i <= mid && j <= to)
    {
        if (arr1[i].length < arr1[j].length) {
            swap(temp[k],arr1[i]);
            k++;
            i++;
        }
        else {
            swap(temp[k],arr1[j]);;
            k++;
            j++;
        }
    }
    // copy remaining elements
    while (i < N && i <= mid) {
       swap(temp[k], arr1[i]);
        k++;
        i++;
    }
    for (int i = from; i <= to; i++) {
        swap(temp[i],arr1[i]);
              
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
Combined sort
*/
void combo_sort(data* arr,int low, int high){ 
  while (low < high)  
    {   
  //size 200 for simple sort, combo sort == hybrid quick sort
    if (high-low + 1 < 200) 
      { 
        //sel_sort(arr, high); 
        sel_sort(arr, low, high);//- more slow
      break; 
    } 
  
    else 
        
        { 
          int pivot = partition(arr, low, high) ; 

      if (pivot-low<high-pivot) 
        { 
          combo_sort(arr, low, pivot - 1);  
        low = pivot + 1; 
      } 
      else
        { 
        combo_sort(arr, pivot + 1, high); 
        high = pivot-1; 
        } 
  
     } 
  
   } 
} 
/*
3c Heap Sort
*/
// function to heapify the tree
void heapify(data arr[], int n, int root)
{
   int largest = root; // root is the largest element
   int l = 2*root + 1; // left = 2*root + 1
   int r = 2*root + 2; // right = 2*root + 2

   if (l < n && arr[l].length > arr[largest].length)
   largest = l;
  
   if (r < n && arr[r].length > arr[largest].length)
   largest = r;
  
   // If largest is not root
   if (largest != root)
      {
      swap(arr[root], arr[largest]);
      heapify(arr, n, largest);
      }
}
  
// implementing heap sort
void heap_sort(data arr[], int n)
{ 

   // build heap
   for (int i = n / 2 - 1; i >= 0; i--){
      heapify(arr, n, i);
  }
  
   for (int i=n-1; i>=0; i--)
   {
      swap(arr[0], arr[i]);
      heapify(arr, i, 0);
   }
}
/*
Print
*/
void print(data *arr,size_t size) {
	for (int i=0; i<size; i++) {
		cout << arr[i].x << " "<<arr[i].y << " "<<arr[i].z /*<<" "<<arr[i].length*/<<endl;
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
        A [i].length=sqrt(A[i].x*A[i].x+A[i].y*A[i].y+A[i].z*A[i].z);
    }
} 
void generation_one(data *A, int n){
	for (int i = 0; i < n; i++) {
        A [i].x = 0;
        A [i].y = 0;
        A [i].z = 0;
    	A [i].length=0;
    }
}
void generation_plus_copy(data* A, data* temp, int n){
	 for (int i = 0; i < n; i++) {
        temp[i].x = A[i].x = (rand() % 50);
        temp[i].y = A[i].y = (rand() % 50);
        temp[i].z = A[i].z = (rand() % 50);
        temp[i].length = A [i].length = sqrt(A[i].x*A[i].x+A[i].y*A[i].y+A[i].z*A[i].z);
    }
}
data* copy_array_loop(data* arr, int size) {
	data* result = new data[size];
	for(std::size_t i = 0; i< size; i++) {
		result[i].x = arr[i].x;
		result[i].y = arr[i].y;
		result[i].z = arr[i].z;
		result[i].length = arr[i].length;
	}
	return result;
	delete[] result;
}
/*
Benchmark mode
*/
void benchmark_mode(){
	int size_of_array;
	cout << "Enter the size of the array: "<<endl;
	cin >> size_of_array;
	data* A=new data[size_of_array+1];
	//generation_plus_copy_one(A,temp,size_of_array+1);
	//generation_one(A,size_of_array);
	generation(A,size_of_array);
	unsigned int start=0, end=0;
	data* A1=new data[size_of_array+1];
	A1=copy_array_loop(A,size_of_array+1);
	data* A2=new data[size_of_array+1];
	A2=copy_array_loop(A,size_of_array+1);
	data* A3=new data[size_of_array+1];
	A3=copy_array_loop(A,size_of_array+1);
	data* A4=new data[size_of_array+1];
	A4=copy_array_loop(A,size_of_array+1);
	data* temp=new data[size_of_array+1];
	temp=copy_array_loop(A,size_of_array+1);
	
	//print(A,size_of_array);
	
	cout << "Selection sort: ";
	start=clock();
	sel_sort(A,0,size_of_array);
	end=clock();
	cout << end-start << " ms"<<endl;
	//print(A, size_of_array);
	
	cout << "Quick sort: ";
	start=clock();
	quick_sort(A1,0,size_of_array-1);
	end=clock();
	cout << end-start << " ms"<<endl;
	//print(A1, size_of_array);
	
	cout << "Merge sort: " ;
	start=clock();
	merge_sort(A2, temp, 0, size_of_array-1, size_of_array);
	end=clock();
	cout << end-start << " ms"<<endl;
	//print(A2, size_of_array);
	
	
	cout << "Combo sort: " ;
	start=clock();
	combo_sort(A3, 0, size_of_array);
	end=clock();
	cout << end-start << " ms"<<endl;
	//print(A3, size_of_array);
	
    cout << "HEAP sort <TREE> : " ;
 	start=clock();
	heap_sort(A4, size_of_array);
	end=clock();
	cout << end-start << " ms"<<endl;
	//print(A4, size_of_array);
  
	
	delete[] A1,A2,A,A3,A4,temp;
	
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
		benchmark_mode();
		break;
	case 9:
		return 0;
	default:
		cerr << "Error data!"<<endl;
		break;
	}
	return 0;
}


