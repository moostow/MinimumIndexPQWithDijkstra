Index Priority Queue
In this assignment we will extend the implementation of a minimum binary heap from tutorial week 8 to build a data structure called a (minimum) index priority queue.  In an index priority queue, the elements we store consist of two parts, a priority and an index.  Think of the situation of a patient coming into the emergency room.  The priority measures the severity of the patient's condition.  We see patients in order of priority.  The index is like the patient's name.  This gives a way to refer and call up patients: "Patient Bob, the doctor is ready to see you now...".  

Likewise, associating each element with an index, or "name", will allow us to call up an element in the queue by its index: we can remove an element with a given index, change the priority associated with an index, or tell if the queue contains an element with a given index.  None of these things can be done in an ordinary priority queue.  

To keep things simple we will always assume that the indices are 0, ..., N-1, where N is the maximum possible number of elements.  The maximum number of elements will be specified by the user when the index priority queue is initialised.  

Let's have a look at the class now.

template <typename T>
class IndexPriorityQueue {
...
};
The class is called IndexPriorityQueue.  It is a templated class where T will denote the type of the priorities.  Comparison of priorities is what determines the ordering of the elements in the queue.  You should think that T could be a very large type, where it is expensive to make copies or assignments---we want to avoid this as much as possible.  Let's go over the member functions you have to implement.

Constructor
explicit IndexPriorityQueue(int N);
The constructor takes as a parameter an integer N which is the maximum number of elements the priority queue can hold.  Each element is a priority with an associated index.  The indices will be 0, ..., N - 1 when the parameter to this constructor is N.  The constructor should run in time 
𝑂
(
𝑁
)
O(N).

Basic Operations
void push(const T& priority, int index);
If an element with the parameter index is already in the priority queue, then do nothing.  Otherwise, add a new element with priority priority and index index to the index priority queue.  This is similar to the push in a normal priority queue except that now a priority is inserted with its associated index.  This function should work in time 
𝑂
(
log
⁡
𝑁
)
O(logN).

void pop();
Remove the element with minimum priority from the index priority queue.  This function should work in time 
𝑂
(
log
⁡
𝑁
)
O(logN).

std::pair<T priority, int index> top() const;
Return a pair with the minimum priority priority in the index priority queue and its associated index index.  This function should work in constant time.

bool empty() const;
int size() const;
Respectively return whether or not there are any elements in the index priority queue and the number of elements in the index priority queue.  These functions should work in constant time.

New Operations
Now we have some new functions that are special to an index priority queue.

void changeKey(const T& priority, int index);
If there is no element with index index in the index priority queue, then insert priority priority with index index into the queue. If there already is an element with index index in the queue, then change its priority to priority.  This function should work in time 
𝑂
(
log
⁡
𝑁
)
O(logN).

 void erase(int index);

If no element with index index exists in the priority queue do nothing.  Otherwise, remove the element with index index from the index priority queue.  This function should work in time 
𝑂
(
log
⁡
𝑁
)
O(logN).

bool contains(int index) const;
Does the index priority queue have an element with index index?  This function should work in constant time.

Implementation
For this challenge implement all member functions in the file index_pq.hpp.  Please don't use any of set, unordered_set, map, or unordered_map in your solution.

We have defined the following private member variables for you in the scaffold.  You are welcome to define additional member variables, or remove these if you see another way to implement an index priority queue meeting the requirements.

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
  ...
};

For the implementation you should think that the priority could be a type requiring a lot of memory.  We don't want to have to be moving around priorities during the operation of the index priority queue.  Therefore we have a vector priorities of size N where priorities.at(i) is the priority associated with index i.  When the index priority queue is initialised with parameter N, the default constructor, assignment operator, and copy constructor of the priority type should each be called at most N times during the entire operation of the index priority queue.

The heap itself is stored in the variable priorityQueue , which stores and manipulates indices.  The indices are just ints, which are cheap to construct and assign as they move within priorityQueue to maintain the minimum heap property.  

In an index priority queue, we also need to be able to lookup an element by its index.  This is done by the vector indexToPosition .  During all operations of the priority queue we maintain the invariant that indexToPosition.at(i) is the position of index i in priorityQueue.  In other words, priorityQueue.at(indexToPosition.at(i)) = i and indexToPosition.at(priorityQueue.at(j)) = j .


Finally, you are also free to add member functions (perhaps analogs of sink and swim we had in Tutorial Week 8?) to index_pq.hpp to assist with your implementation.

Testing
We provide 20 tests in main.cpp to get you started.  You are free to modify main.cpp as you like.  When you hit "mark" your code will be checked against the 20 tests in main plus an additional 20 hidden tests.

Marking
This exercise is worth 15 points.  The points are divided up as follows.

Functionality (12 points): This is graded purely on the basis of passing test cases.  When you hit mark your code will be run on 40 test cases.  Your functionality score is 0.3 times the number of test cases you pass.

Style (1 point) This will be marked by the grading team according to the following criteria.

 1) comments --- comments should explain blocks of code where the intention is not immediately clear from the code itself. 

 2) variable names --- variables are given names that explain their role and use. 

 3) formatting --- consistent formatting in indentation and use of braces.

 4) compiles without warnings.

Design (1 point) For this point we will check if the code well-organised, the path to the solution is direct, and functions are not longer than necessary.

No Bugs (1 point) After seeing common errors we will devise another suite of test cases.  To receive the "No Bugs" point you must pass all the original 40 test cases, plus our additional test cases.

Submission
You must submit your code by pressing the "mark" button on Ed. No other forms of submission will be accepted. You are welcome to develop your code elsewhere, but remember it must compile and run on Ed. As usual, we compile with g++ -std=c++20 -Wall -Wextra for this assignment. 

You may submit as many times as you like before the due date.  We will mark your last submission.

Due Date
Code submission is due by 11:59pm Friday 24 May. Work submitted late without an approved extension is subject to a late penalty of 10 per cent of the total available marks deducted per calendar day that the assessment is overdue.

Plagiarism Checking
All code will be checked for student misconduct and plagiarism using specialised code similarity detection software. The use of Generative AI like ChatGPT is not allowed to produce code for your solution. Do not share your code with others or post it to any public repositories before the deadline has passed. Please include in comments at the top of your code links to or descriptions of any resources you used in the construction of your solution.