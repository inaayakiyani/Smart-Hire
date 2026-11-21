#pragma once
#include <iostream>
#include "candidate.h"
using namespace std;

class RankedCandidate
{
public:
    Candidate candidate;
    int score = 0;
};

class MaxHeap
{
private:
    RankedCandidate* arr;
    int size;
    int capacity;

    bool isBetter(int i, int j)
    {
        if (arr[i].score > arr[j].score)
            return true;

        if (arr[i].score < arr[j].score)
            return false;

        if (arr[i].candidate.id < arr[j].candidate.id)
            return true;

        return false;
    }

    void swapItems(int i, int j)
    {
        RankedCandidate temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    void siftUp(int i)
    {
        while (i > 0)
        {
            int parent = (i - 1) / 2;

            if (isBetter(i, parent))
            {
                swapItems(i, parent);
                i = parent;
            }
            else
            {
                break;
            }
        }
    }

    void siftDown(int i)
    {
        while (true)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int best = i;

            if (left < size)
            {
                if (isBetter(left, best))
                    best = left;
            }

            if (right < size)
            {
                if (isBetter(right, best))
                    best = right;
            }

            if (best == i)
                break;

            swapItems(i, best);
            i = best;
        }
    }

public:
    MaxHeap()
    {
        size = 0;
        capacity = 4;
        arr = new RankedCandidate[capacity];
    }

    ~MaxHeap()
    {
        delete[] arr;
    }

    MaxHeap(const MaxHeap&) = delete;
    MaxHeap& operator=(const MaxHeap&) = delete;

    void insert(Candidate c, int score)
    {
        if (size == capacity)
        {
            int newCapacity = capacity * 2;
            RankedCandidate* newArr = new RankedCandidate[newCapacity];

            for (int i = 0; i < size; i++)
            {
                newArr[i] = arr[i];
            }

            delete[] arr;
            arr = newArr;
            capacity = newCapacity;
        }

        arr[size].candidate = c;
        arr[size].score = score;
        size++;
        siftUp(size - 1);
    }

    bool extractMax(RankedCandidate& out)
    {
        if (size == 0)
            return false;

        out = arr[0];
        arr[0] = arr[size - 1];
        size--;
        siftDown(0);

        return true;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    int getSize()
    {
        return size;
    }
};