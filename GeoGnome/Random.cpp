#include <ctime>
#include <cstdlib>

#include "boost/random.hpp"
#include "boost/random/uniform_smallint.hpp"

#include "Random.hpp"

Random* Random::m_instance = 0;

Random & Random::instance()
{
	if (m_instance == 0)
	{
		m_instance = new Random();
	}
	return *m_instance;

}

Random::Random() :
	m_rng()
{
	//Obtain a random seed
	std::srand(std::time(NULL));
	const unsigned long seed = std::rand(); //Must be of type unsigned long!
	std::cerr << "seed = " << seed << std::endl;
    m_rng.seed(seed);
}

int Random::discrete_zero_or_one()
	{
		static boost::uniform_smallint<> zero_to_one_dist(0, 1);
		static boost::variate_generator<boost::mt19937&, boost::uniform_smallint<> > generator(m_rng, zero_to_one_dist);
		return generator();
	}

int Random::discrete_zero_to_two()
{
	static boost::uniform_smallint<> zero_to_two_dist(0, 2);
	static boost::variate_generator<boost::mt19937&, boost::uniform_smallint<> > generator(m_rng, zero_to_two_dist);
	return generator();
}

int Random::discrete_zero_to_n(int n)
{
	// @TODO: Could cache these in a map.
	boost::uniform_int<> choice_range(0, n);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > generator(m_rng, choice_range);
	return generator();
}

float Random::uniform_zero_to_one()
{
	boost::uniform_01<boost::mt19937, float> generator(m_rng);
	return generator();
}

float Random::uniform_real(float min, float max)
{
	boost::uniform_real<float> selection_distribution(min, max);
	boost::variate_generator<boost::mt19937&, boost::uniform_real<float> >generator(m_rng, selection_distribution);             // glues randomness with mapping
	return generator();
}