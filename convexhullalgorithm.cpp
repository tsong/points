#include "convexhullalgorithm.h"
#include <algorithm>

void ConvexHullAlgorithm::reset() {
    this->vertices.clear();
}

void ConvexHullAlgorithm::addVertex(Vector2f v) {
    this->vertices.push_back(v);
}

void ConvexHullAlgorithm::removeVertex(uint i) {
    this->vertices.erase(vertices.begin() + i);
}

void ConvexHullAlgorithm::moveVertex(uint i, Vector2f v) {
    this->vertices[i] = v;
}

void ConvexHullAlgorithm::setVertices(const vector<Vector2f> &vertices) {
    this->vertices = vertices;
}


//returns the edges of the convex hull using the Graham Scan algorithm
list<Edge> ConvexHullAlgorithm::getEdges() {
    int n = vertices.size();
    list<Edge> edges;
    if (n <= 1) return edges;

    //get vertex with minimum y-value (and x-value if there is a tie)
    Vector2f minVertex = vertices[0];
    for (int i = 1; i < n; i++) {
        Vector2f v = vertices[i];
        if (v[1] < minVertex[1] || (v[1] == minVertex[1] && v[0] < minVertex[0]))
            minVertex = v;
    }

    //sort the remaining vertices with respect to the minimum
    /*vector<Vector2f> sortedVertices(n);
    for (int i = 0; i < n; i++)
        if (vertices[i] != minVertex)
            sortedVertices.push_back(vertices[i]);*/

    vector<Vector2f> sortedVertices = vertices;

    sort<vector<Vector2f>::iterator, ConvexHullCompare>(
            sortedVertices.begin(),
            sortedVertices.end(),
            ConvexHullCompare(minVertex));

    uint mid = 1;
    for (uint i = 2; i < n; i++) {

    }

    return edges;
}



