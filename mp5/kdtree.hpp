/**
* @file kdtree.cpp
* Implementation of KDTree class.
*/

#include <utility>
#include <algorithm>
#include <math.h>

using namespace std;

/**
* This function should take in two templatized Points and a dimension and return
* a boolean value representing whether or not the first Point has a smaller
* value than the second in the dimension specified. That is, if the dimension
* passed in is k, then this should be true if the coordinate of the first point
* at k is less than the coordinate of the second point at k. If there is a tie,
* break it using Point’s operator<. (from MP5 description)
*/
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                               const Point<Dim>& second, int curDim) const
{
   /**
    * @todo Implement this function!
    */

   if (first[curDim] == second[curDim]) {
     return first < second;
   }
   return first[curDim] < second[curDim];
}

/**
* This function should take three templated Points: target, currentBest, and
* potential. This should return true if potential is closer (i.e., has a smaller
* distance) to target than currentBest (with a tie being broken by the operator<
* in the Point class: potential < currentBest). (from MP5 description)
**/
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                               const Point<Dim>& currentBest,
                               const Point<Dim>& potential) const
{
   /**
    * @todo Implement this function!
    */
    int cVal = 0;
    int pVal = 0;
    for (int i = 0; i < Dim; i++) {
      cVal += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
      pVal += (target[i] - potential[i]) * (target[i] - potential[i]);
    }
    if (cVal == pVal) {
      return potential < currentBest;
    }
    return pVal < cVal;
}

/**
* Simple helper function to get the median of our needed bounds.
**/
template <int Dim>
int KDTree<Dim>::getMedian(int begin, int end) const {
   int median = (begin + end) / 2;
   return median;
}

/**
* KDTree Constructor
* First copying the input list of points into a points vector, sorting this
* vector so it represents a k-d tree, and building the actual k-d tree along
* while we sort. (from MP5 description)
**/
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
   /**
    * @todo Implement this function!
    */
    points = newPoints;
    size = points.size();
    int endIndex = (int)(size - 1);
    buildTree(0, endIndex, 0);
    root = constructTree(0, endIndex);
}

/**
* Copy constructor!
**/
template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
 /**
  * @todo Implement this function!
  */
    points = other.points;
    size = other.size;
    size_t endIndex = (int)(size - 1);
    buildTree(0, endIndex, 0);
    root = constructTree(0, endIndex);
}

/**
* Equals operator! Takes in the right hand side and returns a reference for
* performing chained assignments.
**/
template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
 /**
  * @todo Implement this function!
  */
  if (this == &rhs) {
    return *this;
  }
  clearTree(this);
  this = new KDTree(rhs);
  return *this;
}

/**
* Destructor for the KDTree class!
**/
template <int Dim>
KDTree<Dim>::~KDTree() {
 /**
  * @todo Implement this function!
  */
  clearTree(root);
}

/**
* This function takes a reference to a template parameter Point and returns the
* Point closest to it in the tree. We are defining closest here to be the
* minimum Euclidean distance between elements!
**/
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
   /**
    * @todo Implement this function!
    */
   return find(0, (int)(size - 1), 0, points[(points.size() - 1) / 2], query);
}

