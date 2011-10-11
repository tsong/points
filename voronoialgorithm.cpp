#include "voronoialgorithm.h"

#define INFINITE_SCALAR 1E9

#include "glutils.h"
#include <set>

//returns the circumcenter of triangle abc using line intersections
Vector2f circumcenter(Vector2f a, Vector2f b, Vector2f c) {
    Vector2f mid1 = (a+b)/2;
    Vector2f mid2 = (a+c)/2;

    double slope1 = -(a[0]-b[0])/(a[1]-b[1]);
    double slope2 = -(a[0]-c[0])/(a[1]-c[1]);

    double origin1 = mid1[1] - slope1*mid1[0];
    double origin2 = mid2[1] - slope2*mid2[0];

    Vector2f center;
    center[0] = (origin2 - origin1) / (slope1 - slope2);
    center[1] = slope2*center[0] + origin2;
    return center;
}


VoronoiAlgorithm::VoronoiAlgorithm() {

}

void VoronoiAlgorithm::addVertex(Vector2f v) {
    triangulation.addVertex(v);
}

void VoronoiAlgorithm::removeVertex(uint i) {
    triangulation.removeVertex(i);
}

void VoronoiAlgorithm::moveVertex(uint i, Vector2f v) {
    triangulation.moveVertex(i,v);
}

void VoronoiAlgorithm::setVertices(const vector<Vector2f> &vertices) {
    triangulation.setVertices(vertices);
}

list<Edge> VoronoiAlgorithm::getEdges() {
    return triangulation.getEdges();
}

list<Vector2f> VoronoiAlgorithm::getDualVertices() {
    list<Triangle> triangles = triangulation.triangles;
    vector<Vector2f> vertices = triangulation.vertices;
    list<Vector2f> dualVertices;

    for (list<Triangle>::iterator it = triangles.begin(); it != triangles.end(); it++) {
        Triangle t = *it;

        //add the circumcenter of triangles that do not include the bounding vertices
        if (t.i >= 3 && t.j >= 3 && t.k >= 3) {
            //qDebug() << t.i << t.j << t.k;
            dualVertices.push_back(circumcenter(vertices[t.i], vertices[t.j], vertices[t.k]));
        }
    }

    return dualVertices;
}

list<Edge> VoronoiAlgorithm::getDualEdges() {
    list<Edge> edges;

    vector<Vector2f> vertices = triangulation.vertices;
    /*list<Triangle> triangles = triangulation.triangles;
    for (list<Triangle>::iterator it1 = triangles.begin(); it1 != triangles.end(); it1++) {
        for (list<Triangle>::iterator it2 = triangles.begin(); it2 != triangles.end(); it2++) {
            Triangle t1 = *it1;
            Triangle t2 = *it2;

            set<uint> indices;
            indices.insert(t1.i); indices.insert(t1.j); indices.insert(t1.k);
            indices.erase(t2.i); indices.erase(t2.j); indices.erase(t2.k);

            if (indices.size() == 1) {
                Vector2f c1 = circumcenter(vertices[t1.i],vertices[t1.j],vertices[t1.k]);
                Vector2f c2 = circumcenter(vertices[t2.i],vertices[t2.j],vertices[t2.k]);
                edges.push_back(Edge(c1,c2));
            }
        }
    }*/


    map< uint, pair<int, int> > adjVertices = triangulation.adjVertices;
    for (map< uint, pair<int,int> >::iterator it = adjVertices.begin(); it != adjVertices.end(); it++) {
        uint hash = (*it).first;
        uint u,v;
        unhash(hash,u,v);
        pair<int,int> adj = (*it).second;

        if (adj.first >= 0 && adj.second >= 0) {
            //edge connecting two circumcenters that share an edge in the Delaunay triangulation
            Vector2f c1 = circumcenter(vertices[u], vertices[v], vertices[adj.first]);
            Vector2f c2 = circumcenter(vertices[u], vertices[v], vertices[adj.second]);
            edges.push_back(Edge(c1,c2));

        } else if (adj.first >= 3 || adj.second >= 3) {
            //border circumcenter should have an infinitely long
            //perpendicular edge to the border edge in the Delaunay triangulation
            uint idx = adj.first >= 3 ? adj.first : adj.second;
            Vector2f center = circumcenter(vertices[u], vertices[v], vertices[idx]);
            Vector2f edgeMid = (vertices[u] + vertices[v]) / 2;
            //Vector2f d = pointLineTest(vertices[u],vertices[v],vertices[idx]) > 1 ? edgeMid-center : center-edgeMid;
            Vector2f end = (edgeMid-center).unit()*INFINITE_SCALAR + center;
            //edges.push_back(Edge(center, end));
        }
    }

    return edges;
}
