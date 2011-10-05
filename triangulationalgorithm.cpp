#include "triangulationalgorithm.h"

//returns true if vertex d is in the circumcircle of triangle abc
bool inCircle(Vector2f a, Vector2f b, Vector2f c, Vector2f d) {
    Matrix4f M;

    Vector2f *vectors[4] = {&a, &b, &c, &d};
    for (uint i = 0; i < 4; i++) {
        Vector2f &v = *vectors[i];
        M[i] = Vector4f(v[0], v[1], v[0]*v[0] + v[1]*v[1], 1);
    }

    return M.det() > 0;
}

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

