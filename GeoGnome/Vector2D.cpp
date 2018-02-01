#include <cmath>

#include "Vector2D.hpp"
#include "Point2D.hpp"

Vector2D::Vector2D() :
	m_dx(0.0f),
	m_dy(0.0f)
{
}

Vector2D::Vector2D(float dx, float dy) :
	m_dx(dx),
	m_dy(dy)
{
}

Vector2D::Vector2D(const Vector2D & other) :
	m_dx(other.m_dx),
	m_dy(other.m_dy)
{
}

Vector2D::Vector2D(const Point2D & other) :
	m_dx(other.x()),
	m_dy(other.y())
{
}

Vector2D & Vector2D::operator=(const Vector2D & rhs)
{
	if(this != &rhs)
	{
		m_dx = rhs.m_dx;
		m_dy = rhs.m_dy;
	}
	return *this;
}

Vector2D & Vector2D::operator=(const Point2D & rhs)
{
	m_dx = rhs.x();
	m_dy = rhs.y();
	return *this;
}

Vector2D::~Vector2D()
{
}


float Vector2D::dx() const
{
	return m_dx;
}

float Vector2D::dy() const
{
	return m_dy;
}


float Vector2D::length() const
{
	return std::sqrt(m_dx * m_dx + m_dy * m_dy);
}

Vector2D Vector2D::unit() const
{
	float len = length();
	if (len > 0.0f)
	{
		return Vector2D(m_dx / len, m_dy / len);
	}
	return *this;
}

float Vector2D::dot(const Vector2D & rhs)
{
	return m_dx * rhs.m_dx + m_dy * rhs.m_dy;
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const
{
	return Vector2D(m_dx + rhs.m_dx, m_dy + rhs.m_dy);
}

Vector2D Vector2D::operator*(float rhs) const
{
	return Vector2D(m_dx * rhs, m_dy * rhs);
}

Vector2D Vector2D::operator/(float rhs) const
{
	return Vector2D(m_dx / rhs, m_dy / rhs);
}

