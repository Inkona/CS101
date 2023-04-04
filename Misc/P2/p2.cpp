#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void Merge(int numbers[], int i, int j, int k) {
   int mergedSize;                            // Size of merged partition
   int mergePos;                              // Position to insert merged number
   int leftPos;                               // Position of elements in left partition
   int rightPos;                              // Position of elements in right partition
   int* mergedNumbers = nullptr;

   mergePos = 0;
   mergedSize = k - i + 1;
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   mergedNumbers = new int[mergedSize];       // Dynamically allocates temporary array
                                              // for merged numbers
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if (numbers[leftPos] < numbers[rightPos]) {
         mergedNumbers[mergePos] = numbers[leftPos];
         ++leftPos;
      }
      else {
         mergedNumbers[mergePos] = numbers[rightPos];
         ++rightPos;
         
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = numbers[leftPos];
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = numbers[rightPos];
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      numbers[i + mergePos] = mergedNumbers[mergePos];
   }
   delete[] mergedNumbers;
}
void MergeSort(int numbers[], int i, int k) {
   int j;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSort(numbers, i, j);
      MergeSort(numbers, j + 1, k);
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k);
   }
}

int Partition(string strings[], int i, int k) {
   int l;
   int h;
   int midpoint;
   string pivot;
   string temp;
   bool done;
   
   /* Pick middle element as pivot */
   midpoint = i + (k - i) / 2;
   pivot = strings[midpoint];
   
   done = false;
   l = i;
   h = k;
   
   while (!done) {
      
      /* Increment l while strings[l] < pivot */
      while (strings[l] < pivot) {
         ++l;
      }
      
      /* Decrement h while pivot < strings[h] */
      while (pivot < strings[h]) {
         --h;
      }
      
      /* If there are zero or one elements remaining,
       all strings are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap strings[l] and strings[h],
          update l and h */
         temp = strings[l];
         strings[l] = strings[h];
         strings[h] = temp;
         
         ++l;
         --h;
      }
   }
   
   return h;
}

void Quicksort(string strings[], int i, int k) {
   int j;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = Partition(strings, i, k);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   Quicksort(strings, i, j);
   Quicksort(strings, j + 1, k);
}

int main(int argc, char *argv[]){
    ifstream f1(argv[2]), f2(argv[3]);
    if(*argv[1] == 'i')
    {
        int in;
        int index = 0;
        int arr1[20001] = {0};
        int arr2[20001] = {0};
        int size1 = 0;
        int size2 = 0;
        while(f1 >> in)
        { 
            arr1[index] = in;
            index++;
            size1++;
        }

         index = 0;
         while(f2 >> in)
        { 
            arr2[index] = in;
            index++;
            size2++;
        }

      MergeSort(arr1, 0, size1 - 1);
      MergeSort(arr2, 0, size2 - 1);

      int lastVal = arr1[0] - 100;
      for(int i = 0; i < size1; i++) {
         for(int j = 0; j < size2; j++) {
            if(arr1[i] == arr2[j] && lastVal != arr1[i]) {
               lastVal = arr1[i];
               cout << arr1[i] << endl;
            }
         }
      }
   }
   else if(*argv[1] == 's')
   {
        string in;
        int index = 0;
        string arr1[20001];
        string arr2[20001];
        int size1 = 0;
        int size2 = 0;
        while(f1 >> in)
        { 
            arr1[index] = in;
            index++;
            size1++;
        }

         index = 0;
         while(f2 >> in)
        { 
            arr2[index] = in;
            index++;
            size2++;
        }

      //Quicksort(arr1, 0, size1 - 1);
      //Quicksort(arr2, 0, size2 - 1);

      sort(arr1, arr1 + size1);
      sort(arr2, arr2 + size2);

      string lastVal = "\0";
      for(int i = 0; i < size1; i++) {
         for(int j = 0; j < size2; j++) {
            if(arr1[i] == arr2[j] && lastVal != arr1[i]) {
               lastVal = arr1[i];
               cout << arr1[i] << endl;
            }
         }
      }
   //eof
   }
    return 0;
}