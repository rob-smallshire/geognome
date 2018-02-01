#ifndef DEPTHDIMENSION_HPP
#define DEPTHDIMENSION_HPP

#include "Dimension.hpp"

class DepthDimension : public Dimension
{
public:
	DepthDimension();
	explicit DepthDimension(float displacement);
	DepthDimension(const DepthDimension & other);
	virtual DepthDimension & operator=(const Dimension & rhs);
	DepthDimension & operator=(const DepthDimension & rhs);
	virtual DepthDimension* clone() const;
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
	float m_depth;
};

#endif