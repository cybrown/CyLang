#ifndef __STM_INTERFACE__
#define __STM_INTERFACE__

#include "Interface.hpp"
#include "Stm.hpp"

class StmInterface: public Stm {
protected:
	Interface* inter;
public:
	StmInterface();
	StmInterface(Interface* i);
	void setInterface(Interface* i);
	Interface* getInterface();
	void accept(VisitorNode &v);
};

#endif
