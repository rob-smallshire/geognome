#ifndef CONTROLANGLEDIMENSION_HPP
#define CONTROLANGLEDIMENSION_HPP

#include "Dimension.hpp"

class ControlAngleDimension : public Dimension
{
public:
	ControlAngleDimension();
	explicit ControlAngleDimension(float theta);
	ControlAngleDimension(const ControlAngleDimension & other);
	virtual ControlAngleDimension & operator=(const Dimension & rhs);
	ControlAngleDimension & operator=(const ControlAngleDimension & rhs);
	virtual ControlAngleDimension* clone() const;
	virtual float value() const;
	virtual void mutate();
	static void r(float range);
protected:
	virtual float& value();
	virtual float k() const;
	virtual float r() const;
private:
	static const float m_k; // Mutation precision (controls minimum step size)
	static float m_r; // Mutation range (maximum mutation range)
	float m_angle;
};

#endif