#include "logger.hpp"

int main() {
    log_info("Application started");
    log_info("Processing data...");
    log_error("Something went wrong");
    log_info("Application finished");
    return 0;
}
