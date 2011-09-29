#ifndef GLUTILS_H
#define GLUTILS_H

#include "vector.h"
#include <queue>
#include <list>
#include <QDebug>

using namespace std;

class mstCompare {
public:
    mstCompare(const float *distance, uint n) {
        this->distance = distance;
        this->n = n;
    }

    bool operator() (const uint& i, const uint& j) const {
        //qDebug() << "COMPARE:" << i << j << distance[i] << distance[j] << (distance[i] < distance[j]);
        return distance[i] > distance[j];
    }
private:
    const float *distance;
    uint n;
};

list<Vector2i> mst(vector<Vector2f> vertices) {
    uint n = vertices.size();
    list<Vector2i> edges;

    uint parent[n];
    for (uint i = 0; i < n; i++) parent[i] = 0;

    bool visited[n];
    for (uint i = 0; i < n; i++) visited[i] = false;

    float distance[n];
    for (uint i = 0; i < n; i++) distance[i] = 0x3f3f3f3f;
    distance[0] = 0;

    priority_queue< uint, vector<uint>, mstCompare > queue( mstCompare((float*)distance, n) );

    for (uint i = 0; i < n; i++) queue.push(i);
    while (!queue.empty()) {
        uint i = queue.top();
        Vector2f v1 = vertices[i];
        visited[i] = true;
        //qDebug() << "i" << i;

        for (uint j = 0; j < n; j++) {
            if (i != j && !visited[j]) {
                Vector2f v2 = vertices[j];

                float dist = (v1-v2).magnitude();
                if (dist < distance[j]) {
                    parent[j] = i;
                    distance[j] = dist;
                }
            }
        }

        queue.pop();
    }

    /*qDebug() << "[ ";
    for (uint i = 0; i < n; i++)
        qDebug() << parent[i];
    qDebug() << "]\n";*/

    for (uint v = 1; v < n; v++) {
        edges.push_back(Vector2i(parent[v],v));
    }

    return edges;
}



#define PRECISION 360
#define PI 3.14159265
#define DEFAULT_RADIUS 0.01

//draws a circle at (x,y) with radius r using OpenGL
void glDrawCircle(float x, float y, float r=DEFAULT_RADIUS) {
    //translate to x,y
    glLoadIdentity();
    glTranslatef(x,y,0);

    //divide circle into sections
    double angleDelta = 2.0*PI/PRECISION;
    double angle = 0;

    //draw points on the circle
    glBegin(GL_POLYGON);
       for (int i = 0; i < PRECISION; i++) {
            double x = r * cos(angle);
            double y = r * sin(angle);
            angle += angleDelta;

            glVertex2d(x,y);
        }
    glEnd();
    glLoadIdentity();
}


#endif // GLUTILS_H
