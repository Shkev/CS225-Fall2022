/* Your code here! */
#include "dsets.h"

DisjointSets::DisjointSets(int num) {
    parent = std::vector<int>(num, -1);
}

void DisjointSets::addelements(int num) {
    parent.insert(parent.end(), num, -1);
}

int DisjointSets::find(int elem) {
    assert(elem >= 0);
    std::vector<int> children;
    while(parent.at(elem) >= 0) {
        children.push_back(elem);
        elem = parent.at(elem);
    }
    assert(parent.at(elem) <= -1);
    for (int c : children) {
        parent.at(c) = elem;
    }
    return elem;
}

void DisjointSets::setunion(int a, int b) {
    int rep_a = find(a);
    int rep_b = find(b);
    if (rep_a == rep_b) return; // already in same set
    if (size(rep_b) > size(rep_a)) {
        parent.at(rep_b) += parent.at(rep_a);
        parent.at(rep_a) = rep_b;
        assert(parent.at(rep_b) < -1);
    } else {
        parent.at(rep_a) += parent.at(rep_b);
        parent.at(rep_b) = rep_a;
    }
}

int DisjointSets::size(int elem) {
    int rep = find(elem);
    return -parent.at(rep);
}
