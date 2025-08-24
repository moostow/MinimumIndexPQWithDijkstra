// https://stackoverflow.com/questions/69909851/how-to-use-it-empty-in-an-iterator
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
#include <stdexcept>
#include "my_integer.hpp"

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
int Graph<T>::size() const { //returns the number of vertices.
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
    return adjList.at(i).contains(j); //i would be the outer loop, and j be the inner loop
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

// The isSubgraph function checks if H is a subraph of G(the original graph)
template <typename T>
bool isSubgraph(const Graph<T>& H, const Graph<T>& G) {

  if (H.size() > G.size()) {
    return false;
  }
//iterate through all the nodes in h
//for each vertex in H we're going to iterate through each of its edges that meets their neighbours
//if that edge does not exist in G, return false.
  for (int v {}; v < H.size(); v++){ //loops through the whole of H
  //loops through neighbours(edges) at a vertex of H
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
  //BFS. If visited already, cycle exists! return false.
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
T infinity() {
  if (std::numeric_limits<T>::has_infinity) {
    return std::numeric_limits<T>::infinity();
  } else if constexpr (std::is_same_v<T, MyInteger>) {        // Check if T == MyInteger
    return MyInteger {std::numeric_limits<int>::max()};
  } else {
    return std::numeric_limits<T>::max();
  }
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
  bestDistanceTo.at(root) = T{};
  while (!treeQueue.empty()){ //as long as the queue isn't empty
    int currentPositionInTree = treeQueue.front();
  //pops the first elemnt of the queue
    treeQueue.pop();
  // int prev = currentPositionInTree;
  //iterates through all the neighbours of the currentPositionInTree (in the queue)
  for (auto const& [neighbour, weight]: *(tree.neighbours(currentPositionInTree))){
    //if the neighbours of currentPositionInTree haven't been visited, 
    //push them into the queue and visit them (mark them as visited)
    if (not visited.at(neighbour)){ //if neighbour is not visited
      visited.at(neighbour) = true; //visit the neighbour
      treeQueue.push(neighbour); //push the neighbour into the queue
      //the element I'm visiting + element I'm visiting FROM
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
