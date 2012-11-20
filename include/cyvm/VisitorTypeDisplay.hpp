#ifndef __VISITOR_TYPE_DISPLAY__
#define __VISITOR_TYPE_DISPLAY__

#include "VisitorType.hpp"
#include "AllNodes.hpp"
#include "AllTypes.hpp"

/**
This visitor displays the content of the AST.
usefull for debug.
*/
class VisitorTypeDisplay: public VisitorType {
protected:
    int tabs;
    void tabInc();
    void tabDec();
    void showTabs();
public:
    VisitorTypeDisplay();
    void visit(class TypePrimary *n);
    void visit(class TypeArray *n);
    void visit(class TypeFunction *n);
    void visit(class TypeClass *n);
    static const char* type2str(TypePrimary* tp);
};

#endif
