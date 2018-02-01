#include "Polynomial.hpp"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>

float Polynomial::m_s_tolerance = 1e-6f;

Polynomial::Polynomial(float a, float b, float c, float d) :
	m_coeffs(4)
{
	// Reverse order
	m_coeffs[0] = d;
	m_coeffs[1] = c;
	m_coeffs[2] = b;
	m_coeffs[3] = a;
}

Polynomial::~Polynomial()
{
}

size_t Polynomial::degree() const
{
	return m_coeffs.size() - 1;
}

void Polynomial::simplify()
{
    for ( size_t i = degree(); i >= 0; i-- )
	{
		if ( std::abs( m_coeffs[i] ) <= m_s_tolerance )
		{
            m_coeffs.pop_back();
		}
        else
		{
            break;
		}
    }
}

std::vector<float> Polynomial::roots()
{
	// TODO: It would be better if simplify returned a simplified copy
	simplify();
    switch ( degree() )
	{
		case 0: return std::vector<float>();
		case 1: return linear_root();
		case 2: return quadratic_roots();
		case 3: return cubic_roots();
	}
	assert(degree() <= 3);
	return std::vector<float>();
}

std::vector<float> Polynomial::linear_root() const
{
	assert( degree() == 1 );
	std::vector<float> result;
    float a = m_coeffs[1];
    
    if ( a != 0.0f )
	{
        result.push_back( - m_coeffs[0] / a );
	}

    return result;
}

std::vector<float> Polynomial::quadratic_roots() const
{
	assert( degree() == 2 );
    float a = m_coeffs[2];
    float b = m_coeffs[1] / a;
    float c = m_coeffs[0] / a;
    float d = b * b - 4.0f * c;

	assert(d >= 0.0f);

	std::vector<float> results;

    if ( d > 0.0f )
	{
		float e = std::sqrt(d);
        results.push_back( 0.5f * (-b + e) );
        results.push_back( 0.5f * (-b - e) );
    }
	else if ( d == 0.0f )
	{
        // really two roots with same value, but we only return one
        results.push_back( 0.5f * -b );
    }
	return results;
}

/**
 *   This code is based on MgcPolynomial.cpp written by David Eberly.  His
 *   code along with many other excellent examples are avaiable at his site:
 *   http://www.magic-software.com
 *
 */
std::vector<float> Polynomial::cubic_roots() const
{
	assert( degree() == 3 );
	float c3 = m_coeffs[3];
    float c2 = m_coeffs[2] / c3;
    float c1 = m_coeffs[1] / c3;
    float c0 = m_coeffs[0] / c3;

	std::vector<float> results;

    float a       = (3.0f * c1 - c2 * c2) / 3.0f;
    float b       = (2.0f * c2 * c2 * c2 - 9.0f * c1 * c2 + 27.0f * c0) / 27.0f;
    float offset  = c2 / 3.0f;
    float discrim = b * b / 4.0f + a * a * a / 27.0f;
    float halfB   = b / 2.0f;

	if ( std::abs(discrim) <= m_s_tolerance )
	{
		discrim = 0.0f;
	}
    
    if ( discrim > 0.0f )
	{
		float e = std::sqrt(discrim);
        float tmp;
        float root;

        tmp = -halfB + e;
        if ( tmp >= 0.0f )
		{
			root = std::pow(tmp, 1.0f / 3.0f);
		}
        else
		{
			root = -std::pow(-tmp, 1.0f / 3.0f);
		}

        tmp = -halfB - e;
        if ( tmp >= 0.0f )
		{
			root += std::pow(tmp, 1.0f / 3.0f);
		}
        else
		{
			root -= std::pow(-tmp, 1.0f / 3.0f);
		}

        results.push_back( root - offset );
    }
	else if ( discrim < 0.0f )
	{
		float distance = std::sqrt(-a / 3.0f);
		float angle    = std::atan2( std::sqrt(-discrim), -halfB) / 3.0f;
		float cos      = std::cos(angle);
		float sin      = std::sin(angle);
		float sqrt3    = std::sqrt(3.0f);

        results.push_back( 2.0f * distance * cos - offset );
        results.push_back( -distance * (cos + sqrt3 * sin) - offset);
        results.push_back( -distance * (cos - sqrt3 * sin) - offset);
    }
	else
	{
        float tmp;
        if ( halfB >= 0.0f )
		{
			tmp = -std::pow(halfB, 1.0f / 3.0f);
		}
        else
		{
			tmp = std::pow(-halfB, 1.0f / 3.0f);
		}

        results.push_back( 2.0f * tmp - offset );
        // really should return next root twice, but we return only one
        results.push_back( -tmp - offset );
    }
	return results;
}