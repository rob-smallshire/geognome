#include "Gene.hpp"

Gene::Gene()
{
}

Gene::Gene(const Gene & gene)
{
}

Gene & Gene::operator=(const Gene & rhs)
{
	return *this;
}

Gene::~Gene()
{
}

std::ostream & operator<<(std::ostream & stream, const Gene & g)
{
	return g.write(stream);
}