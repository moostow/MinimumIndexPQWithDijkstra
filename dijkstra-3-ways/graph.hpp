#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream>
#include <fstream>
#include <utility>
#include <functional>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <unordered_map>
#include <limits>
#include "my_integer.hpp"
#include "indexPriorityQueue.cpp"

template <typename T>
class Graph {
 private:
  std::vector<std::unordered_map<int, T> > adjList {};
  int numVertices {};

 public:
  // empty graph with N vertices
  explicit Graph(int N);

  // construct graph from edge list in filename
  explicit Graph(const std::string& filename);

  // add an edge directed from vertex i to vertex j with given weight
  void addEdge(int i, int j, T weight);

  // removes edge from vertex i to vertex j
  void removeEdge(int i, int j);

  // is there an edge from vertex i to vertex j?
  bool isEdge(int i, int j) const;

  // return weight of edge from i to j
  // will throw an exception if there is no edge from i to j
  T getEdgeWeight(int i, int j) const;

  // returns number of vertices in the graph
  int size() const;

  // alias a const iterator to our adjacency list type to iterator
  using iterator = 
  typename std::vector<std::unordered_map<int, T> >::const_iterator;

  // cbegin returns const iterator pointing to first element of adjList
  iterator begin() const {
    return adjList.cbegin();
  }

  iterator end() const {
    return adjList.cend();
  }

  // return iterator to a particular vertex
  iterator neighbours(int a) const {
    return adjList.begin() + a;
  }
};

template <typename T>
Graph<T>::Graph(int N) : adjList(N), numVertices {N} {}

template <typename T>
Graph<T>::Graph(const std::string& inputFile) {
  std::ifstream infile {inputFile};
  if (!infile) {
    std::cerr << inputFile << " could not be opened\n";
    return;
  }
  // first line has number of vertices
  infile >> numVertices;
  adjList.resize(numVertices);
  int i {};
  int j {};
  double weight {};
  // assume each remaining line is of form
  // origin dest weight
  while (infile >> i >> j >> weight) {
    addEdge(i, j, static_cast<T>(weight));
  }
}

template <typename T>
int Graph<T>::size() const {
  return numVertices;
}

template <typename T>
void Graph<T>::addEdge(int i, int j, T weight) {
  if (i < 0 or i >= numVertices or j < 0 or j >= numVertices) {
    throw std::out_of_range("invalid vertex number");
  }
  adjList[i].insert({j, weight});
}

template <typename T>
void Graph<T>::removeEdge(int i, int j) {
  // check if i and j are valid
  if (i >= 0 && i < numVertices && j >= 0 && j < numVertices) {
    adjList[i].erase(j);
  }
}

template <typename T>
bool Graph<T>::isEdge(int i, int j) const {
  if (i >= 0 && i < numVertices && j >= 0 && j < numVertices) {
    return adjList.at(i).contains(j);
  }
  return false;
}

template <typename T>
T Graph<T>::getEdgeWeight(int i, int j) const {
  return adjList.at(i).at(j);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Graph<T>& G) {
  for (int i = 0; i < G.size(); ++i) {
    out << i << ':';
    for (const auto& [neighbour, weight] : *(G.neighbours(i))) {
      out << " (" << i << ", " << neighbour << ")[" << weight << ']';
    }
    out << '\n';
  }
  return out;
}

// End of functions from Graph class

// return a number of type T to stand in for "infinity"
template <typename T>
T infinity() {
  if (std::numeric_limits<T>::has_infinity) {
    return std::numeric_limits<T>::infinity();
  } else if constexpr (std::is_same_v<T, MyInteger>) {
    return MyInteger {std::numeric_limits<int>::max()};
  } else {
    return std::numeric_limits<T>::max();
  }
}

// lazy solution as in Tutorial Week 10
template <typename T>
std::vector<T> singleSourceLazyDistance(const Graph<T>& G, int source) {
  // alias the long name for a minimum priority queue holding
  // objects of type DistAndVertex
  using DistAndVertex = std::pair<T, int>; //(ME)stores distance to a vertex ALONG WITH the vertex itself. (distance is T, int is vertex it reaches)
  using minPQ = std::priority_queue<DistAndVertex,
                                  std::vector<DistAndVertex>,
                                  std::greater<DistAndVertex> >; //minimum priorityqueue
  minPQ queue {};
  queue.push({T {}, source});
  // record best distance to vertex found so far
  int N = G.size();
  std::vector<T> bestDistanceTo(N, infinity<T>());
  bestDistanceTo.at(source) = T {};
  // being in visited means we have already explored a vertex's neighbours
  // the bestDistanceTo for a vertex in visited is the true distance.
  std::vector<bool> visited(N);
  while (!queue.empty()) {
    auto [dist, current] = queue.top(); //dist is the distance to vertex //current is the current vertex the distance to is being calculated of
    queue.pop(); //pops it out means it's the lowest in the shortest path tree.
    // as we use a lazy version of Dijkstra a vertex can appear multiple
    // times in the queue.  If we have already visited the vertex we
    // take out of the queue we just go on to the next one
    if (visited.at(current)) {
      continue;
    }
    visited.at(current) = true;
    // relax all outgoing edges of current
    for (const auto& [neighbour, weight] : *(G.neighbours(current))) {
      T distanceViaCurrent = bestDistanceTo.at(current) + weight;
      if (bestDistanceTo.at(neighbour) > distanceViaCurrent) {
        bestDistanceTo.at(neighbour) = distanceViaCurrent;
        // lazy dijkstra: nextPoint could already be in the queue
        // we don't update it with better distance just found.
        queue.push({distanceViaCurrent, neighbour});
      }
    } //graph, that is the shortest path, and im doing that by adding the edges to the shortest path tree getting the shortest path into the shortest path tree
  }
  return bestDistanceTo;
}

