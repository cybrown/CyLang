#include "Type.hpp"
#include <vector>
#include <string>

class Signature {
protected:
	std::vector<Type*>* types;
	std::string mangled_name;
public:
	Signature();
	std::string getMangledName();
	void setMangledName(std::string n);
	std::vector<Type*>* getTypes();
	void addType(Type* t);
};
