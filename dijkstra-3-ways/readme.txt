Dijkstra 3 Ways
In Dijkstra's single source shortest path algorithm we maintain a vector bestDistanceTo holding the length of the shortest path we have found so far from the source to each vertex.  In each round we take the vertex with smallest bestDistanceTo value that we haven't already explored and relax all of its outgoing edges.

There are two main implementation issues in Dijkstra's algorithm:

1) What data structure should we use to quickly find the unexplored vertex with smallest bestDistanceTo value?

2) How should we update this data structure when we find a shorter path to a vertex, i.e., when its bestDistanceTo value goes down?

We have seen that a good data structure for (1) is a priority queue.  In tutorial Week 10 we went over a lazy implementation of Dijkstra's algorithm using a priority queue.  In a lazy implementation of Dijkstra a vertex we essentially ignore item (2).  When we found a better path to a vertex, we did not remove entries in our priority queue corresponding to the this vertex, but just added a new entry with the better distance value.  In this way, a single vertex could appear in the priority queue multiple times.  

In this task we will look at two other ways at implementing Dijkstra's algorithm and compare them.  The key difference in these implementations is how they handle (1) and (2).

a) Lazy Dijkstra: In lazy Dijkstra we simply add the new best distance and vertex to our priority queue.

b) Dijkstra with an index priority queue: here we have the changeKey operation.  Thus we can update the priority of a vertex already in the priority queue with the value of the new best distance we have found.  In this way, the size of the queue is always at most the number of vertices.

c) Dijkstra with a std::set to hold {distance, vertex} pairs.  A set allows fast insertion and deletion, and can iterate over the keys in sorted order.  In this case we can delete the old best distance to the vertex and then insert the newly found distance.  For item (1) we can retrieve the minimum element as it will be pointed to by begin().

This exercise is inspired by this blog post, which goes over different ways of implementing Dijkstra's algorithm  in C++.

Data Sets
We provide a real world data set from the DIMACS shortest path implementation challenge on which you can test your algorithms.  This data is from the streets of New York and has 264,346 vertices.  We will also test your code offline on a data set from roads in Florida with 1,070,376 vertices (unfortunately Ed complains that this file is too big to put on the scaffold).

Task 1 (8 points)
We provide the signatures of 3 functions in the graph.hpp file corresponding to the options (a), (b), (c).

Graph<T> singleSourceLazy(const Graph<T>& G, int source);
Graph<T> singleSourceIndex(const Graph<T>& G, int source);
Graph<T> singleSourceSet(const Graph<T>& G, int source);
In each case you are given a graph G and a source vertex and the task is to output a shortest path tree containing shortest paths in G from the source vertex to every other vertex.  Expect this code to be instantiated where the template type is int, MyInteger, and double.

You are to implement any 2 of these functions.  The only difference between singleSourceLazy and the version of Dijkstra implemented in tutorial Week 10 is that now you are to output a shortest path tree, rather than just a vector holding the lengths of shortest paths from the source to every vertex.

If your index priority queue from the first part of assignment 2 is working, I would suggest using this to implement singleSourceIndex.  Dijkstra's algorithm is very elegant with an index priority queue!  If your index priority queue is not working, then try singleSourceSet.

As a "graduation" from DSA, we provide minimal scaffolding to help you out.  Part of this task is to see how you can use the testing framework developed in part 2 of assignment 2 to write test cases and verify for yourself that your algorithm is working.  We provide a function 

Graph<int> randomGraph(int N, unsigned seed, double p = 0.5)
in main.cpp to generate random graphs you can use to generate examples on which to test your code, in addition to the three graphs that are provided as files.  When you hit "mark" we run your functions against the New York road data set, but do not check that it is correct.  Please still do hit mark occasionally as otherwise we cannot see your code.

Marking Task 1: 

Each of the two functions you choose to implement will be marked out of 4 points.  These 4 points are marked as follows:

Testing Framework (2 points): You write good tests to check that your algorithm is working using the framework developed in part 2.  This testing covers int, doubles, and MyInteger.

Functionality (2 points): We cannot generate test cases for which your algorithm fails.

Task 2 (2 points)
Compare and contrast the different methods for implementing Dijkstra's algorithm.  Do you notice any differences?  You can look at both running time and number of operations (that can be seen using the type MyInteger).  Record your findings in the file "Dijkstra Report" provided in the next challenge.  Put your best shortest path algorithm in the function 

Graph<T> singleSourceShortestPaths(const Graph<T>& G, int source);
We will have a class competition on the performance of this function on the Florida road data set.  Top performers can earn bonus points.

Optional Extra Credit
Successful implementation of all of (a), (b), (c) that pass all our testing will earn 1 bonus point.

Submission
You must submit your code by pressing the "mark" button on Ed. No other forms of submission will be accepted. You are welcome to develop your code elsewhere, but remember it must compile and run on Ed. As usual, we compile with g++ -std=c++20 -Wall -Wextra for this assignment. 

You may submit as many times as you like before the due date.  We will mark the last submission.

Due Date
Code submission is due by 11:59pm 24 May. Work submitted late without an approved extension is subject to a late penalty of 10 per cent of the total available marks deducted per calendar day that the assessment is overdue.

Plagiarism Checking
All code will be checked for student misconduct and plagiarism using specialised code similarity detection software. The use of Generative AI like ChatGPT is not allowed to produce code for your solution. Do not share your code with others or post it to any public repositories before the deadline has passed. Please include in comments at the top of your code links to any online resources you used in the construction of your solution.