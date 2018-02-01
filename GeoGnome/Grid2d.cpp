#include <cmath>

#include "boost/multi_array.hpp"

#include "utility.hpp"
#include "Point2D.hpp"
#include "Vector2D.hpp"
#include "Grid2d.hpp"
#include "Polynomial.hpp"

Grid2d::Grid2d(int size_x, int size_y) :
	m_grid(boost::extents[size_x][size_y]),
	m_origin_x(0.0f),
	m_origin_y(0.0f),
	m_spacing_x(10.0f),
	m_spacing_y(10.0f)	
{
	for(int i = 0; i < size_x; ++i)
	{
		for(int j = 0; j < size_y; ++j)
		{
			m_grid[i][j] = 0.0f;
		}
	}
}


Grid2d::Grid2d(int size_x, int size_y, float origin_x, float origin_y, float spacing_x, float spacing_y) :
	m_grid(boost::extents[size_x][size_y]),
	m_origin_x(origin_x),
	m_origin_y(origin_y),
	m_spacing_x(spacing_x),
	m_spacing_y(spacing_y)		
{
	for(int i = 0; i < size_x; ++i)
	{
		for(int j = 0; j < size_y; ++j)
		{
			m_grid[i][j] = 0.0f;
		}
	}
}

Grid2d::Grid2d(const Grid2d & other_grid):
	m_grid(other_grid.m_grid),
	m_origin_x(other_grid.m_origin_x),
	m_origin_y(other_grid.m_origin_y),
	m_spacing_x(other_grid.m_spacing_x),
	m_spacing_y(other_grid.m_spacing_y)	
{
}

int Grid2d::num_nodes_x() const
{
	return int(m_grid.shape()[0]);
}

int Grid2d::num_nodes_y() const
{
	return int(m_grid.shape()[1]);
}

float Grid2d::min_x() const
{
	return m_origin_x;
}

float Grid2d::min_y() const
{
	return m_origin_y;
}

float Grid2d::max_x() const
{
	return node_x(num_nodes_x() - 1);
}

float Grid2d::max_y() const
{
	return node_y(num_nodes_y() - 1);
}

float Grid2d::min_z() const
{
	float z_value = m_grid[0][0];
	for(int i = 0; i < num_nodes_x(); ++i)
	{
		for(int j = 0; j < num_nodes_y(); ++j)
		{
			if (m_grid[i][j] < z_value)
			{
				z_value = m_grid[i][j];
			}
		}
	}
	return z_value;
}

float Grid2d::max_z() const
{
	float z_value = m_grid[0][0];
	for(int i = 0; i < num_nodes_x(); ++i)
	{
		for(int j = 0; j < num_nodes_y(); ++j)
		{
			if (m_grid[i][j] > z_value)
			{
				z_value = m_grid[i][j];
			}
		}
	}
	return z_value;
}

float Grid2d::node_z(int i, int j) const
{
	assert(i >= 0);
	assert(j >= 0);
	assert(i < num_nodes_x());
	assert(j < num_nodes_y());
	return m_grid[i][j];
}

float Grid2d::node_x(int i) const
{
	assert(i >= 0);
	assert(i < num_nodes_x());
	return min_x() + (i * m_spacing_x);
}

float Grid2d::node_y(int j) const
{
	assert(j >= 0);
	assert(j < num_nodes_y());
	return min_y() + (j * m_spacing_y);
}

float Grid2d::spacing_x() const
{
	return m_spacing_x;
}

float Grid2d::spacing_y() const
{
	return m_spacing_y;
}

void Grid2d::displace_grid(float rho, float theta, float displacement)
{
	for(int i = 0; i < num_nodes_x(); ++i)
	{
		float px = node_x(i);
		float x_cos_theta = px * std::cos(deg2rad(theta));
		for(int j = 0; j < num_nodes_y(); ++j)
		{
			float py = node_y(j);
			float y_sin_theta = py * std::sin(deg2rad(theta));
			float dist_to_cutoff = x_cos_theta + y_sin_theta - rho;
			if (dist_to_cutoff >= 0.0f)
			{
				// hangingwall
				m_grid[i][j] -= displacement / 2.0f;
			}
			else
			{
				//footwall
				m_grid[i][j] += displacement / 2.0f;
			}
		}
	}
}

