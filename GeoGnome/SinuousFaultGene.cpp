#include <cstdlib>
#include <iostream>
#include <cassert>
#include <cmath>

#include "utility.hpp"
#include "SinuousFaultGene.hpp"
#include "Random.hpp"
#include "CoordinateDimension.hpp"
#include "ControlAngleDimension.hpp"
#include "HeaveDimension.hpp"
#include "DepthDimension.hpp"
#include "DipDimension.hpp"

SinuousFaultGene::SinuousFaultGene() :
	Gene(),
	m_dimensions()
{
	float x0            = Random::instance().uniform_real(-200.0f, +1200.0f);
    float y0            = Random::instance().uniform_real(-200.0f, +1200.0f);
	float phi0          = Random::instance().uniform_real(-30.f, +30.0f);
	float x1            = Random::instance().uniform_real(-200.0f, +1200.0f);
    float y1            = Random::instance().uniform_real(-200.0f, +1200.0f);
	float phi1          = Random::instance().uniform_real(-30.f, +30.0f);
	float detach_depth  = Random::instance().uniform_real(0.0f, 200.0f);
	float max_heave     = Random::instance().uniform_real(0.0f, detach_depth / 2.0f);
	float dip           = Random::instance().uniform_real(20.0f, 70.0f);

	initialise(x0, y0, phi0, x1, y1, phi1, max_heave, detach_depth, dip);
}

SinuousFaultGene::SinuousFaultGene(const SinuousFaultGene & other) :
	Gene(other),
	m_dimensions()
{
	for(size_t i = 0 ; i < m_dimensions.size() ; ++i)
	{
		m_dimensions[i] = other.m_dimensions[i]->clone();
	}
}

SinuousFaultGene::SinuousFaultGene(float x0, float y0, float phi0, float x1, float y1, float phi1, float max_heave, float detach_depth, float dip) :
	Gene(),
	m_dimensions()
{
	initialise(x0, y0, phi0, x1, y1, phi1, max_heave, detach_depth, dip);
}

SinuousFaultGene & SinuousFaultGene::operator=(const SinuousFaultGene & rhs)
{
	if ( this != &rhs)
	{
		Gene::operator=(rhs);
		for(size_t i = 0 ; i < m_dimensions.size() ; ++i)
		{
			*(this->m_dimensions[i])   = *(rhs.m_dimensions[i]);
		}
	}
	return *this;
}

void SinuousFaultGene::initialise(float x0, float y0, float phi0, float x1, float y1, float phi1, float max_heave, float detach_depth, float dip)
{
	assert(phi0 >= -30.0f && phi0 <= +30.0f);
	assert(phi1 >= -30.0f && phi1 <= +30.0f);
   
    m_dimensions[m_x0_index]           = new CoordinateDimension(x0);
	m_dimensions[m_y0_index]           = new CoordinateDimension(y0);
	m_dimensions[m_phi0_index]         = new ControlAngleDimension(phi0);
	m_dimensions[m_x1_index]           = new CoordinateDimension(x1);
	m_dimensions[m_y1_index]           = new CoordinateDimension(y1);
	m_dimensions[m_phi1_index]         = new ControlAngleDimension(phi1);
	m_dimensions[m_max_heave_index]    = new HeaveDimension(max_heave);
	m_dimensions[m_detach_depth_index] = new DepthDimension(detach_depth);
	m_dimensions[m_dip_index]          = new DipDimension(dip);
}


SinuousFaultGene::~SinuousFaultGene()
{
	for(size_t i = 0; i < m_dimensions.size(); ++i)
	{
		delete m_dimensions[i];
	}
}

SinuousFaultGene * SinuousFaultGene::create() const
{
	return new SinuousFaultGene();
}

SinuousFaultGene * SinuousFaultGene::clone() const
{
	return new SinuousFaultGene(*this);
}

float SinuousFaultGene::x0() const
{
	return m_dimensions[m_x0_index]->value();
}

float SinuousFaultGene::y0() const
{
	return m_dimensions[m_y0_index]->value();
}
float SinuousFaultGene::phi0() const
{
	return m_dimensions[m_phi0_index]->value();
}

float SinuousFaultGene::x1() const
{
	return m_dimensions[m_x1_index]->value();
}

float SinuousFaultGene::y1() const
{
	return m_dimensions[m_y1_index]->value();
}
float SinuousFaultGene::phi1() const
{
	return m_dimensions[m_phi1_index]->value();
}

float SinuousFaultGene::max_heave() const
{
	return m_dimensions[m_max_heave_index]->value();
}

float SinuousFaultGene::detach_depth() const
{
	return m_dimensions[m_detach_depth_index]->value();
}

float SinuousFaultGene::dip() const
{
	return m_dimensions[m_dip_index]->value();
}

void SinuousFaultGene::express(Grid2d & grid) const
{
	grid.sinuous_displace(x0(), y0(), phi0(), x1(), y1(), phi1(), max_heave(), detach_depth(), dip());
}

void SinuousFaultGene::mutate()
{
	//pick a dimension
	int chosen_dimension = size_t(Random::instance().discrete_zero_to_n(int(m_dimensions.size()) - 1));
	m_dimensions[chosen_dimension]->mutate();
}

std::ostream & SinuousFaultGene::write(std::ostream & stream) const
{
	stream << "x0           = " << x0() << '\n';
	stream << "y0           = " << y0() << '\n';
	stream << "phi0         = " << phi0() << '\n';
	stream << "x1           = " << x1() << '\n';
	stream << "y1           = " << y1() << '\n';
	stream << "phi1         = " << phi1() << '\n';
	stream << "max_heave    = " << max_heave() << '\n';
	stream << "detach_depth = " << detach_depth() << '\n';
	stream << "dip          = " << dip() << '\n';
	return stream;
}
