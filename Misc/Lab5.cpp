//mydynamicarray.cpp

#include <iostream>
using namespace std;

class MyDynamicArray {
 
    private:
    
        int size, capacity, error, *a;
        
    public:
    
        MyDynamicArray() {
            a = new int[capacity = 2];
            size = error = 0;
        }
        
        MyDynamicArray(int s) {
            a = new int[capacity = size = s];
            error = 0;
        }
        
        MyDynamicArray& operator= (const MyDynamicArray& src){
          
          size = src.size;
          capacity= src.capacity;
          error = src.error;
          free(a);
          
          a = new int[capacity];
          
          for ( int i = 0 ; i < size ; i++ )
            *(a+i) = (src.a[i]);
          
        }


        MyDynamicArray(const MyDynamicArray& src)  {
          
          size = src.size;
          capacity= src.capacity;
          error = src.error;
          
          int *temp = new int[capacity];
          for ( int i = 0 ; i < size ; i++ )
            *(temp+i) = (src.a[i]);

          a = temp;
        }
        
        ~MyDynamicArray() {
            delete[] a;
        }
        
        int& operator[](int i){
        
            if (i>=size || i < 0)
            {
              cout << "Out of bounds reference : " << i << endl;
              return error;
            }
            
            return *(a+i);
        }
        void add(int v) {
            
            // Add element to array
            if ( size < capacity ){
              *(a + size ) = v ;
              size++;
              return;
            }
            
            // new element doesn't fit double the size of array
            
            // new array with double capacity
            cout << "Doubling to : " << capacity * 2 << endl;
             
            int *temp = new int[capacity*2];
            
            // copy all elements to new array
            for ( int i = 0 ;  i < capacity ; i++ )
              *(temp + i) = *(a + i);
            
            // capacity is double
            capacity *= 2;
            *(temp + size ) = v ;
            size++;
            
            // free old array
            free(a);
            
            // point to new array
            a = temp;
        }
        
        void del() {
           size--;
           
           if ( size <= (.25) * capacity )
           {
             
             int new_capacity = (.5) * capacity;
             
             cout << "Reducing to :" << new_capacity << endl;

             int *temp = new int[ new_capacity ];
             
             for ( int i = 0 ;  i < size ; i++ )
              *(temp + i) = *(a + i);
              
            capacity = new_capacity;
            
            free(a);
            a = temp;
           }
           
        }
        
        int length() { return size;}
        
        void clear() {
            delete a;
            a = new int[capacity=2];
            size = 0;
        }
};