#ifndef LISTRICFAULTGENE_HPP
#define LISTRICFAULTGENE_HPP

#include <iostream>
#include <cmath>

#include "Gene.hpp"
#include "Grid2d.hpp"
#include "Dimension.hpp"

/**
 *  Straight faults of infinite extent
 */
class ListricFaultGene : public Gene
{
public:	
	ListricFaultGene();
	ListricFaultGene(float x, float y, float strike, float heave, float depth, float dip);
	ListricFaultGene(const ListricFaultGene & other) ;
	ListricFaultGene & operator=(const ListricFaultGene & rhs);
	virtual ~ListricFaultGene();
	virtual ListricFaultGene * create() const;
	virtual ListricFaultGene * clone() const;
	float rho() const;
	float theta() const;
	float heave() const;
    float depth() const;
	float dip() const;
	virtual void mutate();
	virtual void express(Grid2d & grid) const;
	virtual std::ostream & write(std::ostream & stream) const;
private:
	void initialise(float x, float y, float strike, float heave, float depth, float dip);
	boost::array<Dimension*, 5> m_dimensions; // Stores the three dimensions
	static const size_t m_rho_index          = 0; // distance from origin in metres
	static const size_t m_theta_index        = 1; // angle in degrees from origin
	static const size_t m_heave_index        = 2; // heave distance in metres
	static const size_t m_depth_index        = 3; // depth to detechment in metres
	static const size_t m_dip_index          = 4; // surface dip in degrees
};

#endif