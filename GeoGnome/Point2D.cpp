#include "Point2D.hpp"
#include "Vector2D.hpp"

Point2D::Point2D() :
	m_x(0.0f),
	m_y(0.0f)
{
}

Point2D::Point2D(float x, float y) :
	m_x(x),
	m_y(y)
{
}

Point2D::Point2D(const Point2D & other) :
	m_x(other.m_x),
	m_y(other.m_y)
{
}

Point2D & Point2D::operator=(const Point2D & rhs) 
{
	if (this != &rhs)
	{
		m_x = rhs.m_x;
		m_y = rhs.m_y;
	}
	return *this;
}

Point2D::~Point2D()
{
}

float Point2D::x() const
{
	return m_x;
}

float Point2D::y() const
{
	return m_y;
}

Point2D Point2D::lerp(Point2D p, float t) const
{
	return Point2D(m_x + (p.m_x - m_x) * t,
		           m_y + (p.m_y - m_y) * t);
}


Point2D Point2D::operator+(const Vector2D & rhs) const
{
	return Point2D(m_x + rhs.dx(), m_y + rhs.dy());
}

Point2D Point2D::operator-(const Vector2D & rhs) const
{
	return Point2D(m_x - rhs.dx(), m_y - rhs.dy());
}

Vector2D Point2D::operator-(const Point2D & rhs) const
{
	return Vector2D(m_x - rhs.m_x, m_y - rhs.m_y);
}

Vector2D Point2D::operator*(float rhs) const
{
	return Vector2D(m_x * rhs, m_y * rhs);
}
