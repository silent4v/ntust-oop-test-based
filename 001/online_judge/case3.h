#ifndef _CASE_H_
#define _CASE_H_
#define DOCTEST_CONFIG_IMPLEMENT
#define SECRET "Q001: CASE 3"
#include "polynomial.h"
#include "test.h"

TEST_CASE("Case3") {
    double quad[] = {6, 6, 6};           // q = 6 + 6x + 6x^2
    double cubic[] = {7, 3, 5, 1, 6, 8}; // c = 7 + 3x + 5x^2 + x^3 + 6x^4 + 8x^5

    Polynomial q(quad, 3);
    Polynomial c(cubic, 6);
    Polynomial p = q;
    Polynomial r = c;

    // print("r", r)
    CHECK_EQ(r[0], 7);
    CHECK_EQ(r[1], 3);
    CHECK_EQ(r[2], 5);
    CHECK_EQ(r[3], 1);
    CHECK_EQ(r[4], 6);
    CHECK_EQ(r[5], 8);

    // print("p", p)
    CHECK_EQ(p[0], 6);
    CHECK_EQ(p[1], 6);
    CHECK_EQ(p[2], 6);

    c[1] = 5;
    c[0] = 6;

    // print("r", r)
    CHECK_EQ(r[0], 7);
    CHECK_EQ(r[1], 3);
    CHECK_EQ(r[2], 5);
    CHECK_EQ(r[3], 1);
    CHECK_EQ(r[4], 6);
    CHECK_EQ(r[5], 8);

    q[1] = 5;
    q[0] = 6;

    // print("p", p)
    CHECK_EQ(p[0], 6);
    CHECK_EQ(p[1], 6);
    CHECK_EQ(p[2], 6);

    // value of q(3)
    CHECK(evaluate(q, 3) == doctest::Approx(75)); // 6 + 5*3 + 6*9 = 75

    // value of p(3)
    CHECK(evaluate(p, 3) == doctest::Approx(78)); // 6 + 6*3 + 6*9 = 78

    // value of r(-2)
    CHECK(evaluate(r, -2) == doctest::Approx(-147));

    // value of c(6)
    CHECK(evaluate(c, 6) == doctest::Approx(70416));

    // r * c
    p = r * c;
    CHECK_EQ(p.mySize(), 11);
    CHECK(evaluate(p, -2) == doctest::Approx(22344));

    // r * 88
    p = r * 88;
    CHECK_EQ(p.mySize(), 6);
    CHECK(evaluate(p, -2) == doctest::Approx(-12936));

    // 77 * c
    p = 77 * c;
    CHECK_EQ(p.mySize(), 6);
    CHECK(evaluate(p, -2) == doctest::Approx(-11704));

    // r + c
    p = r + c;
    CHECK_EQ(p.mySize(), 6);
    CHECK(evaluate(p, -2) == doctest::Approx(-299));

    // r + 88
    p = r + 88;
    CHECK_EQ(p.mySize(), 6);
    CHECK(evaluate(p, -2) == doctest::Approx(-59));

    // 77 + c
    p = 77 + c;
    CHECK_EQ(p.mySize(), 6);
    CHECK(evaluate(p, -2) == doctest::Approx(-75));

    // r - c
    p = r - c;
    CHECK_EQ(p.mySize(), 2);
    CHECK(evaluate(p, -2) == doctest::Approx(5));

    // r - 88
    p = r - 88;
    CHECK_EQ(p.mySize(), 6);
    CHECK(evaluate(p, -2) == doctest::Approx(-235));

    // 77 - c
    p = 77 - c;
    CHECK_EQ(p.mySize(), 6);
    CHECK(evaluate(p, -2) == doctest::Approx(229));
}

#endif