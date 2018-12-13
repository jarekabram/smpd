#include <QDebug>
#include "calculations.h"

Calculations::Calculations()
{

    m_acerObjectsCount = 0;
    m_quercusObjectsCount = 0;
}
Calculations::~Calculations()
{
    m_acerAverages.clear();
    m_quercusAverages.clear();
    m_acerObjectsCount = 0;
    m_quercusObjectsCount = 0;
}

void Calculations::countAverage(const Database& database)
{
    for(const auto& it : database.getClassCounters())
    {
        std::cout << it.first << " " << it.second << std::endl;
        if(it.first == "Acer"){
            m_acerObjectsCount = static_cast<size_t>(it.second);
        }
        if(it.first == "Quercus"){
            m_quercusObjectsCount = static_cast<size_t>(it.second);
        }
    }
    auto objects = database.getObjects();

    std::vector<std::vector<float>> acer_features;
    std::vector<std::vector<float>> quercus_features;

    size_t acer_count = 0;
    size_t quercus_count = 0;
    for(size_t i = 0; i < objects.size(); i++)
    {
        if(objects[i].getClassName() == "Acer"){
            acer_features.emplace_back(objects[i].getFeatures());
            acer_count = objects[i].getFeatures().size();
        }
        if(objects[i].getClassName() == "Quercus"){
            quercus_features.emplace_back(objects[i].getFeatures());
            quercus_count = objects[i].getFeatures().size();
        }
    }
    float temp;
    for(size_t i = 0; i < acer_count; ++i)
    {
        temp = 0;
        for(size_t j = 0; j < m_acerObjectsCount; ++j)
        {
                temp += acer_features[j][i];
        }
        temp /= m_acerObjectsCount;
        m_acerAverages.emplace_back(temp);
    }
    for(size_t i = 0; i < quercus_count; ++i)
    {
        temp = 0;
        for(size_t j = 0; j < m_quercusObjectsCount; ++j)
        {
                temp += quercus_features[j][i];
        }
        temp /= m_quercusObjectsCount;
        m_quercusAverages.emplace_back(temp);
    }
}

std::vector<std::vector<int>> Calculations::combine(int n, int k) {
	std::vector<std::vector<int>> v;
	int i = 0;
	std::vector<int> p(k, 0);
	while (i >= 0) {
		p[i]++;
		if (p[i] > n) --i;
		else if (i == k - 1) 
			v.emplace_back(p);
		else {
			++i;
			p[i] = p[i - 1];
		}
	}
	return v;
}

float Calculations::countMatrixOfDifferences(const Database& database, size_t noOfFeatures, int dimension)
{
    std::vector<std::vector<float>> acer_features;
    std::vector<std::vector<float>> quercus_features;

	matrix<float> acer_averages_matrix(noOfFeatures, m_acerObjectsCount);
	matrix<float> quercus_averages_matrix(noOfFeatures, m_quercusObjectsCount);
	
	std::vector<float> fisher_results;

    acer_features.resize(noOfFeatures);
    quercus_features.resize(noOfFeatures);

    auto objects = database.getObjects();
    for(size_t count = 0; count < noOfFeatures; ++count)
    {
        for(auto object : objects)
        {
            if(object.getClassName() == "Acer"){
                auto features = object.getFeatures();
                acer_features[count].emplace_back(features[count]);
            }
            if(object.getClassName() == "Quercus"){
                auto features = object.getFeatures();
                quercus_features[count].emplace_back(features[count]);
            }
        }
    }

    for(size_t i = 0; i < noOfFeatures; ++i)
    {
        for(size_t j = 0; j < m_acerObjectsCount; j++)
        {
			acer_averages_matrix(i, j) = acer_features[i][j] - m_acerAverages[i];
        }
    }
	for (size_t i = 0; i < noOfFeatures; ++i)
	{
		for (size_t j = 0; j < m_quercusObjectsCount; j++)
		{
			quercus_averages_matrix(i, j) = quercus_features[i][j] - m_quercusAverages[i];
		}
	}

	auto combinations = combine(noOfFeatures, dimension);

	matrix<float> acer_temp(dimension, m_acerObjectsCount);
	matrix<float> quercus_temp(dimension, m_quercusObjectsCount);
	matrix<float> total_averages(dimension, 1);
	
	initialize_matrix(total_averages);
	int objects_counter;
	for (size_t i = 0; i < combinations.size(); ++i)
	{
		objects_counter = 0;
		for (size_t j = 0; j < combinations[i].size(); ++j) 
		{
			total_averages(j, 0) = m_acerAverages[j];
			total_averages(j, 0) -= m_quercusAverages[j];
			for (size_t count = 0; count < m_acerObjectsCount; ++count) 
			{
				acer_temp(objects_counter, count) = acer_averages_matrix(j, count);
			}
			for (size_t count = 0; count < m_quercusObjectsCount; ++count)
			{
				quercus_temp(objects_counter, count) = quercus_averages_matrix(j, count);
			}
			++objects_counter;
		}

		auto acer_transposed = boost::numeric::ublas::trans(acer_temp);
		auto acer_mult = prod(acer_temp, acer_transposed);
		matrix<float> acer_div = acer_mult / noOfFeatures;
		auto acer_det = ::determinant<float>(acer_div);

		auto quercus_transposed = boost::numeric::ublas::trans(acer_temp);
		auto quercus_mult = prod(acer_temp, acer_transposed);
		matrix<float> quercus_div = acer_mult / noOfFeatures;
		auto quercus_det = ::determinant<float>(acer_div);

		auto dis = distance(total_averages);
		auto det_div = acer_det;
		det_div += quercus_det;
		auto fisher = dis / det_div;
		fisher_results.emplace_back(fisher);
	}
	auto maximum = std::max_element(fisher_results.begin(), fisher_results.end());
	
    return *maximum;
}

void Calculations::printAverages()
{
    std::cout << "Acer" << "\t\t" << "Quercus" << std::endl;
    for(size_t elem = 0; elem < m_acerAverages.size(); elem++)
    {
        m_acerAverages[elem] /= m_acerObjectsCount;
        m_quercusAverages[elem] /= m_quercusObjectsCount;
        std::cout << m_acerAverages[elem] << "\t" << m_quercusAverages[elem] << std::endl;
    }
}

int factorial(int value)
{
	int result = 1;

	for (int i = 1; i <= value; i++)
	{
		result *= i;
	}

	return result;
}

float Calculations::distance(matrix<float> m)
{
	float temp = 0;
	for (int i = 0; i < m.size1(); ++i)
	{
		float temp1 = m(i, 0);
		temp += (temp1*temp1);
	}

	return sqrt(temp);
}
void Calculations::initialize_matrix(matrix<float>& m)
{
	for (int i = 0; i < m.size1(); ++i)
	{
		for (int j = 0; j < m.size2(); ++j) 
		{
			m(i, j) = 0;
		}
	}
}
void Calculations::print_matrix(matrix<float> m)
{
	for (int i = 0; i < m.size1(); ++i) 
	{
		for (int j = 0; j < m.size2(); ++j) 
		{
			qInfo() << m(i, j);
		}
		qInfo() << "\n";
	}
}
