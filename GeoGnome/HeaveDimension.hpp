#ifndef HEAVETDIMENSION_HPP
#define HEAVEDIMENSION_HPP

#include "Dimension.hpp"

class HeaveDimension : public Dimension
{
public:
	HeaveDimension();
	explicit HeaveDimension(float displacement);
	HeaveDimension(const HeaveDimension & other);
	virtual HeaveDimension & operator=(const Dimension & rhs);
	HeaveDimension & operator=(const HeaveDimension & rhs);
	virtual HeaveDimension* clone() const;
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
	float m_heave;
};

#endif