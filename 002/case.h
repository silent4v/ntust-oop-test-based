#ifndef _CASE_H_
#define _CASE_H_
#define DOCTEST_CONFIG_IMPLEMENT
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

inline std::string pure(const std::string& str) {
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    if (end == std::string::npos)
        return "";
    auto trimmed = str.substr(0, end + 1);
    std::string escaped = "`";
    // clang-format off
    for (char ch : trimmed) {
        switch (ch) {
            case '\n': escaped += "\\n"; break;
            case '\t': escaped += "\\t"; break;
            case '\r': escaped += "\\r"; break;
            case '\f': escaped += "\\f"; break;
            case '\v': escaped += "\\v"; break;
            case '\\': escaped += "\\\\"; break;
            default:
                if (std::isprint(static_cast<unsigned char>(ch)))
                    escaped += ch;
                else {
                    char buf[5];
                    std::snprintf(buf, sizeof(buf), "\\x%02X", static_cast<unsigned char>(ch));
                    escaped += buf;
                }
        }
    }
    // clang-format on
    escaped += "`";
    return escaped;
}

TEST_CASE("Case1") {
    INTERCEPTOR
    in << R"(
    Add signal A 
    Set A True 5.0 
    Add signal B 
    Set B True 3.0 
    Add AND G1 
    Bind A G1 0 
    Bind B G1 1 
    Query G1 9.0 
    Query G1 13.0 
    EXIT
    )";
    std::cout.flush();
    OnlineJudge::main();
    ROLLBACK

    expected << "True\n"
             << "True";

    CHECK_EQ(pure(out.str()), pure(expected.str()));
}


TEST_CASE("Case2") {
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
}

TEST_CASE("Case3") {
    INTERCEPTOR
    in << R"(
    Add NAND G1
    Add XOR G2
    Add NOT G3
    Add AND  G4
    Add OR G5
    Add signal A
    Add signal B
    Add signal C
    Set A True 3.0
    Set B True 0.0
    Set B False 5.0
    Set C True 4.3
    Set C False 9.7
    Bind A G1 0
    Bind B G1 1 
    Bind A G2 0
    Bind B G2 1
    Bind G1 G3 0
    Bind G3 G4 0
    Bind C G4 1
    Bind G4 G5 0
    Bind G2 G5 1
    Query G1 18.0
    Query G2 18.0
    Query G4 18.0
    Query G4 29.0
    Query G4 37.0
    Query G5 29.0
    EXIT
    )";
    OnlineJudge::main();
    std::cout.flush();
    ROLLBACK

    expected << "True\n"
             << "True\n"
             << "False\n"
             << "False\n"
             << "False\n"
             << "True\n";

    CHECK_EQ(pure(out.str()), pure(expected.str()));
}

#endif