#ifndef POINT2D_HPP
#define POINT2D_HPP

class Vector2D;

class Point2D
{
public:
	Point2D();
	Point2D(float x, float y);
	Point2D(const Point2D & other);
	Point2D & operator=(const Point2D & rhs);
	~Point2D();

	float x() const;
	float y() const;

	Point2D lerp(Point2D, float t) const;

	Point2D operator+(const Vector2D & rhs) const;
	Point2D operator-(const Vector2D & rhs) const;
    Vector2D operator-(const Point2D & rhs) const;
	Vector2D operator*(float rhs) const;

private:
	float m_x;
	float m_y;
};

#endif