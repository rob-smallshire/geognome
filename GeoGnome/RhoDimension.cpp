#include <typeinfo>
#include <iostream>
#include <cassert>

#include "RhoDimension.hpp"

//this will divide r by 512 //2's pah!
const float RhoDimension::m_k = 9.0f;

//this is the maximum distance a fault can shift by when its location is mutated.
//this will have to change for real to become the maximum dimension of the model.
//const float RhoDimension::m_r = 1000.0f; // M1
//const float RhoDimension::m_r = 100.0f;  // M2,M3,M4
float RhoDimension::m_r;

RhoDimension::RhoDimension() :
    Dimension(),
	m_rho(0.0f)
{
}

RhoDimension::RhoDimension(float rho) :
	Dimension(),	
	m_rho(rho)
{
}

RhoDimension::RhoDimension(const RhoDimension & other) :
	Dimension(other),
    m_rho(other.m_rho)
{
}

RhoDimension & RhoDimension::operator=(const Dimension & rhs)
{
	try
	{
		const RhoDimension& other_rho = dynamic_cast<const RhoDimension &>(rhs);
		operator=(other_rho);
	}
	catch(std::bad_cast & e)
	{
		std::cerr << e.what() << std::endl;
		assert(false && "Incorrect dimension assignment");
	}

	return *this;
}

RhoDimension & RhoDimension::operator=(const RhoDimension & rhs)
{
	if ( this != &rhs)
	{
		Dimension::operator=(rhs);
		this->m_rho = rhs.m_rho;
	}
	return *this;
}

RhoDimension* RhoDimension::clone() const
{
	return new RhoDimension(*this);
}

float RhoDimension::value() const
{
	return m_rho;
}

float& RhoDimension::value()
{
	return m_rho;
}

void RhoDimension::mutate()
{
	//std::cerr << "RhoDimension::mutate\n";
	//float before = m_rho;
	Dimension::mutate();
	//float diff = m_rho - before;
	//std::cout << "m_rho delta = " << diff << '\n';
}

float RhoDimension::k() const
{
	return m_k;
}

float RhoDimension::r() const
{
	return m_r;
}

void RhoDimension::r(float range)
{
	m_r = range;
}
