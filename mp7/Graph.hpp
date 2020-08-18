#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>
using namespace std;

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  return adjList[v.key()].size();
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  pair<string, V &> vert (key, v);
  vertexMap.insert(vert);
  list<edgeListIter> gang;
  pair<string, list<edgeListIter>> boonk (key, gang);
  adjList.insert(boonk);
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  list<edgeListIter> boonk = adjList.at(key);
  for (auto edgecheck : boonk) {
    removeEdge(edgecheck);
  }
  vertexMap.erase(key);
  adjList.erase(key);
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  edgeList.push_front(e);
  adjList[v1.key()].push_front(edgeList.begin());
  adjList[v2.key()].push_front(edgeList.begin());
  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2
  for (auto edgecheck : edgeList) {
    if (edgecheck -> get().directed()) {
      if (edgecheck -> get().source().key() == key1 && edgecheck -> get().dest().key() == key2) {
        edgeList.erase(edgecheck);
        adjList.at(key1).remove(edgecheck);
        adjList.at(key2).remove(edgecheck);
        break;
      }
    }
    else {
      if (edgecheck -> get().source().key() == key2 || edgecheck -> get().dest().key() == key1) {
        edgeList.erase(edgecheck);
        adjList.at(key1).remove(edgecheck);
        adjList.at(key2).remove(edgecheck);
        break;
      }
    }
  }
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  string key1 = it -> get().source().key();
  string key2 = it -> get().dest().key();
  removeEdge(key1, key2);
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  list<edgeListIter> boonk = adjList.at(key);
  for (auto edgecheck : boonk) {
    edges.push_back(*edgecheck);
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  list<edgeListIter> boonk;
  if (adjList.at(key1).size() < adjList.at(key2).size()) {
    list<edgeListIter> yeet = adjList.at(key1);
    boonk = yeet;
  }
  else {
    list<edgeListIter> yeet = adjList.at(key2);
    boonk = yeet;
  }
  for (auto yikes : boonk) {
    if (yikes -> get().source().key() == key1 && yikes -> get().dest().key() == key2) {
      return true;
    }
  }
  return false;
}
