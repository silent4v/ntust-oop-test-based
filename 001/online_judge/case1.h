#ifndef _CASE_H_
#define _CASE_H_
#define DOCTEST_CONFIG_IMPLEMENT
#define SECRET "Q001: CASE 1"
#include "polynomial.h"
#include "test.h"

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

#endif