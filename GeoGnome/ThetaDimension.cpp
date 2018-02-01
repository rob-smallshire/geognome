#include <typeinfo>
#include <iostream>
#include <cassert>
#include <cmath>

#include "ThetaDimension.hpp"

//this will make minimum increment about one degree, but it is only to please Rob.
const float ThetaDimension::m_k = 7.49f;

//this is the maximum angle a fault can shift by when its orientation is mutated.
//this will not need to change.
//const float ThetaDimension::m_r = 180.0f; // M1, M4
//const float ThetaDimension::m_r = 18.0f; // M2,M3
float ThetaDimension::m_r;

ThetaDimension::ThetaDimension() :
    Dimension(),
	m_theta(0.0f)
{
}

ThetaDimension::ThetaDimension(float theta) :
	Dimension(),	
	m_theta(theta)
{
	assert(m_theta >= 0.0f && m_theta <= 360.0f);
}

ThetaDimension::ThetaDimension(const ThetaDimension & other) :
	Dimension(other),
    m_theta(other.m_theta)
{
}

ThetaDimension & ThetaDimension::operator=(const Dimension & rhs)
{
	try
	{
		const ThetaDimension& other_rho = dynamic_cast<const ThetaDimension &>(rhs);
		operator=(other_rho);
	}
	catch(std::bad_cast & e)
	{
		std::cerr << e.what() << std::endl;
		assert(false && "Incorrect dimension assignment");
	}

	return *this;
}

ThetaDimension & ThetaDimension::operator=(const ThetaDimension & rhs)
{
	if ( this != &rhs)
	{
		Dimension::operator=(rhs);
		this->m_theta = rhs.m_theta;
	}
	return *this;
}

ThetaDimension* ThetaDimension::clone() const
{
	return new ThetaDimension(*this);
}

float ThetaDimension::value() const
{
	return m_theta;
}

float& ThetaDimension::value()
{
	return m_theta;
}


void ThetaDimension::mutate()
{
	//std::cerr << "ThetaDimension::mutate\n";
	Dimension::mutate();
	m_theta = std::fmod (m_theta, 360.0f);
}

float ThetaDimension::k() const
{
	return m_k;
}

float ThetaDimension::r() const
{
	return m_r;
}

void ThetaDimension::r(float range)
{
	m_r = range;
}
