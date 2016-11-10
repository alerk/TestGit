#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;
/**
arr[]: array to be sorted
low: starting index
high: ending index
*/
int printList(int arr[], int size);
int swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
	return 0;
}
// This function takes last element as pivot, places the pivot at its correct position in sorted array, and places all smaller to left of pivot and all greater elements to right of pivot
int partition(int arr[], int low, int high)
{
	int pivot = arr[high];
	int pi = high;
	int i, j;
	j = low - 1;
	for (i=low; i<high; i++)
	{
		if(arr[i] <= pivot)
		{
			j++;cout << "j = " << j << " "; 
			if(arr[i]!=arr[j])
			{
				swap(arr[i], arr[j]);
				cout << "; swap  " << arr[j] << " " << arr[i] << ": ";
			}
			printList(arr, 9);
		}
	}
	cout << "swap " << arr[j+1] << " " << arr[high] << " ";
	swap(arr[j+1], arr[high]);
	printList(arr,9);
	return j+1;
}

int printList(int arr[], int size)
{
	for(int i=0;i<size;i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

int quickSort(int arr[], int low, int high)
{
	cout << "quickSort: low " << low << "; high " << high << endl;
	if(low<high)
	{
		//do the partitioning for seperating low -> (high-1) and high -> max
		int pi = partition(arr, low, high);
		//Separately sort elements before partition and after parition
		quickSort(arr, low, pi-1);
		quickSort(arr, pi+1, high);
	}
	return 0;	
}

int main(void)
{
int arr[] = {1,4,2,53,34,11,7,9,15};
int size = sizeof(arr)/sizeof(int);

int low = 0;
int high = size-1;
cout << "Size: " << size << endl;

quickSort(arr, low, high);

for(int i=0; i<size; i++)
{
	cout << arr[i] << " ";
}
cout << endl;
return 0;
}
