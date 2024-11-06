# Robot-Control-via-UDP-with-Real-Time-Data-Feedback

This project explores advanced remote control of mobile robots using lightweight, network-based hardware and protocols. Building on prior developments, the aim was to create a seamless, low-latency interface for controlling robots over local and internet networks with real-time data retrieval. The system’s core leverages small, accessible hardware to enable easy integration into diverse robotic setups, from hobbyist projects to autonomous vehicles.

## Project Objectives
- Develop a robust, UDP-based communication protocol that ensures low latency and real-time responsiveness.
- Enable control over 2.4GHz and 5GHz networks, evaluating latency and performance.
- Prototype a flexible and scalable control system that can interface with multiple types of robots and control devices, such as joysticks and steering wheels.
- Provide a user-friendly GUI to manage robot selection and connectivity based on IP.

## Methodology
In a previous iteration, the control system was built around a Rampage joystick that sent commands via UDP to a Jetson Nano, which then forwarded data to an Arduino for motor control on the MFX-1 robot. However, latency increased significantly after 1 meter on the 5GHz network, limiting usability. https://github.com/leonelfoknob/Wireless-Robot-Control-Using-UDP-and-Joystick

For this update, the system was reconfigured to use a steering wheel joystick connected to a computer over a 2.4GHz network. This computer sends commands directly to an ESP8266 NodeMCU, eliminating the need for the Jetson Nano and Arduino as intermediaries. The ESP8266 NodeMCU, acting as the robot’s controller, processes and executes commands, controls motors, and reads sensor data directly. Real-time data is then sent back via UDP, allowing the system to maintain a strong, low-latency connection even after testing up to 5 meters.

## Key Components and Features
- Steering Wheel Joystick: Enables intuitive control, interfacing with a PC to send UDP commands.
- ESP8266 NodeMCU: Handles all motor and sensor operations, receiving commands over a 2.4GHz network for quick processing.
- Graphical User Interface (GUI): A desktop-based interface for choosing and connecting to specific robots by name and IP. The GUI checks connectivity, retrieves battery voltage, and shows connection status in real time.
- Latency Optimization: Testing revealed significant improvements with the 2.4GHz network, with minimal latency even at extended distances.
- Scalability: With IP-based robot selection, the system can expand to control multiple robots by integrating additional ESP8266 units.

## Prototype & System Diagram
A scaled-down prototype of the robot was built to demonstrate the system's responsiveness and ease of integration. The setup included:

- System Diagram: Detailing connections between joystick, PC, ESP8266, motors, and sensors.
- Prototype Robot: A small-scale version of the MFX-1 equipped with the ESP8266 NodeMCU to showcase control fluidity and response times with the new setup.

## Outcomes and Future Work
The current implementation achieved a stable and responsive control experience, with minimal latency over a 2.4GHz network. The GUI, with its IP-based robot selector, streamlines connections, providing a seamless operator experience. Future plans include expanding to internet-based control, optimizing the system further, and exploring additional data feedback mechanisms to enhance the robot's autonomy.
