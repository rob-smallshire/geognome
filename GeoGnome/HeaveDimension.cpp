#include <typeinfo>
#include <iostream>
#include <cassert>

#include "HeaveDimension.hpp"

//this will divide r by 1024, this gives a minimum displacement of a metre or so //2's pah!
const float HeaveDimension::m_k = 9.0f;

//const float HeaveDimension::m_r = 50.0f; // M4
float HeaveDimension::m_r;

HeaveDimension::HeaveDimension() :
    Dimension(),
	m_heave(0.0f)
{
}

HeaveDimension::HeaveDimension(float displacement) :
	Dimension(),	
	m_heave(displacement)
{
}

HeaveDimension::HeaveDimension(const HeaveDimension & other) :
	Dimension(other),
    m_heave(other.m_heave)
{
}

HeaveDimension & HeaveDimension::operator=(const Dimension & rhs)
{
	try
	{
		const HeaveDimension& other_rho = dynamic_cast<const HeaveDimension &>(rhs);
		operator=(other_rho);
	}
	catch(std::bad_cast & e)
	{
		std::cerr << e.what() << std::endl;
		assert(false && "Incorrect dimension assignment");
	}

	return *this;
}

HeaveDimension & HeaveDimension::operator=(const HeaveDimension & rhs)
{
	if ( this != &rhs)
	{
		Dimension::operator=(rhs);
		this->m_heave = rhs.m_heave;
	}
	return *this;
}

HeaveDimension* HeaveDimension::clone() const
{
	return new HeaveDimension(*this);
}

float HeaveDimension::value() const
{
	return m_heave;
}

float& HeaveDimension::value()
{
	return m_heave;
}

void HeaveDimension::mutate()
{
	//std::cerr << "HeaveDimension::mutate\n";
	Dimension::mutate();
}

float HeaveDimension::k() const
{
	return m_k;
}

float HeaveDimension::r() const
{
	return m_r;
}

void HeaveDimension::r(float range)
{
	m_r = range;
}