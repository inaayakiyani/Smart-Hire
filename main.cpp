#include <iostream>
#include "candidate.h"
#include "bst.h"

using namespace std;

int main()
{
    BST tree;
    int years[] = {5, 3, 8, 1, 4, 7, 9};

    for (int i = 0; i < 7; i++)
    {
        Candidate c;
        c.id = i + 1;
        c.yearsExperience = years[i];
        tree.insert(c);
    }

    tree.inOrder();
    cout << tree.height() << endl;
    tree.range(3, 7);

    tree.remove(1, 4);
    tree.inOrder();

    tree.remove(3, 2);
    tree.inOrder();

    tree.remove(5, 1);
    tree.inOrder();

    BST line;

    for (int i = 1; i <= 5; i++)
    {
        Candidate c;
        c.id = i;
        c.yearsExperience = i;
        line.insert(c);
    }

    cout << line.height() << endl;

    return 0;
}