#ifndef CONVEXHULLALGORITHM_H
#define CONVEXHULLALGORITHM_H

#include "pointsalgorithm.h"
#include "vector.h"

class ConvexHullAlgorithm : public PointsAlgorithm
{
public:
    void addVertex(Vector2f v);
    void setVertices(const vector<Vector2f> &vertices);
    list<Edge> getEdges();
    ConvexHullAlgorithm* getInstance();

protected:
    vector<Vector2f> vertices;
    static ConvexHullAlgorithm *instance;
};

/*STL comparator evaluating polar angle from starting vertex
class ConvexHullCompare {
public:
    ConvexHullCompare(const Vector2f &start)
        : start(start)
    {
    }

    bool operator() (const Vector2f& v1, const Vector2f& v2) const {
        Vector<float,2> d1 = v1 - start;
        Vector<float,2> d2 = v2 - start;

        return d1[0]/d1[1] > d2[0]/d2[1];
    }
private:
    const Vector2f &start;
};*/

#endif // CONVEXHULLALGORITHM_H
