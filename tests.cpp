#include "lib.h"
#include "consumer_out.h"
#include "producer.h"
#include <gtest/gtest.h>

TEST(test_basic, basic_test_set)
{
    testing::internal::CaptureStdout();

    homework::Producer producer(3);
    homework::ConsumerOut consumer_out(std::cout);
    producer.add_customer(&consumer_out);

    producer.produce(std::string("cmd1"));
    producer.produce(std::string("cmd2"));
    producer.produce(std::string("cmd3"));
    producer.produce(std::string("cmd4"));
    producer.produce(std::string("cmd5"));
    producer.flush();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output==std::string(
        "bulk: cmd1, cmd2, cmd3\nbulk: cmd4, cmd5\n"
    ));
}

TEST(test_braces, basic_test_set)
{
    testing::internal::CaptureStdout();

    homework::Producer producer(3);
    homework::ConsumerOut consumer_out(std::cout);
    producer.add_customer(&consumer_out);

    producer.produce(std::string("cmd1"));
    producer.produce(std::string("cmd2"));
    producer.produce(std::string("cmd3"));
    producer.produce(std::string("{"));
    producer.produce(std::string("cmd4"));
    producer.produce(std::string("cmd5"));
    producer.produce(std::string("cmd6"));
    producer.produce(std::string("cmd7"));
    producer.produce(std::string("}"));
    producer.flush();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output==std::string(
        "bulk: cmd1, cmd2, cmd3\nbulk: cmd4, cmd5, cmd6, cmd7\n"
    ));

}

TEST(test_brace_in_brace, basic_test_set)
{
    testing::internal::CaptureStdout();

    homework::Producer producer(3);
    homework::ConsumerOut consumer_out(std::cout);
    producer.add_customer(&consumer_out);

    producer.produce(std::string("{"));
    producer.produce(std::string("cmd1"));
    producer.produce(std::string("cmd2"));
    producer.produce(std::string("{"));
    producer.produce(std::string("cmd3"));
    producer.produce(std::string("cmd4"));
    producer.produce(std::string("}"));
    producer.produce(std::string("cmd5"));
    producer.produce(std::string("cmd6"));
    producer.produce(std::string("}"));
    producer.flush();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_TRUE(output==std::string(
        "bulk: cmd1, cmd2, cmd3, cmd4, cmd5, cmd6\n"
    ));
}

TEST(test_brace_incomplete, basic_test_set)
{
    testing::internal::CaptureStdout();

    homework::Producer producer(3);
    homework::ConsumerOut consumer_out(std::cout);
    producer.add_customer(&consumer_out);

    producer.produce(std::string("cmd1"));
    producer.produce(std::string("cmd2"));
    producer.produce(std::string("cmd3"));
    producer.produce(std::string("{"));
    producer.produce(std::string("cmd4"));
    producer.produce(std::string("cmd5"));
    producer.produce(std::string("cmd6"));
    producer.produce(std::string("cmd7"));
    producer.flush();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output==std::string(
        "bulk: cmd1, cmd2, cmd3\n"
    ));
}

TEST(test_brace_incomplete_2, basic_test_set)
{
    testing::internal::CaptureStdout();

    homework::Producer producer(3);
    homework::ConsumerOut consumer_out(std::cout);
    producer.add_customer(&consumer_out);

    producer.produce(std::string("cmd1"));
    producer.produce(std::string("cmd2"));
    producer.produce(std::string("{"));
    producer.produce(std::string("cmd3"));
    producer.produce(std::string("cmd4"));
    producer.produce(std::string("cmd5"));
    producer.produce(std::string("cmd6"));
    producer.produce(std::string("cmd7"));
    producer.flush();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output==std::string(
        "bulk: cmd1, cmd2\n"
    ));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}