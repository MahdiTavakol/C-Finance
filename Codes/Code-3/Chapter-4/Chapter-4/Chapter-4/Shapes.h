#pragma once

#include <string>

class Shape
{
public: 
	virtual double area() const = 0;
	virtual std::string what_am_i() const;
	virtual ~Shape() = default;
};

class Circle final : public Shape
{
public:
	Circle(double radius);
	double area() const override;
	std::string what_am_i() const override;

	std::string what_i_am() const;

private:
	double radius_;
};

class Rectangle final : public Shape
{
public:
	Rectangle(double length, double width);
	double area() const override;
	std::string what_am_i() const override;

private:
	double length_, width_;
};

class Enclose
{
public:
	Enclose(const Shape& shape)
	{

	}

	double scale_area(double scale) const
	{
		return scale * shape_->area();
	}

private:
	Shape* shape_;
};
