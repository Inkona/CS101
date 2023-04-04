//
// Created by Maddox Guthrie on 1/31/23.
//

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#define DEBUG false

int main(int argc, char *argv[]) {
    // Open the cipher file
    std::ifstream cipherFile;
    cipherFile.open(argv[1]);
    if(!cipherFile.is_open()) {
        std::cout << "ERROR: Could not open" << argv[1] << std::endl;
    }

    // Open the encoded text file
    std::ifstream encodedTextFile;
    encodedTextFile.open(argv[2]);
    if(!cipherFile.is_open()) {
        std::cout << "ERROR: Could not open" << argv[2] << std::endl;
    }

    std::string givenWord = argv[3];

    std::string mapLine, keyLine;
    getline(cipherFile, mapLine);
    getline(cipherFile, keyLine);

    // Create the base map
    std::map<char, char> cipher;
    for(int i = 0; i < mapLine.length(); i++) {
        cipher.insert(std::pair<char,char>(keyLine[i],mapLine[i]));
    }

    if(DEBUG) {
        for (auto const &pair: cipher) {
            std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        }
        std::cout << cipher.size() << std::endl;
    }

    cipherFile.close();

    std::string encodedString;
    std::vector<std::vector<std::string>> encodedText;

    // Add the entire file to a 2D vector
    std::vector<std::string> tokenizeString(std::string stringToTokenize);
    while(std::getline(encodedTextFile, encodedString)) {
        encodedText.push_back(tokenizeString(encodedString));
    }

    // Fill in the remaining cipher from the key word
    int findValidElement(std::string keyWord, std::vector<std::string> tokenizedString, std::map<char,char> cipher);
    std::map<char,char>::iterator it;
    std::string encodedKeyWord;
    int elementIndex;
    for(std::vector<std::string> &lineElement: encodedText) {
        elementIndex = findValidElement(givenWord, lineElement, cipher);
        if(DEBUG) std::cout << elementIndex << "\n";
        if(elementIndex != -1) {
            encodedKeyWord = lineElement[elementIndex];
            if(DEBUG) std::cout << encodedKeyWord << ":" << givenWord << "\n";
            for(int i = 0; i < encodedKeyWord.size(); i++) {
                if(DEBUG) std::cout << givenWord.at(i) << ":" << encodedKeyWord.at(i) << "\n";
                cipher.insert(std::pair<char,char>(encodedKeyWord.at(i), givenWord.at(i)));
            }
        }
    }

    // Find the last key of the cipher

    // Create an array with the alphabet
    char letters[26] = {};
    for(int i = 0; i < 26; i++) {
        letters[i] = 'A' + i;
    }

    char letterToFind;
    for(int i = 0; i < cipher.size(); i++) {
        it = cipher.find(letters[i]);
        if(it == cipher.end()) {
            if(DEBUG) std::cout << letters[i] << "\n";
            letterToFind = letters[i];
            for(auto &element: cipher) {
                for(int j = 0; j < 26; j++) {
                    if(letters[j] == element.second) {
                        letters[j] = '!';
                    }
                }
            }

            for(int j = 0; j < 26; j++) {
                if(letters[j] != '!') {
                    if(DEBUG) std::cout << letters[j] << "\n";
                    cipher.insert(std::pair<char,char>(letterToFind, letters[j]));
                }
            }
            break;
        }
    }

    if(DEBUG) {
        for (auto const &pair: cipher) {
            std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        }
        std::cout << cipher.size() << std::endl;
    }

    encodedTextFile.close();
    encodedTextFile.open(argv[2]);
    if(!encodedTextFile.is_open()) {
        std::cout << "ERROR: Could not open" << argv[2] << std::endl;
    }

    // Fully decode text
    std::string encodedLine;
    while(std::getline(encodedTextFile, encodedLine)) {
        for(char &ch: encodedLine) {
            it = cipher.find(ch);
            if(it != cipher.end()) {
                std::cout << it->second;
            } else {
                std::cout << ch;
            }
        }
        std::cout << "\n";
    }
}

std::vector<std::string> tokenizeString(std::string stringToTokenize) {
    std::vector<std::string> tokenizedString;
    std::string currentToken;

    for(char &ch: stringToTokenize) {
        if(isalpha(ch) || ch == '_') {
            currentToken.push_back(ch);
        } else {
            tokenizedString.push_back(currentToken);
            currentToken.clear();
        }
    }
    tokenizedString.push_back(currentToken);
    return tokenizedString;
}

int findValidElement(std::string keyWord, std::vector<std::string> tokenizedString, std::map<char,char> cipher) {
    std::map<char,char>::iterator it;
    for(int i = 0; i < tokenizedString.size(); i++) {
        if(keyWord.size() == tokenizedString.at(i).size()) {
            std::string decodedString;
            for(char &ch: tokenizedString.at(i)) {
                it = cipher.find(ch);
                if(it != cipher.end()) {
                    decodedString.push_back(it->second);
                } else {
                    decodedString.push_back('_');
                }
            }

            bool isValidPosition = true;

            for(int j = 0; j < keyWord.size(); j++) {
                if(keyWord.at(j) != decodedString.at(j)) {
                    if(decodedString.at(j) != '_') {
                        isValidPosition = false;
                        continue;
                    }
                }
            }

            if(isValidPosition) {
                return i;
            }
        }
    }
    return -1;
}