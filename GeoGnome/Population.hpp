#ifndef POPULATION_HPP
#define POPULATION_HPP

//

#include <list>
#include <iostream>
#include "Genome.hpp"
#include "Grid2d.hpp"
#include "Individual.hpp"

class Population
{
public:
    Population();
    Population(int size, int genome_length);
	Population(const Population & other);
	Population evolve(const Grid2d & target_grid);
	Population & operator=(const Population & rhs);
	float mean_fitness() const;
	const Individual & best_individual() const;
	static void breeding_proportion(float rate);
	static void mutation_rate(float rate);
	friend std::ostream & operator<<(std::ostream & stream, const Population & population);
private:
	Population pure_truncation(const Grid2d & target_grid);
	Population pure_stochastic_universal(const Grid2d & target_grid);
	Population stochastic_universal(const Grid2d & target_grid);
	void mutate();
	void measure_fitness(const Grid2d & target_grid);
	void insert(const Individual & individual);
	std::vector<Individual> m_members;
	static float m_s_breeding_proportion;
	static float m_s_mutation_rate;
};

#endif