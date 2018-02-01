#ifndef SINUOUSFAULTGENE_HPP
#define SINUOUSFAULTGENE_HPP

#include <iostream>
#include <cmath>

#include "Gene.hpp"
#include "Grid2d.hpp"
#include "Dimension.hpp"

/**
 *  Cubic benier faults of with a sinusoidal heave profile
 */
class SinuousFaultGene : public Gene
{
public:	
	SinuousFaultGene();
	SinuousFaultGene(float x0, float y0, float phi0, float x1, float y1, float phi1, float max_heave, float detach_depth, float dip);
	SinuousFaultGene(const SinuousFaultGene & other) ;
	SinuousFaultGene & operator=(const SinuousFaultGene & rhs);
	virtual ~SinuousFaultGene();
	virtual SinuousFaultGene * create() const;
	virtual SinuousFaultGene * clone() const;
	float x0() const;
	float y0() const;
	float phi0() const;
	float x1() const;
	float y1() const;
	float phi1() const;
	float max_heave() const;
    float detach_depth() const;
	float dip() const;
	virtual void mutate();
	virtual void express(Grid2d & grid) const;
	virtual std::ostream & write(std::ostream & stream) const;
private:
	void initialise(float x0, float y0, float phi0, float x1, float y1, float phi1 ,float heave, float depth, float dip);
	boost::array<Dimension*, 9> m_dimensions; // Stores the three dimensions
	static const size_t m_x0_index           = 0; // x position in metres
    static const size_t m_y0_index           = 1; // y position in metres
	static const size_t m_phi0_index         = 2; // control angle in degrees 
	static const size_t m_x1_index           = 3; // x position in metres
	static const size_t m_y1_index           = 4; // y position in metres
	static const size_t m_phi1_index         = 5; // control angle in degrees
	static const size_t m_max_heave_index    = 6; // heave distance in metres
	static const size_t m_detach_depth_index = 7; // depth to detechment in metres
	static const size_t m_dip_index          = 8; // surface dip in degrees
};

#endif