#include "triangulationalgorithm.h"
#include <QDebug>

//tests a point p and line ab using cross product test
//returns 1 if p is clockwise to ab
//returns -1 if p is counter-clockwise to ab
//returns 0 if p is colinear
int pointLineTest (Vector2f a, Vector2f b, Vector2f p) {
    Vector2f v1 = b - a;
    Vector2f v2 = p - a;
    Vector2f c = v1.cross(v2);

    if (c[0] < 0)
        return -1;
    else if (c[0] > 0)
        return 1;
    else
        return 0;
}

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

//returns true if vertex d is in triangle abc
bool inTriangle(Vector2f a, Vector2f b, Vector2f c, Vector2f d) {
    /*qDebug() << "Triangles";
    qDebug() << QString("(%1,%2)").arg(a[0]).arg(a[1]);
    qDebug() << QString("(%1,%2)").arg(b[0]).arg(b[1]);
    qDebug() << QString("(%1,%2)").arg(c[0]).arg(c[1]);
    qDebug() << "Point: " << QString("(%1,%2)").arg(d[0]).arg(d[1]);
    qDebug() << "TEST 1:" << pointLineTest(a,b,d) << -pointLineTest(a,c,d);
    qDebug() << "TEST 2:" << pointLineTest(b,c,d) << -pointLineTest(b,a,d);
    qDebug() << "TEST 3:" << pointLineTest(c,b,d) << -pointLineTest(c,a,d);*/

    return pointLineTest(a,b,d) == -pointLineTest(a,c,d)
           && pointLineTest(b,c,d) == -pointLineTest(b,a,d)
           && pointLineTest(c,b,d) == -pointLineTest(c,a,d);
}

//hashes two vertex indices for map lookup
unsigned long hash(uint i, uint j) {
    if (i > j) {
        uint tmp = i;
        i = j;
        j= tmp;
    }
    return (i << 32) | j;
}

void TriangulationAlgorithm::reset() {
    //clear all data
    vertices.clear();
    triangles.clear();
    adjVertices.clear();

    //add bounding triangle that will contain all other vertices
    vertices.push_back(Vector2f(0, MAX_TRIANGLE_Y));
    vertices.push_back(Vector2f(MIN_TRIANGLE_X, MIN_TRIANGLE_Y));
    vertices.push_back(Vector2f(MAX_TRIANGLE_X, MIN_TRIANGLE_Y));
    addTriangle(Triangle(0,1,2));
}

void TriangulationAlgorithm::addTriangle(Triangle t) {
    triangles.push_back(t);

    //add all edges to adjacent vertices map
    uint T[3] = {t.i, t.j, t.k};
    for (uint i = 0; i < 3; i++) {
        for (uint j = i; j < 3; j++) {
            unsigned long h = hash(T[i],T[j]);
            uint otherIndex = t.i + t.j + t.k - (T[i] + T[j]);    //adjacent vertex is the unused index

            //add pair to map if entry does not already exist
            if (adjVertices.find(h) == adjVertices.end()) {
                adjVertices[h] = pair<int,int>(-1,-1);
            }
            pair<int,int> verts = adjVertices[h];


            if (verts.first < 0)
                verts.first = otherIndex;
            else
                verts.second = otherIndex;

            adjVertices[h] = verts;
        }
    }
}

void TriangulationAlgorithm::removeTriangle(Triangle t) {
    //remove triangles from list
    for (list<Triangle>::iterator it = triangles.begin(); it != triangles.end(); it++) {
        if (t == *it) triangles.erase(it);
    }

    //remove entries from adjVertices map
    uint T[3] = {t.i, t.j, t.k};
    for (uint i = 0; i < 3; i++) {
        for (uint j = i; j < 3; j++) {
            unsigned long h = hash(T[i],T[j]);
            adjVertices.erase(h);
        }
    }
}

void TriangulationAlgorithm::flip(uint a, uint b) {
    pair<int,int> verts = adjVertices[hash(a,b)];

    //if edge ab is exterior facing, then we don't need to flip
    if (verts.first < 0 || verts.second < 0) return;

    //c = point to the right of edge ab
    //d = point to the left of edge ab
    uint c,d;
    if (pointLineTest(vertices[a], vertices[b], vertices[verts.first]) > 0) {
        c = verts.first;
        d = verts.second;
    } else {
        c = verts.second;
        d = verts.first;
    }

    Vector2f d1 = vertices[verts.first] - vertices[a];
    Vector2f d2 = vertices[verts.second] - vertices[a];

    if (inCircle(vertices[a],vertices[b],vertices[c],vertices[d])) {
        //flip ab to pd
        removeTriangle(Triangle(a,b,c));
        addTriangle(Triangle(c,a,d));
        addTriangle(Triangle(c,b,d));

        //test new edges that are formed
        flip(a,d);
        flip(b,d);
    }

}

TriangulationAlgorithm::TriangulationAlgorithm() {
    this->reset();
}

void TriangulationAlgorithm::addVertex(Vector2f v) {
    this->vertices.push_back(v);
    Triangle t;
    bool found = false;

    //find containing triangle
    for (list<Triangle>::iterator it = triangles.begin(); it != triangles.end(); it++) {
        t = *it;
        if (inTriangle(vertices[t.i], vertices[t.j], vertices[t.k], v)) {
            removeTriangle(t);    //delete this triangle
            found = true;
            break;
        }
    }

    if (!found) {
        qDebug() << "VERY BAD: VERTEX IS NOT IN ANY TRIANGLE";
    }

    //divide containing triangle into 3 triangles using v
    uint idx =  vertices.size()-1;
    Triangle t1(t.i, t.j, idx);
    Triangle t2(t.i, t.k, idx);
    Triangle t3(t.j, t.k, idx);
    addTriangle(t1);
    addTriangle(t2);
    addTriangle(t3);

    //test edges
    flip(t.i, t.j);
    flip(t.i, t.k);
    flip(t.j, t.k);
}

void TriangulationAlgorithm::setVertices(const vector<Vector2f> &vertices) {
    this->reset();
    for (uint i = 0; i < vertices.size(); i++) {
        addVertex(vertices[i]);
    }
}

list<Edge> TriangulationAlgorithm::getEdges() {
    list<Edge> edges;

    for (map< unsigned long, pair<int, int> >::iterator it = adjVertices.begin();
        it != adjVertices.end();
        it++)
    {
        unsigned long h = (*it).first;
        uint u = h >> 32;
        uint v = h && 0xFFFFFFFF;
        edges.push_back(Edge(vertices[u],vertices[v]));
    }

    return edges;
}