void Grid2d::listric_displace(float rho, float theta, float heave, float detach_depth, float dip)
{
    const float datum = 0.0f;
	float k = std::tan(deg2rad(dip));

	for(int i = 0; i < num_nodes_x(); ++i)
	{
		float px = node_x(i);
		float x_cos_theta = px * std::cos(deg2rad(theta));
		for(int j = 0; j < num_nodes_y(); ++j)
		{
			float py = node_y(j);
			float y_sin_theta = py * std::sin(deg2rad(theta));
			float dist_to_cutoff = x_cos_theta + y_sin_theta - rho;
			if (dist_to_cutoff >= 0.0f)
			{
				// hangingwall
				float fault_depth = detach_depth * (1.0f - std::exp(-k * dist_to_cutoff / detach_depth));
                float fault_elevation = datum - fault_depth;
				float offset0 = dist_to_cutoff - heave;
				float depth0  = detach_depth * (1.0f - std::exp(-k * offset0 / detach_depth));
				float depth1  = fault_depth - depth0;
				float elev1 = datum - depth1;
				m_grid[i][j] += std::max(fault_elevation, elev1);
			}
			else
			{
				//footwall
				//m_grid[i][j] += 0.0f; -- do nothing
			}
		}
	}
}

void Grid2d::sinuous_displace(float x0, float y0, float phi0, float x1, float y1, float phi1, float max_heave, float detach_depth, float dip)
{
	// Determine the four Bezier control points

	// p1 and p4 are the fault tips
	Point2D p1(x0, y0);
	Point2D p4(x1, y1);

	Vector2D axis = p4 - p1; // Vector from tip to tip
	Vector2D half_axis = axis / 2.0f;
    Point2D  mid_axis = p1 + half_axis;
    Vector2D unit_axis = axis.unit();
    Vector2D unit_heave(unit_axis.dy(), -unit_axis.dx()); // Perpendicular

	float offset2 = half_axis.length() * std::tan(deg2rad(phi0));
    Point2D p2 = mid_axis - unit_heave * offset2;
    
	float offset3 = half_axis.length() * std::tan(deg2rad(phi1));
	Point2D p3 = mid_axis + unit_heave * offset3;

    // Start with Bezier using Bernstein polynomials for weighting functions:
    //     (1-t^3)P1 + 3t(1-t)^2P2 + 3t^2(1-t)P3 + t^3P4
    //
    // Expand and collect terms to form linear combinations of original Bezier
    // controls.  This ends up with a vector cubic in t:
    //     (-P1+3P2-3P3+P4)t^3 + (3P1-6P2+3P3)t^2 + (-3P1+3P2)t + P1
    //             /\                  /\                /\       /\
    //             ||                  ||                ||       ||
    //             c3                  c2                c1       c0

    // Calculate the coefficients

	Vector2D c3;
	{
		Vector2D a = p1 * -1.0f;
		Vector2D b = p2 *  3.0f;
		Vector2D c = p3 * -3.0f;
		Vector2D d = Vector2D(p4) + a + b + c;
		c3 = d;
	}

	Vector2D c2;
	{
		Vector2D a = p1 *  3.0f;
		Vector2D b = p2 * -6.0f;
		Vector2D c = p3 *  3.0f;
		Vector2D d = a + b + c;
		c2 = d;
	}

	Vector2D c1;
	{
		Vector2D a = p1 * -3.0f;
		Vector2D b = p2 *  3.0f;
		Vector2D c = a + b;
		c1 = c;
	}

    Vector2D c0(p1);

	for(int i = 0; i < num_nodes_x(); ++i)
	{
		float px = node_x(i);
		for(int j = 0; j < num_nodes_y(); ++j)
		{
			float py = node_y(j);
			
			// Find normal to line: negative inverse of original line's slope
            Vector2D n = unit_axis;

			// Construct two points on the straight line - using the
			// query point and the heave vector
            Point2D a1(px, py);
			Point2D a2 = a1 + unit_heave;

			// Determine new c coefficient for the line
            float c_line = a1.x() * a2.y() - a2.x() * a1.y();

            // ?Rotate each cubic coefficient using line for new coordinate system?
			// Find roots of rotated cubic
			Polynomial poly( n.dot(c3), n.dot(c2), n.dot(c1), n.dot(c0) + c_line);
			std::vector<float> roots = poly.roots();
			// For each root...
			std::vector<float>::const_iterator r     = roots.begin();
			std::vector<float>::const_iterator r_end = roots.end();
			assert(roots.size() <= 1);
			while(r != r_end)
			{
				float t = *r;
				if (0.0f <= t && t <= 1.0f)
				{
					// We're within the Bezier curve
					// Find point on Bezier
					Point2D p5 = p1.lerp(p2, t);
					Point2D p6 = p2.lerp(p3, t);
					Point2D p7 = p3.lerp(p4, t);

					Point2D p8 = p5.lerp(p6, t);
					Point2D p9 = p6.lerp(p7, t);

					Point2D p10 = p8.lerp(p9, t);

                    // p10 is the intersection between the heave-parallel line
					// through the current query point, and the cubic bezier.

					// The heave will be a sinusoidal function of t, with a
					// heave of zero at the fault tips. So we map t over the inteval
					// [0- > 1] to u over the interval [-PI/2 -> +3PI/4] which are
					// the minimal of the sine curve
                    float u = (-pi<float>() / 2.0f) + (t * 2 * pi<float>());

					float heave = (1.0f + std::sin(u)) * max_heave / 2.0f;
                  
                    Point2D fw_cutoff = p10 - unit_heave * heave / 2.0f;

					// Determine whether we are in the hangingwall or the footwall
					// By determining whether we are in the same direction as the
					// unit_heave: Compute the dot product of fw_cutoff->a1 and the
					// unit_heave vector. If the result is +ve, we are in the HW
					Vector2D transport = a1 - fw_cutoff;
					float side = transport.dot(unit_heave);
					if (side >= 0.0f) {
						// We are in the hangingwall
						float dist_to_cutoff = transport.length();
						const float datum = 0.0f;
						float k = std::tan(deg2rad(dip));
						float fault_depth = detach_depth * (1.0f - std::exp(-k * dist_to_cutoff / detach_depth));
						float fault_elevation = datum - fault_depth;
						float offset0 = dist_to_cutoff - heave;
						float depth0  = detach_depth * (1.0f - std::exp(-k * offset0 / detach_depth));
						float depth1  = fault_depth - depth0;
						float elev1 = datum - depth1;
						m_grid[i][j] += std::max(fault_elevation, elev1);
					}

				}
				++r;
			}
		}
	}
}

