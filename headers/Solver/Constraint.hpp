#ifndef CONSTRAINT_HPP
#define CONSTRAINT_HPP

#include <vector>
#include <algorithm>
#include "Variable.hpp"
#include "Variables.hpp"
#include "../MKCGraph.hpp"
#include <string>
#include <new>

enum ConstraintType
{
    EQUAL,          // (=)
    INFERIOR_EQUAL, // (<=)
    SUPERIOR_EQUAL, //(>=)
};

class Constraint
{

private:
protected:
    double lowerBound;
    double upperBound;
    ConstraintType type;

    std::vector<const Variable *> variables;
    std::vector<double> coefficients;

public:
    Constraint() : lowerBound(0.0),
                   upperBound(0.0),
                   type(EQUAL) {}

    Constraint(const std::vector<const Variable *> &vars,
               const std::vector<double> &coef,
               const double &lb,
               const double &ub,
               const ConstraintType &typ) : variables(vars),
                                            coefficients(coef),
                                            lowerBound(lb),
                                            upperBound(ub),
                                            type(typ){};
    Constraint(const Variable **vars,
               double *coef,
               const int &size,
               const double &lb,
               const double &ub,
               const ConstraintType &typ) : lowerBound(lb),
                                            upperBound(ub),
                                            type(typ)
    {
        std::copy(vars, vars + size, std::back_inserter(variables));
        std::copy(coef, coef + size, std::back_inserter(coefficients));
    }

    const Variable *const *get_variables() const
    {
        return &this->variables[0];
    }

    double get_lower_bound() const
    {
        return this->lowerBound;
    }

    size_t size() const
    {
        return this->variables.size();
    }

    double get_upper_bound() const
    {
        return this->upperBound;
    }

    const double *get_coefficients() const
    {
        return &this->coefficients[0];
    }

    ConstraintType get_type() const
    {
        return this->type;
    }

    std::string to_string() const
    {
        int nb_non_zero_variables = this->size();
        std::string strg;
        strg = "Constraint: ";
        strg += std::to_string(get_lower_bound()) + " <= ";
        for (int i = 0; i < nb_non_zero_variables; ++i)
        {
            strg += std::to_string(this->coefficients[i]) + "*x_( idx" + ") + ";
        }

        strg += "<=" + std::to_string(this->get_upper_bound());

        return strg;
    }

    const int *get_indices_variables(const Variables* solver_variables, std::vector<int> & indices_variables) const
    {
        indices_variables.resize(size());

        for (int i=0; i < size(); ++i)
        {
            indices_variables[i] = solver_variables->get_index(variables[i]);
        }

        return &indices_variables[0];
    }

    std::string to_string(const maxkcut::MKCGraph *graph, const Variables* variabless) const
    {
        int nb_non_zero_variables = this->size();
        std::string strg;
        strg = "Constraint: ";
        strg += std::to_string(get_lower_bound()) + " <= ";
        for (int i = 0; i < nb_non_zero_variables; ++i)
        {
            const maxkcut::Edge *edge = graph->get_edges()->get_edge_by_index(variabless->get_index(variables[i]));
            strg += std::to_string(this->coefficients[i]) + "*x_(";
            strg += std::to_string(edge->get_vertex_i()) + ",";
            strg += std::to_string(edge->get_vertex_j()) + ") + ";
        }

        strg += "<=" + std::to_string(this->get_upper_bound());

        return strg;
    }

    bool operator==(const Constraint &other) const
    {
        return this->lowerBound == other.lowerBound &&
               this->upperBound == other.upperBound &&
               this->variables == other.variables &&
               this->coefficients == other.coefficients;
    }

    ~Constraint()
    {
    }
};

#endif
