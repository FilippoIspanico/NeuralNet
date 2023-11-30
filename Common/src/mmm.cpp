#include "../include/mmm.hpp"
#include <cblas.h>
#include <chrono>

void mmm_blas(MatrixFlat<float>& A, MatrixFlat<float>& B, MatrixFlat<float>& C, int64_t& time) {

    //! Performs C = A*B in single precision using openblas optimized mm multiplication and returns the latency of the operation in variable time


    std::size_t m, n, k;

    m = A.nrows();
    n = B.ncols();
    k = A.ncols();


    const auto t0 = std::chrono::high_resolution_clock::now();

    cblas_sgemm(
            CblasRowMajor,      // Specifies row-major (C) or column-major (Fortran) data ordering.
            CblasNoTrans,       // Specifies whether to transpose matrix A.
            CblasNoTrans,       // Specifies whether to transpose matrix B.
            m,             // Number of rows in matrices A and C.
            n,             // Number of columns in matrices B and C.
            k,             // Number of columns in matrix A; number of rows in matrix B.
            1.0,                // Scaling factor for the product of matrices A and B.
            A.get_ptr(),       // UnsafePointer<Double>! to Matrix A.
            k,
            B.get_ptr(),     // Matrix B.
            n,             // The size of the first dimension of matrix B; if you are passing a matrix B[m][n], the value should be m.
            0.0,                // Scaling factor for matrix C.
            C.get_ptr(),     // Matrix C.
            n             // The size of the first dimension of matrix C; if you are passing a matrix C[m][n], the value should be m.
    );


    const auto t1 = std::chrono::high_resolution_clock::now();

    time = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();



}

void mmm_blas(MatrixFlat<double>& A, MatrixFlat<double>& B, MatrixFlat<double>& C, int64_t& time) {

    //! Performs C = A*B in double precision using openblas optimized mm multiplication and returns the latency of the operation


    std::size_t m, n, k;

    m = A.nrows();
    n = B.ncols();
    k = A.ncols();


    const auto t0 = std::chrono::high_resolution_clock::now();

    cblas_dgemm(
            CblasRowMajor,      // Specifies row-major (C) or column-major (Fortran) data ordering.
            CblasNoTrans,       // Specifies whether to transpose matrix A.
            CblasNoTrans,       // Specifies whether to transpose matrix B.
            m,             // Number of rows in matrices A and C.
            n,             // Number of columns in matrices B and C.
            k,             // Number of columns in matrix A; number of rows in matrix B.
            1.0,                // Scaling factor for the product of matrices A and B.
            A.get_ptr(),       // UnsafePointer<Double>! to Matrix A.
            k,
            B.get_ptr(),     // Matrix B.
            n,             // The size of the first dimension of matrix B; if you are passing a matrix B[m][n], the value should be m.
            0.0,                // Scaling factor for matrix C.
            C.get_ptr(),     // Matrix C.
            n             // The size of the first dimension of matrix C; if you are passing a matrix C[m][n], the value should be m.
    );


    const auto t1 = std::chrono::high_resolution_clock::now();

    time = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    
}

void mmm_naive(const MatrixFlat<double>& A, const MatrixFlat<double>& B, MatrixFlat<double>& C, int64_t& time){

    std::cout<<"Performing naive mmm in double precision (double)  "<<std::endl;
    std::size_t rows = A.nrows(), columns = B.ncols(), inners = A.ncols();


    const auto t0 = std::chrono::high_resolution_clock::now();

    for (std::size_t row = 0; row < rows; row++) {
        for (std::size_t col = 0; col < columns; col++) {
            for (std::size_t inner = 0; inner < inners; inner++) {
                C[row * columns + col] +=
                        A[row * columns + inner] * B[inner * columns + col];
            }
        }
    }

    const auto t1 = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();


};

void mmm_naive(const MatrixFlat<float>& A, const MatrixFlat<float>& B, MatrixFlat<float>& C, int64_t& time){

    std::cout<<"Performing naive mmm in single precision (float) "<<std::endl;
    std::size_t rows = A.nrows(), columns = B.ncols(), inners = A.ncols();


    const auto t0 = std::chrono::high_resolution_clock::now();

    for (std::size_t row = 0; row < rows; row++) {
        for (std::size_t col = 0; col < columns; col++) {
            for (std::size_t inner = 0; inner < inners; inner++) {
                C[row * columns + col] +=
                        A[row * columns + inner] * B[inner * columns + col];
            }
        }
    }

    const auto t1 = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();


};

void mmm_naive_RegisterAcc(const MatrixFlat<double>& A, const MatrixFlat<double>& B, MatrixFlat<double>& C, int64_t& time){

    std::cout<<"Performing naive_mmm_RegisterAcc in double precision (double) "<<std::endl;

    std::size_t rows = A.nrows(), columns = B.ncols(), inners = A.ncols();


    const auto t0 = std::chrono::high_resolution_clock::now();

    for (std::size_t row = 0; row < rows; row++) {
        for (std::size_t col = 0; col < columns; col++) {
            double acc = 0;
            for (std::size_t inner = 0; inner < inners; inner++) {
                acc += A[row * columns + inner] * B[inner * columns + col];
            }
            C[row * columns + col] =  acc;
        }
    }

    const auto t1 = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();



};

void mmm_naive_RegisterAcc(const MatrixFlat<float>& A, const MatrixFlat<float>& B, MatrixFlat<float>& C, int64_t& time){


    std::cout<<"Performing naive_mmm_RegisterAcc in single precision (float) "<<std::endl;

    std::size_t rows = A.nrows(), columns = B.ncols(), inners = A.ncols();

    const auto t0 = std::chrono::high_resolution_clock::now();

    for (std::size_t row = 0; row < rows; row++) {
        for (std::size_t col = 0; col < columns; col++) {
            float acc = 0;
            for (std::size_t inner = 0; inner < inners; inner++) {
                acc += A[row * columns + inner] * B[inner * columns + col];
            }
            C[row * columns + col] =  acc;
        }
    }

    const auto t1 = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();



};