#ifndef GENOME_HPP
#define GENOME_HPP

// making a CLASS called Genome
// the things in Genome will be LISTS (this is a specific TYPE of thing) and the objects in the list have to know what they are made of. They will be made of FaultGenes.
// there can be many things in a list, and the list will be called genelist. 
//There can be many of these lists, but they will be be of the type Genome. 
//There can be many instances of Genome, each will have one list of genelist, which will comprise of objects of the type FaultGene. 
//Eventually an instance of Genome may contain a list, called genelist, which may contain objects of type FaultGene, but also type Compact or type Unfault, maybe... 
//the content of a Genome is only known to the programmer, but it is possible to define a METHOD which may be called to use the contents of Genome for things.
//This can be made known so that other programmers can call it and do things with the contents of a Genome.
//Everything in a struct is public, everything in a class is private, unless otherwise stated. If a thing has to be built using other things, then it should be private, cos you may want
//to change the way it's built later.

#include <list>

#include "boost/shared_ptr.hpp"

#include "FaultGene.hpp"

class Genome
{
public:
    Genome();
    explicit Genome(int size);
	Genome(const Genome & other) ;
	Genome & operator=(const Genome & rhs);
	void express(Grid2d & grid) const;
	void mutate();
	friend std::ostream & operator<<(std::ostream & stream, const Genome & genome);
	size_t size() const;
	static std::pair<Genome, Genome> splice(Genome & maternal_genotype, size_t maternal_splice_point,
		          Genome & paternal_genotype, size_t paternal_splice_point);
private:
	typedef std::list<boost::shared_ptr<Gene> > GeneList;
	GeneList m_genelist;
};

#endif

