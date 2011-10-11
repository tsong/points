#ifndef VORONOIALGORITHM_H
#define VORONOIALGORITHM_H

#include "pointsalgorithm.h"
#include "triangulationalgorithm.h"

class VoronoiAlgorithm : public PointsAlgorithm {
public:
    VoronoiAlgorithm();
    void addVertex(Vector2f v);
    void removeVertex(uint i);
    void moveVertex(uint i, Vector2f v);
    void setVertices(const vector<Vector2f> &vertices);
    list<Edge> getEdges();
    list<Vector2f> getDualVertices();
    list<Edge> getDualEdges();

protected:
    TriangulationAlgorithm triangulation;
};

#endif // VORONOIALGORITHM_H
