#ifndef _CASE_H_
#define _CASE_H_
#define DOCTEST_CONFIG_IMPLEMENT
#include "test.h"
#include "polynomial.h"

TEST_CASE("Case1") {
    double one[] = {1};
    double quad[] = {3, 2, 1};     // q = 3 + 2x + x^2
    double cubic[] = {1, 2, 0, 3}; // c = 1 + 2x + 0x^2 + 3x^3

    Polynomial empty;
    Polynomial One(one, 1);
    Polynomial q(quad, 3);
    Polynomial c(cubic, 4);
    Polynomial p = q; // test copy constructor
    Polynomial r;

    r = q; // operator=
    r = c; // overwrite r

    // Polynomial q
    CHECK_EQ(q[0], 3); // term with degree 0 has coefficient 3
    CHECK_EQ(q[1], 2); // term with degree 1 has coefficient 2
    CHECK_EQ(q[2], 1); // term with degree 2 has coefficient 1

    // Polynomial c
    CHECK_EQ(c[0], 1);
    CHECK_EQ(c[1], 2);
    CHECK_EQ(c[2], 0);
    CHECK_EQ(c[3], 3);

    // value of q(2)
    CHECK(evaluate(q, 2) == doctest::Approx(11)); // 3 + 2*2 + 1*4 = 11

    // value of p(2)
    CHECK(evaluate(p, 2) == doctest::Approx(11)); // same as q

    // value of r(2)
    CHECK(evaluate(r, 2) == doctest::Approx(29)); // same as c

    // value of c(2)
    CHECK(evaluate(c, 2) == doctest::Approx(29));

    // q + c
    r = q + c;
    CHECK(evaluate(r, 2) == doctest::Approx(40)); // (q+c)(2)

    // q - c
    r = q - c;
    CHECK(evaluate(r, 2) == doctest::Approx(-18)); // (q-c)(2)

    // q * c
    r = q * c;
    CHECK_EQ(r.mySize(), 6);

    // Polynomial r (= q * c)
    CHECK_EQ(r[0], 3);
    CHECK_EQ(r[1], 8);
    CHECK_EQ(r[2], 5);
    CHECK_EQ(r[3], 11);
    CHECK_EQ(r[4], 6);
    CHECK_EQ(r[5], 3);

    // value of (q * c)(2)
    CHECK(evaluate(r, 2) == doctest::Approx(319));
}

TEST_CASE("Case2") {
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