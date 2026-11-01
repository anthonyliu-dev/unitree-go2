# unitree-go2
Building toward autonomous quadruped robotics with Unitree Go2 EDU: C++, SDK2, ROS2, perception, teleoperation, navigation, and real-world delivery experiments.

## Development Milestones

### ✅ Milestone 1 — SDK2 Communication and Basic Telemetry

**Status:** Completed

- Installed Ubuntu 20.04 LTS and Unitree SDK2.
- Configured Ethernet communication with the Unitree Go2 EDU.
- Successfully established connectivity with 0% packet loss.
- Compiled and executed SDK2 example programs.
- Received live motor position and velocity data through the `rt/lowstate` DDS topic.

**Outcome:** Established reliable communication between the development laptop and the Go2.

### ✅ Milestone 2 — Full Joint and IMU Telemetry

**Status:** Completed

- Modified and compiled `go2_read_state.cpp`.
- Read positions and velocities from all 12 leg motors.
- Retrieved IMU roll, pitch, yaw, and acceleration measurements.
- Verified live telemetry from the physical Go2.
- Published the working C++ source code to GitHub.

**Outcome:** Created a functioning read-only telemetry application using Unitree SDK2.

### 🔜 Milestone 3 — First Programmatic Motion

**Status:** Planned

- Explore SDK2 high-level motion-control APIs.
- Establish and test safety and stopping procedures.
- Execute a short, supervised movement using C++.
