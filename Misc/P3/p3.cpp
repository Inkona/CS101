#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Person::Person()
{
    this->height = 0;
    this->weight = 0;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

Person::Person(string first, string last, int height, int weight)
{
    this->first = first;
    this->last = last;
    this->height = height;
    this->weight = weight;
    this->nextHeight = nullptr;
    this->nextWeight = nullptr;
}

PersonList::PersonList()
{
    this->size = 0;
    this->headHeightList = nullptr;
    this->headWeightList = nullptr;
}

int PersonList::getSize()
{
    return size;
}

void PersonList::printByHeight(ostream &os)
{
    Person *curr = headHeightList;
    while(curr != nullptr)
    {
        //os << endl << "PRINTBY(X)" << endl;
        os << curr->first << " " << curr->last << ": height=" << curr->height << ", weight=" << curr->weight << "\n";
        curr = curr->nextHeight;
    }
}

void PersonList::printByWeight(ostream &os)
{
    Person *curr = headWeightList;
    while(curr != nullptr)
    {
        //os << endl << "PRINTBY(X)" << endl;
        os << curr->first << " " << curr->last << ": height=" << curr->height << ", weight=" << curr->weight << "\n";
        curr = curr->nextWeight;
    }
}

bool PersonList::exists(string first, string last)
{
    Person *curr = headHeightList;
    while(curr != nullptr)
    {
        if(curr->first == first && curr->last == last)
        {
            return true;
        }
        else
        {
            curr = curr->nextHeight;
        }
    }
    return false;
}

int PersonList::getHeight(string first, string last) {
    if(this->exists(first, last) != true)
    {
        return -1;
    }
    else
    {
        Person *curr = headHeightList;
        while(curr != nullptr)
        {
            if(curr->first == first && curr->last == last)
            {
                return curr->height;
            }
            else
            {
                curr = curr->nextHeight;
            }
        }
    }
}

int PersonList::getWeight(string first, string last) {
    if(this->exists(first, last) != true)
    {
        return -1;
    }
    else
    {
        Person *curr = headWeightList;
        while(curr != nullptr)
        {
            if(curr->first == first && curr->last == last)
            {
                return curr->weight;
            }
            else
            {
                curr = curr->nextWeight;
            }
        }
    }
}

bool PersonList::add(string first, string last, int height, int weight)
{
    if (this->exists(first, last))
    {
        return false;
    }
    Person *p = new Person(first, last, height, weight);
	
    //add to start of list if size is 0
    if(size == 0)
    {
        // add it to "headHeightList"
        p->nextHeight = this->headHeightList;
	    this->headHeightList = p; 

	    // add it to "headWeightList"
	    p->nextWeight = this->headWeightList;
	    this->headWeightList = p; 
        size++;
        return true;
    }

    
    Person *curr = headHeightList;
    Person *prev = headHeightList;
    while(curr != nullptr)
    {
        if(p->height > headHeightList->height && prev == headHeightList)
        {
            p->nextHeight = curr;
            headHeightList = p;
            //cout << "FIRST SPOT RAN" << endl;
            break;
        }
        else if(prev->height > p->height && (p->height > curr->height || (p->height == curr->height && p->weight > curr->weight)))
        {
            prev->nextHeight = p;
            p->nextHeight = curr;
            //cout << "SECOND SPOT RAN" << endl;
            break;
        }
        else if(prev->height > p->height && (p->height > curr->height || (p->height == curr->height && p->weight <= curr->weight)))
        {
            p->nextHeight = curr->nextHeight;
            curr->nextHeight = p;
            //cout << "THIRD SPOT RAN" << endl;
            break;
        }
        else if(curr->nextHeight == nullptr && p->height < curr->height)
        {
            curr->nextHeight = p;
            p->nextHeight = nullptr;
            //cout << "FOURTH SPOT RAN" << endl;
            break;
        }
        prev = curr;
        curr = curr->nextHeight;
    }   

    curr = headWeightList;
    prev = headWeightList;
    while(curr != nullptr)
    {
        //front insert if size > 1
        //GOOD
        if(p->weight < headWeightList->weight && prev == headWeightList)
        {
            p->nextWeight = curr;
            headWeightList = p;
            size++;
            return true;
        }
        //middle/back insert?????
        //if p height is greater than curr height
        else if(prev->weight < p->weight && (p->weight < curr->weight || (p->weight == curr->weight && p->height > curr->height)))
        {
            prev->nextWeight = p;
            p->nextWeight = curr;
            size++;
            return true;
        }   
        // //if p height is less than or equal to curr height
        else if(prev->weight < p->weight && (p->weight < curr->weight || (p->weight == curr->weight && p->height <= curr->height)))
        {
            p->nextWeight = curr->nextWeight;
            curr->nextWeight = p;
            size++;
            return true;
        }
        else if(curr->nextWeight == nullptr && p->weight > curr->weight)
        {
            curr->nextWeight = p;
            p->nextWeight = nullptr;
            size++;
            return true;
        }
        prev = curr;
        curr = curr->nextWeight;
    }   
}

bool PersonList::remove(string first, string last)
{
    Person *prev1 = nullptr;
    Person *curr1 = headHeightList;
    Person *prev2 = nullptr;
    Person *curr2 = headWeightList;

    for(curr1; curr1 != nullptr; curr1 = curr1->nextHeight)
    {
        if(curr1->first == first && curr1->last == last)
        {
            for(curr2; curr2 != nullptr; curr2 = curr2->nextWeight)
            {
                
                if(curr2->first == first && curr2->last == last)
                {
                    if(nullptr == prev1)
                    {
                        this->headHeightList = curr1->nextHeight;
                    }
                    else
                    {
                        prev1->nextHeight = curr1->nextHeight;
                    }

                    if(nullptr == prev2)
                    {
                        this->headWeightList = curr2->nextWeight;
                    }
                    else
                    {
                        prev2->nextWeight = curr2->nextWeight;
                    }
                    delete curr1;
                    return true;
                }
                prev2 = curr2;
            }
        }
        prev1 = curr1;
    }
    return false;
}

//??????????????????
bool PersonList::updateName(string first, string last, string newFirst, string newLast)
{
    if(this->exists(first, last) != true)
    {
        return false;
    }    
    else
    {
        Person *curr = headWeightList;
        while(curr != nullptr)
        {
            if(curr->first == first && curr->last == last)
            {
                curr->first = newFirst;
                curr->last = newLast;
            }
            else
            {
                curr = curr->nextWeight;
            }
        }
    }
}

bool PersonList::updateHeight(string first, string last, int height)
{
    if(this->exists(first, last) != true)
    {
        return false;
    }    
    else
    {
        int weight = getWeight(first, last);
        remove(first, last);
        add(first, last, height, weight); 
        return true;
    }
}

bool PersonList::updateWeight(string first, string last, int weight)
{
    if(this->exists(first, last) != true)
    {
        return false;
    }    
    else
    {
        int height = getHeight(first, last);
        remove(first, last);
        add(first, last, height, weight); 
        return true;
    }
}

PersonList::~PersonList()
{
    Person *curr = headHeightList;
    Person *next;
    while(curr != nullptr)
    {
        next = curr->nextHeight;
        delete curr;
        curr = next;
    }
}

PersonList::PersonList(const PersonList &src)
{
    
}

const PersonList &PersonList::operator=(const PersonList &src)
{
    if(src.headHeightList == nullptr)
    {
        return;
    }

    Person *temp = src.headHeightList;
    Person *curr;
    headHeightList = new Person;
    headHeightList->height = temp->height;
    headHeightList->first = temp->first;
    headHeightList->last = temp->last;
    headHeightList->weight = temp->weight;

    headHeightList->nextHeight = nullptr;

    curr = headHeightList;
    temp = temp->nextHeight;

    while(temp != nullptr)
    {
        curr->nextHeight = new Person;
        curr = curr->nextHeight;
        curr->height = temp->height;
        curr->first = temp->first;
        curr->last = temp->last;
        curr->weight = temp->weight;
        curr->nextHeight = nullptr;
        temp = temp->nextHeight;
    }

    // headWeightList = new Person;
    // headWeightList->weight = temp->weight;
    // headWeightList->nextWeight = nullptr;
    // curr = headWeightList;
    // temp = temp->nextWeight;

    // while(temp != nullptr)
    // {
    //     curr->nextWeight = new Person;
    //     curr = curr->nextWeight;
    //     curr->weight = temp->weight;
    //     curr->nextWeight = nullptr;
    //     temp = temp->nextWeight;
    // }

    return *this;
}
