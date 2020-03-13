#ifndef VARIABLE_SOLVER_HPP
#define VARIABLE_SOLVER_HPP

#include <string>

enum VariableType
{
    CONTINOUS, //
    INTEGER,   //
    SDP,       //
};

class Variable
{
private:
    double lowerBound;
    double upperBound;
    double cost;
    VariableType type = VariableType::CONTINOUS;
    double solution = 0.0;
    std::string code;

public:
    Variable() : lowerBound(0.0), upperBound(0.0), cost(0.0), solution(0.0){};
    Variable(const double &lb,
             const double &ub,
             const double &sol = 0.0,
             const double &cst = 0.0,
             const VariableType typ = VariableType::CONTINOUS,
             const std::string &name = "x") : lowerBound(lb),
                                              upperBound(ub),
                                              cost(cst),
                                              type(typ),
                                              code(name),
                                              solution(sol) {}
    Variable(const Variable &variable) : lowerBound(variable.lowerBound),
                                         upperBound(variable.upperBound),
                                         cost(variable.cost),
                                         type(variable.type),
                                         code(variable.code),
                                         solution(variable.solution) {}

    static Variable *of(const Variable &variable)
    {
        return new Variable(variable.lowerBound,
                            variable.upperBound,
                            variable.solution,
                            variable.cost,
                            variable.type,
                            variable.code);
    }

    double get_lower_bound() const
    {
        return this->lowerBound;
    }

    double get_upper_bound() const
    {
        return this->upperBound;
    }

    double get_cost() const
    {
        return this->cost;
    }

    VariableType get_type() const
    {
        return this->type;
    }

    void update_solution(const double &val)
    {
        this->solution = val;
    }

    double get_solution() const
    {
        return this->solution;
    }

    std::string get_code() const
    {
        return this->code;
    }

    std::string to_string() const
    {
        std::string s;

        s = std::to_string(this->lowerBound) +
            "<= " + this->code + " <= " + std::to_string(this->upperBound);
        s += "; Cost=" + std::to_string(this->cost);
        s += "; Solution=" + std::to_string(this->solution);

        return s;
    }

    ~Variable() {}
};

#endif
