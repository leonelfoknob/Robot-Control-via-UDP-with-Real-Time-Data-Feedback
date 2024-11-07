import tkinter as tk
import socket
import threading
import pygame

# Initialize pygame for joystick handling
pygame.init()
joysticks = {}
commands = {}

# Define robot names and IP addresses
robot_ips = {
    "bot": "192.168.1.14",
    "Robot2": "192.168.4.11",
    "Robot3": "192.168.4.12"
}

# Set UDP port details
UDP_PORT = 12345
RESPONSE_PORT = 12346

# Initialize main Tkinter window
root = tk.Tk()
root.title("Robot Control and Battery Monitor")

# Global variables for socket and IP address
sock = None
robot_ip = None

# Function to start UDP connection and joystick control
def start_connection():
    global sock, robot_ip
    
    robot_name = entry.get()
    robot_ip = robot_ips.get(robot_name)
    
    if robot_ip:
        label_status.config(text=f"Connected to {robot_name} at IP {robot_ip}")
        
        # Set up UDP socket for communication
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.bind(("", RESPONSE_PORT))  # Bind to the local port to receive data
        
        # Start a thread to listen for incoming data (battery voltage)
        threading.Thread(target=receive_data, daemon=True).start()
        
        # Start joystick handling in a separate thread
        threading.Thread(target=joystick_control, daemon=True).start()
        
        # Send initial request for battery voltage
        send_command("Request:Battery")
    else:
        label_status.config(text="Robot name not found. Check the spelling.")

# Function to send commands to the robot
def send_command(command):
    if sock and robot_ip:
        sock.sendto(command.encode(), (robot_ip, UDP_PORT))

# Function to receive data (battery voltage) from the robot
def receive_data():
    global sock
    while True:
        try:
            data, _ = sock.recvfrom(1024)
            message = data.decode()
            if message.startswith("Battery:"):
                voltage = message.split(":")[1]
                label_voltage.config(text=f"Battery Voltage: {voltage} V")
        except socket.timeout:
            pass
        except Exception as e:
            print("Error receiving data:", e)
            break

# Function to handle joystick input and send commands
def joystick_control():
    while True:
        for event in pygame.event.get():
            if event.type == pygame.JOYDEVICEADDED:
                joy = pygame.joystick.Joystick(event.device_index)
                joysticks[joy.get_instance_id()] = joy
            elif event.type == pygame.JOYDEVICEREMOVED:
                del joysticks[event.instance_id]
        
        for joystick in joysticks.values():
            axis0 = joystick.get_axis(0)
            axis1 = joystick.get_axis(1)
            button1 = joystick.get_button(0)
            
            # Format command with joystick values
            command = f"A0:{axis0:.2f},A1:{axis1:.2f},B0:{button1}"
            send_command(command)  # Send joystick command to the robot

        pygame.time.delay(100)  # Delay to avoid flooding the network

# Tkinter GUI Elements
label_name = tk.Label(root, text="Enter Robot Name:")
label_name.pack()

entry = tk.Entry(root)
entry.pack()

button_connect = tk.Button(root, text="Connect", command=start_connection)
button_connect.pack()

label_status = tk.Label(root, text="Status: Not connected")
label_status.pack()

label_voltage = tk.Label(root, text="Battery Voltage: N/A")
label_voltage.pack()

root.mainloop()
