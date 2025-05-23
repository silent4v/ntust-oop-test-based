#ifndef _CASE_H_
#define _CASE_H_
#define DOCTEST_CONFIG_IMPLEMENT
#define SECRET "Q001: CASE 2"
#include "test.h"
#include "polynomial.h"

TEST_CASE("Case2") {
    double quad[] = {3, 2, 1};
    double cubic[] = {1, 2, 0, 3};

    Polynomial q(quad, 3);  // q = 3 + 2x + x^2
    Polynomial c(cubic, 4); // c = 1 + 2x + 0x^2 + 3x^3
    Polynomial p = q;
    Polynomial r = c;

    // --- print("p", p)
    CHECK_EQ(p[0], 3); // term with degree 0 has coefficient 3
    CHECK_EQ(p[1], 2); // term with degree 1 has coefficient 2
    CHECK_EQ(p[2], 1); // term with degree 2 has coefficient 1

    // --- print("r", r)
    CHECK_EQ(r[0], 1); // term with degree 0 has coefficient 1
    CHECK_EQ(r[1], 2); // term with degree 1 has coefficient 2
    CHECK_EQ(r[2], 0); // term with degree 2 has coefficient 0
    CHECK_EQ(r[3], 3); // term with degree 3 has coefficient 3

    // --- q[0] = 6; q[1] = 5;
    q[0] = 6;
    q[1] = 5;

    // --- print("p", p)
    CHECK_EQ(p[0], 3); // unchanged
    CHECK_EQ(p[1], 2);
    CHECK_EQ(p[2], 1);

    // --- c[0] = 6; c[1] = 5;
    c[0] = 6;
    c[1] = 5;

    // --- print("r", r)
    CHECK_EQ(r[0], 1); // still 1
    CHECK_EQ(r[1], 2);
    CHECK_EQ(r[2], 0);
    CHECK_EQ(r[3], 3);

    // --- print("c", c)
    CHECK_EQ(c[0], 6);
    CHECK_EQ(c[1], 5);
    CHECK_EQ(c[2], 0);
    CHECK_EQ(c[3], 3);

    // --- cout << "value of q(2) is " << evaluate(q, 2)
    CHECK(evaluate(q, 2) == doctest::Approx(20)); // 6 + 5*2 + 1*4 = 20

    // --- value of p(2)
    CHECK(evaluate(p, 2) == doctest::Approx(11)); // 3 + 2*2 + 1*4

    // --- value of r(-2)
    CHECK(evaluate(r, -2) == doctest::Approx(-27)); // 1 - 4 + 0 - 24

    // --- value of c(-2)
    CHECK(evaluate(c, -2) == doctest::Approx(-28)); // 6 - 10 + 0 -24

    // --- r * c
    p = r * c;
    CHECK_EQ(p.mySize(), 7); // max degree: 6

    // res = {6, 17, 10, 21, 21, 0, 9}
    CHECK_EQ(p[0], 6);
    CHECK_EQ(p[1], 17);
    CHECK_EQ(p[2], 10);
    CHECK_EQ(p[3], 21);
    CHECK_EQ(p[4], 21);
    CHECK_EQ(p[5], 0);
    CHECK_EQ(p[6], 9);

    // --- value of (r*c)(-2)
    CHECK(evaluate(p, -2) == doctest::Approx(756));

    // --- r * 23
    p = r * 23;
    CHECK_EQ(p.mySize(), 4);
    CHECK_EQ(p[0], 23);
    CHECK_EQ(p[1], 46);
    CHECK_EQ(p[2], 0);
    CHECK_EQ(p[3], 69);
    CHECK(evaluate(p, -2) == doctest::Approx(-621));

    // --- 8 * c
    p = 8 * c;
    CHECK_EQ(p.mySize(), 4);
    CHECK_EQ(p[0], 48);
    CHECK_EQ(p[1], 40);
    CHECK_EQ(p[2], 0);
    CHECK_EQ(p[3], 24);
    CHECK(evaluate(p, -2) == doctest::Approx(-224));

    // --- r + c
    p = r + c;
    CHECK_EQ(p.mySize(), 4);
    CHECK_EQ(p[0], 7); // 1 + 6
    CHECK_EQ(p[1], 7); // 2 + 5
    CHECK_EQ(p[2], 0);
    CHECK_EQ(p[3], 6); // 3 + 3
    CHECK(evaluate(p, -2) == doctest::Approx(-55));

    // --- r + 23
    p = r + 23;
    CHECK_EQ(p.mySize(), 4);
    CHECK_EQ(p[0], 24);
    CHECK_EQ(p[1], 2);
    CHECK_EQ(p[2], 0);
    CHECK_EQ(p[3], 3);
    CHECK(evaluate(p, -2) == doctest::Approx(-4));

    // --- 8 + c
    p = 8 + c;
    CHECK_EQ(p.mySize(), 4);
    CHECK_EQ(p[0], 14);
    CHECK_EQ(p[1], 5);
    CHECK_EQ(p[2], 0);
    CHECK_EQ(p[3], 3);
    CHECK(evaluate(p, -2) == doctest::Approx(-20));

    // --- r - c
    p = r - c;
    CHECK_EQ(p.mySize(), 2);
    CHECK_EQ(p[0], -5);
    CHECK_EQ(p[1], -3);
    CHECK(evaluate(p, -2) == doctest::Approx(1));

    // --- r - 23
    p = r - 23;
    CHECK_EQ(p.mySize(), 4);
    CHECK_EQ(p[0], -22);
    CHECK_EQ(p[1], 2);
    CHECK_EQ(p[3], 3);
    CHECK(evaluate(p, -2) == doctest::Approx(-50));

    // --- 8 - c
    p = 8 - c;
    CHECK_EQ(p.mySize(), 4);
    CHECK_EQ(p[0], 2);
    CHECK_EQ(p[1], -5);
    CHECK_EQ(p[2], 0);
    CHECK_EQ(p[3], -3);
    CHECK(evaluate(p, -2) == doctest::Approx(36));
}

#endif