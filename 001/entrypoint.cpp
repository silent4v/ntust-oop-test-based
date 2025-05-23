#ifdef ONLINE_JUDGE
#    include CASE
#    include "test.h"
#    include <sstream>
#    include <string>

inline std::string buildError(std::stringstream& oss) {
    if (oss.tellp() != 0) {
        std::stringstream builder;
        while (!oss.eof()) {
            std::string s;
            std::getline(oss, s);
            if (s == "==============================================================="
                     "================")
                continue;
            builder << s << "\\n";
        }
        builder << '\n';
        return builder.str();
    } else {
        return "";
    }
}

int main(int argc, char** argv) {
    std::stringstream err_ss;
    doctest::Context ctx;
    ctx.setOption("no-intro", true);
    ctx.setOption("no-version", true);
    ctx.setOption("no-path-filenames", true);
    ctx.setOption("no-line-numbers", true);
    ctx.setOption("no-breaks", true);
    ctx.setOption("success", false);
    ctx.setOption("minimal", true);

    ctx.setCout(&err_ss);
    auto exitCode = ctx.run();
    std::cout << buildError(err_ss);
    if (exitCode != 0) {
        std::cout << "Test Fail";
    } else {
        std::cout << "Test Pass:" << std::endl << SECRET;
    }
    return exitCode;
}
#else
#    include "case.h"
#    include "test.h"

// clang-format off
/**
 * @brief description of options  
 * | Option Name        | Description                                                     |
 * | ------------------ | --------------------------------------------------------------- |
 * | no-intro           | Disables the intro banner shown before test execution           |
 * | no-version         | Suppresses the doctest version number in output                 |
 * | no-path-filenames  | Strips directory paths from filenames in reported test failures |
 * | no-line-numbers    | Omits line numbers from reported test failure locations         |
 * | no-breaks          | Disables breaking into the debugger on test failures            |
 * | success            | Enables printing of passed test cases                           |
 * | minimal            | Enables minimal output mode: only test summary is printed       |
 */
// clang-format on

int main(int argc, char** argv) {
    std::stringstream err_ss;
    doctest::Context ctx;
    ctx.setOption("no-intro", true);
    ctx.setOption("no-version", true);
    ctx.setOption("no-path-filenames", false);
    ctx.setOption("no-line-numbers", false);
    ctx.setOption("no-breaks", false);
    ctx.setOption("success", true);
    ctx.setOption("minimal", true);
    return ctx.run();
}
#endif
