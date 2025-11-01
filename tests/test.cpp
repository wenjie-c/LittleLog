#include <cstddef>
#include <gtest/gtest.h>
#include <LittleLog.hpp>

using namespace std;

TEST(ConsoleLogTest, LogTest)
{
    ConsoleLogger logger;
    LOG_INFO(logger, "This is an informational message.");
}

TEST(FileLogTest, LogTest)
{
    FileLogger logger("test.log");
    LOG_INFO(logger, "This is an informational message.");
}


int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}