// Solution using an index priority queue here
template <typename T>
Graph<T> singleSourceIndex(const Graph<T>& G, int source) {
  int N = G.size();
  IndexPriorityQueue<T> queue{N};
  queue.push(T{}, source); 
  std::vector<T> bestDistanceTo(N, infinity<T>());
  std::vector<int> prev(N, -1);
  bestDistanceTo.at(source) = T {};
  // being in visited means we have already explored a vertex's neighbours
  // the bestDistanceTo for a vertex in visited is the true distance.
  std::vector<bool> visited(N);
  Graph<T> shortestPath{N};
  while (!queue.empty()) {
    auto [dist, current] = queue.top(); //dist is the distance to vertex //current is the current vertex the distance to is being calculated of
  
    queue.pop(); //pops it out means it's the lowest in the shortest path tree.
    if (visited.at(current)) {
      continue;
    }
    visited.at(current) = true;
    // relax all outgoing edges of current
    for (const auto& [neighbour, weight] : *(G.neighbours(current))) {
      T distanceViaCurrent = bestDistanceTo.at(current) + weight;
      if (bestDistanceTo.at(neighbour) > distanceViaCurrent) {// priorities.at(priorityQueue.at(neighbour))
        bestDistanceTo.at(neighbour) = distanceViaCurrent;
        prev.at(neighbour) = current; // previous element pointed to neighbour by current 
        queue.changeKey(distanceViaCurrent, neighbour); //updatest he priority queue to visit the next best priority
      }
    } 
  }
  for (auto i = 0; i < N; i++){
    if(prev.at(i) != -1) {
    shortestPath.addEdge(prev.at(i), i, G.getEdgeWeight(prev.at(i), i));
    }
  }
  return shortestPath;
}

// Implement your lazy solution using std::priority_queue here
template <typename T>
Graph<T> singleSourceLazy(const Graph<T>& G, int source) {
  using DistAndVertex = std::pair<T, int>;
  using minPQ = std::priority_queue<DistAndVertex,
                                  std::vector<DistAndVertex>,
                                  std::greater<DistAndVertex> >; //minimum priorityqueue
  minPQ queue {};
  queue.push({T {}, source});
  // record best distance to vertex found so far
  int N = G.size();
  std::vector<T> bestDistanceTo(N, infinity<T>());
  std::vector<int> prev(N, -1);
  bestDistanceTo.at(source) = T {};
  // being in visited means we have already explored a vertex's neighbours
  // the bestDistanceTo for a vertex in visited is the true distance.
  std::vector<bool> visited(N);
  Graph<T> shortestPath{N};
  while (!queue.empty()) {
    auto [dist, current] = queue.top(); //dist is the distance to vertex //current is the current vertex the distance to is being calculated of
    queue.pop(); //pops it out means it's the lowest in the shortest path tree.
    if (visited.at(current)) {
      continue;
    }
    visited.at(current) = true;
    // relax all outgoing edges of current
    for (const auto& [neighbour, weight] : *(G.neighbours(current))) {
      T distanceViaCurrent = bestDistanceTo.at(current) + weight;
      if (bestDistanceTo.at(neighbour) > distanceViaCurrent) {
        bestDistanceTo.at(neighbour) = distanceViaCurrent;
        prev.at(neighbour) = current; // previous element pointed to neighbour by current 
        // lazy dijkstra: nextPoint could already be in the queue
        // we don't update it with better distance just found.
        queue.push({distanceViaCurrent, neighbour});
      }
      // shortestPath.addEdge(current, neighbour, distanceViaCurrent);
    } //graph, that is the shortest path, and im doing that by adding the edges to the shortest path tree getting the shortest path into the shortest path tree
  }

  for (auto i = 0; i < N; i++){
    if(prev.at(i) != -1) {//&& i != 0) { //checks for source and isolated vertex
      shortestPath.addEdge(prev.at(i), i, G.getEdgeWeight(prev.at(i), i));
    }
  }
  return shortestPath;
}

