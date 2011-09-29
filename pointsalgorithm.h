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

    virtual list<Edge> getEdges(const vector<Vector2f> &vertices) = 0;

protected:
    PointsAlgorithm() {}
    ~PointsAlgorithm() {}
};

#endif // POINTSALGORITHM_H