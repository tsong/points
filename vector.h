#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

typedef unsigned int uint;

template <typename T, uint N>
class Vector {
public:
    Vector() {
        this->zero();
    }

    Vector(const Vector<T,N> &v) {
        for (uint i = 0; i < N; i++)
            this->data[i] = v.data[i];
    }

    Vector(T x, T y) {
        this->zero();
        if (N >= 1) data[0] = x;
        if (N >= 2) data[1] = y;
    }

    Vector(T x, T y, T z) {
        this->zero();
        if (N >= 1) data[0] = x;
        if (N >= 2) data[1] = y;
        if (N >= 3) data[2] = z;
    }

    Vector(T x, T y, T z, T w) {
        this->zero();
        if (N >= 1) data[0] = x;
        if (N >= 2) data[1] = y;
        if (N >= 3) data[2] = z;
        if (N >= 4) data[3] = w;
    }

    void zero() {
        for (uint i = 0; i < N; i++)
            this->data[i] = 0;
    }

    double magnitude() const {
        T sum = 0;
        for (uint i = 0; i < N; i++) {
            sum += data[i]*data[i];
        }

        return sqrt(sum);
    }

    T dot(const Vector<T,N> &v) const {
        T result = 0;
        for (uint i = 0; i < N; i++) {
            result += data[i] * v.data[i];
        }

        return result;
    }

    Vector<T,N> cross(const Vector<T,N> &b) const {
        Vector<T,N> c;
        const T (&a)[N] = data;

        switch(N) {
        case 1:
            c[0] = a[0]*b[0];
            break;
        case 2:
            c[0] = a[1]*b[0] - a[0]*b[1];
            c[1] = a[0]*b[0] - a[0]*b[0];
            break;
        case 3:
            c[0] = a[1]*b[2] - a[2]*b[1];
            c[1] = a[2]*b[0] - a[0]*b[2];
            c[2] = a[0]*b[1] - a[1]*b[0];
        default:
            //TODO: implement general cross product function
            break;
        }

        return c;
    }

    Vector<T,N> operator-(const Vector<T,N> &v) const {
        Vector<T,N> result;
        for (uint i = 0; i < N; i++)
            result.data[i] = data[i] - v.data[i];
        return result;
    }

    Vector<T,N>& operator=(const Vector<T,N> &v) {
        if (this != &v) {
            for (uint i = 0; i < N; i++)
                data[i] = v.data[i];
        }
        return *this;
    }

    bool operator==(const Vector<T,N> &v) const {
        for (uint i = 0; i < N; i++)
            if (data[i] != v.data[i])
                return false;
        return true;
    }

    T& operator[](uint i) {
        return this->data[i];
    }

protected:
    T data[N];
};


typedef Vector<int, 2> Vector2i;
typedef Vector<float, 2> Vector2f;
typedef Vector<double, 2> Vector2d;

typedef Vector<int,3 > Vector3i;
typedef Vector<float, 3> Vector3f;
typedef Vector<double, 3> Vector3d;

typedef Vector<int, 4> Vector4i;
typedef Vector<float, 4> Vector4f;
typedef Vector<double, 4> Vector4d;

#endif // VECTOR_H
