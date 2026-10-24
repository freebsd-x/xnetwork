#include "xserver/network_service.h"
#include "shared/protocol.h"
#include "shared/logger.h"
#include "xserver/crash_handler.h"
#include <csignal>
#include <unistd.h>
#include <atomic>

static std::atomic<bool> g_running{true};

static void signal_handler(int) {
    g_running = false;
}

int main() {
    fbx::shared::Logger::init("xnetwork");
    fbx::xserver::installCrashHandler("xnetwork");
    LOG_INFO("xnetwork starting...");

    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);

    LOG_INFO("NetworkService running. Waiting for SIGTERM/SIGINT.");

    // NetworkService is stateless (all methods are static); the IPC socket
    // is managed by the compositor. This daemon is a placeholder for running
    // NetworkService as a standalone process in the future.
    while (g_running) {
        pause();
    }

    LOG_INFO("xnetwork shutting down.");
    return 0;
}
