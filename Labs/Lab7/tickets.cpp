#include <queue>
#include <iostream>

using namespace std;

int main () {
    string personName = "";
    int counter = 0;
    int youPosition;
    queue<string> peopleInQueue;
    getline(cin, personName);
    while (personName != "-1") 
    {
        //TODO: Add personName to peopleInQueue
        //determine position of "You" (youPosition)
        peopleInQueue.push(personName);
        counter++;
        if(personName == "You")
        {
            youPosition = counter;
            break;
        }
        getline(cin, personName);
    }

    cout << "Welcome to the ticketing service... " << endl;
    cout << "You are number " << youPosition << " in the queue." << endl;

    // TODO: In a loop, remove head person from peopleInQueue,
    //       output their name and that they have purchased a ticket,
    //       then output your position in the queue. When you are at
    //       the head, output that you can purchase your ticket.
    int size = peopleInQueue.size();
    for(int i = 0; i < size; i++)
    {
        if(peopleInQueue.front() == "You")
        {
            cout << "You can now purchase your ticket!" << endl;
            break;
        }
        else
        {
            cout << peopleInQueue.front() << " has purchased a ticket." << endl;
            peopleInQueue.pop();
            counter--;
            cout << "You are now number " << counter << endl;
        }
    }
    return 0;
}