/**
* Recursive helper function for findNearestNeighbor!
**/
template <int Dim>
Point<Dim> KDTree<Dim>::find(int begin, int end, int dimen, const Point<Dim> & best, const Point<Dim> & query) const {
   bool flag = false;
   int median = getMedian(begin, end);
   int dim = (dimen + 1) % Dim;
   Point<Dim> medPoint = points[median];
   Point<Dim> retPoint = best;
   size_t tempCompare = 0;
   size_t tempCur = (medPoint[dimen] - query[dimen]) * (medPoint[dimen] - query[dimen]);

   if (begin == end) {
     if (shouldReplace(query, best, points[begin])) {
       retPoint = points[begin];
       return retPoint;
     }
     retPoint = best;
     return retPoint;
   }

   if (smallerDimVal(points[median], query, dimen)) {
     //testing for invalid case
     if (median >= end) {
       //cout << "lol sike!" << endl;
     }
     else {
       flag = false;
       retPoint = find((median + 1), end, dim, best, query);
     }
   }

   if (smallerDimVal(query, points[median], dimen)) {
     //testing for invalid case
     if (median <= begin) {
       //cout << "lol sike!" << endl;
     }
     else {
       flag = true;
       retPoint = find(begin, (median - 1), dim, best, query);
     }
   }

   if (shouldReplace (query, retPoint, points[median])) {
     retPoint = points[median];
   }

   for (size_t i = 0; i < Dim; i++) {
     tempCompare += pow((query[i] - retPoint[i]), 2);
   }
   tempCompare++;

   if (tempCur < tempCompare) {
     if (flag == true) {
       if (median < end) {
         retPoint = find((median + 1), end, dim, retPoint, query);
       }
     }
     if (flag == false) {
       if (median > begin) {
         retPoint = find(begin, (median - 1), dim, retPoint, query);
       }
     }
   }
   return retPoint;
}

/**
* Essentially a helper function for quickSelect where we take the parameters,
* specifically pivot, in order to swap it around that pivot.
**/
template <int Dim>
int KDTree<Dim>::medIndex(int begin, int end, int dimen, int pivot) {
   int tempIndex = begin;
   Point<Dim> tempPoint = points[pivot];
   Point<Dim> pivotPoint = points[pivot];
   swap(points, pivot, end);
   for (int i = begin; i < (end + 1); i++) {
     if (smallerDimVal(points[i], pivotPoint, dimen)) {
       swap(points, tempIndex, i);
       tempIndex++;
     }
   }
   swap(points, end, tempIndex);
   return tempIndex;
}

/**
* Swap function!
**/
template <int Dim>
void KDTree<Dim>::swap(vector<Point<Dim>>& points, int first, int second)
{
  Point<Dim> x = points[first];
  points[first] = points[second];
  points[second] = x;
}

/**
* Function to find a certain value based on the given parameters. Used
* in buildTree.
**/
template <int Dim>
void KDTree<Dim>::quickSelect(int begin, int end, int dimen, int swag) {
   if (begin > end) {
     return;
   }
   int middle = medIndex(begin, end, dimen, getMedian(begin, end));
   if (swag == middle) {
     return;
   }
   else if (swag < middle) {
     quickSelect(begin, (middle - 1), dimen, swag);
   }
   else {
     quickSelect((middle + 1), end, dimen, swag);
   }
}

/**
* Helper function for destructor!
**/
template <int Dim>
void KDTree<Dim>::clearTree(typename KDTree<Dim>::KDTreeNode * rootNode) {
   if (rootNode == NULL) {
     return;
   }
   clearTree(rootNode -> right);
   clearTree(rootNode -> left);
   delete rootNode;
}

/**
* Takes in parameters of the bounds and dimensions and builds the KDTree!
**/
template <int Dim>
void KDTree<Dim>::buildTree(int begin, int end, int dimen) {
   int median = getMedian(begin, end);
   int dim = (dimen + 1) % Dim;
   quickSelect(begin, end, dimen, median);
   if (begin < median - 1) {
     buildTree( begin, (median - 1), dim);
   }
   if (end > median + 1) {
     buildTree((median + 1), end, dim);
   }
}

/**
* Function to set the root to a KDTreeNode Pointer that fills in values.
**/
template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::constructTree(int begin, int end) {
 if (end < begin) {
   return NULL;
 }
 int index = getMedian(begin, end);
 int sizeP = (int)points.size();
 if (index < sizeP) {
   if (index > -1) {
     KDTree<Dim>::KDTreeNode * newNode = new KDTree<Dim>::KDTreeNode(points[index]);
     newNode -> right = constructTree((index + 1), end);
     newNode -> left = constructTree(begin, (index - 1));
     return newNode;
   }
 }
 else {
   return NULL;
 }
 return NULL;
}
