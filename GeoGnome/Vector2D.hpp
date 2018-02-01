#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

class Point2D;

class Vector2D
{
public:
	Vector2D();
	Vector2D(float dx, float dy);
	Vector2D(const Vector2D & other);
	explicit Vector2D(const Point2D & other);
	Vector2D & operator=(const Vector2D & rhs);
	Vector2D & operator=(const Point2D & rhs);
	~Vector2D();

	float dx() const;
	float dy() const;

	float length() const;
	Vector2D unit() const;
	float dot(const Vector2D & rhs);

	Vector2D operator+(const Vector2D & rhs) const;
	Vector2D operator*(float rhs) const;
	Vector2D operator/(float rhs) const;
private:
	float m_dx;
	float m_dy;
};

#endif