#ifndef MSTALGORITHM_H
#define MSTALGORITHM_H

#include "pointsalgorithm.h"

class MSTAlgorithm : public PointsAlgorithm
{
public:
    void addVertex(Vector2f v);
    void setVertices(const vector<Vector2f> &vertices);
    list<Edge> getEdges();

protected:
    vector<Vector2f> vertices;
};

/*STL comparator evaluating minimum distances given two vertex indices*/
class MSTCompare {
public:
    MSTCompare(const float *distance, uint n) {
        this->distance = distance;
        this->n = n;
    }

    bool operator() (const uint& i, const uint& j) const {
        if (distance[i] < 0) return true;
        if (distance[j] < 0) return false;
        return distance[i] > distance[j];
    }
private:
    const float *distance;
    uint n;
};

#endif // MSTALGORITHM_H
