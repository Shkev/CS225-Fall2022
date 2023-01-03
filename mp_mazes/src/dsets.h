/* Your code here! */
#pragma once

#include <vector>
#include <cassert>

class DisjointSets {
public:
    DisjointSets() = default;

    DisjointSets(int num);

    void addelements(int num);

    int find(int elem);

    void setunion(int a, int b);

    int size(int elem);

private:
    std::vector<int> parent;
};