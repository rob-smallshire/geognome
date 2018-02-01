#ifndef DIPDIMENSION_HPP
#define DIPDIMENSION_HPP

#include "Dimension.hpp"

class DipDimension : public Dimension
{
public:
	DipDimension();
	explicit DipDimension(float theta);
	DipDimension(const DipDimension & other);
	virtual DipDimension & operator=(const Dimension & rhs);
	DipDimension & operator=(const DipDimension & rhs);
	virtual DipDimension* clone() const;
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
	float m_dip;
};

#endif