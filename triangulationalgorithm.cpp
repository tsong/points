#include "triangulationalgorithm.h"

TriangulationAlgorithm::TriangulationAlgorithm() {
}

void TriangulationAlgorithm::addVertex(Vector2f v) {
    this->vertices.push_back(v);
}

void TriangulationAlgorithm::setVertices(const vector<Vector2f> &vertices) {
    this->vertices = vertices;
}

list<Edge> TriangulationAlgorithm::getEdges() {

}

