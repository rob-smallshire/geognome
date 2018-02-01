
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <cmath>

#include "utility.hpp"
#include "FaultGene.hpp"
#include "Random.hpp"
#include "RhoDimension.hpp"
#include "ThetaDimension.hpp"
#include "DisplacementDimension.hpp"

FaultGene::FaultGene() :
	Gene(),
	m_dimensions()
{
	float x            = Random::instance().uniform_real(0.0f, 1000.0f);
    float y            = Random::instance().uniform_real(0.0f, 1000.0f);
    float strike       = Random::instance().uniform_real(0.0f, 360.0f);
    float displacement = Random::instance().uniform_real(0.0f, 50.0f);

	initialise(x, y, strike, displacement);
}

FaultGene::FaultGene(const FaultGene & other) :
	Gene(other),
	m_dimensions()
{
	for(size_t i = 0 ; i < m_dimensions.size() ; ++i)
	{
		m_dimensions[i] = other.m_dimensions[i]->clone();
	}
}

FaultGene::FaultGene(float x, float y, float strike, float displacement) :
	Gene(),
	m_dimensions()
{
	initialise(x, y, strike, displacement);
}

FaultGene & FaultGene::operator=(const FaultGene & rhs)
{
	if ( this != &rhs)
	{
		Gene::operator=(rhs);
		*(this->m_dimensions[m_rho_index])          = *(rhs.m_dimensions[m_rho_index]);
		*(this->m_dimensions[m_theta_index])        = *(rhs.m_dimensions[m_theta_index]);
		*(this->m_dimensions[m_displacement_index]) = *(rhs.m_dimensions[m_displacement_index]);
	}
	return *this;
}

void FaultGene::initialise(float x, float y, float strike, float displacement)
{
	assert(strike >= 0.0f && strike <= 360.0f);

	m_dimensions[m_displacement_index] = new DisplacementDimension(displacement);

	// Calculating theta
	m_dimensions[m_theta_index]  = new ThetaDimension(360.0f - strike);

	// Use the normal form of the line to compute rho = x cos theta * y sin theta
	m_dimensions[m_rho_index]= new RhoDimension(x * std::cos(deg2rad(theta())) + y * std::sin(deg2rad(theta())));

}


FaultGene::~FaultGene()
{
	for(size_t i = 0; i < m_dimensions.size(); ++i)
	{
		delete m_dimensions[i];
	}
}

FaultGene * FaultGene::create() const
{
	return new FaultGene();
}

FaultGene * FaultGene::clone() const
{
	return new FaultGene(*this);
}

float FaultGene::rho() const
{
	return m_dimensions[m_rho_index]->value();
}

float FaultGene::theta() const
{
	return m_dimensions[m_theta_index]->value();
}

float FaultGene::displacement() const
{
	return m_dimensions[m_displacement_index]->value();
}

void FaultGene::express(Grid2d & grid) const
{
	grid.displace_grid(rho(), theta(), displacement());
}

void FaultGene::mutate()
{
	//pick a dimension
	int chosen_dimension = Random::instance().discrete_zero_to_two();

	//std::cerr << "chosen_dimension = " << chosen_dimension << "\n";

	m_dimensions[chosen_dimension]->mutate();
}

std::ostream & FaultGene::write(std::ostream & stream) const
{
	stream << "theta        = " << theta() << '\n';
	stream << "rho          = " << rho() << '\n';
	stream << "displacement = " << displacement() << '\n';
	return stream;
}
