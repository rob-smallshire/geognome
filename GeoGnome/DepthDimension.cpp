#include <typeinfo>
#include <iostream>
#include <cassert>

#include "DepthDimension.hpp"

//this will divide r by 1024, this gives a minimum displacement of a metre or so //2's pah!
const float DepthDimension::m_k = 9.0f;

//this is the maximum amount by which the fault displacement can change when mutated.
//this will need to change when we implement the move_fault gene, 1k of throw is 
//ridiculous for a single increment. For this phase, it is the total throw and is okay.
//const float DepthDimension::m_r = 1000.0f; // M1
//const float DepthDimension::m_r = 100.0f; // M2
//const float DepthDimension::m_r = 25.0f; // M3
//const float DepthDimension::m_r = 50.0f; // M4
float DepthDimension::m_r;

DepthDimension::DepthDimension() :
    Dimension(),
	m_depth(0.0f)
{
}

DepthDimension::DepthDimension(float displacement) :
	Dimension(),	
	m_depth(displacement)
{
}

DepthDimension::DepthDimension(const DepthDimension & other) :
	Dimension(other),
    m_depth(other.m_depth)
{
}

DepthDimension & DepthDimension::operator=(const Dimension & rhs)
{
	try
	{
		const DepthDimension& other_rho = dynamic_cast<const DepthDimension &>(rhs);
		operator=(other_rho);
	}
	catch(std::bad_cast & e)
	{
		std::cerr << e.what() << std::endl;
		assert(false && "Incorrect dimension assignment");
	}

	return *this;
}

DepthDimension & DepthDimension::operator=(const DepthDimension & rhs)
{
	if ( this != &rhs)
	{
		Dimension::operator=(rhs);
		this->m_depth = rhs.m_depth;
	}
	return *this;
}

DepthDimension* DepthDimension::clone() const
{
	return new DepthDimension(*this);
}

float DepthDimension::value() const
{
	return m_depth;
}

float& DepthDimension::value()
{
	return m_depth;
}

void DepthDimension::mutate()
{
	//std::cerr << "DepthDimension::mutate\n";
	Dimension::mutate();
}

float DepthDimension::k() const
{
	return m_k;
}

float DepthDimension::r() const
{
	return m_r;
}

void DepthDimension::r(float range)
{
	m_r = range;
}