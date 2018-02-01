#ifndef RANDOM_HPP
#define RANDOM_HPP

#include "boost/random.hpp"

/**
 *  A random number generator singleton
 */
class Random
{
public:
	static Random & instance();

	int discrete_zero_or_one();
	int discrete_zero_to_two();
    int discrete_zero_to_n(int n);
	float uniform_zero_to_one();
    float uniform_real(float min, float max);
private:
	Random();
	Random(const Random & other);
	Random & operator=(const Random & rhs);

	static Random* m_instance;

	boost::mt19937 m_rng;
};

#endif