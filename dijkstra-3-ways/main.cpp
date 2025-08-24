#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "graph.hpp"
#include "my_integer.hpp"

// First 9 test cases are lazy (int, MyInteger, double, respectively).

//tiny LAZY INT
TEST(LazyIntTinyEWDTest, singleSourceLazy) {
  Graph<int> G {"tinyEWD.txt"};
  Graph<int> shortestPath {singleSourceLazy(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)}; //root is now starting at 4, make a tree starting at 4
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}
//medium LAZY INT
TEST(LazyIntMediumEWDTest, singleSourceLazy) {
  Graph<int> G {"mediumEWD.txt"};
  Graph<int> shortestPath {singleSourceLazy(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)}; //root is now starting at 4, make a tree starting at 4
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}
//USA LAZY INT
TEST(LazyIntUSAGraphTest, singleSourceLazy) {
  Graph<int> G {"USA-road-d.NY.gr"};
  Graph<int> shortestPath {singleSourceLazy(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)}; //root is now starting at 4, make a tree starting at 4
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}

//tinyEWD LAZY MyInteger
TEST(LazyTinyEWDTestMyInteger, singleSourceLazy) {
  Graph<MyInteger> G {"tinyEWD.txt"};
  Graph<MyInteger> shortestPath {singleSourceIndex(G, 0)};
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)};
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}

//mediumEWD LAZY MyInteger
TEST(LazyMediumEWDTestMyInteger, singleSourceLazy) {
  Graph<MyInteger> G {"mediumEWD.txt"};
  Graph<MyInteger> shortestPath {singleSourceIndex(G, 0)};
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)};
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}

//USA LAZY MyInteger
TEST(LazyMyIntegerUSATest, singleSourceLazy) {
  Graph<MyInteger> G {"USA-road-d.NY.gr"};
  Graph<MyInteger> shortestPath {singleSourceIndex(G, 0)};
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)};
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}

//tiny LAZY double
TEST(LazyDoubleTinyEWDTest, singleSourceLazy) {
  Graph<double> G {"tinyEWD.txt"};
  Graph<double> shortestPath {singleSourceLazy(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)}; //root is now starting at 4, make a tree starting at 4
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}
//medium LAZY double
TEST(LazyDoubleMediumEWDTest, singleSourceLazy) {
  Graph<double> G {"mediumEWD.txt"};
  Graph<double> shortestPath {singleSourceLazy(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)}; //root is now starting at 4, make a tree starting at 4
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}
//USA LAZY double
TEST(LazyDoubleUSAGraphTest, singleSourceLazy) {
  Graph<double> G {"USA-road-d.NY.gr"};
  Graph<double> shortestPath {singleSourceLazy(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)}; //root is now starting at 4, make a tree starting at 4
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}

//tiny INDEX
TEST(IndexPQTinyTest, singleSourceIndexInt) {
  Graph<int> G {"tinyEWD.txt"};
  Graph<int> shortestPath {singleSourceIndex(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)};
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}
//medium index int
TEST(IndexPQMediumTest, singleSourceIndexInt) {
  Graph<int> G {"mediumEWD.txt"};
  Graph<int> shortestPath {singleSourceIndex(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)};
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}
//usa index int
TEST(IndexPQUSATest, singleSourceIndexInt) {
  Graph<int> G {"USA-road-d.NY.gr"};
  Graph<int> shortestPath {singleSourceIndex(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)};
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}
//tiny index MyInteger
TEST(IndexPQMyIntegerTinyTest, singleSourceIndex) {
  Graph<MyInteger> G {"tinyEWD.txt"};
  Graph<MyInteger> shortestPath {singleSourceIndex(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)};
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}
//medium index MyInteger
TEST(IndexPQMyIntegerMediumTestInt, singleSourceIndex) {
  Graph<MyInteger> G {"mediumEWD.txt"};
  Graph<MyInteger> shortestPath {singleSourceIndex(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)};
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}
//usa index MyInteger
TEST(IndexPQMyIntegerUSATest, singleSourceIndex) {
  Graph<MyInteger> G {"USA-road-d.NY.gr"};
  Graph<MyInteger> shortestPath {singleSourceIndex(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)};
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}

//tiny INDEX double
TEST(IndexDoublePQTinyTest, singleSourceIndexInt) {
  Graph<double> G {"tinyEWD.txt"};
  Graph<double> shortestPath {singleSourceIndex(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)};
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}
//medium index double
TEST(IndexDoublePQMediumTest, singleSourceIndexInt) {
  Graph<double> G {"mediumEWD.txt"};
  Graph<double> shortestPath {singleSourceIndex(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)};
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}
//usa index double
TEST(IndexDoublePQUSATest, singleSourceIndexInt) {
  Graph<double> G {"USA-road-d.NY.gr"};
  Graph<double> shortestPath {singleSourceIndex(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)};
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}

