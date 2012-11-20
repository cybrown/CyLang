#include "Class.hpp"

// TODO DEBUG
#include <iostream>
using namespace std;

void Class::initialize() {
	this->next_offset = 0;
	this->attributes = new std::map<std::string, Type*>();
	this->attributes_offset = new std::map<std::string, int>();
	this->attr_list = new std::vector<std::string>();
	this->methods = new std::vector<cy::Function*>();
	this->virtual_methods = new std::vector<cy::Function*>();
	this->interfaces = new std::vector<Interface*>();
	this->parent = 0;
	this->has_vtable = false;
}

Class::Class() {
	this->initialize();
}

bool Class::hasVTable() {
	return this->has_vtable;
}

void Class::extends(Class* ex) {
	if (this->parent)
		throw "Class can be overloaded only once !";
	this->parent = ex;
	// inherit attributes
	std::vector<std::string>::iterator it;
	for (it = this->parent->getAttributes()->begin(); it != this->parent->getAttributes()->end(); it++)
	{
		this->addAttribute(*it, this->parent->getAttrType(*it));
	}
	this->has_vtable = ex->hasVTable();
}

void Class::setVTable() {
	if (this->hasVTable())
		return;
	this->has_vtable = true;
	this->addVTableAttr();
}

void Class::addVTableAttr() {
	this->attributes->insert(std::make_pair("vpointer", new TypeArray(new TypeArray(TypePrimary::getByte()))));
	this->attr_list->insert(this->attr_list->begin(), "vpointer");

	for (std::map<std::string, int>::iterator it = this->attributes_offset->begin(); it != this->attributes_offset->end(); it++)
	{
		it->second++;
	}
	this->attributes_offset->insert(std::make_pair("vpointer", 0));
	this->next_offset++;
	// TODO insert vtable pointer at begining of attributes
	// TODO Penser au cas ou la classe parente n'a pas de vpointer...... :(
}

void Class::addMember(std::string name, Type* t, std::vector<Argument*>* args, Stm* body, int method_state) {
	if (!body)
	{
		this->addAttribute(name, t);
	}
	else
	{
		this->addMethod(name, t, args, body, method_state);
	}
}

void Class::addAttribute(std::string name, Type* t) {
	this->attributes->insert(std::make_pair(name, t));
	this->attributes_offset->insert(std::make_pair(name, this->next_offset));
	this->next_offset++;
	this->attr_list->push_back(name);
}

bool areCompatible(std::vector<Type*>* t1, std::vector<Type*>* t2) {
    std::vector<Type*>::iterator it1;
    std::vector<Type*>::iterator it2;
    // Not compatible if size are different
    if (t1->size() != t2->size())
    {
        return false;
    }
    // Testing each arguments and each types
    it2 = t2->begin();
    for (it1 = t1->begin(); it1 != t1->end(); it1++, it2++)
    {
        if (!(*it1)->equals(*it2))
        {
            return false;
        }
    }
    return true;
}

void Class::addMethod(std::string name, Type* t, std::vector<Argument*>* args, Stm* body, int method_state) {
	// Add this argument at the beginning of arg list
	if (!args)
		args = new std::vector<Argument*>();
	// TODO Do not do this for static methods
	if (!(method_state == 1))
	{
		args->insert(args->begin(), new Argument(new TypeClass(this), "this"));
	}
	
	TypeFunction* tf = new TypeFunction(t);
	tf->setVirtual(method_state == 2);
	tf->setClass(this);
	cy::Function* f = new cy::Function(tf, args, body);
	f->setOriginalName(name);
	this->methods->push_back(f);
	// Do specific operation
	tf->setStatic(false);
	f->setStatic(false);
	switch (method_state)
	{
		case 1:	// Method is static
			tf->setStatic(true);
			f->setStatic(true);
			break;
		case 2:	// Virtual method
			f->setVirtual(true);
			tf->setVirtual(true);
			this->setVTable();		// Set pointer to vtable attribute
			this->virtual_methods->push_back(f);
			break;
		case 3: // Overriden method
			tf->setOverridden(true);
			if (!this->getParent())
			{
				throw __FILE__ "(" QUOTE(__LINE__) "): Method " + name + " is overridden, but no super class.";
			}

			std::vector<Type*>* types = new std::vector<Type*>();
			std::vector<Argument*>::iterator itarg;
			for (itarg = args->begin(); itarg != args->end(); itarg++)
			{
				types->push_back((*itarg)->getType());
			}
			// Verify method with same name and same types exists in 
			if (!this->getParent()->getMethod(name, types))
			{
				throw __FILE__ "(" QUOTE(__LINE__) "): Method " + name + " is overridden, but not in super class.";
			}
			delete types;
			break;
	}
}

void Class::addMethod(std::string name, cy::Function* f) {
	f->setOriginalName(name);
	this->methods->push_back(f);
}

std::vector<std::string>* Class::getAttributes() {
	return this->attr_list;
}

void Class::setName(std::string n) {
	this->name = n;
}

