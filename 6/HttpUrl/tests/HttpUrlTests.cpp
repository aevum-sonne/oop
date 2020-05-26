#define BOOST_TEST_MODULE HttpUrlTests

#include <HttpUrl/HttpUrl.h>
#include <Protocol/Protocol.h>
#include <UrlParsingError/UrlParsingError.h>
#include <boost/test/unit_test.hpp>
#include <limits>

BOOST_AUTO_TEST_SUITE(verify_correct_initialization_of_constructors)
    BOOST_AUTO_TEST_SUITE(url_constructor_with_1_argument)
        BOOST_AUTO_TEST_CASE(correct_construction_with_correct_url)
        {
            BOOST_CHECK_NO_THROW(HttpUrl httpUrl("https://questionoverflow.com:505/question.txt"));
            BOOST_CHECK_NO_THROW(HttpUrl httpUrl("https://questionoverflow.com/question.txt"));
            BOOST_CHECK_NO_THROW(HttpUrl httpUrl("https://questionoverflow.com"));
        }

        BOOST_AUTO_TEST_CASE(incorrect_construction_with_incorrect_protocol_in_url)
        {
            BOOST_CHECK_THROW(HttpUrl httpUrl("htttps://questionoverflow.com:505/questions/question.txt"), UrlParsingError);
        }

        BOOST_AUTO_TEST_CASE(incorrect_construction_with_incorrect_domain_in_url)
        {
            BOOST_CHECK_THROW(HttpUrl httpUrl("https://questionoverflowcom:505/questions/question.txt"), UrlParsingError);
        }

        BOOST_AUTO_TEST_CASE(incorrect_construction_with_incorrect_port_in_url)
        {
            BOOST_CHECK_THROW(HttpUrl httpUrl("https://questionoverflow.com:2147483647/questions/question.txt"), UrlParsingError);
        }

        BOOST_AUTO_TEST_CASE(incorrect_construction_with_incorrect_document_in_url)
        {
            BOOST_CHECK_THROW(HttpUrl httpUrl("https://questionoverflow.com:505/questions/question"), UrlParsingError);
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(url_constructor_with_3_arguments)
        BOOST_AUTO_TEST_CASE(correct_construction_with_correct_domain_document_protocol_port)
        {
            BOOST_CHECK_NO_THROW(HttpUrl httpUrl("yvideos.com", "all/video.mp4", Protocol::HTTPS));
        }

        BOOST_AUTO_TEST_CASE(incorrect_construction_with_correct_document_protocol_port_and_incorrect_domain)
        {
            BOOST_CHECK_THROW(HttpUrl httpUrl("yvideoscom", "all/video.mp4", Protocol::HTTPS), UrlParsingError);
        }

        BOOST_AUTO_TEST_CASE(correct_construction_with_domain_protocol_port_and_incorrect_document)
        {
            BOOST_CHECK_THROW(HttpUrl httpUrl("yvideos.com", "all/video", Protocol::HTTPS), UrlParsingError);
        }
    BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE(url_constructor_with_4_arguments)
        BOOST_AUTO_TEST_CASE(correct_construction_with_correct_domain_document_protocol_port)
        {
            BOOST_CHECK_NO_THROW(HttpUrl httpUrl("yvideos.com", "video.mp4", Protocol::HTTPS, 88));
        }

        BOOST_AUTO_TEST_CASE(incorrect_construction_with_correct_document_protocol_port_and_incorrect_domain)
        {
            BOOST_CHECK_THROW(HttpUrl httpUrl("yvideoscom", "video.mp4", Protocol::HTTPS, 88), UrlParsingError);
        }

        BOOST_AUTO_TEST_CASE(incorrect_construction_with_correct_domain_protocol_port_and_incorrect_document)
        {
            BOOST_CHECK_THROW(HttpUrl httpUrl("yvideos.com", "video", Protocol::HTTPS, 88), UrlParsingError);
        }
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(correct_port_validation)
    BOOST_AUTO_TEST_CASE(correct_port)
    {
        BOOST_CHECK_NO_THROW(HttpUrl httpsUrl("https://questionoverflow.com/question.txt"));
    }

    BOOST_AUTO_TEST_CASE(empty_port)
    {
        BOOST_CHECK_NO_THROW(HttpUrl httpsUrl("https://questionoverflow.com:/question.txt"));
    }

    BOOST_AUTO_TEST_CASE(set_correct_default_port)
    {
        HttpUrl httpsUrl("https://questionoverflow.com/question.txt");
        BOOST_CHECK(443 == httpsUrl.GetPort());

        HttpUrl httpUrl("http://yvideos.com/videos/video.mp4");
        BOOST_CHECK(80 == httpUrl.GetPort());
    }

    BOOST_AUTO_TEST_CASE(negative_port)
    {
        BOOST_CHECK_THROW(HttpUrl httpsUrl("https://questionoverflow.com:-433/question.txt"), UrlParsingError);
        BOOST_CHECK_THROW(HttpUrl httpsUrl("https://questionoverflow.com:-1/question.txt"), UrlParsingError);
    }

    BOOST_AUTO_TEST_CASE(port_is_greater_unsigned_short)
    {
        BOOST_CHECK_THROW(HttpUrl httpsUrl("https://questionoverflow.com:2147483647/question.txt"), UrlParsingError);
        BOOST_CHECK_THROW(HttpUrl httpsUrl("https://questionoverflow.com:999999999/question.txt"), UrlParsingError);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(correct_print_info_about_url)
    BOOST_AUTO_TEST_CASE(correct_info_output_about_lower_case_url)
    {
        HttpUrl httpsUrl("https://questionoverflow.com/question.txt");
        std::string expectedOut = "URL: https://questionoverflow.com/question.txt\n"
                                  "Protocol: HTTPS\n"
                                  "Domain: questionoverflow.com\n"
                                  "Port: 443\n"
                                  "Document: /question.txt\n";

        std::stringstream ss;
        httpsUrl.Print(ss);

        BOOST_CHECK_EQUAL(expectedOut, ss.str());
    }

    BOOST_AUTO_TEST_CASE(correct_info_output_about_lower_case_url_without_document)
    {
        HttpUrl httpsUrl("https://questionoverflow.com");
        std::string expectedOut = "URL: https://questionoverflow.com/\n"
                                  "Protocol: HTTPS\n"
                                  "Domain: questionoverflow.com\n"
                                  "Port: 443\n"
                                  "Document: /\n";

        std::stringstream ss;
        httpsUrl.Print(ss);

        BOOST_CHECK_EQUAL(expectedOut, ss.str());
    }

    BOOST_AUTO_TEST_CASE(correct_info_output_about_upper_case_url)
    {
        HttpUrl httpsUrl("HTTPS://QUESTIONOVERFLOW.COM/QUESTION.TXT");
        std::string expectedOut = "URL: https://questionoverflow.com/question.txt\n"
                                  "Protocol: HTTPS\n"
                                  "Domain: questionoverflow.com\n"
                                  "Port: 443\n"
                                  "Document: /question.txt\n";

        std::stringstream ss;
        httpsUrl.Print(ss);

        BOOST_CHECK_EQUAL(expectedOut, ss.str());
    }

    BOOST_AUTO_TEST_CASE(correct_info_output_about_mixed_case_url)
    {
        HttpUrl httpsUrl("HttPS://quEsTiOnOverFLow.CoM/questioN.TxT");
        std::string expectedOut = "URL: https://questionoverflow.com/question.txt\n"
                                  "Protocol: HTTPS\n"
                                  "Domain: questionoverflow.com\n"
                                  "Port: 443\n"
                                  "Document: /question.txt\n";

        std::stringstream ss;
        httpsUrl.Print(ss);

        BOOST_CHECK_EQUAL(expectedOut, ss.str());
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(add_slash_to_beginning_of_document_name_if_it_doesnt_have_one)
{
    HttpUrl httpUrl("yvideos.com", "all/video.mp4", Protocol::HTTPS);

    BOOST_CHECK_EQUAL("/all/video.mp4", httpUrl.GetDocument());
}