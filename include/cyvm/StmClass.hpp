#ifndef __STM_CLASS__
#define __STM_CLASS__

#include "Class.hpp"
#include "Stm.hpp"

class StmClass: public Stm {
protected:
	Class* cl;
public:
	StmClass();
	StmClass(Class* c);
	void setClass(Class* c);
	Class* getClass();
	void accept(VisitorNode &v);
};

#endif
