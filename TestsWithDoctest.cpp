#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "Converter.h"
#include "Cell.h"
#include "CellInterface.h"

TEST_SUITE("Converter tests") 
{

    TEST_CASE("toInt function") 
    {
        Converter converter;

        SUBCASE("Empty string should return default cell") 
        {
            CellInterface<int>* result = converter.toInt("");
            CHECK(result->first() == 0);
            CHECK(result->second() == false);
            delete result;
        }

        SUBCASE("Valid positive integer") 
        {
            CellInterface<int>* result = converter.toInt("123");
            CHECK(result->first() == 123);
            CHECK(result->second() == true);
            delete result;
        }

        SUBCASE("Valid negative integer") 
        {
            CellInterface<int>* result = converter.toInt("-123");
            CHECK(result->first() == -123);
            CHECK(result->second() == true);
            delete result;
        }

        SUBCASE("String with invalid characters should return default cell") 
        {
            CellInterface<int>* result = converter.toInt("123a");
            CHECK(result->first() == 0);
            CHECK(result->second() == false);
            delete result;
        }
    }

    TEST_CASE("toDouble function") 
    {
        Converter converter;

        SUBCASE("Empty string should return default cell") 
        {
            CellInterface<double>* result = converter.toDouble("");
            CHECK(result->first() == 0.0);
            CHECK(result->second() == false);
            delete result;
        }

        SUBCASE("Valid positive double") 
        {
            CellInterface<double>* result = converter.toDouble("123.456");
            CHECK(result->first() == 123.456);
            CHECK(result->second() == true);
            delete result;
        }

        SUBCASE("Valid negative double") 
        {
            CellInterface<double>* result = converter.toDouble("-123.456");
            CHECK(result->first() == -123.456);
            CHECK(result->second() == true);
            delete result;
        }

        SUBCASE("String with invalid characters should return default cell") 
        {
            CellInterface<double>* result = converter.toDouble("123.456a");
            CHECK(result->first() == 0.0);
            CHECK(result->second() == false);
            delete result;
        }
    }

    TEST_CASE("isString function") 
    {
        Converter converter;

        SUBCASE("String enclosed in double quotes should be considered a string") 
        {
            CHECK(converter.isString("\"hello\"") == true);
        }

        SUBCASE("String not enclosed in double quotes should not be considered a string") 
        {
            CHECK(converter.isString("hello") == false);
        }
    }

    TEST_CASE("isNull function") 
    {
        Converter converter;

        SUBCASE("String 'NULL' should be considered null") 
        {
            CHECK(converter.isNull("NULL") == true);
        }

        SUBCASE("Other strings should not be considered null") 
        {
            CHECK(converter.isNull("hello") == false);
            CHECK(converter.isNull("") == false);
        }
    }

    TEST_CASE("convertLineToParametersList function") 
    {
        Converter converter;

        SUBCASE("Single word input") {
            std::vector<std::string> parameters;
            converter.convertLineToParametersList("hello", parameters);
            REQUIRE(parameters.size() == 1);
            CHECK(parameters[0] == "hello");
        }

        SUBCASE("Multiple words input") {
            std::vector<std::string> parameters;
            converter.convertLineToParametersList("hello world", parameters);
            REQUIRE(parameters.size() == 2);
            CHECK(parameters[0] == "hello");
            CHECK(parameters[1] == "world");
        }

        SUBCASE("Quoted strings input") {
            std::vector<std::string> parameters;
            converter.convertLineToParametersList("\"hello world\"", parameters);
            REQUIRE(parameters.size() == 1);
            CHECK(parameters[0] == "\"hello world\"");
        }

        SUBCASE("Mixed input") {
            std::vector<std::string> parameters;
            converter.convertLineToParametersList("say \"hello world\"", parameters);
            REQUIRE(parameters.size() == 2);
            CHECK(parameters[0] == "say");
            CHECK(parameters[1] == "\"hello world\"");
        }

        SUBCASE("Escaped quotes in strings") {
            std::vector<std::string> parameters;
            converter.convertLineToParametersList("\"He said \\\"hello\\\"\"", parameters);
            REQUIRE(parameters.size() == 1);
            CHECK(parameters[0] == "\"He said \"hello\"\"");
        }
    }
}