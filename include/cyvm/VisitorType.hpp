#ifndef __VISITOR_TYPE__
#define __VISITOR_TYPE__


/**
The base Visitor class to visit types.
*/
class VisitorType {
public:
    virtual void visit(class TypePrimary *n)=0;
    virtual void visit(class TypeArray *n)=0;
    virtual void visit(class TypeFunction *n)=0;
    virtual void visit(class TypeClass *n)=0;
};

#endif
