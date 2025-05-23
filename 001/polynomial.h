#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_
#include <cmath>
#include <map>

class Polynomial {
public:
    std::map<int, double> coef;
    inline Polynomial(){};

    inline Polynomial(double* params, int size) {
        for (int i = 0; i < size; ++i) {
            coef[i] = params[i];
        }
    };

    inline Polynomial(const Polynomial&) = default;

    inline int mySize() {
        int maxCoef = -1;
        for (auto& pair : this->coef) {
            if (pair.second != 0 && pair.first >= maxCoef)
                maxCoef = pair.first;
        }
        return maxCoef + 1;
    }

    inline Polynomial& operator=(const Polynomial& rhs) {
        coef = rhs.coef;
        return *this;
    }

    /* setter */
    inline double& operator[](int index) {
        return coef[index];
    }

    /* Addition */
    inline Polynomial operator+(const Polynomial& rhs) {
        Polynomial p(*this);

        for (const auto& pair : rhs.coef) {
            p.coef[pair.first] += pair.second;
        }

        return p;
    }

    inline Polynomial operator+(double var) {
        Polynomial p(*this);
        p[0] += var;
        return p;
    }

    inline friend Polynomial operator+(double var, const Polynomial& rhs) {
        Polynomial p(rhs);
        return p + var;
    }

    /* Multiplication */
    inline Polynomial operator*(const Polynomial& rhs) {
        Polynomial p;

        for (const auto& p1 : this->coef) {
            for (const auto& p2 : rhs.coef) {
                int pow = p1.first + p2.first;
                p[pow] += p1.second * p2.second;
            }
        }

        return p;
    }

    inline Polynomial operator*(double var) {
        Polynomial p(*this);
        for (auto& pair : this->coef) {
            p[pair.first] *= var;
        }
        return p;
    }

    inline friend Polynomial operator*(double var, const Polynomial& rhs) {
        Polynomial p(rhs);
        return p * var;
    }

    /* Subtraction */
    inline Polynomial operator-(const Polynomial& rhs) {
        Polynomial p(*this);
        auto x = (-1 * rhs);
        return p + (-1 * rhs);
    }

    inline Polynomial operator-(double var) {
        Polynomial p(*this);
        p[0] -= var;
        return p;
    }

    inline friend Polynomial operator-(double var, const Polynomial& rhs) {
        Polynomial p(rhs);
        return var + (-1 * rhs);
    }
};

inline double evaluate(const Polynomial& poly, const double& var) {
    double result = 0;
    for (const auto& pair : poly.coef) {
        result += pow(var, pair.first) * pair.second;
    }
    return result;
}
#endif