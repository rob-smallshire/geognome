#include <cstdlib>
#include <iostream>
#include <cassert>
#include <cmath>

#include "utility.hpp"
#include "ListricFaultGene.hpp"
#include "Random.hpp"
#include "RhoDimension.hpp"
#include "ThetaDimension.hpp"
#include "HeaveDimension.hpp"
#include "DepthDimension.hpp"
#include "DipDimension.hpp"

ListricFaultGene::ListricFaultGene() :
	Gene(),
	m_dimensions()
{
	float x      = Random::instance().uniform_real(0.0f, 1000.0f);
    float y      = Random::instance().uniform_real(0.0f, 1000.0f);
    float strike = Random::instance().uniform_real(0.0f, 360.0f);
	float depth  = Random::instance().uniform_real(0.0f, 200.0f);
	float heave  = Random::instance().uniform_real(0.0f, 50.0f);
	float dip    = Random::instance().uniform_real(20.0f, 70.0f);

	initialise(x, y, strike, heave, depth, dip);
}

ListricFaultGene::ListricFaultGene(const ListricFaultGene & other) :
	Gene(other),
	m_dimensions()
{
	for(size_t i = 0 ; i < m_dimensions.size() ; ++i)
	{
		m_dimensions[i] = other.m_dimensions[i]->clone();
	}
}

ListricFaultGene::ListricFaultGene(float x, float y, float strike, float heave, float depth, float dip) :
	Gene(),
	m_dimensions()
{
	initialise(x, y, strike, heave, depth, dip);
}

ListricFaultGene & ListricFaultGene::operator=(const ListricFaultGene & rhs)
{
	if ( this != &rhs)
	{
		Gene::operator=(rhs);
		*(this->m_dimensions[m_rho_index])   = *(rhs.m_dimensions[m_rho_index]);
		*(this->m_dimensions[m_theta_index]) = *(rhs.m_dimensions[m_theta_index]);
		*(this->m_dimensions[m_heave_index]) = *(rhs.m_dimensions[m_heave_index]);
		*(this->m_dimensions[m_depth_index]) = *(rhs.m_dimensions[m_depth_index]);
		*(this->m_dimensions[m_dip_index])   = *(rhs.m_dimensions[m_dip_index]);
	}
	return *this;
}

void ListricFaultGene::initialise(float x, float y, float strike, float heave, float depth, float dip)
{
	assert(strike >= 0.0f && strike <= 360.0f);

	// Calculating theta
	m_dimensions[m_theta_index]  = new ThetaDimension(360.0f - strike);

	// Use the normal form of the line to compute rho = x cos theta * y sin theta
	m_dimensions[m_rho_index]= new RhoDimension(x * std::cos(deg2rad(theta())) + y * std::sin(deg2rad(theta())));
	m_dimensions[m_heave_index] = new HeaveDimension(heave);
	m_dimensions[m_depth_index] = new DepthDimension(depth);
	m_dimensions[m_dip_index] = new DipDimension(dip);
}


ListricFaultGene::~ListricFaultGene()
{
	for(size_t i = 0; i < m_dimensions.size(); ++i)
	{
		delete m_dimensions[i];
	}
}

ListricFaultGene * ListricFaultGene::create() const
{
	return new ListricFaultGene();
}

ListricFaultGene * ListricFaultGene::clone() const
{
	return new ListricFaultGene(*this);
}

float ListricFaultGene::rho() const
{
	return m_dimensions[m_rho_index]->value();
}

float ListricFaultGene::theta() const
{
	return m_dimensions[m_theta_index]->value();
}

float ListricFaultGene::heave() const
{
	return m_dimensions[m_heave_index]->value();
}

float ListricFaultGene::depth() const
{
	return m_dimensions[m_depth_index]->value();
}

float ListricFaultGene::dip() const
{
	return m_dimensions[m_dip_index]->value();
}

void ListricFaultGene::express(Grid2d & grid) const
{
	grid.listric_displace(rho(), theta(), heave(), depth(), dip());
}

void ListricFaultGene::mutate()
{
	//pick a dimension
	int chosen_dimension = Random::instance().discrete_zero_to_n(m_dimensions.size() - 1);
	m_dimensions[chosen_dimension]->mutate();
}

std::ostream & ListricFaultGene::write(std::ostream & stream) const
{
	stream << "theta  = " << theta() << '\n';
	stream << "rho    = " << rho() << '\n';
	stream << "heave  = " << heave() << '\n';
	stream << "depth  = " << depth() << '\n';
	stream << "dip    = " << dip() << '\n';
	return stream;
}
