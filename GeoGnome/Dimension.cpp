
#include "Dimension.hpp"
#include "Random.hpp"

Dimension::Dimension()
{
}

Dimension::Dimension(const Dimension & other)
{
}

Dimension & Dimension::operator=(const Dimension & rhs)
{
	return *this;
}

void Dimension::mutate()
{
		// Mutation equation Vm = V * s * r * 2^(-uk)
		//   where s = sign = {-1, +1) uniform random
		//   r = range
		//   u = [0..1] uniform random
		//   k = precision
		int toss = Random::instance().discrete_zero_or_one();
		int sign = (toss == 0) ? -1 : +1;
	
		float u = Random::instance().uniform_zero_to_one();

		value() += sign * r() * std::pow(2, -u * k());
}

std::ostream & operator<<(std::ostream & stream, const Dimension & dim)
{
	stream << "value = " << dim.value() << '\n';
	return stream;
}