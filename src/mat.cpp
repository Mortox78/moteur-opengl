#include <iostream>
#include <assert.h>
#include <math.h>
#include "mat.h"
#include "mat4.h"
#include <vector>
#include <assert.h>

using namespace Core::Maths;

mat::mat()
{

}

mat::mat(int n, int m)
{
    array.resize(n * m, 0);
    this->n = n;
    this->m = m;
}

mat::mat(const mat4& matrix4)
{
    array = matrix4.array;
    this->n = matrix4.n;
    this->m = matrix4.m;
}

mat::mat(const mat& matrix)
{
    array = matrix.array;
    this->n = matrix.n;
    this->m = matrix.m;
}

mat::~mat()
{

}

float& mat::accessor(int i, int j)
{
    return array[(i * this->m) + j];
}

mat mat::identity(int m)
{
    assert(m > 0);
    mat matIdentity(m, m);

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (i == j)
            {
                matIdentity.accessor(i, j) = 1;
            }
            else
            {
                matIdentity.accessor(i, j) = 0;
            }
        }
    }
    
    return matIdentity;
}


mat mat::zero(int n, int m)
{
    assert(n > 0 && m > 0);
    mat matZero(n, m);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            matZero.accessor(i, j) = 0;
        }
    }

    return matZero;
}


void mat::transpose()
{
    mat transposedMatrix(this->m, this->n);
    
    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < m; ++i)
        {
            transposedMatrix.accessor(i, j) = this->accessor(j, i);
        }
    }
    this->n = transposedMatrix.n;
    this->m = transposedMatrix.m;

    for (int i = 0; i < n * m; ++i)
    {
        this->array[i] = transposedMatrix.array[i];
    }
}

mat mat::operator+(mat const& secondMat)
{
    assert(secondMat.n == this->n);
    assert(secondMat.m == this->m);

    mat newMatrix(secondMat.n, secondMat.m);

    for (int i = 0; i < secondMat.n * secondMat.m; ++i)
    {
        newMatrix.array[i] = secondMat.array[i] + array[i];
    }

    return newMatrix;
}

mat mat::operator-(mat const& secondMat)
{
    assert(secondMat.n == this->n);
    assert(secondMat.m == this->m);
    
    mat newMatrix(secondMat.n, secondMat.m);

    for (int i = 0; i < secondMat.n * secondMat.m; ++i)
    {
        newMatrix.array[i] = secondMat.array[i] - array[i];
    }

    return newMatrix;
}

mat mat::operator*(mat& secondMat)
{
    assert(this->m == secondMat.n);

    mat newMatrix(this->n, secondMat.m);

    for (int i = 0; i < newMatrix.n; ++i)
    {
        for (int j = 0; j < newMatrix.m; ++j)
        {
            float newData = 0;

            // y < this->m  OR y < a.n
            for (int y = 0; y < this->m; ++y)
            {
                newData += (this->accessor(i, y) * secondMat.accessor(y, j));
            }
            newMatrix.accessor(i, j) = newData;
        }
    }

    return newMatrix;
}

float mat::getDeterminant_1x1()
{
    return accessor(0,0);
}

float mat::getDeterminant_2x2()
{
    return accessor(0,0) * accessor(1, 1) - accessor(0,1) * accessor(1, 0);
}

float mat::getDeterminant_3x3()
{
    float determinant = 0;
    for (int i = 0; i < 3; ++i)
    {
        mat subMatrix = getSubMatrix(*this, 0, i);
        float determinant2x2 = array[i] * subMatrix.getDeterminant_2x2();
        if (i == 1)
            determinant2x2 *= -1;

        determinant += determinant2x2;
    }
    
    return determinant;
}

float mat::getDeterminant_4x4()
{
    float determinant = 0;
    for (int i = 0; i < 4; ++i)
    {
        mat subMatrix = getSubMatrix(*this, 0, i);
        float determinant3x3 = array[i] * subMatrix.getDeterminant_3x3();
        if (i == 1 || i == 3)
            determinant3x3 *= -1;

        determinant += determinant3x3;
    }

    return determinant;
}

float mat::getDeterminant_NxN()
{
    assert(n == m && n > 0 && m > 0);
    if (n == 2)
    {
        return getDeterminant_2x2();
    }
    float determinant = 0;
    for (int i = 0; i < n; ++i)
    {
        mat subMatrix = getSubMatrix(*this, 0, i);
        float determinantStock = array[i];
        if (subMatrix.n == 2)
        {
            determinantStock *= subMatrix.getDeterminant_2x2();
        }
        else
        {
            determinantStock *= subMatrix.getDeterminant_NxN();
        }
        if (i % 2 == 1)
            determinantStock *= -1;

        determinant += determinantStock;
    }

    return determinant;
}



mat Core::Maths::getSubMatrix(mat& matrix, int excludedLineIndex, int excludedColumnIndex)
{
    assert(matrix.n > 1 && matrix.m > 1);

    mat subMatrix(matrix.n - 1, matrix.m - 1);

    int indexSubMatrix = 0;

    for (int i = 0; i < matrix.n; ++i)
    {
        for (int j = 0; j < matrix.m; ++j)
        {
            if (i != excludedLineIndex && j != excludedColumnIndex)
            {
                subMatrix.array[indexSubMatrix] = matrix.accessor(i, j);
                ++indexSubMatrix;
            }
        }
    }

    return subMatrix;
}

float mat::getMinor(int n, int m)
{
    mat subMatrix = getSubMatrix(*this, n, m);
    return subMatrix.getDeterminant_NxN();
}

float mat::getCofactor(int n, int m)
{
    return getMinor(n, m) * pow(-1, n + m);
}

mat mat::getComatrix()
{
    assert(n == m && n > 0 && m > 0);
    mat comatrix(n, m);

    for (int i = 0; i < comatrix.n; ++i)
    {
        for (int j = 0; j < comatrix.m; ++j)
        {
            comatrix.accessor(i ,j) = this->getCofactor(i, j);
        }
    }
    return comatrix;
}

mat mat::getAdj()
{
    assert(n == m && n > 0 && m > 0);
    mat adj = getComatrix();
    adj.transpose();

    return adj;
}

mat mat::getReverseMatrix()
{
    assert(n == m && n > 0 && m > 0);
    float determinant = getDeterminant_NxN();
    assert(determinant != 0);
    mat reverseMatrix = getAdj();

    for (int i = 0; i < n * m; ++i)
    {
        reverseMatrix.array[i] /= determinant;
    }

    return reverseMatrix;
}

bool mat::isMatrixReversable()
{
    if (this->getDeterminant_NxN() == 0)
        return false;
    else
        return true;
}

bool mat::isMatrixOrthogonal()
{
    if (n == m && n > 0 && m > 0 && this->isMatrixReversable())
    {
        mat matTransposed = *this;
        matTransposed.transpose();
        

        if (((matTransposed * *this) == (*this * matTransposed)) &&  (*this * matTransposed) == mat::identity(n) && (matTransposed * *this) == mat::identity(n))
            return true;
    }
    
    return false;
}

mat mat::resolveSystem(mat& matProduct)
{
    assert(matProduct.m == 1 && this->m == matProduct.n && this-> m == this->n);
    mat matReverse = getReverseMatrix();
    
    return *this * matProduct;
}

void mat::display()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            std::cout << "|| " << accessor(i, j) << " ||";
        }
        std::cout << std::endl;
    }
}


bool mat::operator==(mat secondMat)
{
    assert(this->n == secondMat.n);
    assert(this->m == secondMat.m);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (accessor(i, j) != secondMat.accessor(i, j))
                return false;
        }
    }

    return true;
}