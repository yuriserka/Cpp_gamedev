#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()

#include "catch.hpp"

unsigned int soma2( unsigned int number ) {
    return number+2;
}

TEST_CASE( "soma 2 are computed", "[soma2]" ) {
    REQUIRE(soma2(0) == 2);
    REQUIRE( soma2(1) == 3 );
    REQUIRE( soma2(3) == 4 );
}