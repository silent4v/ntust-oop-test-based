#ifndef _CASE_H_
#define _CASE_H_
#define DOCTEST_CONFIG_IMPLEMENT
#define SECRET "Q001: CASE 5"
#include "polynomial.h"
#include "test.h"

TEST_CASE("Case5") {
    // Construct two sparse polynomials with degree 99
    std::vector<double> f_coef(100, 0.0);
    std::vector<double> g_coef(100, 0.0);
    f_coef[99] = 2;
    g_coef[99] = 3;

    Polynomial f(f_coef.data(), f_coef.size()); // f(x) = 2 * x^99
    Polynomial g(g_coef.data(), g_coef.size()); // g(x) = 3 * x^99

    // Verify only the highest-degree term is non-zero
    CHECK_EQ(f[99], 2);
    CHECK_EQ(g[99], 3);
    for (int i = 0; i < 99; ++i) {
        CHECK_EQ(f[i], 0);
        CHECK_EQ(g[i], 0);
    }

    // f + g = 5 * x^99
    Polynomial sum = f + g;
    CHECK_EQ(sum.mySize(), 100);
    CHECK_EQ(sum[99], 5);
    CHECK_EQ(evaluate(sum, 1), 5);
    CHECK_EQ(evaluate(sum, 2), 5 * std::pow(2, 99));

    // f - g = -1 * x^99
    Polynomial diff = f - g;
    CHECK_EQ(diff.mySize(), 100);
    CHECK_EQ(diff[99], -1);
    CHECK_EQ(evaluate(diff, 1), -1);

    // f * g = 6 * x^198
    Polynomial prod = f * g;
    CHECK_EQ(prod.mySize(), 199);
    for (int i = 0; i < 198; ++i) {
        CHECK_EQ(prod[i], 0);
    }
    CHECK_EQ(prod[198], 6);
    CHECK_EQ(evaluate(prod, 1), 6);
}


#endif