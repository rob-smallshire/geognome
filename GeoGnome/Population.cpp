#include <vector>
#include <algorithm>
#include <iostream>
#include "boost/tuple/tuple.hpp"
#include "Random.hpp"
#include "Genome.hpp"
#include "Individual.hpp"
#include "Population.hpp"

Population::Population() :
    m_members()
{
}

Population::Population(int size, int genome_length) :
    m_members()
{
    for(int i = 0; i < size ; ++i)
    {
        m_members.push_back(Individual(genome_length));
    }
}

Population::Population(const Population & other) :
    m_members(other.m_members)
{
}

Population & Population::operator=(const Population & rhs)
{
	if ( this != &rhs)
	{
		this->m_members = rhs.m_members;
	}
	return *this;
}


void Population::measure_fitness(const Grid2d & target_grid)
{
    for(size_t i = 0; i < m_members.size() ; ++i)
    {
        m_members[i].measure_fitness(target_grid);
    }

	std::sort(m_members.begin(), m_members.end());
}

float Population::mean_fitness() const
{
	float mean_fitness = 0.0f;
	for(size_t i = 0; i < m_members.size() ; ++i)
    {
        mean_fitness += m_members[i].fitness();
    }
	mean_fitness /= m_members.size();
	
	return mean_fitness;
}

const Individual & Population::best_individual() const
{
	size_t best_index = 0;
	float best_fitness = 0.0f;
    for(size_t i = 0; i < m_members.size() ; ++i)
    {
		if (m_members[i].fitness() > best_fitness)
		{
			best_fitness = m_members[i].fitness();
			best_index = i;
		}
	}
	return m_members[best_index];
}

Population Population::evolve(const Grid2d & target_grid)
{
	//Population next_generation = pure_truncation(target_grid);
	Population next_generation = stochastic_universal(target_grid);
    next_generation.mutate();
	return next_generation;
}

Population Population::pure_truncation(const Grid2d & target_grid)
{
	Population next_generation;
	// measure fitness
	measure_fitness(target_grid);
	
	// reverse the list
	
	std::reverse(m_members.begin(), m_members.end());
	
	// take first half of fitness list

	std::vector<Individual>::iterator median = m_members.begin();	
	assert (m_members.size() % 2 == 0);
	std::advance(median, m_members.size() / 2 );

	// randomise list

	std::random_shuffle(m_members.begin(), median);

	// combine partners

	std::vector<Individual>::iterator p = m_members.begin();	
	std::vector<Individual>::reverse_iterator q(median);	
	while (p != median)
	{
		//   randomly selection crossover point
		//   recombine genomes of partners onto new individuals
		//   store in new population

		Individual thing_one;
		Individual thing_two;
		boost::tie(thing_one, thing_two) = (*p).crossover(*q);
		next_generation.insert(thing_one);
		next_generation.insert(thing_two);

		// select next victim		

		++p;
		++q;
	}
	return next_generation;
}

Population Population::pure_stochastic_universal(const Grid2d & target_grid)
{
	// measure fitness
	measure_fitness(target_grid);
	
	// reverse the list
	// make contiguous list of fitnesses
	
	std::reverse(m_members.begin(), m_members.end());

	//1. first way of storing breeding potential. This way is a part of an individual and that is bad.

	//m_members[0].breed_potential = 0.0f;
	//float max_breed_potential = 0.0f;
    //for(size_t i = 0; i < m_members.size() ; ++i)
    //{
    //    m_members[i].breed_potential += m_members[i].fitness;
	//	max_breed_potential = m_members[i].breed_potential;
    //}

	//2. alternative way of storing breeding potential. This one is local to this algorithm.
	// select increment between selected individuals

	std::vector<float> breed_potential(m_members.size());

	breed_potential[0] = m_members[0].fitness();
    for(size_t i = 1; i < m_members.size() ; ++i)
    {
        breed_potential[i] = breed_potential[i-1] + m_members[i].fitness();
		//std::cout << "m_members[" << i << "].fitness() = " << m_members[i].fitness() << ", breed_potential[" << i << "] = " << breed_potential[i] << '\n';
    }
	size_t breed_pop_size = m_members.size();
	float selector_increment = breed_potential.back() / breed_pop_size;

	// select starting point, randomly within range 0 to length of list/number of new individuals
	float individual_selector = Random::instance().uniform_real(0.0001f, selector_increment);        // simulate rolling a die
	//std::cout << "selector_increment = " << selector_increment << '\n';
	//std::cout << "individual_selector = " << individual_selector << '\n';

	//select individuals pointed to by the pointers and add them to a population called breeding_stock
	// combine partners from population called breeding_stock
	std::vector<size_t> breeding_stock;
	size_t i = 0;
	while (i < m_members.size())
	{
		if (individual_selector < breed_potential[i]) 
		{
			breeding_stock.push_back(i);
			//std::cout << i << " ";
			individual_selector += selector_increment;
		}
		else 
		{
			++i;
		}
	}
	//std::cout <<"\n breeding stock population size " << breeding_stock.size() << '\n';
	assert (breeding_stock.size() == breed_pop_size);
	//std::cout <<"breed potential " << breed_potential.back() <<'\n';

	// randomise list

	std::random_shuffle(breeding_stock.begin(), breeding_stock.end());

	//set up list counters and next generation population

	std::vector<size_t>::iterator p = breeding_stock.begin();	
	std::vector<size_t>::reverse_iterator q = breeding_stock.rbegin();
	std::vector<size_t>::iterator p_end = p;
	size_t end_limit = (breeding_stock.size() % 2) == 1 ? ((breeding_stock.size() / 2) + 1) : (breeding_stock.size() / 2);
	std::advance(p_end, end_limit);
	Population new_generation;
	while (p != p_end)
	{
		//   randomly selection crossover point
		//   recombine genomes of partners onto new individuals
		//   store in new population

		Individual thing_one;
		Individual thing_two;
		boost::tie(thing_one, thing_two) = m_members[*p].crossover(m_members[*q]);
		new_generation.insert(thing_one);
		new_generation.insert(thing_two);

		// select next victim		

		++p;
		++q;
	}
	return new_generation;
}


