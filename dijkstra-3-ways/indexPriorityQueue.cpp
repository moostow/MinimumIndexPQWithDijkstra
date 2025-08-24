#ifndef INDEX_PRIORITY_QUEUE_HPP_
#define INDEX_PRIORITY_QUEUE_HPP_

#include <vector>
#include <algorithm>

template <typename T>
class IndexPriorityQueue {
 private:
  // vector to hold priorities.  
  // priorities.at(i) is the priority associated to index i
  // the heap will only contain indices, we look up priorities
  // in this vector as needed
  std::vector<T> priorities {};
  // priorityQueue stores indices: priorityQueue.at(i) is an index
  // priorityQueue functions as the heap and is heap ordered: 
  // priorities.at(priorityQueue.at(i)) <= priorities.at(priorityQueue.at(2 * i)) 
  // priorities.at(priorityQueue.at(i)) <= priorities.at(priorityQueue.at(2 * i) + 1) 
  std::vector<int> priorityQueue {};
  // indexToPosition.at(i) is the position in priorityQueue of index i
  // priorityQueue.at(indexToPosition.at(i)) = i
  // indexToPosition.at(priorityQueue.at(j)) = j
  std::vector<int> indexToPosition {};
  int size_ = 0;
  int maxSize_ = 0; // newly added

 public:
  explicit IndexPriorityQueue(int);
  void push(const T&, int);
  void pop();
  void erase(int);
  bool contains(int) const;
  void changeKey(const T&, int);
  std::pair<T, int> top() const;
  bool empty() const;
  int size() const;
  int maxSize() const; //initialises to be the maximum size which is N in the constructor, to then be used in contains to check if index is within range.

 private:
  void swim(int i); 
  void sink(int index);
};

// Useful helper functions
int leftChild(int i) {
  return 2*i;
}

int rightChild(int i) {
  return 2*i + 1;
}

int parent(int i) {
  return i/2;
}

//Difficult
// IndexPriorityQueue member functions
template <typename T>
IndexPriorityQueue<T>::IndexPriorityQueue(int N) { //Constructor
  priorityQueue.push_back(int {});
  priorities.resize(N);
  indexToPosition.resize(N, -1);
  size_ = 0; 
  maxSize_ = N; //initialises to be the maximum size which is N to later on be used in contains to check if index is within range.
}
template <typename T>
bool IndexPriorityQueue<T>::empty() const { 
  return size_ == 0;
}

template <typename T>
int IndexPriorityQueue<T>::size() const {
  return size_;
}

template <typename T> //returns the max size as N to later be called in contains.
int IndexPriorityQueue<T>::maxSize() const {
  return maxSize_;
}

template <typename T> 
void IndexPriorityQueue<T>::push(const T& priority, int name) {
  
  if (contains(name)){ //if element with parameter name is already in the priority queue,-
    return; //-don't push. (return)
  }
  // If an element with the parameter index is already in the priority queue, then do nothing.
  priorityQueue.push_back(name);
  ++size_;
  priorities.at(name) = priority; //set priority at index name as priority. 
  indexToPosition.at(name) = size_; //set indexToPosition of name as the last element(size_).
  swim(size_); //swim the new element upwards (swim checks if this is needed).
} 


//Remove the element with the minimum priority (first element in the a minimum heap).
template <typename T>
void IndexPriorityQueue<T>::pop() {
  //check if elements in heap exist first
  if (size_ == 0){
    std::cout << "no elements in the heap" << '\n';
    return; //nothing to pop.
  }
  std::swap(priorityQueue.at(1), priorityQueue.at(size_)); //swap the first elements(minimum element) priorityQueue with the first elements priorityQueue.
  std::swap(indexToPosition.at(priorityQueue.at(1)), indexToPosition.at(priorityQueue.at(size_))); //swap the last elements index with the first elements index.
  indexToPosition.at(priorityQueue.at(size_)) = -1; //set the last element to -1 (non-existent position)
  priorityQueue.pop_back(); //remove the last element(size_) from the queue (formerly the min heap)
  --size_; //decrease the size.
  sink(1); //sink the first element (which has the priority of the former size_ priority) to the correct position.
}


//Erase removes the index that the user prompts to remove at index. Similar to pop, however, it removes any index is pleases
//the index to be removed is swapped with the size_(last element) and then popped the heap is popped back(deletes the last element in the heap which is the index).
template <typename T>
void IndexPriorityQueue<T>::erase(int index) { 
  if (!contains(index)){ //if the element being called to be erased does not exist, do nothing as there is nothing to erase.
    return;
  }
//swap the priorityQueue(position number) of the index with the last elements position number(size_)

/* Normally the index is popped back after being swapped with the size_ (last) element and then swam/sunk.-
to prevent swimming a position that doesn't exist, we check if the index being called to be removed is the size_ element */
  if (indexToPosition.at(index) == size_){ 
    indexToPosition.at(index) = -1; // clear the indexToPosition of the index.
    priorityQueue.pop_back(); // pop back the last element in the node
    --size_; //reduce size
    return; //end here as we don't need to implement the normal erase procedure or swim/sink.
  }
  int positionToBeErased = indexToPosition.at(index); //stores the index to be erased safely in order to swim/sink that position later on.
  std::swap(priorityQueue.at(positionToBeErased), priorityQueue.at(size_)); //swaps the priorityQueue at the index that is meant is being called to be removed with the size_ 
  // -(last) element just like pop.
  //(regarding the first swapping parameter for the next line): As it's being swapped on line 143^, you need to keep track of the index by swapping the initial value.
  std::swap(indexToPosition.at(priorityQueue.at(positionToBeErased)), indexToPosition.at(priorityQueue.at(size_)));   //swap the indexToPosition of the index with the last elements index (size_)
  priorities.at(priorityQueue.at(indexToPosition.at(index))) = T{}; //remove the priorities associated with the index being removed to 0. 
  indexToPosition.at(index) = -1; //make index unaccessible by initialising it to -1
  priorityQueue.pop_back(); //remove the last element which was element index
  --size_; 
  //swim or sink at where size_ is currently, formerly where indexToPosition.at(index) was before being swapped.
  swim(positionToBeErased); 
  sink(positionToBeErased); //added a parameter as it was needed to track where we needed to sink as pop wasn't the only function utilising sink now.
}