std::string Class::getName() {
	return this->name;
}

Type* Class::getAttrType(std::string name) {
	return (*this->attributes)[name];
}

Type* Class::getMethodReturnType(std::string mangled_name) {
	return this->getMethodType(mangled_name)->getType();
}

TypeFunction* Class::getMethodType(std::string mangled_name) {
	std::vector<cy::Function*>::iterator it;
	cy::Function* f = 0;
	for (it = this->methods->begin(); it != this->methods->end(); it++)
	{
		// Use of mangled name because it is unique
		if ((*it)->getMangledName() == mangled_name)
		{
			f = *it;
		}
	}
	// Method not found in this class, look up in parent
	if (!f)
	{
		if (this->parent)
		{
			return this->parent->getMethodType(mangled_name);
		}
		else
		{
			throw __FILE__ "(" QUOTE(__LINE__) "): Class " + this->getName() + " does not have a method " + mangled_name;
		}
	}
	TypeFunction* res = dynamic_cast<TypeFunction*>(f->getType());
	return res;
}

int Class::getAttrOffset(std::string name) {
	return (*this->attributes_offset)[name];
}

std::vector<cy::Function*>* Class::getMethods() {
	return this->methods;
}

std::vector<cy::Function*>* Class::getVirtualMethods() {
	std::vector<cy::Function*>* res = new std::vector<cy::Function*>();
	std::vector<cy::Function*>* pvm;
	std::vector<cy::Function*>::iterator it;
	pvm = this->getParent() ? this->getParent()->getVirtualMethods() : new std::vector<cy::Function*>();

	std::vector<cy::Function*>::iterator itf;
	std::vector<Type*>* types = new std::vector<Type*>();
	std::vector<Argument*>::iterator itarg;
	cy::Function* overrider = 0;
	for (itf = pvm->begin(); itf != pvm->end(); itf++)
	{
		types->clear();
		for (itarg = (*itf)->getArgs()->begin(); itarg != (*itf)->getArgs()->end(); itarg++)
		{
			types->push_back((*itarg)->getType());
		}
		overrider = this->getMethod((*itf)->getOriginalName(), types);
		res->push_back(overrider ? overrider : (*itf));
	}


	for (it = this->virtual_methods->begin(); it != this->virtual_methods->end(); it++)
	{
		res->push_back(*it);
	}
	return res;
}

Class* Class::getParent() {
	return this->parent;
}

cy::Function* Class::getMethod(std::string original_name, std::vector<Type*>* types) {
	std::vector<cy::Function*>::iterator it;
	std::vector<Argument*>::iterator it_arg;
	std::vector<Type*>* types2 = new std::vector<Type*>();
	cy::Function* f = 0;
	for (it = this->methods->begin(); it != this->methods->end(); it++)
	{
		types2->clear();
		types2 = new std::vector<Type*>();
		// Use of mangled name because it is unique
		if ((*it)->getOriginalName() == original_name)
		{
			for (it_arg = (*it)->getArgs()->begin(); it_arg != (*it)->getArgs()->end(); it_arg++)
			{
				types2->push_back((*it_arg)->getType());
			}
			if (areCompatible(types, types2))
			{
				f = *it;
				break;
			}
		}
	}
	return f;
}

void Class::dump() {
	std::vector<cy::Function*>::iterator it_meth = this->methods->begin();
	std::map<std::string, Type*>::iterator it_attr = this->attributes->begin();
	cout << "METHODS" << endl;
	for (; it_meth != this->methods->end(); it_meth++)
	{
		cout << (*it_meth)->getMangledName() << " (" << (*it_meth)->getOriginalName() << ")" << endl;
	}
	cout << "ATTRIBUTES" << endl;
	for (; it_attr != this->attributes->end(); it_attr++)
	{
		cout << it_attr->first << ": " << it_attr->second << endl;
	}
	cout << endl;
}

void Class::dumpVTable() {
	if (this->hasVTable())
    {
        cout << "Virtual table for " << this->getName() << ":" << endl;
        std::vector<cy::Function*>* vms = this->getVirtualMethods();
        std::vector<cy::Function*>::iterator it;
        for (it = vms->begin(); it != vms->end(); it++)
        {
            cout << (*it)->getMangledName() << " (" << (*it)->getOriginalName() << ")" << endl;
        }
    }
    else
    {
    	cout << "No virtual table for " << this->getName() << "." << endl;
    }
    cout << endl;
}


int Class::getVirtualMethodOffset(std::string name) {
	std::vector<cy::Function*>* vms = this->getVirtualMethods();
	std::vector<cy::Function*>::iterator it;
	int index = 0;
	for (it = vms->begin(); it != vms->end(); it++)
	{
		if ((*it)->getMangledName() == name)
			return index;
		index++;
	}
	return -1;
}

void Class::implements(Interface* inter) {
	this->interfaces->push_back(inter);
}

std::vector<Interface*>* Class::getInterfaces() {
	return this->interfaces;
}
