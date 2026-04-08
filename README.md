# SLYR — System-Linked Runtime
<img src="https://raw.githubusercontent.com/myrachane/slyr.cpp/refs/heads/main/assets/ascii-art-text%20(1).png" alt="Alt Text" width="2000">

SLYR is a modular avionics system for autonomous UAVs, built around a dual-compute architecture that separates real-time flight control from high-level autonomy.

---

## Overview

SLYR enforces a strict separation of responsibilities:

* **STM32 (Flight Kernel)** — deterministic, real-time control
* **Raspberry Pi (Autonomy Layer)** — perception, planning, and decision-making

This design improves system stability, safety, and extensibility while enabling advanced autonomy without compromising control integrity.

---

## Product Line

SLYR is designed as a unified platform supporting multiple aerial and flight systems:

* **SLYR-Q** — Quadcopter systems (multirotor UAVs)
* **SLYR-F** — Fixed-wing aircraft systems
* **SLYR-K** — Kinetic launch systems (student rockets)

Each series shares the same core runtime and communication architecture while adapting to platform-specific requirements.

---

## System Architecture

```text id="q7j3z1"
[ Sensors ]
     ↓
[ STM32 Flight Kernel ]
  - State Estimation
  - PID Control
  - Motor Output
     ↓
[ Communication Layer ]
     ↓
[ Autonomy Layer (Raspberry Pi) ]
  - Navigation
  - Perception
  - Decision Engine (SLM)
     ↓
[ Behavior Manager ]
     ↓
[ Control Targets ]
     ↓
[ STM32 Execution ]
```

---

## Core Components

### Flight Kernel (STM32)

* Real-time control loop (~1 kHz)
* Sensor fusion (IMU, GPS, barometer)
* Attitude and rate PID controllers
* Motor output (DShot / PWM)
* Failsafe and watchdog systems

---

### Autonomy Layer (Raspberry Pi)

* Waypoint navigation
* Obstacle detection and avoidance
* Mission planning
* Decision engine (SLM-based or rule-based)

---

### Communication Layer (SLYR Link)

* Custom binary protocol
* UART / SPI transport
* CRC validation
* Heartbeat monitoring and failsafe triggers

---

### Command Shaping Layer

* Input smoothing (curve-based transitions)
* Rate limiting
* Constraint enforcement

Ensures all control inputs remain within safe operational bounds before execution.

---

## Control Interface

```json id="9mz3xn"
{
  "roll": 5,
  "pitch": 0,
  "yaw_rate": 20,
  "throttle": 0.6
}
```

---

## Mission Definition

```json id="9v5x7o"
{
  "mission": [
    {"lat": 22.1, "lon": 88.5, "alt": 20},
    {"lat": 22.2, "lon": 88.6, "alt": 25, "action": "HOLD"},
    {"lat": 22.3, "lon": 88.7, "alt": 20, "action": "RETURN_HOME"}
  ]
}
```

---

## Repository Structure

```bash id="f2s9kk"
SLYR/
 ├── firmware/        # STM32 flight kernel (SLYR Core)
 ├── autonomy/        # Raspberry Pi services
 ├── protocol/        # communication specifications (SLYR Link)
 ├── simulation/      # testing and validation tools
 ├── groundstation/   # monitoring and control interface (planned)
 └── docs/            # system documentation and diagrams
```

---

## Safety Model

SLYR enforces strict isolation between:

* **Decision Layer** (autonomy / AI)
* **Control Layer** (flight kernel)

All incoming commands are:

* validated
* clamped
* smoothed

before being applied to the control system.

The flight kernel retains final authority over actuation.

---

## Development Roadmap

### Phase 1

* Communication layer
* Basic stabilization

### Phase 2

* Attitude control
* Manual flight

### Phase 3

* GPS-based navigation

### Phase 4

* Obstacle detection and avoidance

### Phase 5

* AI-assisted decision integration

---

## Documentation & Updates

For updates, architecture insights, and development logs:

**https://slyr.emtypyie.in**

---

## Disclaimer

This project is intended for research and educational use only.
Ensure compliance with local regulations before deploying on real hardware.

---

## Vision

SLYR aims to provide a unified avionics platform combining:

* Real-time embedded systems
* Autonomous navigation
* Intelligent decision-making

for next-generation aerial and space systems.
