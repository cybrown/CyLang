template <typename T> cy::Value* UtilCalc::CalcOP2(ExprOP2::op o, T a, T b) {
    switch (o)
    {
        case ExprOP2::ADD:
            return new cy::Value(a + b);
        case ExprOP2::SUB:
            return new cy::Value(a - b);
        case ExprOP2::MUL:
            return new cy::Value(a * b);
        case ExprOP2::DIV:
            return new cy::Value(a / b);
        case ExprOP2::MOD:
            return new cy::Value(a % b);
        case ExprOP2::AND:
            return new cy::Value(a && b);
        case ExprOP2::OR:
            return new cy::Value(a || b);
        case ExprOP2::LT:
            return new cy::Value(a < b);
        case ExprOP2::LTE:
            return new cy::Value(a <= b);
        case ExprOP2::GT:
            return new cy::Value(a > b);
        case ExprOP2::GTE:
            return new cy::Value(a >= b);
        case ExprOP2::EQ:
            return new cy::Value(a == b);
        case ExprOP2::NEQ:
            return new cy::Value(a != b);
        case ExprOP2::B_AND:
            return new cy::Value(a & b);
        case ExprOP2::B_XOR:
            return new cy::Value(a ^ b);
        case ExprOP2::B_OR:
            return new cy::Value(a | b);
        case ExprOP2::SHL:
            return new cy::Value(a << b);
        case ExprOP2::SHR:
            return new cy::Value(a >> b);
        default:
            throw "Unknow integer binary operator.";
    }
}

template <typename T> cy::Value* UtilCalc::CalcOP2F(ExprOP2::op o, T a, T b) {
switch (o)
{
    case ExprOP2::ADD:
        return new cy::Value(a + b);
    case ExprOP2::SUB:
        return new cy::Value(a - b);
    case ExprOP2::MUL:
        return new cy::Value(a * b);
    case ExprOP2::DIV:
        return new cy::Value(a / b);
    case ExprOP2::AND:
        return new cy::Value(a && b);
    case ExprOP2::OR:
        return new cy::Value(a || b);
    case ExprOP2::LT:
        return new cy::Value(a < b);
    case ExprOP2::LTE:
        return new cy::Value(a <= b);
    case ExprOP2::GT:
        return new cy::Value(a > b);
    case ExprOP2::GTE:
        return new cy::Value(a >= b);
    case ExprOP2::EQ:
        return new cy::Value(a == b);
    case ExprOP2::NEQ:
        return new cy::Value(a != b);
    case ExprOP2::B_AND:
    default:
        throw "Unknow floating binary operator.";
    }
}

template <typename T> cy::Value* UtilCalc::CalcOP1(ExprOP1::op o, T a) {
    switch (o)
    {
        case ExprOP1::NEG:
            return new cy::Value(-a);
        case ExprOP1::POS:
            return new cy::Value(+a);
        case ExprOP1::B_NOT:
            return new cy::Value(~a);
        case ExprOP1::NOT:
            return new cy::Value(!a);
        default:
            throw "Unknow integer unary operator.";
    }
}

template <typename T> cy::Value* UtilCalc::CalcOP1F(ExprOP1::op o, T a) {
    switch (o)
    {
        case ExprOP1::NEG:
            return new cy::Value(-a);
        case ExprOP1::POS:
            return new cy::Value(+a);
        case ExprOP1::NOT:
            return new cy::Value(!a);
        default:
            throw "Unknow floating unary operator.";
    }
}
