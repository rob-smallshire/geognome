#ifndef GRID2D_HPP
#define GRID2D_HPP

#include <iostream>
#include "boost/multi_array.hpp"

class Grid2d
{
public:
    Grid2d(int size_x, int size_y);
	Grid2d(int size_x, int size_y, float origin_x, float origin_y, float spacing_x, float spacing_y);
	Grid2d(const Grid2d & other_grid);
	int num_nodes_x() const;
	int num_nodes_y() const;	
	float min_x() const;
	float min_y() const;
	float max_x() const;
	float max_y() const;
	float min_z() const;
	float max_z() const;
	float node_x(int i) const;
	float node_y(int j) const;
	float node_z(int i, int j) const;
	float spacing_x() const;
	float spacing_y() const;
	void displace_grid(float rho, float theta, float displacement);
	void listric_displace(float rho, float theta, float heave, float detatch_depth, float dip);
	void sinuous_displace(float x0, float y0, float phi0, float x1, float y1, float phi1, float max_heave, float detach_depth, float dip);
	float comparison(const Grid2d &) const; //0 equals identical

private:
	boost::multi_array<float, 2> m_grid;
	float m_origin_x;
	float m_origin_y;
	float m_spacing_x;
	float m_spacing_y;
};

std::ostream & operator<<(std::ostream & stream, const Grid2d & grid);
#endif