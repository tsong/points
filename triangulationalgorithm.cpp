#include "triangulationalgorithm.h"
#include <QDebug>

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
        for (uint j = i+1; j < 3; j++) {
            uint h = hash(T[i],T[j]);
            uint other = t.i + t.j + t.k - (T[i] + T[j]);    //adjacent vertex is the unused index

            //add pair to map if entry does not already exist
            if (adjVertices.find(h) == adjVertices.end()) {
                adjVertices[h] = pair<int,int>(-1,-1);
            }
            pair<int,int> verts = adjVertices[h];

            if (verts.first < 0)
                verts.first = other;
            else
                verts.second = other;

            adjVertices[h] = verts;
        }
    }
}

void TriangulationAlgorithm::removeTriangle(Triangle t) {
    //remove triangles from list
    for (list<Triangle>::iterator it = triangles.begin(); it != triangles.end(); it++) {
        if (t == *it) {
            triangles.erase(it);
            break;
        }
    }

    //remove entries from adjVertices map
    uint T[3] = {t.i, t.j, t.k};
    for (uint i = 0; i < 3; i++) {
        for (uint j = i+1; j < 3; j++) {
            uint h = hash(T[i],T[j]);
            uint other = t.i + t.j + t.k - (T[i] + T[j]);    //adjacent vertex is the unused index

            //clean up adjacency vertex map
            pair<int,int> verts = adjVertices[h];
            if (verts.first < 0 || verts.second < 0) {
                adjVertices.erase(h);
            } else if (verts.first == (int)other) {
                verts.first = -1;
                adjVertices[h] = verts;
            } else if (verts.second == (int)other) {
                verts.second = -1;
                adjVertices[h] = verts;
            }

        }
    }
}

void TriangulationAlgorithm::flip(uint a, uint b) {
    //get the two adjacent vertices of edge ab
    pair<int,int> verts = adjVertices[hash(a,b)];

    //if edge ab is exterior facing, then we don't need to flip
    if (verts.first < 0 || verts.second < 0) return;

    //c = point to the right of edge ab
    //d = point to the left of edge ab
    uint c,d;
    if (pointLineTest(vertices[a], vertices[b], vertices[verts.first]) < 0) {
        c = verts.first;
        d = verts.second;
    } else {
        c = verts.second;
        d = verts.first;
    }

    if (inCircle(vertices[a],vertices[b],vertices[c],vertices[d])) {
        //flip ab to cd if current triangulation violates circle test
        removeTriangle(Triangle(a,b,c));
        removeTriangle(Triangle(a,b,d));
        addTriangle(Triangle(c,a,d));
        addTriangle(Triangle(c,b,d));

        //test new edges that are formed
        flip(a,d);
        flip(b,d);
        flip(a,c);
        flip(b,c);
    }

}

TriangulationAlgorithm::TriangulationAlgorithm() {
    this->reset();
}

void TriangulationAlgorithm::moveVertex(uint i, Vector2f v) {
    //remove bounding vertices
    vector<Vector2f>::iterator start = vertices.begin();
    vertices.erase(start,start+3);

    //move and reapply vertices
    vertices[i] = v;
    vector<Vector2f> tmp = this->vertices;
    setVertices(tmp);
}

void TriangulationAlgorithm::removeVertex(uint i) {
    //remove bounding vertices
    vector<Vector2f>::iterator start = vertices.begin();
    vertices.erase(start,start+3);

    //remove and reapply vertices
    this->vertices.erase(start + i);
    vector<Vector2f> tmp = this->vertices;
    setVertices(tmp);
}

void TriangulationAlgorithm::addVertex(Vector2f v) {
    this->vertices.push_back(v);
    Triangle t;
    bool found = false;

    //find containing triangle
    for (list<Triangle>::iterator it = triangles.begin(); it != triangles.end(); it++) {
        t = *it;
        if (inTriangle(vertices[t.i], vertices[t.j], vertices[t.k], v)) {
            found = true;
            break;
        }
    }

    if (!found) {
        qDebug() << "VERY BAD: VERTEX IS NOT IN ANY TRIANGLE";
    }

    //divide containing triangle into 3 triangles using v
    removeTriangle(t);    //delete this triangle
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

    //all the edges of the triangulation are stored in our map
    for (map< uint, pair<int, int> >::iterator it = adjVertices.begin();
        it != adjVertices.end();
        it++)
    {
        //unhash to get edge uv
        uint h = (*it).first;
        uint u,v;
        unhash(h,u,v);

        //don't add bounding triangle edges
        if (u >= 3 && v >= 3)
            edges.push_back(Edge(vertices[u],vertices[v]));
    }

    return edges;
}

