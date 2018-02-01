#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <vector>

class Polynomial
{
public:
	Polynomial(float a, float b, float c, float d); // Cubic
	~Polynomial();

	size_t degree() const;
	void simplify();
	std::vector<float> roots();
private:
	Polynomial();
	Polynomial(const Polynomial & other);
	Polynomial & operator=(const Polynomial & rhs);

	std::vector<float> linear_root() const;
	std::vector<float> quadratic_roots() const;
	std::vector<float> cubic_roots() const;

	std::vector<float> m_coeffs;

	static float m_s_tolerance;
};

#endif