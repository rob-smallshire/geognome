#ifndef DISPLACEMENTDIMENSION_HPP
#define DISPLACEMENTDIMENSION_HPP

#include "Dimension.hpp"

class DisplacementDimension : public Dimension
{
public:
	DisplacementDimension();
	explicit DisplacementDimension(float displacement);
	DisplacementDimension(const DisplacementDimension & other);
	virtual DisplacementDimension & operator=(const Dimension & rhs);
	DisplacementDimension & operator=(const DisplacementDimension & rhs);
	virtual DisplacementDimension* clone() const;
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
	float m_displacement;
};

#endif
