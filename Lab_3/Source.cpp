#include <iostream>
#include <cmath>
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
Print
*/
void print(data *arr,size_t size) {
	for (int i=0; i<size; i++) {
		cout << arr[i].x << " "<<arr[i].y << " "<<arr[i].z << endl;
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

	return 0;
}


