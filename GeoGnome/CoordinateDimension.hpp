#ifndef COORDINATEDIMENSION_HPP
#define COORDINATEDIMENSION_HPP

#include "Dimension.hpp"

class CoordinateDimension : public Dimension
{
public:
	CoordinateDimension();
	explicit CoordinateDimension(float coordinate);
	CoordinateDimension(const CoordinateDimension & other);
	virtual CoordinateDimension & operator=(const Dimension & rhs);
	CoordinateDimension & operator=(const CoordinateDimension & rhs);
	virtual CoordinateDimension* clone() const;
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
	float m_coordinate;
};

#endif