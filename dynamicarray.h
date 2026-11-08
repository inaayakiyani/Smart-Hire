#pragma once
#include <iostream>
#include "candidate.h"
using namespace std;
class DynamicArray
{
private:
    Candidate* arr;
    int size;
    int capacity;
public:
    DynamicArray()
    {
        size = 0;
        capacity = 2;
        arr = new Candidate[capacity];
    }
    ~DynamicArray()
    {
        delete[] arr;
    }
    void add(Candidate c)
    {
        if (size == capacity)
        {
            int newCapacity = capacity * 2;

            Candidate* newArr = new Candidate[newCapacity];

            for (int i = 0; i < size; i++)
            {
                newArr[i] = arr[i];
            }

            delete[] arr;

            arr = newArr;
            capacity = newCapacity;
        }

        arr[size] = c;
        size++;
    }

    Candidate get(int i)
    {
        if (i < 0 || i >= size)
        {
            cout << "Invalid index!" << endl;
            return Candidate();
        }

        return arr[i];
    }

    int getSize()
    {
        return size;
    }

    int getCapacity()
    {
        return capacity;
    }
};