#ifndef _CASE_H_
#define _CASE_H_
#define DOCTEST_CONFIG_IMPLEMENT
#define SECRET "Q002: CASE 4"
#include "circuit.h"
#include "test.h"
#include <cctype>
#include <string>

#define INTERCEPTOR                                  \
    std::streambuf* __orig_cout = std::cout.rdbuf(); \
    std::streambuf* __orig_cin = std::cin.rdbuf();   \
    std::stringstream in{}, out{}, expected{};       \
    std::cin.rdbuf(in.rdbuf());                      \
    std::cout.rdbuf(out.rdbuf());

#define ROLLBACK                \
    std::cin.rdbuf(__orig_cin); \
    std::cout.rdbuf(__orig_cout);


TEST_CASE("Case4") {
    INTERCEPTOR
    in << R"(
    Add XOR G1
    Add AND G2
    Add XOR G3
    Add AND G4
    Add OR G5
    Add signal A
    Add signal B
    Add signal C
    Set A True 0.0
    Set A False 5.0
    Set B False 3.7
    Set C True 0.3
    Set B True 13.0
    Bind A G1 0
    Bind B G1 1
    Bind C G3 1
    Bind C G4 0
    Bind A G2 0
    Bind B G2 1
    Bind G1 G3 0
    Bind G1 G4 1
    Bind G4 G5 0
    Bind G2 G5 1
    Query G2 6.0
    EXIT
    )";
    OnlineJudge::main();
    std::cout.flush();
    ROLLBACK

    expected << "False\n";

    CHECK_EQ(pure(out.str()), pure(expected.str()));
    std::cout << "CHECKPOINT 4";
}
#endif