#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "database.h"
#include "matrixutil.hpp"

using namespace boost::numeric::ublas;

class Calculations
{
private:
    std::vector<float> m_acerAverages;
    std::vector<float> m_quercusAverages;
    size_t m_acerObjectsCount;
    size_t m_quercusObjectsCount;

	std::vector<std::vector<int>> combine(int n, int k);
	float distance(matrix<float> m);
	float detereminant(matrix<float> m);
	void print_matrix(matrix<float> m); 
	void initialize_matrix(matrix<float>& m);
	
public:
    Calculations();
    ~Calculations();
    void countAverage(const Database& database);
    float countFisher(const Database& database, size_t noOfFeatures, int dimension);
	void countSFS(const Database& database, size_t noOfFeatures, int dimension, float best, int index);
    void printAverages();

};

#endif // CALCULATIONS_H
