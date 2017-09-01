#ifndef BASE
#define BASE

class Base: 
{
private:
public:
	Base();
	~Base();
	Base(const Base& other);
	Base& operator=(const Base& rhs);
};

#endif
