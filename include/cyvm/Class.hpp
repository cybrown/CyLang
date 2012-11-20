#ifndef __CLASS22__
#define __CLASS22__

#define QUOTE(x) PREQUOTE(x)
#define PREQUOTE(x) #x

#include <string>
#include <vector>
#include <map>
#include "Type.hpp"
#include "Stm.hpp"
#include "Function.hpp"
#include "Argument.hpp"
#include "TypeFunction.hpp"
#include "TypePrimary.hpp"
#include "TypeArray.hpp"
#include "TypeClass.hpp"
#include "Interface.hpp"

/**
Class to reprensent a class.
*/
class Class {
protected:
	std::map<std::string, Type*>* attributes;         // Map each attributes to a type
    std::map<std::string, int>*   attributes_offset;  // Offset of each attributes in structure
    std::vector<std::string>*     attr_list;          // Order of attributes
    std::vector<cy::Function*>*   methods;
    std::vector<cy::Function*>*   virtual_methods;
    std::vector<Interface*>*      interfaces;
	std::string                   name;
    int                           next_offset;
    Class*                        parent;
    bool                          has_vtable;
    void                          setVTable();
    void                          addVTableAttr();
    void                          initialize();
public:
	Class();
                                  // Add attributes and methods
    void                          addMember(std::string name, Type* t, std::vector<Argument*>* args, Stm* body, int method_state);
    void                          addAttribute(std::string name, Type* t);
    void                          addMethod(std::string name, Type* t, std::vector<Argument*>* args, Stm* body, int method_state);
    void                          addMethod(std::string name, cy::Function* f);

                                  // Get attributes properties
    std::vector<std::string>*     getAttributes();
    int                           getAttrOffset(std::string name);
    Type*                         getAttrType(std::string name);

                                  // Get methods, types, virtual methods
    cy::Function*                 getMethod(std::string original_name, std::vector<Type*>* types);
    std::vector<cy::Function*>*   getMethods();
    std::vector<cy::Function*>*   getVirtualMethods();
    TypeFunction*                 getMethodType(std::string mangled_name);
    Type*                         getMethodReturnType(std::string mangled_name);
    int                           getVirtualMethodOffset(std::string name);
    int                           getVirtualMethodInterface(std::string mangled_name);
    int                           getVirtualMethodInterfaceId(std::string mangled_name);
    
                                  // Inheritance and interfaces
    void                          extends(Class* ex);
    void                          implements(Interface* inter);
    Class*                        getParent();
    std::vector<Interface*>*      getInterfaces();
    bool                          hasVTable();

                                  // General class information
    void                          setName(std::string n);
    std::string                   getName();

                                  // Debug methods
    void                          dump();
    void                          dumpVTable();
};

#endif
