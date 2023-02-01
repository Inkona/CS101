#include <iostream>
#include <cstring>
#include <fstream>

// Include any necessary libraries here.

using namespace std;

int main() {
   string fileToOpen;
   cin >> fileToOpen;
   string fileName;
   ifstream inFile;
   inFile.open(fileToOpen);

   while(getline(inFile, fileName)) {
      fileName.erase(fileName.find("photo.jpg"));
      fileName.append("info.txt");
      cout << fileName << "\n";
   }

   return 0;
}