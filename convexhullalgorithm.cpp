#include "convexhullalgorithm.h"
#include "pointsutil.h"
#include <algorithm>
#include <QDebug>

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
    if (n == 2) {
        edges.push_back(Edge(vertices[0],vertices[1]));
        return edges;
    }

    //get vertex with minimum y-value (and x-value if there is a tie)
    Vector2f minVertex = vertices[0];
    for (int i = 1; i < n; i++) {
        Vector2f v = vertices[i];
        if (v[1] < minVertex[1] || (v[1] == minVertex[1] && v[0] < minVertex[0]))
            minVertex = v;
    }

    //sort the remaining vertices with respect to the minimum
    vector<Vector2f> sortedVertices = vertices;
    sort<vector<Vector2f>::iterator, ConvexHullCompare>(
            sortedVertices.begin(),
            sortedVertices.end(),
            ConvexHullCompare(minVertex));

    //stack contains the convex hull so far
    vector<uint> stack;
    stack.push_back(0);
    stack.push_back(1);
    stack.push_back(2);

    //try to add each vertex to the convex hull
    for (uint i = 3; i < n; i++) {
        uint a = *(stack.end()-2);
        uint b = *(stack.end()-1);

        //if we encounter a clockwise test, then pop the convex hull stack until a counter-clockwise test is reached
        while (pointLineTest(sortedVertices[a], sortedVertices[b], sortedVertices[i]) >= 0) {
            stack.pop_back();
            a = *(stack.end()-2);
            b = *(stack.end()-1);
        }
        stack.push_back(i);
    }

    //build and return the edges of the convex hull
    for (vector<uint>::iterator it = stack.begin(); it != stack.end()-1; it++) {
        Vector2f v1 = sortedVertices[(*it)];
        Vector2f v2 = sortedVertices[*(it+1)];
        edges.push_back(Edge(v1,v2));
    }
    Vector2f v1 = sortedVertices[*(stack.end()-1)];
    Vector2f v2 = sortedVertices[*(stack.begin())];
    edges.push_back(Edge(v1,v2));

    return edges;
}



