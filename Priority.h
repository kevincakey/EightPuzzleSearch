#ifndef PRIORITY_H
#define PRIORITY_H

#include "Node.h"
#include "Problem.h"

using namespace std;

struct compare {
    bool operator()(Node* n1, Node* n2)
    {
        return n1->getCost() > n2->getCost();
    }
};

#endif
// References used: https://www.geeksforgeeks.org/stl-priority-queue-for-structure-or-class/
// discussed with partner Jordan Sam