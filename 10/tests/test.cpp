#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"

#include "../parser.hpp"
#include <string>
#include <array>
#include <sstream>

std::stringstream testinput(
    R":([({(<(())[]>[[{[]{<()<>>
[(()[<>])]({[<{<<[]>>(
{([(<{}[<>[]}>{[]{[(<()>
(((({<>}<{<{<>}{[]{[]{}
[[<[([]))<([[{}[[()]]]
[{[{({}]{}}([{[{{{}}([]
{<[[]]>}<{[{[{[]{()[[[]
[<(<(<(<{}))><([]([]()
<{([([[(<>()){}]>(<<{{
<{([{{}}[<[[[<>{}]]]>[]]):" );

TEST_CASE("Line Checker", "[Parser]"){

    char result;
    std::string test;

    //1
    testinput >> test;
    result = checkline(test);
    REQUIRE(result == '\0');
    
    /*WARNING: test buffer string is dirty. Could fail if next line is shorter
    correct with test.clear() before next read.  */
    testinput >> test;
    result = checkline(test);
    REQUIRE(result == '\0');
    

    //3
    testinput >> test;
    result = checkline(test);
    REQUIRE(result == '}');
    

    testinput >> test;
    result = checkline(test);
    REQUIRE(result == '\0');
    

    // 5 
    testinput >> test;
    result = checkline(test);
    REQUIRE(result == ')');
    

    // 6 ]
    testinput >> test;
    result = checkline(test);
    REQUIRE(result == ']');
    

    // 7 OK
    testinput >> test;
    result = checkline(test);
    REQUIRE(result == '\0');

    // 8 )
    testinput >> test;
    result = checkline(test);
    REQUIRE(result == ')');

    //9 >
    testinput >> test;
    result = checkline(test);
    REQUIRE(result == '>');

    // 10 OK
    testinput >> test;
    result = checkline(test);
    REQUIRE(result == '\0');

}

TEST_CASE("Scoring", "[Score]"){
    REQUIRE(getscore(')') == 3);
    REQUIRE(getscore(']') == 57);
    REQUIRE(getscore('}') == 1197);
    REQUIRE(getscore('>') == 25137);
    REQUIRE(getscore('a') == 0);
}

TEST_CASE("Complements", "[Parser]"){
    REQUIRE(complement('(') == ')');
    REQUIRE(complement('[') == ']');
    REQUIRE(complement('{') == '}');
    REQUIRE(complement('<') == '>');
    REQUIRE(complement('a') == '\0');
}


TEST_CASE("Scoring Functions", "[Scoring]"){
    scores.clear();
    scores.emplace_back(15);
    scores.emplace_back(10);
    scores.emplace_back(20);

    SECTION("Sorts Final Scores"){
        auto finalscore = getincomplete();
        REQUIRE(scores[0] == 10);
        REQUIRE(scores[1] == 15);
        REQUIRE(scores[2] == 20);
    }

    SECTION("Returns correct answer"){
        auto finalscore = getincomplete();
        REQUIRE(finalscore == 15);
    }
}

TEST_CASE("Scoring Incomplete Brackets", "[Scoring]"){
    using namespace std::string_literals;
    incompletes.clear();
    scores.clear();
    incompletes.push_back(")]}>"s);

    constexpr int targetscore = 5*(5*(5*((5*0) + 1) + 2) + 3) + 4;
    scoreincomplete();
    auto finalscore = getincomplete();

    REQUIRE(finalscore == targetscore);
}