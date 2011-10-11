#include "voronoialgorithm.h"

#define INFINITE_SCALAR 1E9

Vector2f circumcenter(Vector2f a, Vector2f b, Vector2f c) {
    return Vector2f(0,0,0);
}


VoronoiAlgorithm::VoronoiAlgorithm() {
}

void VoronoiAlgorithm::addVertex(Vector2f v) {
    triangulation.addVertex(v);
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
        dualVertices.push_back(circumcenter(vertices[t.i], vertices[t.j], vertices[t.k]));
    }

    return dualVertices;
}

list<Edge> VoronoiAlgorithm::getDualEdges() {
    list<Edge> edges;

    vector<Vector2f> vertices = triangulation.vertices;
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

        } else if (adj.first >= 0 || adj.second >= 0) {
            //border circumcenter should have an infinitely long
            //perpendicular edge to the border edge in the Delaunay triangulation
            uint idx = adj.first >= 0 ? adj.first : adj.second;
            Vector2f center = circumcenter(vertices[u], vertices[v], vertices[idx]);
            Vector2f edgeMid = (vertices[u] + vertices[v]) / 2;
            Vector2f end = (edgeMid-center).unit()*INFINITE_SCALAR + center;
            edges.push_back(Edge(center, end));
        } else {
            qDebug() << "ADJACENCY MAP CORRUPTED!";
        }
    }
}
