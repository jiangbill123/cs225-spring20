#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  //Iterator_current = Point(-1,-1);
  flag = true;
}

ImageTraversal::Iterator::Iterator(ImageTraversal * traversal, Point FS_start){
  traversal_ = traversal;
  Iterator_start = FS_start;
  Iterator_current = FS_start;
  flag = false;
  visited.resize(traversal->png_.width());
  for (unsigned i = 0; i < visited.size(); i++) {
      visited[i].resize(traversal->png_.height());
      for (unsigned j = 0; j < visited[i].size(); j++) {
          visited[i][j] = false;
      }
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point curr = traversal_->pop();
  visited[curr.x][curr.y] = true;
  Point right(curr.x+1, curr.y);
  Point left(curr.x - 1, curr.y);
  Point below(curr.x, curr.y + 1);
  Point above(curr.x, curr.y - 1); 
  double del;

  //need the start pixel and the current pixel
  //right pixel
  if (right.x < traversal_->png_.width()){
    if (visited[right.x][right.y] == false){
      del = calculateDelta(
        traversal_->png_.getPixel(Iterator_start.x, Iterator_start.y), //start
        traversal_->png_.getPixel(right.x, right.y) //current
      );
      if (del < traversal_->getTolerance()){
        traversal_->add(right);
      }
    }
  }

  //below
  if (below.y < traversal_->png_.height()){
    if (visited[below.x][below.y] == false){
      del = calculateDelta(
        traversal_->png_.getPixel(Iterator_start.x, Iterator_start.y), 
        traversal_->png_.getPixel(below.x, below.y)
      );
      if (del < traversal_->getTolerance()){
        traversal_->add(below);
      }
    }
  }
  
  //left pixel
  if (left.x < traversal_->png_.width()){
    if (visited[left.x][left.y] == false){
      del = calculateDelta(
        traversal_->png_.getPixel(Iterator_start.x, Iterator_start.y), 
        traversal_->png_.getPixel(left.x, left.y)
      );
      if (del < traversal_->getTolerance()){
        traversal_->add(left);
      }
    }
  }

  //above
  if (above.y < traversal_->png_.height()){
    if (visited[above.x][above.y] == false){
      del = calculateDelta(
        traversal_->png_.getPixel(Iterator_start.x, Iterator_start.y), 
        traversal_->png_.getPixel(above.x, above.y)
      );
      if (del < traversal_->getTolerance()){
        traversal_->add(above);
      }
    }
  }

  while ( !(traversal_->empty()) && (visited[traversal_->peek().x][traversal_->peek().y])) {
  	traversal_->pop();
  }
  if (traversal_->empty()) {
    flag = true;
  	return *this;
  }
  Iterator_current = traversal_->peek();
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return this->Iterator_current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return !(flag == other.flag);
}

