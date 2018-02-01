#ifndef RHODIMENSION_HPP
#define RHODIMENSION_HPP

#include "Dimension.hpp"

class RhoDimension : public Dimension
{
public:
	RhoDimension();
	explicit RhoDimension(float rho);
	RhoDimension(const RhoDimension & other);
	virtual RhoDimension & operator=(const Dimension & rhs);
	RhoDimension & operator=(const RhoDimension & rhs);
	virtual RhoDimension* clone() const;
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
	float m_rho;
};

#endif