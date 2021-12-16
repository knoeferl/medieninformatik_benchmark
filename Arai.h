//
// Created by mknoe on 16.12.2021.
//

#ifndef UNTITLED_ARAI_H
#define UNTITLED_ARAI_H

#include <math.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/operation_blocked.hpp>
#include <utility>
using namespace boost::numeric::ublas;

 const double C1[] = { 1, cos(M_PI / 16 * 1), cos(M_PI / 16 * 2), cos(M_PI / 16 * 3), cos(M_PI / 16 * 4),
                cos(M_PI / 16 * 5), cos(M_PI / 16 * 6), cos(M_PI / 16 * 7) };

const double A1[] ={ 1, C1[4], C1[2] - C1[6], C1[4], C1[6] + C1[2], C1[6] };

 const double S[] = { 1.0 / (2 * sqrt(2)), 1.0 / (4 * C1[1]), 1.0 / (4 * C1[2]), 1.0 / (4 * C1[3]),
                1.0 / (4 * C1[4]), 1.0 / (4 * C1[5]), 1.0 / (4 * C1[6]), 1.0 / (4 * C1[7]) };




matrix<double> basicArai(matrix<double> &matrix, int row, int col){

    int numCols= matrix.size2();
    double x0;
    double x1;
    double x2;
    double x3;
    double x4;
    double x5;
    double x6;
    double x7;

    int startIndex=row*numCols+col;
    //col
    for(int i=0;i<8;i++){
        int index=startIndex+i;

        x0 = matrix(index);
        x7 = matrix(index);
        x1 = matrix(index+=numCols);
        x6 = matrix(index);
        x2 = matrix(index+=numCols);
        x5 = matrix(index);
        x3 = matrix(index+=numCols);
        x4 = matrix(index);
        x3 = x3+matrix(index+=numCols);
        x4 = x4-matrix(index);
        x5 = x5-matrix(index+=numCols);
        x2 = x2+matrix(index);
        x1 = x1+matrix(index+=numCols);
        x6 = x6-matrix(index);
        x0 = x0+matrix(index+=numCols);
        x7 = x7-matrix(index);

        double v8 = x0 + x3;
        double v9 = x1 + x2;
        x2 = x1 - x2;
        x3 = x0 - x3;
        x4 = -x4 - x5;
        x5 = (x5 + x6) * A1[3];
        x6 = x6 + x7;

        x2 = (x2 + x3) * A1[1];
        double v10 = (x4 + x6) * A1[5];

        x4 = -x4 * A1[2] - v10;
        x6 = x6 * A1[4] - v10;

        double v11 = x5 + x7;
        x5 = x7 - x5;
        matrix(index-=numCols*7)=S[0] * (v8 + v9);
        matrix(index+=numCols)=S[1] * (v11 + x6);
        matrix(index+=numCols)=S[2] * (x2 + x3);
        matrix(index+=numCols)=S[3] * (x5 - x4);
        matrix(index+=numCols)=S[4] * (v8 - v9);
        matrix(index+=numCols)=S[5] * (x4 + x5);
        matrix(index+=numCols)=S[6] * (x3 - x2);
        matrix(index+numCols)=S[7] * (v11 - x6);
    }

    //row
    for(int i=0;i<8;i++){
        int index=(i+row)*numCols+col;

        x0 = matrix(index);
        x7 = matrix(index);
        x1 = matrix(index+=1);
        x6 = matrix(index);
        x2 = matrix(index+=1);
        x5 = matrix(index);
        x3 = matrix(index+=1);
        x4 = matrix(index);
        x3 = x3+matrix(index+=1);
        x4 = x4-matrix(index);
        x5 = x5-matrix(index+=1);
        x2 = x2+matrix(index);
        x1 = x1+matrix(index+=1);
        x6 = x6-matrix(index);
        x0 = x0+matrix(index+=1);
        x7 = x7-matrix(index);

        double v8 = x0 + x3;
        double v9 = x1 + x2;
        x2 = x1 - x2;
        x3 = x0 - x3;
        x4 = -x4 - x5;
        x5 = (x5 + x6) * A1[3];
        x6 = x6 + x7;

        x2 = (x2 + x3) * A1[1];
        double v10 = (x4 + x6) * A1[5];

        x4 = -x4 * A1[2] - v10;
        x6 = x6 * A1[4] - v10;

        double v11 = x5 + x7;
        x5 = x7 - x5;
        matrix(index-=7)=S[0] * (v8 + v9);
        matrix(index+=1)=S[1] * (v11 + x6);
        matrix(index+=1)=S[2] * (x2 + x3);
        matrix(index+=1)=S[3] * (x5 - x4);
        matrix(index+=1)=S[4] * (v8 - v9);
        matrix(index+=1)=S[5] * (x4 + x5);
        matrix(index+=1)=S[6] * (x3 - x2);
        matrix(index+1)=S[7] * (v11 - x6);
    }
    return matrix;
}

matrix<double> calcBasic(matrix<double> &input)
{
    for (int row = 0; row < input.size1(); row += 8){
        std::cout << "start: " << row << std::endl;
        for (int col = 0; col < input.size2(); col += 8){
            basicArai(input, row, col);
        }
        std::cout << "end: " << row << std::endl;
    }
    return input;
}

#endif //UNTITLED_ARAI_H
