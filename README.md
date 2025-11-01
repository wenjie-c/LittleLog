# What is this?
This is a little and lightweight library for logging. You can include `LittleLog.hpp` as a header-only library.
It is based on this post [Leonardo](https://leo88.medium.com/devlog-writing-a-logging-library-in-c-9601ec3699eb).
# How to use?
1. Declare a Logger-derived object. `ConsoleLogger logger;`
2. Use LOG macros functions. `LOG_INFO(logger, "This is useful.")`

There are 5 levels of log: `LOG_DEBUG` , `LOG_INFO`, `LOG_WARNING`, `LOG_ERROR`, `LOG_CRITICAL`.
