#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

typedef unsigned int uint;

template <typename T, uint N>
class Vector {
public:
    Vector() {}
    Vector(const Vector<T,N> &v) {
        for (uint i = 0; i < N; i++)
            this->data[i] = v.data[i];
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

    Vector<T,N> cross(const Vector<T,N> &v) const;

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

template <typename T>
class Vector2 : public Vector<T,2> {
public:
    Vector2() {}
    Vector2(T x, T y) {
        Vector<T,2>::data[0] = x;
        Vector<T,2>::data[1] = y;
    }
};

template <typename T>
class Vector3 : public Vector<T,3> {
public:
    Vector3() {}
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
