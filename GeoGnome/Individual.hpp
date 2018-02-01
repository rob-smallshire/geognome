#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

//

#include <list>
#include <iostream>
#include "Genome.hpp"
#include "Grid2d.hpp"

class Individual
{
public:
    Individual();
    explicit Individual(int size);
	Individual(const Individual & other);
	explicit Individual(const Genome & existing_genotype) ;
	Individual & operator=(const Individual & rhs);
	void measure_fitness(const Grid2d & target_grid);
	void mutate();
	float fitness() const;
	bool operator< (const Individual & rhs) const;
	std::pair<Individual, Individual> crossover(const Individual & father);
    const Genome & genome() const;
	friend std::ostream & operator<<(std::ostream & stream, const Individual & individual);
private:
    Genome m_genotype;
	float m_fitness;
};

#endif