float Grid2d::comparison(const Grid2d & other_grid) const
{
	float total = 0;
	for(int j = 0; j < num_nodes_y(); ++j)
	{
		for(int i = 0; i < num_nodes_x(); ++i)
		{
			float first_point  = this->m_grid[i][j];
			float second_point = other_grid.m_grid[i][j];
			float diff = first_point - second_point;
			float square = diff * diff;
			total += square;
		}
	}
	float mean = total / (num_nodes_x() * num_nodes_y());
	float result = std::sqrt(mean);
	return result;
}

std::ostream & operator<<(std::ostream & stream, const Grid2d & grid)
{
	stream << "DSAA\n";
	stream << grid.num_nodes_x() << " " << grid.num_nodes_y() << "\n";
	stream << grid.min_x() << " " << grid.max_x() << "\n";
	stream << grid.min_y() << " " << grid.max_y() << "\n";
	stream << grid.min_z() << " " << grid.max_z() << "\n";

	for(int j = 0; j < grid.num_nodes_y(); ++j)
	{
		int counter = 0;
		for(int i = 0; i < grid.num_nodes_x(); ++i)	
		{
			if (counter == 10)
			{
				stream << '\n';
				counter = 0;
			}
			stream << grid.node_z(i,j) << ' ';
			++counter;
		}
		stream << "\n\n";
	}
	stream << "\n";
	return stream;
}