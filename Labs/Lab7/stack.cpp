#include <iostream>
#include <deque>
#include <string>
using namespace std;

int main(int argc, char **argv){
    deque<char> list;
    string input = argv[1];
    int size = input.size();
    char c;
    char b;
    for(int i = 0; i < size; i++)
    {
        //cout << "Stack: " << list << endl;
        cout << "Stack: ";
        for (auto it = list.begin(); it != list.end(); ++it)
        cout << ' ' << *it;
        cout << endl;
        c = input[i];
        cout << "Character: " << c << endl;
        if(c == '(' || c == '[' || c == '{' || c == '<')
        {
            list.push_back(c);
            cout << "Push" << endl;
        }
        else if(c == ')' || c == ']' || c == '}' || c == '>')
        {
            if(list.empty())
            {
                cout << "Error: unmatched right symbol " << c << endl;
                return false;
            }
            else if(!list.empty() && (list.front() != ')' || list.front() != ']' || list.front() != '}' || list.front() != '>'))
            {
                b = list.back();
                if(c == b + 1 || c == b + 2)
                {
                    cout << "Matching " << b << " and " << c << endl;
                    list.pop_back();
                    cout << "Pop" << endl;
                }
                else
                {
                    cout << "Error: mismatched pair " << b << " and " << c << endl;
                    return false;

                } 
            }
        } 
        else if((c == ')' || c == ']' || c == '}' || c == '>') && (list.front() == ')' || list.front() == ']' || list.front() == '}' || list.front() == '>') && (list.size() > 1))
        {
            cout << "Error: unmatched right symbol " << c << endl;
            return false;
        }
        else
        {
            cout << "Error: invalid character " << c << endl;
            return false;
        }
    }


    cout << "Stack: ";
    for (auto it = list.begin(); it != list.end(); ++it)
    cout << ' ' << *it;
    cout << endl;
    cout << "Reached end of string" << endl;
    if(list.empty())
    {
        cout << "String is properly balanced" << endl;
        return list.empty();
    }
    else
    {
        cout << "Error: unmatched left symbol " << list.back() << endl;
    }
}