// Example showing how to use MyInteger class to get performance data
TEST(DijkstraTest, distanceFrom0LazyMyInteger) {
  Graph<MyInteger> G {"tinyEWD.txt"};

  // set all counts to 0 before running shortest path algorithm
  MyInteger::clearCounts();
  std::vector<MyInteger> result = singleSourceLazyDistance<MyInteger>(G, 0);
  // see how many operations on MyInteger the algorithm made
  MyInteger::printCounts();
  // EXPECT_EQ(result[0], MyInteger {0});
  // EXPECT_EQ(result[1], MyInteger {105});
  // EXPECT_EQ(result[2], MyInteger {26});
  // EXPECT_EQ(result[3], MyInteger {99});
  // EXPECT_EQ(result[4], MyInteger {38});
  // EXPECT_EQ(result[5], MyInteger {73});
  // EXPECT_EQ(result[6], MyInteger {151});
  // EXPECT_EQ(result[7], MyInteger {60});
}

// Example Test of shortest path algorithm from tutorial
TEST(IndexIntTinyDijkstraTest, distanceFrom0Index) {
  Graph<int> G {"tinyEWD.txt"};
  Graph<int> shortestPath {singleSourceIndex(G, 0)};
}
TEST(IndexIntMediumDijkstraTest, distanceFrom0Index) {
  Graph<int> G {"mediumEWD.txt"};
  Graph<int> shortestPath {singleSourceIndex(G, 0)};
}
TEST(IndexIntUSADijkstraTest, distanceFrom0Index) {
  Graph<double> G {"USA-road-d.NY.gr"};
  Graph<double> shortestPath {singleSourceIndex(G, 0)};
}

// Example showing how to use MyInteger class to get performance data
TEST(IndexMyIntegerTinyDijkstraTest, distanceFrom0Index) {
  Graph<MyInteger> G {"tinyEWD.txt"};
  // set all counts to 0 before running shortest path algorithm
  MyInteger::clearCounts();
  Graph<MyInteger> shortestPath {singleSourceIndex(G, 0)};
  MyInteger::printCounts();
}

TEST(IndexMyIntegerMediumDijkstraTest, distanceFrom0Index) {
  Graph<MyInteger> G {"mediumEWD.txt"};
  // set all counts to 0 before running shortest path algorithm
  MyInteger::clearCounts();
  Graph<MyInteger> shortestPath {singleSourceIndex(G, 0)};
  MyInteger::printCounts();
}

TEST(IndexMyIntegerUSADijkstraTest, distanceFrom0Index) {
  Graph<MyInteger> G {"USA-road-d.NY.gr"};
  // set all counts to 0 before running shortest path algorithm
  MyInteger::clearCounts();
  Graph<MyInteger> shortestPath {singleSourceIndex(G, 0)};
  MyInteger::printCounts();
}

TEST(IndexDoubleTinyDijkstraTest, distanceFrom0Index) {
  Graph<double> G {"tinyEWD.txt"};
  Graph<double> shortestPath {singleSourceIndex(G, 0)};
}
TEST(IndexDoubleMediumDijkstraTest, distanceFrom0Index) {
  Graph<double> G {"mediumEWD.txt"};
  Graph<double> shortestPath {singleSourceIndex(G, 0)};
}
TEST(IndexDoubleUSADijkstraTest, distanceFrom0Index) {
  Graph<double> G {"USA-road-d.NY.gr"};
  Graph<double> shortestPath {singleSourceIndex(G, 0)};
}

TEST(LazyIntTinyDijkstraTest, distanceFrom0Lazy) {
  Graph<int> G {"tinyEWD.txt"};
  Graph<int> shortestPath {singleSourceLazy(G, 0)};
}

TEST(LazyIntMediumDijkstraTest, distanceFrom0Lazy) {
  Graph<int> G {"mediumEWD.txt"};
  Graph<int> shortestPath {singleSourceLazy(G, 0)};
}

TEST(LazyIntUSADijkstraTest, distanceFrom0Lazy) {
  Graph<int> G {"USA-road-d.NY.gr"};
  Graph<int> shortestPath {singleSourceLazy(G, 0)};
}

TEST(LazyMyIntegerTinyDijkstraTest, distanceFrom0Lazy) {
  Graph<MyInteger> G {"tinyEWD.txt"};
  // set all counts to 0 before running shortest path algorithm
  MyInteger::clearCounts();
  Graph<MyInteger> shortestPath {singleSourceLazy(G, 0)};
  MyInteger::printCounts();
}

TEST(LazyMyIntegerMediumDijkstraTest, distanceFrom0Lazy) {
  Graph<MyInteger> G {"mediumEWD.txt"};
  // set all counts to 0 before running shortest path algorithm
  MyInteger::clearCounts();
  Graph<MyInteger> shortestPath {singleSourceLazy(G, 0)};
  MyInteger::printCounts();
}

