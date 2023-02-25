#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#define DEBUG false

using namespace std;

int findVal(string keyWord, vector<string> tokenStr, map<char,char> c) 
{
    map<char,char>::iterator iter;

    for(int i = 0; i < tokenStr.size(); i++) 
    {
        if(keyWord.size() == tokenStr.at(i).size()) 
        {
            string decStr;
            for(char &ch: tokenStr.at(i)) 
            {
                iter = c.find(ch);
                if(iter != c.end()) 
                {
                    decStr.push_back(iter->second);
                } else 
                {
                    decStr.push_back('_');
                }
            }

            bool isValPos = true;

            for(int j = 0; j < keyWord.size(); j++) 
            {
                if(keyWord.at(j) != decStr.at(j)) 
                {
                    if(decStr.at(j) != '_') 
                    {
                        isValPos = false;
                        continue;
                    }
                }
            }

            if(isValPos) 
            {
                return i;
            }
        }
    }
    return -1;
}

vector<string> tokenizeStr(string stringToTokenize) {
    vector<string> tokenizedString;
    string currToken;

    for(char &ch: stringToTokenize) {
        if(isalpha(ch) || ch == '_') {
            currToken.push_back(ch);
        } else {
            tokenizedString.push_back(currToken);
            currToken.clear();
        }
    }
    tokenizedString.push_back(currToken);
    return tokenizedString;
}

int main(int argc, char *argv[]) {
    ifstream cFile;
    cFile.open(argv[1]);
    ifstream encFile;
    encFile.open(argv[2]);
    string givenWord = argv[3];
    string mapLine, keyLine;
    getline(cFile, mapLine);
    getline(cFile, keyLine);
    map<char, char> c;
    for(int i = 0; i < mapLine.length(); i++) 
    {
        c.insert(pair<char,char>(keyLine[i],mapLine[i]));
    }
    c.insert(pair<char,char>('a','a'));
    if(DEBUG) 
    {
        for (auto const &pair: c) 
        {
            cout << "{" << pair.first << ": " << pair.second << "}\n";
        }
        cout << c.size() << endl;
    }

    cFile.close();

    string encodedString;
    vector<vector<string>> encodedText;

    vector<string> tokenizeStr(string stringToTokenize);
    while(getline(encFile, encodedString)) {
        encodedText.push_back(tokenizeStr(encodedString));
    }

    map<char,char>::iterator iter;
    string encodedKeyWord;
    int elementIndex;
    for(vector<string> &lineElement: encodedText) 
    {
        elementIndex = findVal(givenWord, lineElement, c);
        if(DEBUG) cout << elementIndex << "\n";
        if(elementIndex != -1) 
        {
            encodedKeyWord = lineElement[elementIndex];
            if(DEBUG) cout << encodedKeyWord << ":" << givenWord << "\n";
            for(int i = 0; i < encodedKeyWord.size(); i++) 
            {
                if(DEBUG) cout << givenWord.at(i) << ":" << encodedKeyWord.at(i) << "\n";
                c.insert(pair<char,char>(encodedKeyWord.at(i), givenWord.at(i)));
            }
        }
    }

    char letters[26] = {};
    for(int i = 0; i < 26; i++) 
    {
        letters[i] = 'A' + i;
    }

    char letterToFind;
    for(int i = 0; i < c.size(); i++) 
    {
        iter = c.find(letters[i]);
        if(iter == c.end()) 
        {
            if(DEBUG) cout << letters[i] << "\n";
            letterToFind = letters[i];
            for(auto &element: c) 
            {
                for(int j = 0; j < 26; j++) 
                {
                    if(letters[j] == element.second) 
                    {
                        letters[j] = '!';
                    }
                }
            }

            for(int j = 0; j < 26; j++) 
            {
                if(letters[j] != '!') 
                {
                    if(DEBUG) cout << letters[j] << "\n";
                    c.insert(pair<char,char>(letterToFind, letters[j]));
                }
            }
            break;
        }
    }

    if(DEBUG) {
        for (auto const &pair: c) 
        {
            cout << "{" << pair.first << ": " << pair.second << "}\n";
        }
        cout << c.size() << endl;
    }

    encFile.close();
    encFile.open(argv[2]);
    if(!encFile.is_open()) 
    {
        cout << "ERROR: Could not open" << argv[2] << endl;
    }

    string encLine;
    while(getline(encFile, encLine)) 
    {
        for(char &ch: encLine) 
        {
            iter = c.find(ch);
            if(iter != c.end()) 
            {
                cout << iter->second;
            } else 
            {
                cout << ch;
            }
        }
        cout << "\n";
    }
}