Checking Shortest Paths
Shortest path algorithms can be complicated.  How can we check that they are correct?

Luckily, there are simple and efficient algorithms to verify that the output of a single source shortest path algorithm is correct.  Your task in this part of the assignment is to implement such an algorithm.  You will then use this algorithm to check that your single source shortest path algorithm in part 3 is correct!

Background
For this part all graphs will be directed and weighted, and can possibly have negative weights.  We will use the graph class from Week 10 Tutorial with the additions that now the class is templated and we add public member functions to remove edges and check if an edge is present.  The template  type T represents the type of the edge weights.  For us, T can be int, MyInteger, or double.  All the functions you write will also be templated.  

If an algorithm claims that the shortest path in a graph 
𝐺
G from vertex 0 to vertex 5 has length 20, we need to verify two things:

1) There actually is a path from vertex 0 to vertex 5 of length 20.

2) There is no path from vertex 0 to vertex 5 of length < 20.

Item (1) is relatively simple to verify, but (2) is much more interesting.  The way we will verify (1) is through a shortest path tree, which we discuss next.

Shortest Path Trees
In part 3 of this assignment you will write a single source shortest path algorithm that outputs a shortest path tree.  A shortest path tree for a graph G with N vertices is a graph with only (at most) N-1 edges that has all the information to construct a shortest path from the source to any vertex in G.  The source vertex is the root of the tree, i.e., all edges are directed away from the source.  Technically a shortest path tree is not necessarily a tree, because in the original graph G some vertices may not be reachable from the source.  In the shortest path tree such non-reachable vertices will be isolated vertices--vertices no incoming or outgoing edges.  Precisely, a shortest path tree will have the following properties:

a) It is a tree plus some isolated vertices.  Any vertex not reachable from the source must be isolated, there are no cycles even ignoring edge directions, and all edges are directed away from the root.

b) All edges of the tree are also edges in the original graph, with the same weight.  That is, the tree is a subgraph of the original graph.

c) The length of the (unique!) path from the root of the tree to any other non-isolated vertex is the same as the length of a shortest path in the original graph from the source to that vertex.

You will write functions to verify each of these three properties.

To check (a) we have the function

template <typename T>
bool isTreePlusIsolated(const Graph<T>& G, int root);
This function should return false if and only if G contains a cycle when edge directions are ignored, or if there is a non-isolated vertex which is not reachable from the root.

To check (b) we have the function

template <typename T>
bool isSubgraph(const Graph<T>& H, const Graph<T>& G);
As this function is pretty simple, we generalise it beyond trees to two graphs H and G.  The function should return true if and only if H is a subgraph of G, that is the size of H is at most that of G and every edge of H is also an edge in G with the same weight.

To help verify (c) we have a function that returns a vector that records the length of the path from the root to every other vertex in the tree.  

template <typename T>
std::vector<T> pathLengthsFromRoot(const Graph<T>& tree, int root);
As we are using this to check a "more complicated" shortest path algorithm, you should take advantage of the fact that this is a tree to use a "simple" algorithm (hint: depth or breadth-first search).

Taken together, these functions can verify part 1 because they show there is a path in the tree from the source to a given vertex of a certain length, and all edges of the tree are also edges in the original graph.  Now let us turn to (2).

No shorter paths
Item (2) is quite interesting.  How can we verify there is no shorter path without trying all of them?  All the shortest path algorithms we have studied are based on relaxing edges.  We maintain a vector bestDistanceTo, where bestDistanceTo.at(v) is always an upper bound on the length of a shortest path from the source to v.  We then go over edges in some order and relax them.  If there is an edge from u to v we do:

if (bestDistanceTo.at(u) > bestDistanceTo(v) + G.getEdgeWeight(v, u) {
    bestDistanceTo.at(u) = bestDistanceTo(v) + G.getEdgeWeight(v, u)
}
Think about the Bellman-Ford shortest path algorithm.  We initialise bestDistanceTo.at(source) = 0 and bestDistanceTo.at(v) = infinity for every other vertex v.  Thus bestDistanceTo.at(v) starts as an upper bound on the distance from vertex 0 to vertex v.  We then do n-1 rounds of relaxing every edge, when the graph has n vertices.  If there is no negative weight cycle, the final bestDistanceTo values will be the shortest path lengths.

If in any round of Bellman-Ford no bestDistanceTo value changes during the relaxation of all the edges, then no bestDistanceTo value will change for the rest of the algorithm.  We have already found the shortest path lengths.

This is the idea we use to verify shortest path lengths.  Given a bestDistanceTo vector where bestDistanceTo.at(v) is guaranteed to be an upper bound on the length of a shortest path from the source to v, we check the following two things:

1) bestDistanceTo.at(source) == 0

2) After relaxing all edges no bestDistanceTo value changes.

Why this works: If either (1) or (2) does not hold then bestDistanceTo cannot be correct.  If (1) holds then we can imagine starting the Bellman-Ford algorithm "midstream" with the bestDistanceTo vector.  If (2) holds then running the Bellman-Ford algorithm won't change bestDistanceTo, so it must already have the correct shortest path lengths!

Implement this check in the algorithm

template <typename T>
bool allEdgesRelaxed(const std::vector<T>& bestDistanceTo, const Graph<T>& G, int source) {
Technical note: There is some decision to be made as to how unreachable vertices should be handled in bestDistanceTo.  Intuitively, if v is unreachable from the source we would set bestDistanceTo.at(v) to "infinity".  However, the notion of infinity differs depending on the template type T.  With doubles we can use std::numeric_limits<double>::infinity(), but this does not work with ints.  To avoid this issue, in all test cases here all vertices are reachable from the source.  For your reference, we have handled this issue by using the following function, which you are free to copy.

template <typename T>
T infinity() {
  if (std::numeric_limits<T>::has_infinity) {
    return std::numeric_limits<T>::infinity();
  } else if constexpr (std::is_same_v<T, MyInteger>) {        // Check if T == MyInteger
    return MyInteger {std::numeric_limits<int>::max()};
  } else {
    return std::numeric_limits<T>::max();
  }
}

Testing
We provide 18 test cases in main.cpp to get you started.  You are free to modify main.cpp as you like.  Implement your solution in the file graph.hpp.  When you hit mark your code will be tested on 

5 test cases for isSubgraph

20 test cases for isTreePlusIsolated

20 test cases for pathLengthsFromRoot

20 test cases for allEdgesRelaxed

Marking
This part of the assignment is worth 5 points.  

Functionality (3.9 points): This is judged purely on passing test cases.  Each test case is worth 0.06 points.

No Bugs (1.1 points): If you pass all the test cases on "mark" you can additionally earn the "No Bugs" 1.1 point if our markers cannot come up with a test case to make your code fail.

Submission
You must submit your code by pressing the "mark" button on Ed. No other forms of submission will be accepted. You are welcome to develop your code elsewhere, but remember it must compile and run on Ed. As usual, we compile with g++ -std=c++20 -Wall -Wextra for this assignment. 

You may submit as many times as you like before the due date.  We will mark your last submission.

Due Date
Code submission is due by 11:59pm Friday 24 May. Work submitted late without an approved extension is subject to a late penalty of 10 per cent of the total available marks deducted per calendar day that the assessment is overdue.

Plagiarism Checking
All code will be checked for student misconduct and plagiarism using specialised code similarity detection software. The use of Generative AI like ChatGPT is not allowed to produce code for your solution. Do not share your code with others or post it to any public repositories before the deadline has passed. Please include in comments at the top of your code links to or descriptions of any resources you used in the construction of your solution.