#define BOOST_TEST_MODULE MyListTests

#include <MyList/MyList.h>
#include <boost/test/unit_test.hpp>
#include <string>

BOOST_AUTO_TEST_SUITE(my_list_constructor)
    BOOST_AUTO_TEST_CASE(correct_list_construction)
    {
        BOOST_CHECK_NO_THROW(MyList<bool> myListOfBooleans);
        BOOST_CHECK_NO_THROW(MyList<int> myListOfIntegers);
        BOOST_CHECK_NO_THROW(MyList<double> myListOfDoubles);
        BOOST_CHECK_NO_THROW(MyList<char> myListOfChars);
        BOOST_CHECK_NO_THROW(MyList<std::string> myListOfStrings);
    }

    BOOST_AUTO_TEST_CASE(no_throw_deep_copy_construction_empty)
    {
        MyList<int> list1;

        BOOST_CHECK_NO_THROW(auto list2 = list1);
    }

    BOOST_AUTO_TEST_CASE(no_throw_deep_copy_construction_non_empty)
    {
        MyList<int> list1;
        list1.push_back(0);
        list1.push_back(1);
        list1.push_back(2);
        list1.push_front(-1);
        list1.push_front(-2);

        BOOST_CHECK_NO_THROW(auto list2 = list1);
    }

    BOOST_AUTO_TEST_CASE(correct_values_deep_copy_construction_int)
    {
        MyList<int> list1;
        list1.push_back(0);
        list1.push_back(1);
        list1.push_back(2);

        auto list2 = list1;

        BOOST_CHECK_EQUAL(list1, list2);
    }

    BOOST_AUTO_TEST_CASE(correct_values_deep_copy_construction_string)
    {
        MyList<std::string> list1;
        list1.push_back("ss\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
        list1.push_back("tt@@@@####$$");
        list1.push_back("r4948848484jdfdfkldkfjr");

        auto list2 = list1;

        BOOST_CHECK_EQUAL(list1, list2);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(my_list_iterator)
    BOOST_AUTO_TEST_CASE(no_throw_call_all_methods_that_returns_iterator)
    {
        MyList<std::string> list;
        list.push_back("ss\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
        list.push_back("tt@@@@####$$");
        list.push_back("r4948848484jdfdfkldkfjr");

        BOOST_CHECK_NO_THROW(MyList<std::string>::iterator it = list.begin());
        BOOST_CHECK_NO_THROW(MyList<std::string>::iterator it = list.end());
        BOOST_CHECK_NO_THROW(MyList<std::string>::reverse_iterator it = list.rbegin());
        BOOST_CHECK_NO_THROW(MyList<std::string>::reverse_iterator it = list.rend());
    }

    BOOST_AUTO_TEST_CASE(verify_iterator_begin_method)
    {
        MyList<std::string> list;
        list.push_back("str");
        list.push_back("trs");
        list.push_back("st");

        auto it = list.begin();

        BOOST_CHECK_EQUAL(*it, list.front());
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(data_manipulation_in_list)
    BOOST_AUTO_TEST_CASE(correct_push_back_in_list)
    {
        MyList<char> list;
        list.push_back('a');
        list.push_back('b');
        list.push_back('c');

        BOOST_CHECK_EQUAL('a', list.front());
        BOOST_CHECK_EQUAL('c', list.back());

        std::string expected = "a b c";
        std::stringstream ss;
        ss << list;

        BOOST_CHECK_EQUAL(expected, ss.str());
    }

    BOOST_AUTO_TEST_CASE(correct_push_front_in_list)
    {
        MyList<int> list;
        list.push_front(9);
        list.push_front(8);
        list.push_front(7);
        list.push_front(1);

        BOOST_CHECK_EQUAL(1, list.front());
        BOOST_CHECK_EQUAL(9, list.back());

        std::string expected = "1 7 8 9";
        std::stringstream ss;
        ss << list;

        BOOST_CHECK_EQUAL(expected, ss.str());
    }

    BOOST_AUTO_TEST_CASE(verify_iterator_insert_method)
    {
        MyList<std::string> list;
        list.push_back("str");
        list.push_back("trs");
        list.push_back("st");

        auto it = list.begin();
        list.insert(it, "first string");
        std::string expected = "first string";

        BOOST_CHECK_EQUAL(expected, list.front());

        expected = "last string";
        ++it;
        list.insert(++it, "last string");

        BOOST_CHECK_EQUAL(expected, list.back());
    }

    BOOST_AUTO_TEST_CASE(verify_iterator_remove_method)
    {
        MyList<int> list;
        list.push_back(3);
        list.push_back(4);
        list.push_back(5);
        list.push_front(2);
        list.push_front(1);
        list.push_front(0);
        list.push_front(0);
        list.push_front(0);

        list.remove(0);

        MyList<int> expected;
        expected.push_back(3);
        expected.push_back(4);
        expected.push_back(5);
        expected.push_front(2);
        expected.push_front(1);

        BOOST_CHECK_EQUAL(expected, list);
    }

    BOOST_AUTO_TEST_CASE(verify_iterator_erase_method)
    {
        MyList<std::string> list;
        list.push_back("str");
        list.push_back("trs");
        list.push_back("st");

        auto it = list.begin();
        list.erase(it);
        std::string expected = "trs";

        BOOST_CHECK_EQUAL(expected, list.front());
    }
BOOST_AUTO_TEST_SUITE_END()