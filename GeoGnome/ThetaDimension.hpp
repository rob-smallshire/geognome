#ifndef THETADIMENSION_HPP
#define THETADIMENSION_HPP

#include "Dimension.hpp"

class ThetaDimension : public Dimension
{
public:
	ThetaDimension();
	explicit ThetaDimension(float theta);
	ThetaDimension(const ThetaDimension & other);
	virtual ThetaDimension & operator=(const Dimension & rhs);
	ThetaDimension & operator=(const ThetaDimension & rhs);
	virtual ThetaDimension* clone() const;
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
	float m_theta;
};

#endif
