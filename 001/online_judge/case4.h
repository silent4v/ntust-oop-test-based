#ifndef _CASE_H_
#define _CASE_H_
#define DOCTEST_CONFIG_IMPLEMENT
#define SECRET "Q001: CASE 4"
#include "polynomial.h"
#include "test.h"

TEST_CASE("Case4") {
    double quad[] = {7, 7, 7, 7}; // q = 7 + 7x + 7x^2 + 7x^3
    double cubic[] = {8};         // c = 8
    Polynomial q(quad, 4);
    Polynomial c(cubic, 1);
    Polynomial p = q;
    Polynomial r = c;

    // print("r", r)
    CHECK_EQ(r[0], 8); // term with degree 0 has coefficient 8

    // print("p", p)
    CHECK_EQ(p[0], 7);
    CHECK_EQ(p[1], 7);
    CHECK_EQ(p[2], 7);
    CHECK_EQ(p[3], 7);

    c[1] = 62;
    c[0] = 78;

    // print("r", r)
    CHECK_EQ(r[0], 8);

    q[1] = 23;
    q[0] = 19;

    // print("p", p)
    CHECK_EQ(p[0], 7);
    CHECK_EQ(p[1], 7);
    CHECK_EQ(p[2], 7);
    CHECK_EQ(p[3], 7);

    // value of q(3)
    CHECK(evaluate(q, 3) == doctest::Approx(340));

    // value of p(3)
    CHECK(evaluate(p, 3) == doctest::Approx(280));

    // value of r(-2)
    CHECK(evaluate(r, -2) == doctest::Approx(8));

    // value of c(6)
    CHECK(evaluate(c, 6) == doctest::Approx(450));

    // r * c
    p = r * c;
    CHECK_EQ(p.mySize(), 2);
    CHECK(evaluate(p, -2) == doctest::Approx(-368));

    // r * 88
    p = r * 88;
    CHECK_EQ(p.mySize(), 1);
    CHECK(evaluate(p, -2) == doctest::Approx(704));

    // 77 * c
    p = 77 * c;
    CHECK_EQ(p.mySize(), 2);
    CHECK(evaluate(p, -2) == doctest::Approx(-3542));

    // r + c
    p = r + c;
    CHECK_EQ(p.mySize(), 2);
    CHECK(evaluate(p, -2) == doctest::Approx(-38));

    // r + 88
    p = r + 88;
    CHECK_EQ(p.mySize(), 1);
    CHECK(evaluate(p, -2) == doctest::Approx(96));

    // 77 + c
    p = 77 + c;
    CHECK_EQ(p.mySize(), 2);
    CHECK(evaluate(p, -2) == doctest::Approx(31));

    // r - c
    p = r - c;
    CHECK_EQ(p.mySize(), 2);
    CHECK(evaluate(p, 44) == doctest::Approx(-2798));

    // r - 88
    p = r - 88;
    CHECK_EQ(p.mySize(), 1);
    CHECK(evaluate(p, -2) == doctest::Approx(-80));

    // 77 - c
    p = 77 - c;
    CHECK_EQ(p.mySize(), 2);
    CHECK(evaluate(p, -2) == doctest::Approx(123));
}

#endif