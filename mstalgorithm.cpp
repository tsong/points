#include "mstalgorithm.h"

#include <queue>

void MSTAlgorithm::reset() {
    this->vertices.clear();
}

void MSTAlgorithm::addVertex(Vector2f v) {
    this->vertices.push_back(v);
}

void MSTAlgorithm::moveVertex(uint i, Vector2f v) {
    this->vertices[i] = v;
}

void MSTAlgorithm::removeVertex(uint i) {
    this->vertices.erase(vertices.begin() + i);
}

void MSTAlgorithm::setVertices(const vector<Vector2f> &vertices) {
    this->vertices = vertices;
}

//calculates and returns the edges of a MST using Prim's Algorithm
list<Edge> MSTAlgorithm::getEdges() {
    uint n = vertices.size();
    list<Edge> edges;
    if (n <= 1) return edges;

    //parent[i] = parent vertex of i in the MST
    uint parent[n];
    for (uint i = 0; i < n; i++) parent[i] = 0;

    //visited[i] = true if vertex i has been put in the MST
    bool visited[n];
    for (uint i = 0; i < n; i++) visited[i] = false;

    //distance[i] = closest distance calculated for vertex i so far
    float distance[n];
    for (uint i = 0; i < n; i++) distance[i] = 0x3f3f3f3f;
    distance[0] = 0;

    //priority queue based on the calculated distance of each vertex
    priority_queue< uint, vector<uint>, MSTCompare > queue( MSTCompare((float*)distance, n) );
    for (uint i = 0; i < n; i++) queue.push(i);

    //visit each vertex in the order of increasing distance
    while (!queue.empty()) {
        uint i = queue.top();
        Vector2f v1 = vertices[i];
        visited[i] = true;
        edges.push_back(Edge(vertices[i], vertices[parent[i]]));

        for (uint j = 0; j < n; j++) {
            if (i != j && !visited[j]) {
                Vector2f v2 = vertices[j];

                //relax distance
                float dist = (v1-v2).magnitude();
                if (dist < distance[j]) {
                    parent[j] = i;
                    distance[j] = dist;
                }
            }
        }

        queue.pop();
    }

    return edges;
}

