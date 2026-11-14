// This file contains the most common sort algorithms for Arrays, Trees, and Graphs.
// Input is read from a text file containing the array's length and its elements.
// You can modify the numbers in the input file to test the algorithms.

#include <iostream>
#include <fstream>

using namespace std;

void Array();

int main(int argc, char **argv){
    Array();
    return 0;
}


void MergeSortRic(int *array, int start, int end){
    int m = (start+end)/2;
    int k = start, j = m+1, i=0;
    int *tmp = new int[end-start+1];         //create support array
    while(k<m+1 && j <=end){                 // Merge the two sorted halves into tmp
        if(array[k]>array[j]){  
            tmp[i]=array[j];
            j++;
        }else {                             
            tmp[i]=array[k];
            k++;
        }
        i++;
    }

    while(k<m+1){                           // Copy any remaining elements from the left half, if any                          
        tmp[i]=array[k];
        k++;
        i++;
    }

    while(j<=end){                          // Copy any remaining elements from the right half, if any
        tmp[i]=array[j];
        j++;
        i++;
    }
    for(int i=0;i<end-start+1;i++)array[start+i]=tmp[i];   // Copy back the sorted elements to the original array
    delete [] tmp;                                         // Free the dynamically allocated memory
}

void MergeSort(int *array, int start, int end){
    if(start>=end)return;                                           //check if the array is already sorted
    int m = (start+end)/2;                                          //O(nlog(n)) time complexity
    MergeSort(array, start, m);                                     //Recursively sort the first and second halves
    MergeSort(array, m+1, end);
    MergeSortRic(array, start, end);                                // Assuming [start, m] and [m+1, end] are sorted, we now combine them.
}

int FindPivot(int *array, int start, int end){ 
    int mid = start + (end - start) / 2;
    if (array[start] > array[end])swap(array[start], array[end]);
    if (array[mid] > array[end])swap(array[mid], array[end]);        // Median-of-three: uses if conditions to find a better pivot and avoid the worst-case scenario.
    if (array[mid] > array[start])swap(array[mid], array[start]);    // Partitions the array around the pivot, places it in its correct sorted position, and returns that index.
    int m=array[start], j=start;                                 // If an element is smaller than the pivot, increment j and swap to expand the partition of smaller elements.
    for(int i=start+1;i<=end;i++){                               // At the end, place the pivot in its correct position by swapping it with array[j] (last smaller number found).
        if(m>array[i]){                                          // O(n log n) time complexity in the average and best cases, O(n^2) in the worst case (Merge Sort guarantees O(n log n) worst-case).
            j++;
            swap(array[i], array[j]);
        }
    }
    swap(array[start], array[j]);
    return j;
}

void QuickSort(int *array, int start, int end){
    if(start>end)return;
    int pivot = FindPivot(array, start, end);  //search pivot (index) and put it in the rigth position
    QuickSort(array, start, pivot-1);          //do the same thing with the left and right part of the array
    QuickSort(array, pivot+1, end);
}



void CountingSort(int *array, int length){              // Uses a support array to count occurrences (tmp[array[i] - min]++), incrementing it if the same number appears more than once.
    if(length<2)return;                                 // O(n+k) time complexity, where 'n' is the length of the array and 'k' is max-min+1 (check the outer while loop).
    int max=array[0], min=array[0], j=0, k=0;           // Do not use it when the range of numbers is very big due to high memory usage.
    for(int i=1;i<length;i++){
        if(min>array[i])min=array[i];
        if(max<array[i])max=array[i];
    }
    int *tmp=new int[max-min+1]();
    for(int i=0;i<length;i++)tmp[array[i]+abs(min)]++;
    while(j<length){
        while (tmp[k]!=0){
            array[j]=k+min;
            tmp[k]--;
            j++;
        }
        k++;        
    }
    delete [] tmp;
}

void SelectionSort(int *array, int length){  // Finds the minimum of the array and puts it in the first place, repeating n times.
    int min, k;                              // O(n^2) time complexity in the best and worst cases.
    for(int i = 0;i<length;i++){             //uses of k to save the position of the min
        min=array[i];
        k=i;
        for(int j=i+1;j<length;j++){
            if(min>array[j]){
                min=array[j]; 
                k=j;
            }
        }
        if(k!=i){                            //if k==i we can skip the swap because the min is already in position
            array[k]=array[i];
            array[i]=min;
        }
        }
}




void InsertionSort(int *array, int length){  // Takes the element at index i and shifts it backwards as long as the previous elements are greater.
    int tmp, j,k;                            //O(n^2) in the worst case                             
    for(int i =0;i<length;i++){              //uses of j for previous element (i-1 at the start of the while) and k for the ordered position of the element (i at the start of while) 
        tmp=array[i];                        //O(1) space cost
        j=i-1;
        k=i;
        while(k!=0 && tmp<array[j]){         // Check if the position is 0 (we can't shift back) or if tmp is greater than the previous number
            array[k] = array[j];             // When the loop ends, we put tmp into its correct position
            k--;
            j--;
        }
        array[k]=tmp;
    } 
}


void PrintArray(int *array ,int length){
    for(int i=0;i<length;i++)cout<<array[i]<<" ";
    cout<<"\n\n";
}

void CopyArray(int *ArrayToPaste, int *ArrayB, int length){
    for(int i=0;i<length;i++)ArrayB[i]=ArrayToPaste[i];
}

void Array(){
ifstream in("inputArray.txt");
if(!in.is_open()){
    cout<<"The input file does not exist in your directory!!"<<endl;
    exit(1);
}
    int lengthArray;
    in>>lengthArray;
    int *arrayToSort=new int[lengthArray];
    int *array=new int[lengthArray];
    for(int i=0;i<lengthArray;i++)in>>array[i];
    CopyArray(array, arrayToSort, lengthArray);
    cout<<"\nArray before the sort: ";
    PrintArray(arrayToSort, lengthArray);
    InsertionSort(arrayToSort, lengthArray);
    cout<<"\nArray after INSERTION SORT: ";
    PrintArray(arrayToSort, lengthArray);
    CopyArray(array, arrayToSort, lengthArray);
    cout<<"\nArray before the sort: ";
    PrintArray(arrayToSort, lengthArray);
    SelectionSort(arrayToSort, lengthArray);
    cout<<"\nArray after SELECTION SORT: ";
    PrintArray(arrayToSort, lengthArray);
    CopyArray(array, arrayToSort, lengthArray);
    cout<<"\nArray before the sort: ";
    PrintArray(arrayToSort, lengthArray);
    CountingSort(arrayToSort, lengthArray);
    cout<<"\nArray after COUNTING SORT: ";
    PrintArray(arrayToSort, lengthArray);
    CopyArray(array, arrayToSort, lengthArray);
    cout<<"\nArray before the sort: ";
    PrintArray(arrayToSort, lengthArray);
    QuickSort(arrayToSort, 0,lengthArray-1);
    cout<<"\nArray after QUICK SORT: ";
    PrintArray(arrayToSort, lengthArray);
    CopyArray(array, arrayToSort, lengthArray);
    cout<<"\nArray before the sort: ";
    PrintArray(arrayToSort, lengthArray);
    MergeSort(arrayToSort, 0,lengthArray-1);
    cout<<"\nArray after MERGE SORT: ";
    PrintArray(arrayToSort, lengthArray);
    in.close();
    delete [] arrayToSort;
}
