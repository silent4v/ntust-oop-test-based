#ifndef _CASE_H_
#define _CASE_H_
#define DOCTEST_CONFIG_IMPLEMENT
#define SECRET "Q002: CASE 3"
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


TEST_CASE("Case3") {
    INTERCEPTOR
    in << R"(
    Add AND G1
    Add AND G2
    Add XOR G3
    Add OR G4
    Add signal A
    Add signal B
    Add signal C
    Set A True 1.0
    Set C False 0.0
    Set B True 1.5
    Set C True 10.0
    Set A False 3.0
    Set B False 5.7
    Bind A G2 0
    Bind A G1 0
    Bind B G1 1
    Bind C G3 1 
    Bind G1 G2 1
    Bind G1 G4 0
    Bind G1 G3 0
    Bind G3 G4 1
    Query G2 15.5
    Query G2 30.3
    Query G4 30.3
    EXIT
    )";
    OnlineJudge::main();
    std::cout.flush();
    ROLLBACK

    expected << "False\n"
             << "False\n"
             << "True";

    CHECK_EQ(pure(out.str()), pure(expected.str()));
    std::cout << "CHECKPOINT 3";
}
#endif