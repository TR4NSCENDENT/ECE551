#include <sstream>

class Expression {
public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
  long number;
public:
  NumExpression() : number(0) {}
  NumExpression(long n) : number(n) {}
  virtual std::string toString() const {
    std::stringstream s;
    s << number;
    return s.str();
  }
  virtual long evaluate() const {
    return number;
  }
  virtual ~NumExpression() {}
};

class OpExpression : public Expression {
protected:
  Expression * lhs;
  char op; //operator
  Expression * rhs;
public:
  OpExpression(Expression * lhs, char op, Expression * rhs) : lhs(lhs), op(op), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream s;
    s << '(' << lhs->toString() << ' ' << op << ' ' << rhs->toString() << ')';
    return s.str();
  }
  virtual long evaluate() const = 0;
  virtual ~OpExpression() {
    delete lhs;
    delete rhs;
  }
};

class PlusExpression : public OpExpression {
public:
  PlusExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, '+', rhs) {}
  virtual long evaluate() const {
    return lhs->evaluate() + rhs->evaluate();
  }
  virtual ~PlusExpression() {}
};

class MinusExpression : public OpExpression {
public:
  MinusExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, '-', rhs) {}
  virtual long evaluate() const {
    return lhs->evaluate() - rhs->evaluate();
  }
  virtual ~MinusExpression() {}
};

class TimesExpression : public OpExpression {
public:
  TimesExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, '*', rhs) {}
  virtual long evaluate() const {
    return lhs->evaluate() * rhs->evaluate();
  }
  virtual ~TimesExpression() {}
};

class DivExpression : public OpExpression {
public:
  DivExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, '/', rhs) {}
  virtual long evaluate() const {
    return lhs->evaluate() / rhs->evaluate();
  }
  virtual ~DivExpression() {}
};
