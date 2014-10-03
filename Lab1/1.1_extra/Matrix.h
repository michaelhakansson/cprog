#ifndef MATRIX_H
#define MATRIX_H
#include "Vector.h"
#include <iostream>
#include <stdexcept>

// template <class T>
// class Vector : public std::vector< T > {
// public:
//     explicit Vector <T> (std::size_t size  = 0, T data = T()) : std::vector<T>(size, data) {}
//     const T& operator[](unsigned int i) const throw(std::out_of_range) {
//         return this->at( i );
//     }
//     T& operator[](unsigned int i) throw(std::out_of_range) {
//         return this->at( i );
//     }    
// };

//using namespace std;

class Matrix
{
 public:
    typedef unsigned int index;
    
    class matrix_row : private Vector< int >
    {
    public:
        matrix_row( std::size_t s = 0) : Vector< int >( s ) {}
        using Vector<int>::operator [];
    private:
        friend std::istream& operator>>( std::istream&, Matrix& );
    };
    
    Matrix( );
    Matrix( std::size_t, std::size_t );
    Matrix( const Matrix& );
    Matrix(std::size_t size);
    ~Matrix( );
    
    Matrix& operator= ( const Matrix& );
    Matrix operator+ ( const Matrix& ) const;
    Matrix operator* ( const Matrix& ) const;
    Matrix operator* ( int ) const;
    Matrix operator-( const Matrix& ) const;
    Matrix operator-( ) const;
    
    Matrix& transpose( );
    
    matrix_row& operator[]( index i );
    const matrix_row& operator[]( index i ) const;
    
    std::size_t rows() const;
    std::size_t cols() const;
    
 protected:
 private:
    Vector< matrix_row >        *m_vectors;
    std::size_t                 m_rows;
    std::size_t                 m_cols;
    
    void add_row( );            // Non mandatory help function
    friend std::istream& operator>> ( std::istream&, Matrix& );
};


Matrix::Matrix( ) : Matrix::Matrix(0) {
    // Delegate
}

Matrix::Matrix(std::size_t num_rows, std::size_t num_columns) 
    :   m_vectors(new Vector<matrix_row>(num_rows, num_columns)),
        m_rows(num_rows),
        m_cols(num_columns) {

    for (std::size_t i = 0; i < m_rows; ++i) {
        for (std::size_t j = 0; j < m_cols; ++j) {
            (*m_vectors)[i][j] = 0;
        }
    }
}

// Copy constructor
Matrix::Matrix(const Matrix& src)
    :   m_vectors(new Vector<matrix_row>(src.m_rows, src.m_cols)),
        m_rows(src.m_rows),
        m_cols(src.m_cols) {

    for (std::size_t i = 0; i < m_rows; ++i) {
        for (std::size_t j = 0; j < m_cols; ++j) {
            (*m_vectors)[i][j] = (*src.m_vectors)[i][j];
        }
    }
}


// Constructor for nxn id-matrix
Matrix::Matrix(std::size_t size)
    :   m_vectors( new Vector<matrix_row>(size, size) ),
        m_rows(size),
        m_cols(size) {

    for (std::size_t i = 0; i < m_rows; ++i) {
        for (std::size_t j = 0; j < m_cols; ++j) {
            (*m_vectors)[i][j] = (j == i ? 1 : 0);
        }
    }

}

// Destructor
Matrix::~Matrix( ) {
    delete m_vectors;
}

// Copy assignment operator
Matrix& Matrix::operator= ( const Matrix& src ) {
    if (this != &src) {
        delete m_vectors;
        m_vectors = new Vector<matrix_row>(src.m_rows, src.m_cols);
        m_rows = src.m_rows;
        m_cols = src.m_cols;
        for (std::size_t i = 0; i < m_rows; ++i) {
            for (std::size_t j = 0; j < m_cols; ++j) {
                (*m_vectors)[i][j] = (*src.m_vectors)[i][j];
            }
        }
    }
    return *this;
}

Matrix::matrix_row& Matrix::operator[]( index i ) {
    if(i >= m_rows) {
        throw std::out_of_range("Index out of bounds");
    }
    return (*m_vectors)[i];
}

const Matrix::matrix_row& Matrix::operator[]( index i ) const {
    if(i >= m_rows) {
        throw std::out_of_range("Index out of bounds");
    }
    return (*m_vectors)[i];
}


std::istream& operator>> ( std::istream& input, Matrix& matrix ) {
    Matrix::matrix_row current_row;

    while (input) {
        char ch = input.peek();
        if (ch == ']') {
            matrix.m_vectors->push_back(current_row);
            break;
        } else if (ch == '[' || ch == ' ') {
            input.ignore(1);
        } else if (ch == ';') {
            input.ignore(1);
            matrix.m_vectors->push_back(current_row);
            current_row.clear();
        } else {
            int i;
            input >> i;
            current_row.push_back(i);
        }
    }

    matrix.m_rows = matrix.m_vectors[0].size();
    matrix.m_cols = matrix[0].size();

    return input;
}

std::ostream& operator<< ( std::ostream& output, Matrix& matrix) {
    output << "[ ";
    for (std::size_t i = 0; i < matrix.rows(); ++i) {
        output << (i == 0 ? "" : "\n; ");
        for (std::size_t j = 0; j < matrix.cols(); ++j) {
            output << matrix[i][j] << " ";
        }
    }
    output << "]";
    return output;
}

Matrix operator* ( int, const Matrix& );

std::size_t Matrix::rows() const {
    return m_rows;
}

std::size_t Matrix::cols() const {
    return m_cols;
}

#endif // MATRIX_H
