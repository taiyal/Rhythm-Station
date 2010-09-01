#include "Type.h"

std::string convert::toString(int _in)
{
	std::stringstream out;
	out << _in;
	return out.str();
}
std::string convert::toString(double _in)
{
	std::stringstream out;
	out << _in;
	return out.str();
}
std::string convert::toString(bool _in)
{
	std::stringstream out;
	if ( _in )
		out << "true";
	else
		out << "false";
	return out.str();
}
