#include "convexhullalgorithm.h"

ConvexHullAlgorithm *ConvexHullAlgorithm::instance = 0;

ConvexHullAlgorithm* ConvexHullAlgorithm::getInstance() {
    if (!instance)
        instance = new ConvexHullAlgorithm();

    return instance;
}

list<Edge> ConvexHullAlgorithm::getEdges(const vector<Vector2f> &vertices) {
    int n = vertices.size();
    list<Edge> edges;
    if (n <= 1) return edges;

    /*
    //get vertex with minimum y-value (and x-value if there is a tie)
    Vector2f minVertex = vertices[0];
    for (int i = 1; i < n; i++) {
        Vector2f v = vertices[i];
        if (v[1] < minVertex[1] || (v[1] == minVertex[1] && v[0] < minVertex[0]))
            minVertex = v;
    }

    //sort the vertices
    list<Vector2f&> sortedVertices;
    for (int i = 0; i < n; i++)
        if (vertices[i] != minVertex)
            sortedVertices.push_back(vertices[i]);
    sort<list<Vector2f&>::iterator, ConvexHullCompare>(
            sortedVertices.begin(),
            sortedVertices.end(),
            ConvexHullCompare(minVertex));
    */

    return edges;
}


