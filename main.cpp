#include <iostream>
#include "candidate.h"
#include "dynamicarray.h"

using namespace std;

int main()
{
    DynamicArray list;

    for (int i = 1; i <= 5; i++)
    {
        Candidate c;
        c.id = i;
        c.name = "Candidate" + to_string(i);
        list.add(c);
        cout << "Added " << i << " | size: " << list.getSize() << " | capacity: " << list.getCapacity() << endl;
    }

    for (int i = 0; i < list.getSize(); i++)
    {
        cout << list.get(i).id << " " << list.get(i).name << endl;
    }

    list.get(10);

    return 0;
}