Population Population::stochastic_universal(const Grid2d & target_grid)
{
	// measure fitness
	measure_fitness(target_grid);
	
	// reverse the list
	// make contiguous list of fitnesses
	
	std::reverse(m_members.begin(), m_members.end());

	//1. first way of storing breeding potential. This way is a part of an individual and that is bad.

	//m_members[0].breed_potential = 0.0f;
	//float max_breed_potential = 0.0f;
    //for(size_t i = 0; i < m_members.size() ; ++i)
    //{
    //    m_members[i].breed_potential += m_members[i].fitness;
	//	max_breed_potential = m_members[i].breed_potential;
    //}

	//2. alternative way of storing breeding potential. This one is local to this algorithm.
	// select increment between selected individuals

	std::vector<float> breed_potential(m_members.size());

	breed_potential[0] = m_members[0].fitness();
    for(size_t i = 1; i < m_members.size() ; ++i)
    {
        breed_potential[i] = breed_potential[i-1] + m_members[i].fitness();
		//std::cout << "m_members[" << i << "].fitness() = " << m_members[i].fitness() << ", breed_potential[" << i << "] = " << breed_potential[i] << '\n';
    }

	Population new_generation;

	//size_t breed_pop_size = m_members.size() * 3 / 4;
	size_t breed_pop_size = static_cast<size_t>(std::floor(m_members.size() * m_s_breeding_proportion));

    if (breed_pop_size > 0)
	{

		float selector_increment = breed_potential.back() / breed_pop_size;

		// select starting point, randomly within range 0 to length of list/number of new individuals
		float individual_selector = Random::instance().uniform_real(0.0001f, selector_increment);        // simulate rolling a die
		//std::cout << "selector_increment = " << selector_increment << '\n';
		//std::cout << "individual_selector = " << individual_selector << '\n';

		//select individuals pointed to by the pointers and add them to a population called breeding_stock
		// combine partners from population called breeding_stock
		std::vector<size_t> breeding_stock;
		size_t i = 0;
		while (i < m_members.size())
		{
			if (individual_selector < breed_potential[i]) 
			{
				breeding_stock.push_back(i);
				//std::cout << i << " ";
				individual_selector += selector_increment;
			}
			else 
			{
				++i;
			}
		}
		//std::cout <<"\n breeding stock population size " << breeding_stock.size() << '\n';
		assert (breeding_stock.size() == breed_pop_size);
		//std::cout <<"breed potential " << breed_potential.back() <<'\n';

		// randomise list

		std::vector<size_t> ranked_stock(breeding_stock);

		std::random_shuffle(breeding_stock.begin(), breeding_stock.end());

		//set up list counters and next generation population

		std::vector<size_t>::iterator p = breeding_stock.begin();	
		std::vector<size_t>::reverse_iterator q = breeding_stock.rbegin();
		std::vector<size_t>::iterator p_end = p;
		size_t end_limit = (breeding_stock.size() % 2) == 1 ? ((breeding_stock.size() / 2) + 1) : (breeding_stock.size() / 2);
		std::advance(p_end, end_limit);
		
		while (p != p_end)
		{
			//   randomly selection crossover point
			//   recombine genomes of partners onto new individuals
			//   store in new population

			Individual thing_one;
			Individual thing_two;
			boost::tie(thing_one, thing_two) = m_members[*p].crossover(m_members[*q]);
			new_generation.insert(thing_one);
			new_generation.insert(thing_two);

			// select next victim		

			++p;
			++q;
		}
	}

	// Make copies of the best remaining individuals from the previous generation
	// to make up the remainder of the population
	std::vector<Individual>::iterator r = m_members.begin();
	while(new_generation.m_members.size() < m_members.size())
	{
		new_generation.insert(*r);
		++r;
	}

	return new_generation;
}

// Breeding proportion, the proportion of the population use for breeding
float Population::m_s_breeding_proportion = 1.0f;

void Population::breeding_proportion(float proportion)
{
	m_s_breeding_proportion = proportion;
}

// Mutation rate == 0.0f ==> no mutation
float Population::m_s_mutation_rate = 0.0f;

void Population::mutation_rate(float rate)
{
	m_s_mutation_rate = rate;
}

void Population::mutate()
{
	std::vector<Individual>::iterator p = m_members.begin();
	while (p != m_members.end())
	{
		float u = Random::instance().uniform_zero_to_one();
		if (u > (1.0f - m_s_mutation_rate))
		{
			(*p).mutate();
		}
		++p;
	}
	
}

void Population::insert(const Individual & individual)
{
	m_members.push_back(individual);
}

std::ostream & operator<<(std::ostream & stream, const Population & population)
{
	stream << "START POPULATION \n";
	
	std::vector<Individual>::const_iterator p = population.m_members.begin();
	while (p != population.m_members.end())
	{
		stream << *p << '\n';
		++p;
	}
	stream << "END POPULATION \n";
	return stream;
}