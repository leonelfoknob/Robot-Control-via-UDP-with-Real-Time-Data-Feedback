import pygame
import socket
import time

# Initialize Pygame for joystick handling
pygame.init()

# Set up the UDP socket
UDP_IP = "192.168.1.14"  # Replace with ESP8266's IP address
UDP_PORT = 12345        # Choose a port number to match ESP8266

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Initialize joystick
pygame.joystick.init()
if pygame.joystick.get_count() < 1:
    print("No joystick connected!")
    pygame.quit()
    exit()

joystick = pygame.joystick.Joystick(0)
joystick.init()

# Main loop to read joystick and send UDP messages
try:
    while True:
        pygame.event.pump()

        # Example: read axis and button data
        axis0 = joystick.get_axis(0)
        axis1 = joystick.get_axis(1)
        button0 = joystick.get_button(0)

        # Format the data as a string (e.g., "A0:0.1,A1:-0.2,B0:1")
        message = f"A0:{axis0:.2f},A1:{axis1:.2f},B0:{button0}"
        sock.sendto(message.encode(), (UDP_IP, UDP_PORT))
        
        # Print sent message for debugging
        print("Sent:", message)
        time.sleep(0.05)  # Send data every 50 ms

except KeyboardInterrupt:
    print("Closing connection.")
finally:
    sock.close()
    pygame.quit()
