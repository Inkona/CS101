#include <string>
#include <fstream>
#include <iostream>

using namespace std;

static string Decrypt(string in, string oldA, string newA, string word)
{
    string out = "";
    int inLen = in.size();
    int k = 0;
    
    for(int i = 0; i < inLen; ++i) 
    {
        int oldChar = oldA.find(in[i]);
        if(oldChar >= 0)
        {
            //cout << "Y- " << in[i] << endl;
            out.push_back(newA[oldChar]);
        }
        else
        {
            //cout << "N- " << in[i] << endl;
            if(isalpha(in[i]))
            {
                oldA += in[i];
                newA += word[k];
                out.push_back(word[k]);
                k++;
            }
            else
            {
                out.push_back(in[i]);
            }
        }
    }
    return out;
}

int main(int argc, char *argv[])
{
    ifstream file1;
    ifstream file2;
    string word = argv[3];
    
    string fi1li1;
    string fi1li2;
    string fi2li1;
    int grab = 1;
    string line;
    
    file1.open(argv[1]);
    
    while(getline(file1, line))
    {
        if(grab == 1)
        {
            fi1li1 = line;
        }
        if(grab == 2)
        {
            fi1li2 = line;
        }
        grab++;
    }
    //cout << fi1li1 << endl;
    //cout << fi1li2 << endl;
    file2.open(argv[2]);
    while(getline(file2, line))
    {
        fi2li1 = line;
    }

    //cout << fi2li1 << endl;

    string alpha = fi1li1;
    string cipher = fi1li2;
    string text = fi2li1;

    string plain = Decrypt(text, alpha, cipher, word);
    cout << plain << endl;
    
    return 0;
} 