#include <iostream>
#include "candidate.h"
#include "avl.h"

using namespace std;

int main()
{
    AVL a;

    for (int i = 1; i <= 5; i++)
    {
        Candidate c;
        c.id = i;
        c.yearsExperience = i;
        a.insert(c);
    }
    a.inOrder();
    cout << a.height() << endl;

    AVL b;
    int bx[] = {3, 1, 2};

    for (int i = 0; i < 3; i++)
    {
        Candidate c;
        c.id = i + 1;
        c.yearsExperience = bx[i];
        b.insert(c);
    }

    cout << b.height() << endl;

    AVL d;

    for (int i = 1; i <= 15; i++)
    {
        Candidate c;
        c.id = i;
        c.yearsExperience = i;
        d.insert(c);
    }

    cout << d.height() << endl;

    AVL e;
    int ex[] = {3, 3, 3, 1, 5};

    for (int i = 0; i < 5; i++)
    {
        Candidate c;
        c.id = i + 1;
        c.yearsExperience = ex[i];
        e.insert(c);
    }

    e.range(3, 3);

    AVL f;

    for (int i = 1; i <= 7; i++)
    {
        Candidate c;
        c.id = i;
        c.yearsExperience = i;
        f.insert(c);
    }

    f.inOrder();
    cout << f.height() << endl;

    f.remove(1, 1);
    f.inOrder();
    cout << f.height() << endl;

    f.remove(2, 2);
    f.inOrder();
    cout << f.height() << endl;

    f.remove(4, 4);
    f.inOrder();
    cout << f.height() << endl;

        AVL g;
    int gx[] = {2, 1, 3, 4};

    for (int i = 0; i < 4; i++)
    {
        Candidate c;
        c.id = i + 1;
        c.yearsExperience = gx[i];
        g.insert(c);
    }

    g.remove(1, 2);
    g.inOrder();
    cout << g.height() << endl;
    return 0;
}