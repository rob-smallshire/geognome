#ifndef DIMENSION_HPP
#define DIMENSION_HPP

#include <iosfwd>

class Dimension
{
public:
	virtual float value() const = 0;
	virtual void mutate();
	virtual Dimension* clone() const = 0;
	virtual Dimension & operator=(const Dimension & rhs);
	virtual float& value() = 0;
protected:
	virtual float k() const = 0;
	virtual float r() const = 0;
	Dimension();
	Dimension(const Dimension & other);

};

std::ostream & operator<<(std::ostream & stream, const Dimension & dim);

#endif
