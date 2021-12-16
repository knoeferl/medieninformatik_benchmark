//
// Created by mknoe on 16.12.2021.
//

#include <math.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/operation_blocked.hpp>
#include <utility>
using namespace boost::numeric::ublas;


const double C[] = {1.0 / sqrt(2), 1, 1, 1, 1, 1, 1, 1 };

  matrix<double> generateA() {
    matrix<double> A(8, 8);

    const double prefix = sqrt(2./8);

    for (int k = 0; k < 8; ++k) {
        for (int n = 0; n < 8; ++n) {
            A(k, n) = C[k] * prefix * cos(((n << 1) + 1) * (k * M_PI) / (2*8) );
        }
    }

    return A;
}

  matrix<double> generateAT()  {
    return boost::numeric::ublas::trans(generateA());
}

const  matrix<double> A = generateA();
const  matrix<double> AT = generateAT();

matrix<double> calcTestData()
{
    matrix<double> m (3840, 2160);
    for (unsigned i = 0; i < m.size1 (); ++ i)
        for (unsigned j = 0; j < m.size2 (); ++ j)
            m (i, j) = (i + j * 8) % 256;
    return m;
}

matrix<double> naive(matrix<double> &input)
{
     int n = 8;
    matrix<double> matrixY = matrix<double>(n, n);
    for (int j = 0; j < n; j++)
        for (int i = 0; i < n; i++)
        {
            double temp = 0;
            for (int x = 0; x < n; x++)
                for (int y = 0; y < n; y++)
                    temp += input(y, x) * cos((2 * x + 1) * i * M_PI / (2.0 * n)) * cos((2 * y + 1) * j * M_PI / (2.0 * n));

            double yIj = 2.0 / n * C[i] * C[j] * temp;
            matrixY(j, i) = yIj;
        }
    input = matrixY;
    return matrixY;
}

matrix<double> advanced(matrix<double>  &input){
    return input = block_prod<matrix<double>, 8>(block_prod<matrix<double>, 8>(A, input), AT);
}


matrix<double> mMMatrixWithSize(matrix<double> &x,const std::function<matrix<double>(matrix<double>&)> &c,
                                            int size)
{
    matrix<double> m;
    for (int col = 0; col < x.size2(); col += size)
    {
        for (int row = 0; row < x.size1(); row += size)
        {
            const basic_range<> &r1 = range(row, row + size);
            const basic_range<> &r2 = range(col, col + size);
            matrix<double> matrixRange = project(x, r1, r2);
            matrixRange = c(matrixRange);
        }
    }
    return x;
}

matrix<double> mMMatrix(matrix<double> &x,const std::function<matrix<double>(matrix<double>&)>& c)
{
    return mMMatrixWithSize(x, c, 8);
}
