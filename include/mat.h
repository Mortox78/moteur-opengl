#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>

namespace Core
{
    namespace Maths
    {
        class mat4;

        class mat
        {
            public:
                int n;
                int m;
                std::vector<float> array;

                mat();
                mat(int n, int m);
                mat(const mat& matrix);
                mat(const mat4& matrix4);
                ~mat();

                float& accessor(int i, int j);
                static mat identity(int m);
                static mat zero(int n, int m);
                void transpose();
                mat operator+(const mat& secondMat);
                mat operator-(const mat& secondMat);
                mat operator*(mat& secondMat);
                float getDeterminant();
                float getDeterminant_1x1();
                float getDeterminant_2x2();
                float getDeterminant_3x3();
                float getDeterminant_4x4();
                float getDeterminant_NxN();
                float getMinor(int n, int m);
                float getCofactor(int n, int m);
                mat getComatrix();
                mat getAdj();
                mat getReverseMatrix();
                mat resolveSystem(mat& matProduct);
                bool isMatrixReversable();
                bool isMatrixOrthogonal();
                bool operator==(mat secondMat);
                void display();


        };

        mat getSubMatrix(mat& matrix, int excludedLineIndex, int excludedColumnIndex);
    }
}

#endif