#include "logger.hpp"

int main() {
    log_info("Application started");
    log_warn("This is a warning");
    log_error("Something went wrong");
    log_info("Application finished");
}
