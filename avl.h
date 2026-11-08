#pragma once
#include <iostream>
#include "candidate.h"
using namespace std;
class AVL
{
private:
    class Node
    {
    public:
        Candidate data;
        Node* left;
        Node* right;
        int height;

        Node(Candidate c)
        {
            data = c;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };

    Node* root;

    int getHeight(Node* node)
    {
        if (node == nullptr)
            return 0;

        return node->height;
    }

    void updateHeight(Node* node)
    {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        if (leftHeight > rightHeight)
            node->height = leftHeight + 1;
        else
            node->height = rightHeight + 1;
    }

    int getBalance(Node* node)
    {
        if (node == nullptr)
            return 0;

        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateRight(Node* x)
    {
        Node* y = x->left;
        Node* temp = y->right;

        y->right = x;
        x->left = temp;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* rotateLeft(Node* x)
    {
        Node* y = x->right;
        Node* temp = y->left;

        y->left = x;
        x->right = temp;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* rebalance(Node* node)
    {
        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1)
        {
            if (getBalance(node->left) < 0)
                node->left = rotateLeft(node->left);

            return rotateRight(node);
        }

        if (balance < -1)
        {
            if (getBalance(node->right) > 0)
                node->right = rotateRight(node->right);

            return rotateLeft(node);
        }

        return node;
    }

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

        else
            return node;

        return rebalance(node);
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

        return rebalance(node);
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

    AVL()
    {
        root = nullptr;
    }

    ~AVL()
    {
        destroy(root);
    }

    AVL(const AVL&) = delete;
    AVL& operator=(const AVL&) = delete;

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
        return getHeight(root);
    }
};