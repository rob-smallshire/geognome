#ifndef FAULTGENE_HPP
#define FAULTGENE_HPP

// making an object that represents a fault event or gene
// this will be a class, a type of object
// it will contain location of fault centre, direction of fault strike and displacement value

#include <iostream>
#include <cmath>

#include "Gene.hpp"
#include "Grid2d.hpp"
#include "Dimension.hpp"

/**
 *  Straight faults of infinite extent
 */
class FaultGene : public Gene
{
public:	
	FaultGene();
	FaultGene(float x, float y, float strike, float displacement);
	FaultGene(const FaultGene & other) ;
	FaultGene & operator=(const FaultGene & rhs);
	virtual ~FaultGene();
	virtual FaultGene * create() const;
	virtual FaultGene * clone() const;
	float rho() const;
	float theta() const;
	float displacement() const;
	virtual void mutate();
	virtual void express(Grid2d & grid) const;
	virtual std::ostream & write(std::ostream & stream) const;
private:
	void initialise(float x, float y, float strike, float displacement);
	boost::array<Dimension*, 3> m_dimensions; // Stores the three dimensions
	static const size_t m_rho_index          = 0; // distance from origin in metres
	static const size_t m_theta_index        = 1; // angle in degrees from origin
	static const size_t m_displacement_index = 2; // displacement in metres
};

#endif



