#pragma once
#include <iostream>
#include "candidate.h"
using namespace std;
class BST
{
private:

       class Node
    {
    public:
        Candidate data;
        Node* left;
        Node* right;

        Node(Candidate c)
        {
            data = c;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    Node* insert(Node* node, Candidate c)
    {
        if (node == nullptr)
            return new Node(c);

        if (c.yearsExperience < node->data.yearsExperience)
            node->left = insert(node->left, c);

        else if (c.yearsExperience > node->data.yearsExperience)
            node->right = insert(node->right, c);

        else if (c.id < node->data.id)
            node->left = insert(node->left, c);

        else if (c.id > node->data.id)
            node->right = insert(node->right, c);

        return node;
    }

    void inOrder(Node* node)
    {
        if (node == nullptr)
            return;

        inOrder(node->left);

        cout << node->data.yearsExperience << " ";

        inOrder(node->right);
    }

    void range(Node* node, int min, int max)
    {
        if (node == nullptr)
            return;

        if (node->data.yearsExperience >= min)
            range(node->left, min, max);

        if (node->data.yearsExperience >= min &&
            node->data.yearsExperience <= max)
        {
            cout << node->data.yearsExperience << " ";
        }

        if (node->data.yearsExperience <= max)
            range(node->right, min, max);
    }

    Node* search(Node* node, int experience)
    {
        if (node == nullptr)
            return nullptr;

        if (node->data.yearsExperience == experience)
            return node;

        if (experience < node->data.yearsExperience)
            return search(node->left, experience);

        return search(node->right, experience);
    }

    Node* findMin(Node* node)
    {
        while (node->left != nullptr)
            node = node->left;

        return node;
    }

    Node* remove(Node* node, int experience, int id)
    {
        if (node == nullptr)
            return nullptr;

        if (experience < node->data.yearsExperience)
            node->left = remove(node->left, experience, id);

        else if (experience > node->data.yearsExperience)
            node->right = remove(node->right, experience, id);

        else if (id < node->data.id)
            node->left = remove(node->left, experience, id);

        else if (id > node->data.id)
            node->right = remove(node->right, experience, id);

        else
        {
            if (node->left == nullptr)
            {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            else if (node->right == nullptr)
            {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);

            node->data = temp->data;

            node->right = remove(
                node->right,
                temp->data.yearsExperience,
                temp->data.id
            );
        }

        return node;
    }

    int height(Node* node)
    {
        if (node == nullptr)
            return 0;

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        if (leftHeight > rightHeight)
            return leftHeight + 1;

        return rightHeight + 1;
    }

    void destroy(Node* node)
    {
        if (node == nullptr)
            return;

        destroy(node->left);
        destroy(node->right);

        delete node;
    }

public:

    BST()
    {
        root = nullptr;
    }

    ~BST()
    {
        destroy(root);
    }

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(Candidate c)
    {
        root = insert(root, c);
    }

    void inOrder()
    {
        inOrder(root);
        cout << endl;
    }

    void range(int min, int max)
    {
        range(root, min, max);
        cout << endl;
    }

    Candidate* search(int experience)
    {
        Node* result = search(root, experience);

        if (result == nullptr)
            return nullptr;

        return &(result->data);
    }

    void remove(int experience, int id)
    {
        root = remove(root, experience, id);
    }

    int height()
    {
        return height(root);
    }
};