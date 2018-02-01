#include <typeinfo>
#include <iostream>
#include <cassert>

#include "CoordinateDimension.hpp"

//this will divide r by 1024, this gives a minimum displacement of a metre or so //2's pah!
const float CoordinateDimension::m_k = 9.0f;

float CoordinateDimension::m_r;

CoordinateDimension::CoordinateDimension() :
    Dimension(),
	m_coordinate(0.0f)
{
}

CoordinateDimension::CoordinateDimension(float displacement) :
	Dimension(),	
	m_coordinate(displacement)
{
}

CoordinateDimension::CoordinateDimension(const CoordinateDimension & other) :
	Dimension(other),
    m_coordinate(other.m_coordinate)
{
}

CoordinateDimension & CoordinateDimension::operator=(const Dimension & rhs)
{
	try
	{
		const CoordinateDimension& other_rho = dynamic_cast<const CoordinateDimension &>(rhs);
		operator=(other_rho);
	}
	catch(std::bad_cast & e)
	{
		std::cerr << e.what() << std::endl;
		assert(false && "Incorrect dimension assignment");
	}

	return *this;
}

CoordinateDimension & CoordinateDimension::operator=(const CoordinateDimension & rhs)
{
	if ( this != &rhs)
	{
		Dimension::operator=(rhs);
		this->m_coordinate = rhs.m_coordinate;
	}
	return *this;
}

CoordinateDimension* CoordinateDimension::clone() const
{
	return new CoordinateDimension(*this);
}

float CoordinateDimension::value() const
{
	return m_coordinate;
}

float& CoordinateDimension::value()
{
	return m_coordinate;
}

void CoordinateDimension::mutate()
{
	//std::cerr << "CoordinateDimension::mutate\n";
	Dimension::mutate();
    // Reflect out-of-range mutations from the range ends.
	if (m_coordinate < -200.0f)
	{
		m_coordinate =  -400.0f - m_coordinate;
	}
	if (m_coordinate > 1200.0f)
	{
		m_coordinate = 2400.0f - m_coordinate;
	}
}

float CoordinateDimension::k() const
{
	return m_k;
}

float CoordinateDimension::r() const
{
	return m_r;
}

void CoordinateDimension::r(float range)
{
	m_r = range;
}