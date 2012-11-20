#ifndef __INTERFACE__
#define __INTERFACE__

#include <vector>
#include <map>
#include <string>
#include "Function.hpp"
#include "TypePrimary.hpp"

/**
Class to represent an interface.
*/
class Interface {
protected:
	std::string name;
	int id;
	std::vector<cy::Function*>* methods;
public:
	static int next_id;
public:
	Interface();
	void addMethod(std::string original_name, Type* return_type, std::vector<Argument*>* args);
	std::vector<cy::Function*>* getMethods();
	Type* getMethodReturnType();
	int   getMethodOffset();
	int   getId();
	std::string getName();
	void setName(std::string n);
};

#endif