/* Sink plays a role in maintaining the minimum heap by replacing(or sinking) heap elements down the heap into the correct position if an element was larger than its child */
template <typename T>
void IndexPriorityQueue<T>::sink(int position) {
  for (int current = position; leftChild(current) <= size_;) { //begin iterating from position as long as the left child is at most the size.
    int left = leftChild(current);
    int elementToSwap = left; //element that will be swapped with.

/* if the right child is at most the size and the priority of the left child is larger than the right child, we look into swapping the current with the right child. */
    if (left + 1 <= size_ && priorities.at(priorityQueue.at(left)) > priorities.at(priorityQueue.at(left + 1))){ 
      ++elementToSwap;
    }
    //if the priority of the current element is smaller or equal to the priority of the child it's swapping with, return as the min heap order is maintained.
    if (priorities.at(priorityQueue.at(current)) <= priorities.at(priorityQueue.at(elementToSwap))){ 
      return;
    }
    std::swap(priorityQueue.at(current), priorityQueue.at(elementToSwap)); //swap the current patients(parent) priority with the child that is smaller than itself.
    std::swap(indexToPosition.at(priorityQueue.at(current)), indexToPosition.at(priorityQueue.at(elementToSwap))); //swap and match the current patients priorityQueue index with the child that is smaller than itself.
    current = elementToSwap; //the parent index is now the child. Needed for next iteration if further sinking is needed.
  }
}

/* Swim plays a role in maintaining the minimum heap by replacing(or swimming) heap elements up the heap into the correct position if an element was smaller than its parent */
template <typename T>
void IndexPriorityQueue<T>::swim(int i) {
  //let's say to swim, we intitalise p to be the parent of
  // it's child, i
  //we then check loop as long as p is bigger than 0
  for (int p = parent(i); p > 0; p = parent(p)) {
    if (priorities.at(priorityQueue.at(p)) > priorities.at(priorityQueue.at(i))){ // if the priority of the parent is larger than its child, swap the element to maintain the min heap.
      std::swap(priorityQueue.at(i), priorityQueue.at(p)); //swap child with parent in the priorityQueue.
      std::swap(indexToPosition.at(priorityQueue.at(i)), indexToPosition.at(priorityQueue.at(p))); //swap the indexToPosition position of the parent and child.
      i = p; //the child index is now the parent. Needed for next iteration if further swimming is needed.
    }
    else {
      return; //If no swimming needs to be done, return.
    }
  }
}

/* The top function returns the minimum element. In the case of a min heap, that would be first element in the heap. */
template <typename T>
std::pair<T, int> IndexPriorityQueue<T>::top() const {
  if (size_ > 0){ // if there are elements in the heap.
    return {priorities.at(priorityQueue.at(1)), priorityQueue.at(1)}; //return the priority of the first element, as well as what it's referred as (name - priorityQueue).
  }
  std::cout << "no elements in the heap" << '\n';
  return {T {}, 0};
}

// if vertex i is not present, insert it with key
// otherwise change the associated key value of i to key
/* The changeKey function pushes an index with a priority if there is no element with patientName in the index priority queue. 
If there is already an element with that patientName, change it's priority and then swim or sink to the right position in the heap accordingly. */
template <typename T>
void IndexPriorityQueue<T>::changeKey(const T& key, int patientName) {
  if (!contains(patientName)){ //if there no patietName with patientName in the index priority queue-
    push(key, patientName); //-push element inside with that patientName.
  }
  else { //if there is a patientName with patientName-
    priorities.at(patientName) = key; //-overrite old priority with new priority
    swim(indexToPosition.at(patientName)); // first, check if the element needs to swim (this happens in the swim function) and then swim or refrain from swimming accordingly.
    sink(indexToPosition.at(patientName)); // otherwise, check if the elemennt needs to sink (this happens in the sink function) and then sink or refrain from sinking accordingly. 
  }
}

/* The contains function checks if the index priority queue contains index as element */
template <typename T>
bool IndexPriorityQueue<T>::contains(int index) const {
  if(index >= maxSize_ || index < 0) return false; //Checks if the index is within range(In-bound)? if yes,- 
  return indexToPosition.at(index) != -1; //- check if it's in the queue.
}


#endif      // INDEX_PRIORITY_QUEUE_HPP_
