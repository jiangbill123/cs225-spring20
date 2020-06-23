/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     * true if the coordinate of the first point at k is less than the 
     * coordinate of the second point at k. If there is a tie, 
     * break it using Point’s operator<
     */
    if (first[curDim] == second[curDim]){
      return first < second;
    }
    else 
      return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     * This should return true if potential is closer to target than 
     * currentBest (with a tie being broken by the operator< in the 
     * Point class: potential < currentBest)
     */
    double curr = 0.0;
    double pot = 0.0;
    for (int i = 0; i < Dim; i++){
      curr = curr + (currentBest[i]-target[i])*(currentBest[i]-target[i]);
      pot = pot + (potential[i]-target[i])*(potential[i]-target[i]);
    }
    if (curr == pot){
      return potential < currentBest;
    }
     return pot < curr;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    //Tree T is empty
    if (newPoints.empty() == true){
      size = 0;
      root = NULL;
    }
    else{
      size = 0;
      vector<Point<Dim>> mypoints = newPoints;
      root = construct(mypoints, 0, mypoints.size()-1, 0);
    }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::construct(vector<Point<Dim>>& list, unsigned left, unsigned right, int dimension){
  //parameter check
  if (left > right || left<0 || right<0 || right >= list.size() || left >= list.size()){
    return NULL;
  }
  unsigned median = (left + right)/2;
  Point<Dim> root_point = select(list, left, right, median, dimension);
  KDTreeNode* new_root = new KDTreeNode(root_point);
  size ++;
  // splitting dimension (d+1) mod k.
  dimension = (dimension+1)%Dim;
  new_root->left = construct(list, left, median - 1, dimension); //recurse left
  new_root->right = construct(list, median + 1, right, dimension); //recurse right
  return new_root;
}

//reference https://en.wikipedia.org/wiki/Quickselect
template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>>& list, unsigned left, unsigned right, unsigned k, int dimension){
  if (left == right) return list[left];

  unsigned pivotIndex = (left + right)/2;
  pivotIndex = partition(list, left, right, pivotIndex, dimension);

  if (k == pivotIndex) return list[k];
  else if (k < pivotIndex) 
    return select(list, left, pivotIndex-1, k, dimension);
  else 
    return select(list, pivotIndex + 1, right, k, dimension);
}

template <int Dim>
unsigned KDTree<Dim>::partition(vector<Point<Dim>>& list, unsigned left, unsigned right, unsigned pivotIndex, int dimension){
  Point<Dim> pivotValue = list[pivotIndex];
  list[pivotIndex] = list[right];
  list[right] = pivotValue;
  unsigned storeIndex = left;
  Point<Dim> temp;
  for (unsigned i = left; i < right; i++){
    //if (list[i] < pivotValue)
    if (smallerDimVal(list[i], pivotValue, dimension)){
      temp = list[storeIndex];
      list[storeIndex] = list[i];
      list[i] = temp; 
      storeIndex++;
    }
  }
  swap(list[right], list[storeIndex]);
  return storeIndex;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy(this->root, other->root);
  this->size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  clean(root);
  copy(this->root, rhs.root);
  this->size = rhs.size;

  return *this;
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode* this_tree, KDTreeNode* other){
  if (other == NULL) return;
  this_tree = new KDTreeNode();
  this_tree->point = other->point;
  copy(this_tree->left, other->left);
  copy(this_tree->right, other->right);
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clean(root);
}

template <int Dim>
void KDTree<Dim>::clean(KDTreeNode* subroot){
  if (subroot == NULL) return;
  clean(subroot->left);
  clean(subroot->right);
  delete subroot;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    //Point<Dim> BestMatch = root->point;
    return NNhelper(root, root, query, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::NNhelper(KDTreeNode* Node, KDTreeNode* parent,
                                 const Point<Dim>& query, int dimension) const{               
    if (Node == NULL){
      return parent->point;
    }
    Point<Dim> root = Node->point;
    Point<Dim> potential;
    Point<Dim> bestMatch;
    KDTreeNode* backtrack; //use for revisiting 
    // if ((Node->left == NULL && Node->right == NULL)){
    //   return root;
    // }
    if (smallerDimVal(query, root, dimension)){
      parent = Node;
      backtrack = Node->right;
      potential = NNhelper(Node->left, parent, query, (dimension+1)%Dim);
    }
    else{
      parent = Node;
      backtrack = Node->left;
      potential = NNhelper(Node->right, parent, query, (dimension+1)%Dim);
    }

    if (shouldReplace(query, potential, root)){
      potential = root;
    }
    
    double distance = pow(root[dimension] - query[dimension], 2);
    double radius = 0.0;
    for(int i = 0; i < Dim; i++){
      radius += pow(potential[i] - query[i], 2);
    }
    if (distance <= radius){
      //backtracking step
      bestMatch = NNhelper(backtrack, parent, query, (dimension+1)%Dim);
      if (shouldReplace(query, potential, bestMatch)){
        potential = bestMatch;
      }
    }

    return potential;
}

