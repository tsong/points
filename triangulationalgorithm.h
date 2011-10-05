#ifndef TRIANGULATIONALGORITHM_H
#define TRIANGULATIONALGORITHM_H

#include "pointsalgorithm.h"
#include "matrix.h"

#include <map>
#include <set>

//coordinates of bounding triangle
#define MIN_TRIANGLE_X -1000000
#define MAX_TRIANGLE_X  1000000
#define MIN_TRIANGLE_Y -1000000
#define MAX_TRIANGLE_Y  1000000

//represents a triangle using the ith, jth, and kth vertices
typedef struct Triangle {
    uint i;
    uint j;
    uint k;

    Triangle() : i(0), j(0), k(0) {}

    Triangle(uint a, uint b, uint c) {
        i = a;
        j = b;
        k = c;
    }

    bool operator==(Triangle &t) {
        set<uint> indices;
        indices.insert(t.i);
        indices.insert(t.j);
        indices.insert(t.k);

        set<uint>::iterator fail = indices.end();
        return indices.find(i) != fail && indices.find(j) != fail && indices.find(k) != fail;
    }
} Triangle;


class TriangulationAlgorithm : public PointsAlgorithm {
public:
    TriangulationAlgorithm();
    void addVertex(Vector2f v);
    void setVertices(const vector<Vector2f> &vertices);
    list<Edge> getEdges();
protected:
    //clears all vertices and adds boudning triangle
    void reset();

    //add triangle to triangulation and update adjacent vertices map
    void addTriangle(Triangle t);

    //remove a triangle from the list
    void removeTriangle(Triangle t);

    //flip edge ab of trianble abc if needed
    void flip(uint a, uint b);

protected:
    vector<Vector2f> vertices;
    list<Triangle> triangles;

    //Given points u,v, this maps hash(u,v) to (w,x)
    //such that uvw and uvx are triangles in the triangulation.
    //It may be possible that uv is an external edge, in which
    //case only one of (w,x) is a positive index.
    map< unsigned long, pair<int, int> > adjVertices;
};

#endif // TRIANGULATIONALGORITHM_H
