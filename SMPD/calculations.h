#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/qvm/mat_operations.hpp>

#include "database.h"

using namespace boost::numeric::ublas;

class Calculations
{
private:
    std::vector<float> m_acerAverages;
    std::vector<float> m_quercusAverages;
    long long m_acerObjectsCount;
    long long m_quercusObjectsCount;

    float detereminant(matrix<float> m);
    void test();

public:
    Calculations();
    void countAverage(const Database& database);
    void countMatrixOfDifferences(const Database& database);
    void printAverages();

};

#endif // CALCULATIONS_H
