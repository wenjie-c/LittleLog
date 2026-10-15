#include <cstddef>
#include <gtest/gtest.h>
#include <LittleLog.hpp>

using namespace std;

TEST(ConsoleLogTest, LogTest)
{
    ConsoleLogger logger;
    LOG_INFO(logger, "This is an informational message.");
    LOG_WARNING(logger, "This is a warning message.");
    LOG_ERROR(logger, "This is an error message.");
}

TEST(FileLogTest, LogTest)
{
    FileLogger logger("test.log");
    LOG_INFO(logger, "This is an informational message.");
    LOG_WARNING(logger, "This is a warning message.");
    LOG_ERROR(logger, "This is an error message.");
}


int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}