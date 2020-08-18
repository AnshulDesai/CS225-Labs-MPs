/* Your code here! */
#include "dsets.h"
#include <vector>
#include <algorithm>

void DisjointSets::addelements(int num) {
  for(int i = 0; i < num; i++){
    uptrees_.push_back(-1);
  }
}

int DisjointSets::find(int elem) {
  if (uptrees_[elem] < 0) {
    return elem;
  }
  return find(uptrees_[elem]);
}

void DisjointSets::setunion(int a, int b) {
  int first = find(a);
  int second = find(b);
  if (first == second) {
    return;
  }
  int boonk = uptrees_[first] + uptrees_[second];
  if (uptrees_[first] > uptrees_[second]) {
    uptrees_[first] = boonk;
    uptrees_[second] = first;
  }
  else {
    uptrees_[second] = boonk;
    uptrees_[first] = second;
  }
}

int DisjointSets::size(int elem) {
  return -1 * uptrees_[find(elem)];
}
