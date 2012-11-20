#include "VisitorTypeDisplay.hpp"
#include <iostream>

using namespace std;

VisitorTypeDisplay::VisitorTypeDisplay() {
    
}

void VisitorTypeDisplay::visit(class TypePrimary *n) {
    cout << this->type2str(n);
}

void VisitorTypeDisplay::visit(class TypeArray *n) {
    cout << "[";
    n->getType()->acceptVisitor(*this);
    cout << "]";
}

void VisitorTypeDisplay::visit(class TypeFunction *n) {
    cout << "<";
    if (n->getType())
        n->getType()->acceptVisitor(*this);
    else
        cout << "0";
    cout << ">";
    cout << "(";
    for (std::vector<Type*>::iterator it = n->getSignature()->begin(); it != n->getSignature()->end(); it++)
    {
        if (it != n->getSignature()->begin())
        {
            cout << ", ";
        }
        (*it)->acceptVisitor(*this);
    }
    cout << ")";
}

void VisitorTypeDisplay::visit(class TypeClass *n) {
    cout << "{" << n->getClass()->getName() << "}";
}

const char* VisitorTypeDisplay::type2str(TypePrimary* tp) {
    if (tp->isBool())
        return "Bool";
    if (tp->isByte())
        return "Byte";
    if (tp->isShort())
        return "Short";
    if (tp->isInt())
        return "Int";
    if (tp->isLong())
        return "Long";
    if (tp->isFloat())
        return "Float";
    if (tp->isDouble())
        return "Double";
    if (tp->isVoid())
        return "Void";
    return "Unknown primary type";
}
