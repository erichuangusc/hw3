#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <iostream>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

  std::vector<T> vals;

private:
  /// Add whatever helper functions and data members you need below
  PComparator comp;
  size_t h_size;         // size of the heap
  size_t num_child;     // number of children
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) {
  h_size = 0;
  num_child = m;
  comp = c;
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {

}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
  return h_size;
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
  return 0 == h_size;
}


// Push implementation
template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
  vals.push_back(item);
  ++h_size;

  // loop to find correct position
  std::size_t pos = vals.size() - 1;
  while (pos) {
      // formula to find the parent (refer to heap slides)
      std::size_t parent_pos = (pos - 1) / num_child;
      T &child = vals[pos];
      T &parent = vals[parent_pos];
      // compare child vs parent (comparator for min vs max-heap)
      if (comp(child, parent)) {
          // swap position of child and parent if true
          std::swap(child, parent);
          pos = parent_pos;
      }
    // break loop if child is well positioned
    else {
        break;
    }
  } 
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const {
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::out_of_range("Empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return vals[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap

// HEAPIFY IMPLEMENTATION

template <typename T, typename PComparator>
void Heap<T,PComparator>::pop() {
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::out_of_range("Empty");
  }

  // change the first element into the last one and pop last element
  vals[0] = vals[vals.size() - 1];
  vals.pop_back();
  --h_size;
  std::size_t pos = 0;
  
  // trickle down implementation (heap slides)
  while (true) {
      std::size_t smallestChild = pos * num_child + 1;

      // Find the smallest child among all children
      for (std::size_t i = 2; i <= num_child; ++i) {
          std::size_t currentChild = pos * num_child + i;
          if (currentChild < vals.size() && comp(vals[currentChild], vals[smallestChild])) {
              smallestChild = currentChild;
          }
      }

      // If the smallest child is smaller than the current node, swap them
      if (smallestChild < vals.size() && comp(vals[smallestChild], vals[pos])) {
          std::swap(vals[smallestChild], vals[pos]);
          pos = smallestChild;
      } 
      else {
          break;
      }
    }
}


#endif

