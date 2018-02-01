
#include <list>

#include "Random.hpp"

#include "Genome.hpp"
#include "FaultGene.hpp"
#include "ListricFaultGene.hpp"
#include "SinuousFaultGene.hpp"

// constructor
Genome::Genome() :
    m_genelist()
{
}

Genome::Genome(int size) :
    m_genelist()
{
    for(int i = 0; i < size ; ++i)
    {
		m_genelist.push_back( boost::shared_ptr<Gene>(new SinuousFaultGene()) );
    }
}

/**
 *  Deep copy with value semantics
 */
Genome::Genome(const Genome & other) :
	m_genelist()
{
	GeneList::const_iterator p     = other.m_genelist.begin();
	GeneList::const_iterator p_end = other.m_genelist.end();
	while(p != p_end)
	{
		m_genelist.push_back( boost::shared_ptr<Gene>((*p)->clone()) );
		++p;
	}
}
void Genome::express(Grid2d & grid) const
{
	GeneList::const_iterator p = m_genelist.begin();
	while (p != m_genelist.end())
	{
		(*p)->express(grid);
		++p;
	}
}

/**
 *  Deep assignment with value semantics
 */
Genome & Genome::operator=(const Genome & rhs)
{
	if ( this != &rhs)
	{
		m_genelist.clear();
		GeneList::const_iterator p     = rhs.m_genelist.begin();
	    GeneList::const_iterator p_end = rhs.m_genelist.end();
	    while(p != p_end)
	    {
		    m_genelist.push_back( boost::shared_ptr<Gene>((*p)->clone()) );
		    ++p;
	    }
	}
	return *this;
}

size_t Genome::size() const
{
	return m_genelist.size();
}

std::pair<Genome, Genome> Genome::splice(Genome & thing_one_genotype, size_t thing_one_splice_point,
		                                 Genome & thing_two_genotype, size_t thing_two_splice_point)
{
	GeneList::iterator b1 = thing_one_genotype.m_genelist.begin();
    GeneList::iterator e1 = thing_one_genotype.m_genelist.end();
	GeneList::iterator s1 = b1;
	std::advance(s1, thing_one_splice_point);

    GeneList::iterator b2 = thing_two_genotype.m_genelist.begin();
    GeneList::iterator e2 = thing_two_genotype.m_genelist.end();
	GeneList::iterator s2 = b2;
	std::advance(s2, thing_two_splice_point);
	GeneList::iterator splice_point_marker = boost::prior(s2);

	thing_two_genotype.m_genelist.splice(s2, thing_one_genotype.m_genelist, b1, s1);
	++splice_point_marker;

	assert(s1 == thing_one_genotype.m_genelist.begin());

	thing_one_genotype.m_genelist.splice(s1, thing_two_genotype.m_genelist, b2, splice_point_marker);

	assert ( splice_point_marker == thing_two_genotype.m_genelist.begin());

	return std::make_pair(thing_one_genotype, thing_two_genotype);
}

void Genome::mutate()
{
	//pick a fault gene

	int chosen_gene = Random::instance().discrete_zero_to_n( size() - 1 );

	//on the gene list go along the list until you reach chosen_gene entry
	//on that member of the genelist call FaultGene::mutate()

	GeneList::iterator p = m_genelist.begin();
	std::advance (p, chosen_gene);
	(*p)->mutate();

	// TODO: Model transposition, deletion and duplication here
}


std::ostream & operator<<(std::ostream & stream, const Genome & genome)
{
	stream << "START GENOME (" << genome.size() << ")\n";
	
	Genome::GeneList::const_iterator p = genome.m_genelist.begin();
	while (p != genome.m_genelist.end())
	{
		stream << **p << '\n';
		++p;
	}

	stream << "END GENOME \n";
	return stream;
}