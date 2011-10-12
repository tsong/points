#ifndef TRIANGULATIONALGORITHM_H
#define TRIANGULATIONALGORITHM_H

#include "pointsalgorithm.h"
#include "matrix.h"

#include <map>
#include <set>

#include <QDebug>

//coordinates of bounding triangle
#define MIN_TRIANGLE_X -1000000
#define MAX_TRIANGLE_X  1000000
#define MIN_TRIANGLE_Y -1000000
#define MAX_TRIANGLE_Y  1000000

//utility functions
uint hash(uint,uint);
void unhash(uint,uint&,uint&);
bool inTriangle(Vector2f, Vector2f, Vector2f, Vector2f);
int pointLineTest (Vector2f, Vector2f, Vector2f);

class VoronoiAlgorithm;

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

    //comparison that treats permutation of the vertices of the triangle as the same
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
    void reset();
    void addVertex(Vector2f v);
    void moveVertex(uint i, Vector2f v);
    void removeVertex(uint i);
    void setVertices(const vector<Vector2f> &vertices);
    list<Edge> getEdges();
    list<Vector2f> getDualVertices() { return list<Vector2f>(); }
    list<Edge> getDualEdges() { return list<Edge>(); }

    friend class VoronoiAlgorithm;

protected:
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
    map< uint, pair<int, int> > adjVertices;
};

#endif // TRIANGULATIONALGORITHM_H
