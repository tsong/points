#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

typedef unsigned int uint;

template <typename T, uint N>
class Vector {
public:
    Vector() {}

    double magnitude() {
        T sum = 0;
        for (uint i = 0; i < N; i++) {
            sum += data[i]*data[i];
        }

        return sqrt(sum);
    }

    T dot(Vector<T,N> v) {
        T result = 0;
        for (uint i = 0; i < N; i++) {
            result += data[i] * v.data[i];
        }

        return result;
    }

    Vector<T,N> cross(Vector<T,N> v);

    T& operator[](uint i) {
        return this->data[i];
    }

protected:
    T data[N];
};

template <typename T>
class Vector2 : public Vector<T,2> {
public:
    Vector2(int x, int y) {
        this->data[0] = x;
        this->data[1] = y;
    }
};

template <typename T>
class Vector3 : public Vector<T,3> {
public:
    Vector3(T x, T y, T z) {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
    }
};


typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;

#endif // VECTOR_H
