
#include <iostream>
#include <cassert>
#include "boost/tuple/tuple.hpp"
#include "Individual.hpp"
#include "Genome.hpp"
#include "Grid2D.hpp"
#include "Random.hpp"


Individual::Individual() :
	m_genotype(),
	m_fitness(-1.0f)
{
	
}

Individual::Individual(int size) :
	m_genotype(size),
	m_fitness(-1.0f)
{
	
}

Individual::Individual(const Genome & existing_genotype) :
	m_genotype(existing_genotype),
	m_fitness(-1.0f)
{	
}

Individual::Individual(const Individual & other) :
	m_genotype(other.m_genotype),
	m_fitness(other.m_fitness)
{	
}

Individual & Individual::operator=(const Individual & rhs)
{
	if ( this != &rhs)
	{
		this->m_genotype = rhs.m_genotype;
		this->m_fitness = rhs.m_fitness;
	}
	return *this;
}

void Individual::mutate()
{
	m_genotype.mutate();
}

void Individual::measure_fitness(const Grid2d & target_grid)
{
	//make matching grid
	Grid2d phenotype(target_grid.num_nodes_x(), target_grid.num_nodes_y(),
		target_grid.min_x(), target_grid.min_y(), target_grid.spacing_x(), target_grid.spacing_y());
	// test perfect match - Grid2d phenotype(target_grid);
 	//express genotype
	//void express(Grid2d & grid) const;
	m_genotype.express(phenotype);
	//do comparison
	//Grid2d::comparison(const Grid2d & other_grid) const
	float rms = target_grid.comparison(phenotype);
	if (rms != 0.0f) 
	{
		m_fitness = 1.0f / rms;
	}
	else
	{
		m_fitness = std::numeric_limits<float>::max();
	}
}

float Individual::fitness() const
{
	return m_fitness;
}

bool Individual::operator< (const Individual & rhs) const
{
	return this->m_fitness < rhs.m_fitness;
}

std::pair<Individual, Individual> Individual::crossover(const Individual & father)
{
	static int c = 1;
	//std::cout << "c " <<c <<"\tmother\t" <<*this << "\t\t father\t" <<father <<"\n";
	
	
	//ask mother how long she is
	//choose random number between 0 and size
	
	Individual & mother = *this;
	
	//create thing1 and add to it mother genelist up to random_number_mum and father genelist from random_number_dad
	
	Genome thing_one_genotype(mother.m_genotype);
	Genome thing_two_genotype(father.m_genotype);

	//size_t thing_one_splice_point = 1 + (std::rand() % (thing_one_genotype.size() - 2));
	// @TODO: Check this!
	size_t thing_one_splice_point = 1 + Random::instance().discrete_zero_to_n(thing_one_genotype.size() - 3);


	//ask father how long he is
	//choose random number between 0 and size

	//size_t thing_two_splice_point = 1 + (std::rand() % (thing_two_genotype.size() - 2));
	// @TODO: Check this!
	size_t thing_two_splice_point = 1 + Random::instance().discrete_zero_to_n(thing_two_genotype.size() - 3);

	//std::cout << "c " <<c <<"\tthing_one_splice_point\t" << thing_one_splice_point << "\t\t thing_two_splice_point\t" << thing_two_splice_point <<"\n";

	//create thing2 and do inverse

	boost::tie(thing_one_genotype, thing_two_genotype) = Genome::splice(thing_one_genotype, thing_one_splice_point, thing_two_genotype, thing_two_splice_point);
	
	//patricide
	
	++c;

	return std::make_pair(Individual(thing_one_genotype), Individual(thing_two_genotype));
}

const Genome & Individual::genome() const
{
	return m_genotype;
}

std::ostream & operator<<(std::ostream & stream, const Individual & individual)
{
	stream << "fitness = " << individual.fitness();
	return stream;
}