#ifndef TRIANGULATIONALGORITHM_H
#define TRIANGULATIONALGORITHM_H

#include "pointsalgorithm.h"

class TriangulationAlgorithm : public PointsAlgorithm {
public:
    TriangulationAlgorithm();
    void addVertex(Vector2f v);
    void setVertices(const vector<Vector2f> &vertices);
    list<Edge> getEdges();
protected:
    vector<Vector2f> vertices;
};

#endif // TRIANGULATIONALGORITHM_H
