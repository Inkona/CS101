//file input output
//getline() read from file
//store in list or linked list

//probe getline to get singular word
//run singular word through correct hashing algo
//place word into hashtable

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
   list<string> hashList;
   
   void map();

   void dhMap();

   

};

int main(int argc, char **argv) {
   ifstream f1(argv[0]), f2(argv[1]);
   int tableSize = atoi(argv[2]);
   string lineRead;
   string singleWord;
   if(argc != 4)
   {
      int dhk = atoi(argv[4]);
   }
   
   while(!feof)
   {
      getline(f1, lineRead);
      sscanf(lineRead, "%s", singleWord);



      if(argv[3] == "lp")
      {
         
      }
      else if(argv[3] == "qp")
      {

      }
      else if(argv[3] == "dh")
      {

      }
      else
      {
         cout << "FAILURE: IMPROPER COLLISION RESOLUTION STRATEGY" << endl;
      }
   }
   return 0;
}
