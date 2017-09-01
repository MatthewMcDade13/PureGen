#ifndef BASE
#define BASE

class Base : protected Child
{
private:
public:
	Base();
	~Base();
	Base(const Base& other);
};

#endif
