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

float Calculations::countFisher(const Database& database, size_t noOfFeatures, int dimension)
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
			total_averages(j, 0) = m_acerAverages[combinations[i][j] - 1];
			total_averages(j, 0) -= m_quercusAverages[combinations[i][j] - 1];

			qInfo() << combinations[i][j];
			for (size_t count = 0; count < m_acerObjectsCount; ++count) 
			{
				acer_temp(objects_counter, count) = acer_averages_matrix(combinations[i][j]-1, count);
			}
			for (size_t count = 0; count < m_quercusObjectsCount; ++count)
			{
				quercus_temp(objects_counter, count) = quercus_averages_matrix(combinations[i][j]-1, count);
			}
			++objects_counter;

		}
		auto acer_transposed = boost::numeric::ublas::trans(acer_temp);
		auto acer_mult = prod(acer_temp, acer_transposed);
		matrix<float> acer_div = acer_mult / noOfFeatures;
		print_matrix(acer_div);
		float acer_det = ::determinant<float>(acer_div);
		qDebug() << "acer_det: " << acer_det;

		auto quercus_transposed = boost::numeric::ublas::trans(quercus_temp);
		auto quercus_mult = prod(quercus_temp, quercus_transposed);
		matrix<float> quercus_div = quercus_mult / noOfFeatures;
		print_matrix(quercus_div);
		float quercus_det = ::determinant<float>(quercus_div);

		auto dis = distance(total_averages);
		float det_div = acer_det;
		det_div += quercus_det;
		auto fisher = dis / det_div;
		fisher_results.emplace_back(fisher);
		qDebug() << "fisher: " << fisher;
	}
	auto maximum = std::max_element(fisher_results.begin(), fisher_results.end());
	
    return *maximum;
}

void Calculations::countSFS(const Database& database, size_t noOfFeatures, int dimension, float best, int index)
{
	std::vector<std::vector<float>> acer_features;
	std::vector<std::vector<float>> quercus_features;

	acer_features.resize(noOfFeatures);
	quercus_features.resize(noOfFeatures);

	auto objects = database.getObjects();
	for (int count = 0; count < noOfFeatures; ++count)
	{
		for (auto object : objects)
		{
			if (object.getClassName() == "Acer") {
				auto features = object.getFeatures();
				acer_features[count].emplace_back(features[count]);
			}
			if (object.getClassName() == "Quercus") {
				auto features = object.getFeatures();
				quercus_features[count].emplace_back(features[count]);
			}
		}
	}

	std::vector<float> acer_averages;
	std::vector<float> acer_stds;
	std::vector<float> quercus_averages;
	std::vector<float> quercus_stds;
	std::vector<float> fishers;

	acer_averages.resize(noOfFeatures);
	acer_stds.resize(noOfFeatures);
	quercus_averages.resize(noOfFeatures);
	quercus_stds.resize(noOfFeatures);

	for (int dim = 0; dim < dimension; ++dim) 
	{
		for (int i = 0; i < acer_features.size(); ++i)
		{
			for (int j = 0; j < m_acerObjectsCount; ++j)
			{
				acer_averages[i] += acer_features[i][j];
				acer_stds[i] += acer_features[i][j] * acer_features[i][j];
			}
			for (int j = 0; j < m_quercusObjectsCount; ++j)
			{
				quercus_averages[i] += quercus_features[i][j];
				quercus_stds[i] += quercus_features[i][j] * quercus_features[i][j];
			}
			acer_averages[i] /= m_acerObjectsCount;
			acer_stds[i] = std::sqrt(acer_stds[i] / m_acerObjectsCount - acer_averages[i] * acer_averages[i]);
			quercus_averages[i] /= m_quercusObjectsCount;
			quercus_stds[i] = std::sqrt(quercus_stds[i] / m_quercusObjectsCount - quercus_averages[i] * quercus_averages[i]);
			auto fisher = std::abs(acer_averages[i] - quercus_averages[i]) / (acer_stds[i] + quercus_stds[i]);
			fishers.emplace_back(fisher);
		}
		auto max = std::max_element(fishers.begin(), fishers.end());
		auto index = std::distance(fishers.begin(), max);
		qInfo() << "max: " << *max << " index: " << index;
		acer_features.erase(acer_features.begin()+index);
		

	}
}
float Calculations::detereminant(matrix<float> m)
{
	return m(0, 0)*m(1, 1) - m(0, 1)*m(1, 0);
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

float Calculations::distance(matrix<float> m)
{
	float temp = 0;
	for (int i = 0; i < m.size1(); ++i)
	{
		qDebug() << m(i, 0);
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
			qDebug() << m(i, j) << " ";
		}
		qDebug() << "\n";
	}
}
