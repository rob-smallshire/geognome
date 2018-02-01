#include <typeinfo>
#include <iostream>
#include <cassert>
#include <cmath>

#include "ControlAngleDimension.hpp"

//this will make minimum increment about one degree, but it is only to please Rob.
const float ControlAngleDimension::m_k = 7.49f;

//this is the maximum angle a fault trend can shif when it is mutated
//const float ControlAngleDimension::m_r = 180.0f; // M1, M4
//const float ControlAngleDimension::m_r = 18.0f; // M2,M3
float ControlAngleDimension::m_r;

ControlAngleDimension::ControlAngleDimension() :
    Dimension(),
	m_angle(0.0f)
{
}

ControlAngleDimension::ControlAngleDimension(float theta) :
	Dimension(),	
	m_angle(theta)
{
	assert(m_angle >= -30.0f && m_angle <= +30.0f);
}

ControlAngleDimension::ControlAngleDimension(const ControlAngleDimension & other) :
	Dimension(other),
    m_angle(other.m_angle)
{
}

ControlAngleDimension & ControlAngleDimension::operator=(const Dimension & rhs)
{
	try
	{
		const ControlAngleDimension& other_rho = dynamic_cast<const ControlAngleDimension &>(rhs);
		operator=(other_rho);
	}
	catch(std::bad_cast & e)
	{
		std::cerr << e.what() << std::endl;
		assert(false && "Incorrect dimension assignment");
	}

	return *this;
}

ControlAngleDimension & ControlAngleDimension::operator=(const ControlAngleDimension & rhs)
{
	if ( this != &rhs)
	{
		Dimension::operator=(rhs);
		this->m_angle = rhs.m_angle;
	}
	return *this;
}

ControlAngleDimension* ControlAngleDimension::clone() const
{
	return new ControlAngleDimension(*this);
}

float ControlAngleDimension::value() const
{
	return m_angle;
}

float& ControlAngleDimension::value()
{
	return m_angle;
}


void ControlAngleDimension::mutate()
{
	//std::cerr << "ControlAngleDimension::mutate\n";
	Dimension::mutate();
	// If the mutation takes the value out-of-range, 'reflect' of the
	// ends back into range
	if (m_angle > +30.0f) {
		m_angle = +60.0f - m_angle;
	}
	if (m_angle < -30.0f) {
		m_angle = -60.0f + m_angle;
	}
	assert(m_angle >= -30.0f && m_angle <= +30.0f);
}

float ControlAngleDimension::k() const
{
	return m_k;
}

float ControlAngleDimension::r() const
{
	return m_r;
}

void ControlAngleDimension::r(float range)
{
	m_r = range;
}
