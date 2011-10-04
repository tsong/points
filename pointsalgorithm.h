#ifndef POINTSALGORITHM_H
#define POINTSALGORITHM_H

#include <list>
#include <vector>
#include "vector.h"

using namespace std;

typedef struct edge {
    const Vector2f *u;
    const Vector2f *v;

    edge(const Vector2f *ptr1, const Vector2f *ptr2) : u(ptr1), v(ptr2) {}
} Edge;

//Abstract class defining points algorithms that return an edge list
class PointsAlgorithm
{
public:

    virtual void addVertex(Vector2f v) = 0;
    virtual void setVertices(const vector<Vector2f> &vertices) = 0;
    virtual list<Edge> getEdges() = 0;

protected:
    PointsAlgorithm() {}
    ~PointsAlgorithm() {}
};

#endif // POINTSALGORITHM_H
