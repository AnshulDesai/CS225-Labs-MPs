/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {
    vector<Vertex> boonk = g_.getVertices();
    for (Vertex vertex : boonk) {
      flow_.insertVertex(vertex);
      residual_.insertVertex(vertex);
    }
    vector<Edge> gang = g_.getEdges();
    for (Edge edge : gang) {
      flow_.insertEdge(edge.source, edge.dest);
      residual_.insertEdge(edge.dest, edge.source);
      residual_.insertEdge(edge.source, edge.dest);
      residual_.setEdgeWeight(edge.source, edge.dest, edge.getWeight());
      residual_.setEdgeWeight(edge.dest, edge.source, 0);
      flow_.setEdgeWeight(edge.source, edge.dest, 0);
    }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   * @@params: visited -- A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @@params: path   -- The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  int cap = residual_.getEdgeWeight(path[0], path[1]);
  for (unsigned i = 1; i < path.size() - 1; i++) {
    if (cap > residual_.getEdgeWeight(path[i], path[i + 1])) {
      cap = residual_.getEdgeWeight(path[i], path[i + 1]);
    }
  }
  return cap;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @@outputs: The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  vector<Vertex> lol;
  while (findAugmentingPath(source_, sink_, lol)) {
    int check = pathCapacity(lol);
    for (unsigned x = 1; x < lol.size(); x++) {
      if (flow_.edgeExists(lol[x - 1], lol[x]) == false) {
        flow_.setEdgeWeight(lol[x], lol[x - 1], flow_.getEdgeWeight(lol[x], lol[x - 1]) - check);
      }
      else {
        flow_.setEdgeWeight(lol[x - 1], lol[x], flow_.getEdgeWeight(lol[x - 1], lol[x]) + check);
      }
      residual_.setEdgeWeight(lol[x - 1], lol[x], residual_.getEdgeWeight(lol[x - 1], lol[x]) - check);
      residual_.setEdgeWeight(lol[x], lol[x - 1], residual_.getEdgeWeight(lol[x], lol[x - 1]) + check);
    }
  }
  int betski = 0;
  vector<Edge> yeet = flow_.getEdges();
  for (Edge edge : yeet) {
    if (edge.source == source_) {
      betski += edge.getWeight();
    }
  }
  maxFlow_ = betski;
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