TEST(LazyMyIntegerUSADijkstraTest, distanceFrom0Lazy) {
  Graph<MyInteger> G {"USA-road-d.NY.gr"};
  // set all counts to 0 before running shortest path algorithm
  MyInteger::clearCounts();
  Graph<MyInteger> shortestPath {singleSourceLazy(G, 0)};
  MyInteger::printCounts();
}

TEST(LazyDoubleTinyDijkstraTest, distanceFrom0Lazy) {
  Graph<double> G {"tinyEWD.txt"};
  Graph<double> shortestPath {singleSourceLazy(G, 0)};
}

TEST(LazyDoubleMediumDijkstraTest, distanceFrom0Lazy) {
  Graph<double> G {"mediumEWD.txt"};
  Graph<double> shortestPath {singleSourceLazy(G, 0)};
}

TEST(LazyDoubleUSADijkstraTest, distanceFrom0Lazy) {
  Graph<double> G {"USA-road-d.NY.gr"};
  Graph<double> shortestPath {singleSourceLazy(G, 0)};
}



// You can generate some random graphs to help in your testing
// The graph has N vertices and p is the probability there is an
// edge between any two vertices. 
// You can vary seed to get different graphs
Graph<int> randomGraph(int N, unsigned seed, double p = 0.5) {
  std::mt19937 mt {seed};
  // set up random number generator that is 1 with probability p and
  // 0 with probability 1-p
  std::binomial_distribution<int> heads {1, p};
  // Set the minimum and maximum edge weight here
  const int minWeight {1};
  const int maxWeight {10};
  std::uniform_int_distribution<int> weight {minWeight, maxWeight};
  Graph<int> G {N};
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (heads(mt)) {
        // add edge between i and j with random weight 
        // between minWeight and maxWeight
        G.addEdge(i, j, weight(mt));
      }
    }
  }
  return G;
}

Graph<double> randomGraphDouble(int N, unsigned seed, double p = 0.5) {
  std::mt19937 mt {seed};
  // set up random number generator that is 1 with probability p and
  // 0 with probability 1-p
  std::binomial_distribution<int> heads {1, p};
  // Set the minimum and maximum edge weight here
  // int N = {G.size()};
  // Double dN = new Double(N); 
  const int minWeight {1};
  const int maxWeight {10};
  std::uniform_int_distribution<int> weight {minWeight, maxWeight};
  Graph<double> G (N);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (heads(mt)) {
        // add edge between i and j with random weight 
        // between minWeight and maxWeight
        G.addEdge(i, j, weight(mt));
      }
    }
  }
  return G;
}

TEST(LazyIntRandomGraphDijkstraTest, distanceFrom0Lazy) {
  Graph<int> G {randomGraph(500, 2353, 0.65)};
  Graph<int> shortestPath {singleSourceLazy(G, 0)};
}
TEST(LazyDoubleRandomGraphDijkstraTest, distanceFrom0Lazy) {
  Graph<double> G{randomGraphDouble(500, 2353, 0.65)};
  Graph<double> shortestPath {singleSourceLazy(G, 0)};
}

TEST(IndexDoubleRandomGraphTest, singleSourceIndex) {
  Graph<double> G{randomGraphDouble(500, 2353, 0.65)};
  Graph<double> shortestPath {singleSourceIndex(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)};
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}

TEST(IndexIntRandomGraphTest, singleSourceIndex) {
  Graph<int> G{randomGraph(500, 2353, 0.65)};
  Graph<int> shortestPath {singleSourceIndex(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)};
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}

TEST(LazyIntRandomGraphTest, singleSourceLazy) {
  Graph<int> G{randomGraph(500, 2353, 0.65)};
  Graph<int> shortestPath {singleSourceLazy(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)}; //root is now starting at 4, make a tree starting at 4
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}

TEST(LazyDoubleRandomGraphTest, singleSourceLazy) {
  Graph<double> G{randomGraphDouble(500, 2353, 0.65)};
  Graph<double> shortestPath {singleSourceLazy(G, 0)}; //calls method in {} to call the shortest graph.
  EXPECT_TRUE(isSubgraph(shortestPath, G)); 
  EXPECT_TRUE(isTreePlusIsolated(shortestPath, 0));
  auto bestDistanceTo {pathLengthsFromRoot(shortestPath, 0)}; //root is now starting at 4, make a tree starting at 4
  EXPECT_TRUE(allEdgesRelaxed(bestDistanceTo, G, 0));
}



int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  // Graph<int> G {"tinyEWD.txt"};
  // std::cout << G << std::endl;
  // Graph<int> shortestPath {singleSourceLazy(G, 0)};
  // Graph<int> shortestPath {singleSourceIndex(G, 0)}; 
  // std::cout << shortestPath << std::endl;
  // Graph<int> shortestPath {"mediumEWD.txt"};
  // std::cout << shortestPath << std::endl;
  // "mediumEWD.txt"
  return RUN_ALL_TESTS();
}
