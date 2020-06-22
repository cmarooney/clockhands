#include <iostream>
#include <cmath>

/*
* Exercise to calculate the angle between the hands of the clock at a given time specified by integer hour and minute values.
* This version assumes a standard 12 hour clock with 60 minute hours.
* It assumes the hour hand moves smoothly between the hours.
* Calculation is done twice: 
* method 1 uses the scalar product of the vectors representing the hands. It is more resource intensive (trigonometric functions)
* but requires no further logic to get the angle in the right range, so useful for testing.
* method 2 uses the hand angle wrt hour=12 directly to get the difference between the angles. This requires noting that the
* angle may be negative and/or reentrant and correct this.
* Both answers are printed.
* The program loops over successive inputs of hour and minute from the console until terminated by hour<0.
*/

// Define PI (<cmath> does not appear to have M_PI in the present project setup)
const double twopi = 3.14159265358979323846 * 2;

// Define hours in the clock and minutes in the hour
// At some stage this could be read from a configuration file
const double HOURS_PER_CLOCK = 12.0;
const double MINS_PER_HOUR = 60;

// Define a 2D vector (x,y) and a dot product. The norm() method is provided but not used.
// It is used to calculate the angle between 2 vectors from a DOT b = |a||b|cos theta under one method considered here
class Vec2d
{
	double x, y;
public:
	Vec2d(double _x, double _y) : x(_x), y(_y) {}
	double operator*(const Vec2d& v) { return x * v.x + y * v.y; } // returns dot product
	double norm() { return std::sqrt((*this) * (*this)); }
};

// Class for any hand with a position and an angle
// HourHand and MinuteHand specialise this
class Hand
{
protected:
	// value for time
	double time;
	// value of angle of real 2d vector wrt hour=12
	double angle;
public:
	Hand(double _val) : time(_val), angle(-666.0) {} // angle calc'd in subclasses, initialised to bad value
	Vec2d vector_from_angle() const { return Vec2d(std::cos(angle), std::sin(angle)); }
	double get_angle() const { return angle; }
};

class HourHand : public Hand
{
public:
	HourHand(int _hval, int _mval) : Hand(_hval + _mval / MINS_PER_HOUR) { angle = to_angle(); }
private:
	double to_angle() const { return time * twopi / HOURS_PER_CLOCK; }
};

class MinuteHand : public Hand
{
public:
	MinuteHand(int _val) : Hand(_val) { angle = to_angle(); }
private:
	double to_angle() const { return time * twopi / MINS_PER_HOUR; }
};


int main()
{
	while (true)
	{
		std::cout << "Hello World!\n";
		std::cout << "Input hour value (int, <0 to exit): ";
		int hour;
		std::cin >> hour;
		if (hour < 0) break;
		std::cout << "Input minute value (int): ";
		int min;
		std::cin >> min;
		const HourHand h(hour, min);
		const MinuteHand m(min);
		const double cosangle = h.vector_from_angle() * m.vector_from_angle();
		double angle = std::acos(cosangle) * 360.0 / twopi;
		std::cout << "Angle between hands = " << angle << std::endl;
		const double hangle = h.get_angle();
		const double mangle = m.get_angle();
		angle = std::fabs(hangle - mangle);
		if (angle * 2.0 > twopi) angle = twopi - angle;
		angle *= 360.0 / twopi;
		std::cout << "Angle between hands = " << angle << std::endl;
	}
}

