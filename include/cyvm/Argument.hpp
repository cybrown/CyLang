#ifndef __ARGUMENT__
#define __ARGUMENT__

#include <string>
#include "Type.hpp"

class Argument {
protected:
	std::string name;
	Type* type;
public:
	Argument();
	Argument(Type* t, std::string n);
	std::string getName();
	void setName(std::string n);
	Type* getType();
	void setType(Type* t);
};

#endif
