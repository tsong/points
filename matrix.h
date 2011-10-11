#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include <QDebug>

template<typename T, uint N>
class RowVector {
public:
    RowVector() {
        data = 0;
    }

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
        if (M != N) return 0;
        if (N == 1) return data[0][0];
        if (N == 2) return data[0][0]*data[1][1] - data[0][1]*data[1][0];

        double result = 0;
        for (uint j = 0; j < N; j++) {
            int sign = j % 2 == 0 ? 1 : -1;

            /*Matrix<T,M-1,N-1> C = cofactor(0,j);

            qDebug() << "SUB:" << M-1 << N-1 << j;
            for (uint k = 0; k < M-1; k++) {
                QString line = "";
                for (uint l = 0; l < N-1; l++)
                    line += QString("%1 ").arg(C[k][l]);
                qDebug() << line;
            }*/
            result += sign * data[0][j] * cofactor(0,j).det();
        }

        /*qDebug() << "MAT:" << M << N;
        for (uint k = 0; k < M; k++) {
            QString line = "";
            for (uint l = 0; l < N; l++)
                line += QString("%1 ").arg(data[k][l]);
            qDebug() << line;
        }
        qDebug() << "DET: " << result;*/

        return result;
    }

    Matrix<T,M-1,N-1> cofactor(uint row, uint column) {
        Matrix<T,M-1,N-1> C;

        uint ii = 0;
        uint jj = 0;
        for (uint i = 0; i < M; i++) {
            if (i == row) continue;

            for (uint j = 0; j < N; j++) {
                if (j == column) continue;
                C[ii][jj++] = data[i][j];
            }

            ii++;
            jj = 0;
        }
        return C;
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

//template specialization so cofactor method doesn't recurse infinitely
template <typename T>
class Matrix <T,0,0> {
public:
    double det() { return 0; }
    RowVector<T,0> operator[](uint) { return RowVector<T,0>(); }
};

typedef Matrix<int, 3, 3> Matrix3i;
typedef Matrix<float, 3, 3> Matrix3f;
typedef Matrix<double, 3, 3> Matrix3d;

typedef Matrix<int, 4, 4> Matrix4i;
typedef Matrix<float, 4, 4> Matrix4f;
typedef Matrix<double, 4, 4> Matrix4d;

#endif // MATRIX_H