// Implement your solution using std::set here
template <typename T>
Graph<T> singleSourceSet(const Graph<T>& G, int source) {
  return Graph<T> {G.size()};
}

// put your "best" solution here
// this is the one we will use for performance testing
template <typename T>
Graph<T> singleSourceShortestPaths(const Graph<T>& G, int source) {
  return Graph<T> {G.size()}; 
}


template <typename T>
bool isSubgraph(const Graph<T>& H, const Graph<T>& G) {

  if (H.size() > G.size()) {
    return false;
  }
//iterate through all the nodes in h
//for each node in H we're going to iterate through each edge of that node
//if that edge does not exist in G, return false.
  // for (loop G graph) // no need to do that as you can just do if H.contains()
  // v for vertex!
  for (int v {}; v < H.size(); v++){ //loops through the whole of H
  //loops through neighbours(edges) at a vertex of H, once the 146 loop reaches i++ the index increases and 
  //looks into another vertex of H
    for (auto const& [neighbour, weight]: *(H.neighbours(v))){
      if (!G.isEdge(v, neighbour)){ //boolean that checks if edge exists in G or not, if it does, it continues, if not, it exits the loop
        return false;
        }
        if (G.getEdgeWeight(v, neighbour) != weight){ //v = vertex, neighbour = edge which ultimately equals the weight of the edge
          return false;
      }
    }
  }
      return true;
}

template <typename T>
bool isTreePlusIsolated(const Graph<T>& G, int root) {
  //BFS. If visited node > 1, cycle exists! return false.
  std::queue<int> graphQueue {}; //storing int number of vertices
  std::vector<bool> visited(G.size());
  graphQueue.push(root);
  visited.at(root) = true;
  while (!graphQueue.empty()) {
    int currentNodeBeingVisited = graphQueue.front();
    graphQueue.pop();

    for (auto const& [neighbour, weight]: *(G.neighbours(currentNodeBeingVisited))){
      if (not visited.at(neighbour)){
        visited.at(neighbour) = true;
        graphQueue.push(neighbour);
      }
      else {
        return false;
      }
    }
  }
      for (int i {}; i < G.size(); i++){ 
      //i is vertex you are checking
      //at the vertex if its not visited then check if it has neighbours
      if (!visited.at(i) && !(G.neighbours(i)) -> empty()){ //not visited neighbours?
        return false;
      }
    }
  return true;
}

template <typename T>
std::vector<T> pathLengthsFromRoot(const Graph<T>& tree, int root) { 
  std::vector<T> bestDistanceTo(tree.size(), infinity<T>());//makes the bestDistanceTo //size and each elements starting point
  std::queue<int> treeQueue {};
  std::vector<bool> visited(tree.size()); 
  //pushes the first element into the queue
  treeQueue.push(root);
  //marks the first element visited
  visited.at(root) = true;
  //make the root vertex 0 as the weight will be zero all the time
  bestDistanceTo.at(root) = T{};
  while (!treeQueue.empty()){ //as long as the queue isn't empty
  //(1st)returns reference to the first element of the queue
    int currentPositionInTree = treeQueue.front();
  //pops the first elemnt of the queue
    treeQueue.pop();
  // int prev = currentPositionInTree;
  //iterates through all the neighbours of the currentPositionInTree (in the queue)
  for (auto const& [neighbour, weight]: *(tree.neighbours(currentPositionInTree))){
    //if the neighbours of currentPositionInTree haven't been visited, 
    //push them into the queue and visit them (mark them as visited)
    if (not visited.at(neighbour)){ //if neighbour is not visited
    // std::cout<< "hi";
      visited.at(neighbour) = true; //visit the neighbour
      treeQueue.push(neighbour); //push the neighbour into the queue
      //the element I'm visiting + element I'm visiting FROM
      // bestDistanceTo.at(currentPosition)
      
    }
    bestDistanceTo.at(neighbour) = weight + bestDistanceTo.at(currentPositionInTree); //first iteration would be 1 + 0
  }
  }
  return bestDistanceTo;
}



template <typename T>
bool allEdgesRelaxed(const std::vector<T>& bestDistanceTo, const Graph<T>& G, 
                      int source) {
  
  if (bestDistanceTo.at(source) != T{}){
    return false;
  }

  for (int v {}; v < G.size(); v++){
    for (auto const& [neighbour, weight]: *(G.neighbours(v))){
      if (bestDistanceTo.at(neighbour) > bestDistanceTo.at(v) + G.getEdgeWeight(v, neighbour)) {
        return false;
        }
      }
    }
  return true;
}


#endif      // GRAPH_HPP_
