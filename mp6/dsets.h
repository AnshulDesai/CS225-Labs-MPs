/* Your code here! */
#ifndef DSETS_H
#define DSETS_H

#include <vector>

class DisjointSets {
  public:
    void addelements(int num);
    int find(int elem);
    void setunion(int a, int b);
    int size(int elem);
    std::vector<int> uptrees_;
};

#endif
