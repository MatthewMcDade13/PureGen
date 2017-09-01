#include "./Base.h"

Base::Base()
{

}

Base::~Base()
{

}

Base& Base::operator=(const Base& rhs)
{
	if (this == &rhs) return *this;
	return *this;
}

Base::Base(const Base& other)
{

}


