#include <stdint.h>
#include <stdbool.h>

namespace IMU {
    void init();
    void update();
}

namespace Fusion {
    void init();
    void update();
}

namespace Control {
    void init();
    void update();
}

namespace Comms {
    void init();
    void sendTelemetry();
    void receiveCommands();
}

namespace Safety {
    void init();
    void check();
}

// Timing Needs to be fix later!
uint32_t millis();

//  Task intervals in ms 
#define IMU_INTERVAL        5    // 200 Hz
#define FUSION_INTERVAL     5    // 200 Hz
#define CONTROL_INTERVAL    5    // 200 Hz
#define COMMS_TX_INTERVAL   20   // 50 Hz
#define COMMS_RX_INTERVAL   10   // 100 Hz
#define SAFETY_INTERVAL     10   // 100 Hz

// ---- Last execution timestamps ----
static uint32_t lastIMU = 0;
static uint32_t lastFusion = 0;
static uint32_t lastControl = 0;
static uint32_t lastCommsTX = 0;
static uint32_t lastCommsRX = 0;
static uint32_t lastSafety = 0;


void runtime_init() {
    IMU::init();
    Fusion::init();
    Control::init();
    Comms::init();
    Safety::init();
}

// ---- Runtime Loop ----
void runtime_loop() {
    uint32_t now = millis();

    // ---- IMU Update ----
    if (now - lastIMU >= IMU_INTERVAL) {
        lastIMU = now;
        IMU::update();
    }

    // ---- Sensor Fusion ----
    if (now - lastFusion >= FUSION_INTERVAL) {
        lastFusion = now;
        Fusion::update();
    }

    // ---- Control Loop ----
    if (now - lastControl >= CONTROL_INTERVAL) {
        lastControl = now;
        Control::update();
    }

    // Receive Commands 
    if (now - lastCommsRX >= COMMS_RX_INTERVAL) {
        lastCommsRX = now;
        Comms::receiveCommands();
    }

    // Telemetry (ESP32 → Pi) 
    if (now - lastCommsTX >= COMMS_TX_INTERVAL) {
        lastCommsTX = now;
        Comms::sendTelemetry();
    }

  
    if (now - lastSafety >= SAFETY_INTERVAL) {
        lastSafety = now;
        Safety::check();
    }
}
