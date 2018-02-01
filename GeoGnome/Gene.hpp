#ifndef GENE_HPP
#define GENE_HPP

#include <iosfwd>

// Forward declarations
class Grid2d;

/**
 *  Abstract Base Class for Genes
 */
class Gene
{
public:
	Gene();
	Gene(const Gene & other);
	Gene & operator=(const Gene & rhs);
	virtual ~Gene();
	virtual Gene * create() const = 0;
	virtual Gene * clone() const = 0;
	virtual void mutate() = 0;
	virtual void express(Grid2d & grid) const = 0;
	virtual std::ostream & write(std::ostream & stream) const = 0;
private:
};

std::ostream & operator<<(std::ostream & stream, const Gene & g);

#endif