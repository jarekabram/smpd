#include "calculations.h"

Calculations::Calculations()
{
    m_acerAverages.resize(64);
    m_quercusAverages.resize(64);
    m_acerObjectsCount = 0;
    m_quercusObjectsCount = 0;
}

void Calculations::countAverage(const Database& database)
{
    for(const auto& it : database.getClassCounters())
    {
        std::cout << it.first << " " << it.second << std::endl;
        if(it.first == "Acer"){
            m_acerObjectsCount = it.second;
        }
        if(it.first == "Quercus"){
            m_quercusObjectsCount = it.second;
        }
    }
    auto objects = database.getObjects();

    for(size_t i = 0; i < objects.size(); i++)
    {
        if(objects[i].getClassName() == "Acer"){
            std::vector<float> features = objects[i].getFeatures();
            for(size_t feature_counter = 0; feature_counter < features.size(); feature_counter++)
            {
                m_acerAverages[feature_counter] += features[feature_counter];
            }
        }
        if(objects[i].getClassName() == "Quercus"){
            std::vector<float> features = objects[i].getFeatures();
            for(size_t feature_counter = 0; feature_counter < features.size(); feature_counter++)
            {
                m_quercusAverages[feature_counter] += features[feature_counter];
            }
        }
    }
}

void Calculations::countMatrixOfDifferences(const Database& database)
{
    std::vector<std::vector<float>> acer_features;
    std::vector<std::vector<float>> quercus_features;

    matrix<float> acer_matrix(2, m_acerObjectsCount);
    matrix<float> acer_averages_matrix(2, m_acerObjectsCount);
    matrix<float> quercus_matrix(2, m_quercusObjectsCount);
    matrix<float> quercus_averages_matrix(2, m_quercusObjectsCount);

    std::vector<matrix<float>> acer_matrix_results;
    std::vector<matrix<float>> quercus_matrix_results;

    acer_features.resize(64);
    quercus_features.resize(64);

    auto objects = database.getObjects();
    for(int count = 0; count < 64; ++count)
    {
        for(auto object : objects)
        {
            if(object.getClassName() == "Acer"){
                auto features = object.getFeatures();
                //std::cout << count << " " << features[count] << std::endl;
                acer_features[count].emplace_back(features[count]);
            }
            if(object.getClassName() == "Quercus"){
                auto features = object.getFeatures();
                //std::cout << count << " " << features[count] << std::endl;
                quercus_features[count].emplace_back(features[count]);
            }
        }
    }

    int acer_counter = 0;
    for(int i = 0; i < 64; ++i)
    {
        for(int j = ++acer_counter; j < 64; ++j)
        {
            for(int k = 0; k < m_acerObjectsCount; k++)
            {
                acer_averages_matrix(0, k) = m_acerAverages[i];
                acer_averages_matrix(1, k) = m_acerAverages[j];
                acer_matrix(0, k) = acer_features[i][k];
                acer_matrix(1, k) = acer_features[j][k];
            }
            auto substracted_matrix = acer_matrix - acer_averages_matrix;
            auto result_matrix = prod(substracted_matrix, trans(substracted_matrix))/4;
            acer_matrix_results.emplace_back(result_matrix);
        }
    }

    int quercus_counter = 0;
    for(int i = 0; i < 64; ++i)
    {
        for(int j = ++quercus_counter; j < 64; ++j)
        {
            for(int k = 0; k < m_quercusObjectsCount; k++)
            {
                quercus_averages_matrix(0, k) = m_quercusAverages[i];
                quercus_averages_matrix(1, k) = m_quercusAverages[j];
                quercus_matrix(0, k) = quercus_features[i][k];
                quercus_matrix(1, k) = quercus_features[j][k];
            }
            auto substracted_matrix = quercus_matrix - quercus_averages_matrix;
            auto result_matrix = prod(substracted_matrix, trans(substracted_matrix))/4;
//            std::cout << result_matrix <<std::endl;
            quercus_matrix_results.emplace_back(result_matrix);
        }
    }

    std::vector<float> final_results;
    matrix<float> acer_average(1,2);
    matrix<float> quercus_average(1,2);
    int averages_counter = 0;
    int results_counter = -1;
    for(int i = 0; i < 64; ++i)
    {
        for(int j = ++averages_counter; j < 64; ++j)
        {
            ++results_counter;
            acer_average(0,0) = m_acerAverages[i];
            acer_average(0,1) = m_acerAverages[j];
            quercus_average(0,0) = m_quercusAverages[i];
            quercus_average(0,1) = m_quercusAverages[j];
            auto division = acer_average-quercus_average;
            auto distance = sqrt(pow(division(0,0), 2)+pow(division(0,1), 2));
            auto sum = acer_matrix_results[results_counter] + acer_matrix_results[results_counter];
            auto result = distance/detereminant(sum);
            final_results.emplace_back(result);
            std::cout << std::setprecision(100) << result << std::endl;
        }
    }
    auto minimum = *std::min_element(final_results.begin(), final_results.end());
    auto maximum = *std::max_element(final_results.begin(), final_results.end());
    std::cout << "minimum: " << minimum << " maximum: " << maximum << std::endl;

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

float Calculations::detereminant(matrix<float> m)
{
    return m(0,0)*m(1,1)-m(0,1)*m(1,0);
}

void Calculations::test()
{
    matrix<int> m1(2, 4);
    matrix<int> m2(2, 4);

    std::vector<std::vector<int>> v =
    {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,16}
    };

    std::vector<int> v1 = { 22, 33, 44, 55 };

    int counter = 0;
    for(int i = 0; i < 4; ++i)
    {
        for(int j = ++counter; j < 4; ++j)
        {
            for(int k = 0; k < 4; k++)
            {
                m2(0, k) = v1[i];
                m2(1, k) = v1[j];
                m1(0, k) = v[i][k];
                m1(1, k) = v[j][k];
            }
            std::cout << m1 <<std::endl;
            std::cout << m2 <<std::endl;
        }
    }
}
