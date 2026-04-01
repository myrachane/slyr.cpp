# SLYR

**SLYR** is a modular avionics system for autonomous UAVs, built around a dual-compute architecture that separates real-time flight control from high-level autonomy.

---

## Overview

SLYR is designed with a strict separation of responsibilities:

* **STM32** handles deterministic, real-time flight control
* **Raspberry Pi** handles autonomy, perception, and decision-making

This architecture ensures stability, safety, and extensibility.

---

## Architecture

```text
[ Sensors ]
     ↓
[ STM32 Flight Kernel ]
  - State Estimation
  - PID Control
  - Motor Output
     ↓
[ Communication Layer ]
     ↓
[ Autonomy Layer (Pi) ]
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
* Motor mixing (DShot/PWM)
* Failsafe handling

---

### Autonomy Layer (Raspberry Pi)

* Waypoint navigation
* Obstacle detection and avoidance
* Mission planning
* AI-assisted decision system (SLM)

---

### Communication System

* Custom binary protocol
* UART / SPI transport
* CRC validation
* Heartbeat and failsafe triggers

---

### Command Shaping Layer

* Input smoothing (curve-based transitions)
* Rate limiting
* Constraint enforcement

---

## Control Interface

```json
{
  "roll": 5,
  "pitch": 0,
  "yaw_rate": 20,
  "throttle": 0.6
}
```

---

## Mission Example

```json
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

```bash
SLYR/
 ├── firmware/        # STM32 flight kernel
 ├── autonomy/        # Pi-side services
 ├── protocol/        # communication specifications
 ├── simulation/      # testing and validation
 ├── groundstation/   # UI (planned)
 └── docs/
```

---

## Safety Model

SLYR enforces strict separation between:

* decision layer (AI / SLM)
* control layer (flight kernel)

All inputs are:

* validated
* clamped
* smoothed

before being applied to the control system.

---

## Roadmap

### Phase 1

* Communication layer
* Basic stabilization

### Phase 2

* Attitude control
* Manual flight

### Phase 3

* GPS-based navigation

### Phase 4

* Obstacle avoidance

### Phase 5

* AI-assisted decision integration

---

## Disclaimer

This project is intended for research and educational purposes only.
Ensure compliance with local laws and regulations before real-world deployment.

---

## Vision

SLYR aims to provide a unified platform combining:

* real-time embedded systems
* autonomous navigation
* intelligent decision-making

for next-generation UAV systems.
