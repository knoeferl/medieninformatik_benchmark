#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "Benchmarker.h"
#include "Arai.h"
#include "DCT.h"

using namespace boost::numeric::ublas;

matrix<double> testData;

void setUp()
{
    testData = calcTestData();
}


void advancedB(){
    mMMatrix(testData, advanced);
}


void araiB(){
    calcBasic(testData);
}



int main() {



//    bench(setUp, advancedB, "advanced");
    bench(setUp, araiB,  "arai");










    return 0;
}
