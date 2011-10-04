#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

template <typename T, uint M, uint N>
class Matrix {
public:
    Matrix() {
        this->zero();
    }

    Matrix(const Matrix<T,M,N>& M) {
        for (uint i = 0; i < M; i++)
            for (uint j = 0; j < N; j++)
                this->data[i][j] = M.data[i][j];
    }

    void zero() {
        for (uint i = 0; i < M; i++)
            for (uint j = 0; j < N; j++)
                this->data[i][j] = 0;
    }

   /* Matrix<T,M,N>& operator+(const Matrix<T,M,N>& M) const {

    }*/

protected:
    T data[M][N];
};

#endif // MATRIX_H
