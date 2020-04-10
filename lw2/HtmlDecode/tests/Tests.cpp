#include "Tests.h"

TEST_CASE("No arguments")
{
    const char* stream[] = {
            NULL
    };
    Args args;

    REQUIRE(args.ParseArgs(1, stream) == std::nullopt);
}

TEST_CASE("Empty string")
{
    expectedHtml = "";
    testHtml = "";
    resultHtml = HtmlDecode(testHtml);

    REQUIRE(resultHtml == expectedHtml);
}

TEST_CASE("String without HTML entities")
{
    expectedHtml = "123456789 987654321 && ;;; '''''";
    testHtml = "123456789 987654321 && ;;; '''''";
    resultHtml = HtmlDecode(testHtml);

    REQUIRE(resultHtml == expectedHtml);
}

TEST_CASE("String with HTML entities")
{
    expectedHtml = "Cat <says> \"Meow\". M&M's";
    testHtml = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
    resultHtml = HtmlDecode(testHtml);

    REQUIRE(resultHtml == expectedHtml);
}

TEST_CASE("String with all HTML entities")
{
    expectedHtml = "&&&& ''' <>\"\"\"";
    testHtml = "&amp;&amp;&amp;&amp; &apos;&apos;&apos; &lt;&gt;&quot;&quot;&quot;";
    resultHtml = HtmlDecode(testHtml);

    REQUIRE(resultHtml == expectedHtml);
}