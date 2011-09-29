#include "mstalgorithm.h"

#include <queue>

MSTAlgorithm *MSTAlgorithm::instance = 0;

MSTAlgorithm* MSTAlgorithm::getInstance() {
    if (!instance) {
        instance = new MSTAlgorithm();
    }

    return instance;
}

list<Edge> MSTAlgorithm::getEdges(const vector<Vector2f> &vertices) {
    uint n = vertices.size();
    list<Edge> edges;

    uint parent[n];
    for (uint i = 0; i < n; i++) parent[i] = 0;

    bool visited[n];
    for (uint i = 0; i < n; i++) visited[i] = false;

    float distance[n];
    for (uint i = 0; i < n; i++) distance[i] = 0x3f3f3f3f;
    distance[0] = 0;

    priority_queue< uint, vector<uint>, MSTCompare > queue( MSTCompare((float*)distance, n) );

    for (uint i = 0; i < n; i++) queue.push(i);
    while (!queue.empty()) {
        uint i = queue.top();
        Vector2f v1 = vertices[i];
        visited[i] = true;
        edges.push_back(Edge(&vertices[i], &vertices[parent[i]]));

        for (uint j = 0; j < n; j++) {
            if (i != j && !visited[j]) {
                Vector2f v2 = vertices[j];

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

