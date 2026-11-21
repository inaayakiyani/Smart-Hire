#pragma once
#include <iostream>
#include <string>
using namespace std;

class HashTable
{
private:
    class Node
    {
    public:
        string skill;
        int candidateIndex;
        Node* next;

        Node(string s, int index)
        {
            skill = s;
            candidateIndex = index;
            next = nullptr;
        }
    };

    Node** buckets;
    int bucketCount;
    int count;

    int hashFunction(string key)
    {
        int hash = 0;
        int length = key.length();

        for (int i = 0; i < length; i++)
        {
            hash = (hash * 31 + key[i]) % bucketCount;
        }

        if (hash < 0)
            hash = hash + bucketCount;

        return hash;
    }

public:
    HashTable()
    {
        bucketCount = 31;
        count = 0;
        buckets = new Node*[bucketCount];

        for (int i = 0; i < bucketCount; i++)
        {
            buckets[i] = nullptr;
        }
    }

    ~HashTable()
    {
        for (int i = 0; i < bucketCount; i++)
        {
            Node* current = buckets[i];

            while (current != nullptr)
            {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }

        delete[] buckets;
    }

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    void insert(string skill, int candidateIndex)
    {
        int position = hashFunction(skill);
        Node* current = buckets[position];

        while (current != nullptr)
        {
            if (current->skill == skill)
            {
                if (current->candidateIndex == candidateIndex)
                    return;
            }

            current = current->next;
        }

        Node* newNode = new Node(skill, candidateIndex);
        newNode->next = buckets[position];
        buckets[position] = newNode;
        count++;
    }

    int search(string skill, int result[])
    {
        int found = 0;
        Node* current = buckets[hashFunction(skill)];

        while (current != nullptr)
        {
            if (current->skill == skill)
            {
                result[found] = current->candidateIndex;
                found++;
            }

            current = current->next;
        }

        return found;
    }

    int getCount()
    {
        return count;
    }
};