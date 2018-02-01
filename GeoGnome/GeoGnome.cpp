// GeoGnome.cpp : Defines the entry point for the console application.

#include <iostream>
#include <cmath>
#include <fstream>
#include "boost/tuple/tuple.hpp"
#include "FaultGene.hpp"
#include "SinuousFaultGene.hpp"
#include "Genome.hpp"
#include "Grid2d.hpp"
#include "Individual.hpp"
#include "Population.hpp"
#include "RhoDimension.hpp"
#include "ThetaDimension.hpp"
#include "DisplacementDimension.hpp"
#include "DepthDimension.hpp"
#include "HeaveDimension.hpp"
#include "DipDimension.hpp"
#include "CoordinateDimension.hpp"
#include "ControlAngleDimension.hpp"

// main goes here


int main(int argc, char* argv[])
{

	// Convert the command line arguments
	//float meta_rho_range   = static_cast<float>(std::atof(argv[1]));
	//float meta_theta_range = static_cast<float>(std::atof(argv[2]));
	//float meta_disp_range  = static_cast<float>(std::atof(argv[3]));
	//float meta_breed_prop  = static_cast<float>(std::atof(argv[4]));
	//float meta_mut_rate    = static_cast<float>(std::atof(argv[5]));

	//std::cerr << "meta_rho_range   = " << meta_rho_range   << std::endl;
	//std::cerr << "meta_theta_range = " << meta_theta_range << std::endl;
	//std::cerr << "meta_disp_range  = " << meta_disp_range  << std::endl;
	//std::cerr << "meta_breed_prop  = " << meta_breed_prop  << std::endl;
	//std::cerr << "meta_mut_rate    = " << meta_mut_rate   << std::endl;

	// Straight Faults
	RhoDimension::r(500.0f);
	ThetaDimension::r(180.0f);
	DisplacementDimension::r(50.0f);

    // Listric Faults
	DepthDimension::r(100.0f);
	HeaveDimension::r(50.0f);
	DipDimension::r(45.0f);

	// Sinuous Faults
	CoordinateDimension::r(500.0f);
	ControlAngleDimension::r(15.0f);

	// GA parameters
	Population::breeding_proportion(0.6f);
	Population::mutation_rate(0.1f);

    /***********************************/

 //   Grid2d target_grid(100,100);
	//SinuousFaultGene target_genome(150.0f, 400.0f, 15.0f, 700.0f, 700.0f, 20.0f, 50.0f, 300.0f, 60.0f);
	//target_genome.express(target_grid);

	//std::cout << target_genome << std::endl;

 //   std::ofstream gridfile1("target.grd");
	//gridfile1 << target_grid << '\n';
	//gridfile1.close();

    //return 0;

    /***********************************/

	size_t NUMBER_OF_RUNS = 1;
    size_t INITIAL_GENOME_LENGTH = 30;
	size_t POPULATION_SIZE = 100;
	size_t NUMBER_OF_GENERATIONS = 200;

	float final_fitness_total = 0.0f;

    for(size_t a = 0 ; a < NUMBER_OF_RUNS ; ++a)
	{

		//std::cout << "Run = " << a << '\n';

		Grid2d target_grid(100,100);
		Genome target_genome(INITIAL_GENOME_LENGTH);
		target_genome.express(target_grid);

		std::ofstream gridfile1("target.grd");
		gridfile1 << target_grid << '\n';
		gridfile1.close();

		Population current_generation(POPULATION_SIZE, INITIAL_GENOME_LENGTH);

		Individual best_overall_individual;

        float final_fitness = 0.0f;

		for (size_t i = 0; i < NUMBER_OF_GENERATIONS ; ++i)
		{
            //float t = float(i) * 3.14159f / float(NUMBER_OF_GENERATIONS);
			//float mutation_rate = std::min( 0.01f + (std::cos(t) + 1.0f) / 2.0f, 1.0f) / 2.0f;
			//std::cout << "mutation_rate = " << mutation_rate << std::endl;
            //Population::mutation_rate(mutation_rate);

			Population next_generation(current_generation.evolve(target_grid));
			float mean_fitness = current_generation.mean_fitness();

			std::cout << "mean_fitness " << mean_fitness << ",\t";

			Individual best_of_generation = current_generation.best_individual();
			if (best_of_generation.fitness() > best_overall_individual.fitness())
			{
				best_overall_individual = best_of_generation;
			}

			current_generation = next_generation;
			final_fitness = mean_fitness; // This will be left with the final value

			std::cout << "best so far = " << best_overall_individual.fitness() << '\n';

			Grid2d evolved_grid(100,100);
			best_overall_individual.genome().express(evolved_grid);

			std::ofstream gridfile2("evolved.grd");
			gridfile2 << evolved_grid << '\n';
			gridfile2.close();
		}

        final_fitness_total += final_fitness;

		std::cout << "Winning genome " << best_overall_individual.genome() << '\n';
		std::cout << "with fitness " << best_overall_individual.fitness() << '\n';

	}

	// Compute the mean of final mean fitness over the runs
	float result = final_fitness_total / NUMBER_OF_RUNS;
	std::cout << "Mean final fitness = " << result << std::endl;

	return 0;
}






