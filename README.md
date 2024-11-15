# CORE
CORE - Control Operations and Robotics Environment

CORE is a robotics programming API for general purpose and autonomous robotics.

## Functionality
 * ```CORE/base/```:
   * Arduino-like functions
   * Digital, analog, & serial r/w capabilities
 * ```CORE/control/```:
   * PID controller
   * Safety features
   * Estimation functions (kalman & complimentary filters)
   * Signal filters
 * ```CORE/subsystem/```:
   * DC, servo, & stepper motor classes
   * IMU sensor
   * Barometer sensor
   * Hygrometer sensor
   * Thermister/thermometer sensor
   * Ultrasonic distance sensor
 * ```CORE/algorithm/```:
   * Curve (Bézier and trajectory) generation
   * A* pathfinder (with preset maps)
   * Basic drivetrain class (uses bezier curve movements)

## License
This repository is under a [Gnu General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.en.html)
