#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"

TEST_CASE("Check step function", "[Helper]"){
    bool a{true};
    REQUIRE(a);
    REQUIRE_FALSE(!a);
}
