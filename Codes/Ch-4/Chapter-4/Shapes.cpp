#include "Shapes.h"
#include <numbers>

#include <iostream>
#include <format>

std::string Shape::what_am_i() const
{
	return "Shape";
}

Circle::Circle(double radius) : radius_{ radius } {}

std::string Circle::what_am_i() const
{
	return "Circle";
}

std::string Circle::what_i_am() const
{
	return "Circle";
}

double Circle::area() const
{
	return std::numbers::pi * radius_ * radius_;
}

Rectangle::Rectangle(double length, double width) :
	length_{ length}, width_{ width} {}

std::string Rectangle::what_am_i() const
{
	return "Rectangle";
}

double Rectangle::area() const
{
	return length_ * width_;
}

void shapes_examples()
{
	using std::cout;
	using std::format;

	cout << "\n*** shapes_examples() ***\n";

	double radius = 1.0;
	double length = 3.0;
	double width = 2.0;

	Circle circle{ radius };
	Rectangle rect{ length,width };

	cout << format("Area of {} with radius = {}: {}\n", circle.what_am_i(), radius, circle.area());
	cout << format("Area of {} width length = {} and width = {}: {}\n\n", rect.what_am_i(), length, width, rect.area());
}
