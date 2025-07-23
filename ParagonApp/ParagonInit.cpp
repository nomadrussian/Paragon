#include "ParagonApplication.hpp"

#include <core/Core.hpp>
#include <util/Log.hpp>

#include <exception>
#include <iostream>
#include <memory>

int main()
{
    std::unique_ptr<ParagonApplication> paragonApp = nullptr;
    Core *core = nullptr;

    log_debug("Starting Paragon...");

    try {
        log_debug("Initializing Core...");
        Core::init();
        log_debug("Creating Paragon instance...");
        paragonApp = std::make_unique<ParagonApplication>();
    }  catch (const std::exception& e) {
        log_error(std::string("Failed to launch: ") + e.what());
        return -1;
    }

    core = &Core::getInstance();

    log_debug("Connecting Paragon to Core...");
    core->setApplicationInstance(std::move(paragonApp));

    try {
        log_debug("Launching Core...");
        core->run();
    } catch (const std::exception& e) {
        log_error(std::string("Fatal exception while running Paragon: ") + e.what());
    }

    log_debug("Shutting down...");

    return 0;
}
