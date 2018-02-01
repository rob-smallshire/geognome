#include <typeinfo>
#include <iostream>
#include <cassert>
#include <cmath>

#include "DipDimension.hpp"

//this will make minimum increment about one degree, but it is only to please Rob.
const float DipDimension::m_k = 7.49f;

//this is the maximum angle a fault can shift by when its orientation is mutated.
//this will not need to change.
//const float DipDimension::m_r = 180.0f; // M1, M4
//const float DipDimension::m_r = 18.0f; // M2,M3
float DipDimension::m_r;

DipDimension::DipDimension() :
    Dimension(),
	m_dip(0.0f)
{
}

DipDimension::DipDimension(float theta) :
	Dimension(),	
	m_dip(theta)
{
	assert(m_dip >= 0.0f && m_dip <= 90.0f);
}

DipDimension::DipDimension(const DipDimension & other) :
	Dimension(other),
    m_dip(other.m_dip)
{
}

DipDimension & DipDimension::operator=(const Dimension & rhs)
{
	try
	{
		const DipDimension& other_rho = dynamic_cast<const DipDimension &>(rhs);
		operator=(other_rho);
	}
	catch(std::bad_cast & e)
	{
		std::cerr << e.what() << std::endl;
		assert(false && "Incorrect dimension assignment");
	}

	return *this;
}

DipDimension & DipDimension::operator=(const DipDimension & rhs)
{
	if ( this != &rhs)
	{
		Dimension::operator=(rhs);
		this->m_dip = rhs.m_dip;
	}
	return *this;
}

DipDimension* DipDimension::clone() const
{
	return new DipDimension(*this);
}

float DipDimension::value() const
{
	return m_dip;
}

float& DipDimension::value()
{
	return m_dip;
}


void DipDimension::mutate()
{
	//std::cerr << "DipDimension::mutate\n";
	Dimension::mutate();
	// If the mutation takes the value out-of-range, 'reflect' of the
	// ends back into range
	if (m_dip > 90.0f) {
		m_dip = 180.0f - m_dip;
	}
	if (m_dip < 0.0f) {
		m_dip = -m_dip;
	}
	assert(m_dip >= 0.0f && m_dip <= 90.0f);
}

float DipDimension::k() const
{
	return m_k;
}

float DipDimension::r() const
{
	return m_r;
}

void DipDimension::r(float range)
{
	m_r = range;
}
