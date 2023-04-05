//probe getline to get singular word
//run singular word through correct hashing algo
//place word into hashtable

//fix word read in 
//count collisions
//print table and values


#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
#include <vector>
#include <list>
//false include since in std lib
#include <map>
//ree

using namespace std;

// Store the return of this function as an unsigned long!
unsigned long djb2(string str) {
   const char *ptr = str.c_str();
   unsigned long hash = 5381;
   int c;
   while ((c = *ptr++)) {
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
   }
   return hash;
}

class HashTable {
   vector<string> table;
   int capacity;

public: 
   int collisions = 0;
   int uniqueWords = 0;
   //
   HashTable(int X);
   //
   void insertLP(string str);
   void insertQP(string str);
   void insertDH(string str, int dhk);

   void searchLP(string str);
   void searchQP(string str);
   void searchDH(string str, int dhk);
};

HashTable::HashTable(int tableSize)
{
   int size = tableSize;
   this->capacity = size;
   table.resize(capacity); 
   fill(table.begin(), table.end(), " ");
}

void HashTable::insertLP(string str)
{
   int locCol = 0;
   int index = 0;
   for(int i = 0; i < (int) table.size(); i++)
   {
      index = (djb2(str) + i) % capacity;
      if(table.at(index) == " ")
      {
         table.at(index) = str;
      }
      locCol = i;
   }
   collisions += locCol;
}

void HashTable::insertQP(string str)
{
   int locCol = 0;
   int index = 0;
   for(int i = 0; i < (int) table.size(); i++)
   {
      index = (djb2(str) + i * i) % capacity;
      if(table.at(index) == " ")
      {
         table.at(index) = str;
      }
      else if(table.at(index) == str)
      {

      }
      locCol = i;
   }
   collisions += locCol;
}

void HashTable::insertDH(string str, int dhk)
{
   int locCol = 0;
   int index = 0;
   for(int i = 0; i < (int) table.size(); i++)
   {
      index = (djb2(str) + i * (dhk - (djb2(str) % dhk))) % capacity;
      if(table.at(index) == " ")
      {
         table.at(index) = str;
      }
      locCol = i;
   }
   collisions += locCol;
}

int main(int argc, char **argv) {
   ifstream f1(argv[0]), f2(argv[1]);
   int tableSize = atoi(argv[2]);
   string lineRead;
   string singleWord;
   int count = 0;
   int dhk = 0;
   HashTable myTable(tableSize);
   map<string, list<int>> myMap;
   if(argc != 4)
   {
      dhk = atoi(argv[4]);
   }
   
   //DOESNT ENTER HERE
   while(!feof)
   {
      getline(f1, lineRead);
 
      istringstream instream(lineRead);
      while(instream >> singleWord)
      {
         //if(singleWord != ())
         cout << singleWord << " - GOT WORD" << endl;

         if(argv[3] == "lp")
         {
            myTable.insertLP(singleWord);
            count++;
            cout << "RAN LP" << endl;
         }
         else if(argv[3] == "qp")
         {
            myTable.insertQP(singleWord);
            count++;
            cout << "RAN QP" << endl;
         }
         else if(argv[3] == "dh")
         {
            myTable.insertDH(singleWord, dhk);
            count++;
            cout << "RAN DH" << endl;
         }
         else
         {
            cout << "FAILURE: IMPROPER COLLISION RESOLUTION STRATEGY" << endl;
         }
      }
   }
   cout << "The number of words found in the file was " << count << endl;
   cout << myTable.collisions << endl;
   return 0;
}