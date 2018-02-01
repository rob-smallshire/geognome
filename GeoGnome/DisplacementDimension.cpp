#include <typeinfo>
#include <iostream>
#include <cassert>

#include "DisplacementDimension.hpp"

//this will divide r by 1024, this gives a minimum displacement of a metre or so //2's pah!
const float DisplacementDimension::m_k = 9.0f;

//this is the maximum amount by which the fault displacement can change when mutated.
//this will need to change when we implement the move_fault gene, 1k of throw is 
//ridiculous for a single increment. For this phase, it is the total throw and is okay.
//const float DisplacementDimension::m_r = 1000.0f; // M1
//const float DisplacementDimension::m_r = 100.0f; // M2
//const float DisplacementDimension::m_r = 25.0f; // M3
//const float DisplacementDimension::m_r = 50.0f; // M4
float DisplacementDimension::m_r;

DisplacementDimension::DisplacementDimension() :
    Dimension(),
	m_displacement(0.0f)
{
}

DisplacementDimension::DisplacementDimension(float displacement) :
	Dimension(),	
	m_displacement(displacement)
{
}

DisplacementDimension::DisplacementDimension(const DisplacementDimension & other) :
	Dimension(other),
    m_displacement(other.m_displacement)
{
}

DisplacementDimension & DisplacementDimension::operator=(const Dimension & rhs)
{
	try
	{
		const DisplacementDimension& other_rho = dynamic_cast<const DisplacementDimension &>(rhs);
		operator=(other_rho);
	}
	catch(std::bad_cast & e)
	{
		std::cerr << e.what() << std::endl;
		assert(false && "Incorrect dimension assignment");
	}

	return *this;
}

DisplacementDimension & DisplacementDimension::operator=(const DisplacementDimension & rhs)
{
	if ( this != &rhs)
	{
		Dimension::operator=(rhs);
		this->m_displacement = rhs.m_displacement;
	}
	return *this;
}

DisplacementDimension* DisplacementDimension::clone() const
{
	return new DisplacementDimension(*this);
}

float DisplacementDimension::value() const
{
	return m_displacement;
}

float& DisplacementDimension::value()
{
	return m_displacement;
}

void DisplacementDimension::mutate()
{
	//std::cerr << "DisplacementDimension::mutate\n";
	Dimension::mutate();
}

float DisplacementDimension::k() const
{
	return m_k;
}

float DisplacementDimension::r() const
{
	return m_r;
}

void DisplacementDimension::r(float range)
{
	m_r = range;
}