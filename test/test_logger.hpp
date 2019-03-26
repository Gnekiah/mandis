#ifndef MANDIS_TEST_LOGGER_HPP_
#define MANDIS_TEST_LOGGER_HPP_

#include <boost/filesystem.hpp>

#include "../include/logger.h"
#include "../include/timelib.h"

bool TestLoggerCase1() {
    timelib::Time time;
    std::string log_path = (boost::filesystem::temp_directory_path() / "mandis.log").string();
    logger::Logger *logger = new logger::Logger(log_path, LOG_LEVEL_TRACE);
    logger->Start();
    LOG_ERROR(logger, "Error");
    LOG_WARNING(logger, "Warning");
    LOG_INFO(logger, "Information");
    LOG_DEBUG(logger, "Debug");
    LOG_TRACE(logger, "Trace");
    time.MilliSleep(100);
    logger->Stop();
    logger->Join();
    return 0;
}


#endif // !MANDIS_TEST_LOGGER_HPP_

