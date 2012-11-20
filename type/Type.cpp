#include "Type.hpp"

bool Type::isArray() {
    return false;
}

bool Type::isClass() {
    return false;
}

bool Type::isFunction() {
    return false;
}

bool Type::isPrimary() {
    return false;
}

int Type::stackSize() {
    return 4;
}

int Type::heapSize() {
    return 4;
}

std::string Type::mangle() {
	return "X";
}
