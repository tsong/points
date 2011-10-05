#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

template<typename T, uint N>
class RowVector {
public:
    RowVector(T *data) {
        this->data = data;
    }

    RowVector<T,N>& operator=(Vector<T,N> v) {
        for (uint i = 0; i < N; i++)
            this->data[i] = v[i];
        return *this;
    }

    T& operator[](uint i) {
        return *(data + i);
    }

protected:
    T *data;
};

template <typename T, uint M, uint N>
class Matrix {
public:
    Matrix() {
        this->zero();
    }

    Matrix(const Matrix<T,M,N>& mat) {
        this->operator=(mat);
    }

    void zero() {
        for (uint i = 0; i < M; i++)
            for (uint j = 0; j < N; j++)
                this->data[i][j] = 0;
    }

    double det() {
        return 0;
    }

    Matrix<T,M,N> operator+(const Matrix<T,M,N>& mat) const {
        Matrix<T,M,N> result = mat;
        for (uint i = 0; i < M; i++)
            for (uint j = 0; j < N; j++)
                result.data[i][j] = this->data[i][j];
        return result;
    }

    Matrix<T,N,M>& operator=(const Matrix<T,M,N>& mat) {
        if (this != &mat) {
            for (uint i = 0; i < M; i++)
                for (uint j = 0; j < N; j++)
                    this->data[i][j] = mat.data[i][j];
        }

        return *this;
    }

    RowVector<T,N> operator[](uint i) {
        RowVector<T,N> rowVector((T*)data + i*M);
        return rowVector;
    }

protected:
    T data[M][N];
};

typedef Matrix<int, 3, 3> Matrix3i;
typedef Matrix<float, 3, 3> Matrix3f;
typedef Matrix<double, 3, 3> Matrix3d;

typedef Matrix<int, 4, 4> Matrix4i;
typedef Matrix<float, 4, 4> Matrix4f;
typedef Matrix<double, 4, 4> Matrix4d;

#endif // MATRIX_H
