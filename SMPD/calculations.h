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
    size_t m_acerObjectsCount;
    size_t m_quercusObjectsCount;

    float detereminant(matrix<float> m);
    void test();

public:
    Calculations();
    ~Calculations();
    void countAverage(const Database& database);
    std::pair<float, float> countMatrixOfDifferences(const Database& database, size_t noOfFeatures);
    void printAverages();

};

#endif // CALCULATIONS_H
