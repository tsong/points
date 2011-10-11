#ifndef POINTSALGORITHM_H
#define POINTSALGORITHM_H

#include <list>
#include <vector>
#include "vector.h"

using namespace std;

//represents an edge between point u and point v
typedef struct Edge {
    Vector2f u;
    Vector2f v;

    Edge(const Vector2f a, const Vector2f b) : u(a), v(b) {}
} Edge;

//Abstract class defining points algorithms that return edges and vertices
class PointsAlgorithm
{
public:
    virtual void reset() = 0;
    virtual void addVertex(Vector2f v) = 0;
    virtual void removeVertex(uint i) = 0;
    virtual void moveVertex(uint i, Vector2f v) = 0;
    virtual void setVertices(const vector<Vector2f> &vertices) = 0;
    virtual list<Edge> getEdges() = 0;
    virtual list<Vector2f> getDualVertices() = 0;
    virtual list<Edge> getDualEdges() = 0;

protected:
    PointsAlgorithm() {}
    ~PointsAlgorithm() {}
};

#endif // POINTSALGORITHM_H
