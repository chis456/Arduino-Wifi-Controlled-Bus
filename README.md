# Wifi Controlled Mini Bus
An RC car built with an Arduino and a NodeMCU controllable over a wifi network and modelled after Translink's Double Decker Bus
![20240501_182652](https://github.com/chis456/Arduino-Wifi-Controlled-Bus/assets/55999720/176f5731-4a3b-4ac5-8a80-4bffefd60732)

# Main Components and Equipment Used
- Arduino Uno Rev3
- NodeMCU ESP8266
- x4 12V DC Motors
- x2 L298N Motor Drivers
- Atleast 2x 12 Volt DC sources (I used 4x 9 Volt batteries, 18V for each Motor Driver)
- Power Banks for Microcontrollers
- Soldering Iron

# Functional Requirements
- NodeMCU ESP8226 must be able to connect to a Wi-Fi network and receive commands from a device also connected to the same network
- NodeMCU ESP8226 must be able to send received commands to the Arduino Microcontroller via physical circuit connections
- Arduino Microcontroller must control motors and motor controllers according to received commands

# How it works and Development Documentation
Initially, I was planning on using bluetooth as the communication to the controller device, but the range would be only about 10 meters, so I decided to opt for a Wi-Fi connection instead to have a wider control coverage.
First, the NodeMCU and Arduino are connected in such a way that they can send data to eachother, more specifically it's in master slave configuration so that data can be sent through serial. The code on the  NodeMCU first connects to a Wi-Fi network, and then creates a webserver that devices connected to the same network can access. Devices are able to access this webserver via typing in the IP address of the ESP8266 in any browser, where they can input controls to the system/vehicle.
If the user for example presses "W" to move the bus forward, the NodeMCU will receive and then send that data to the Arduino which will then control the 
motors accordingly. Although the motors and the motor drivers are rated for 12V, I supplied them with 18V due to the weight of the system.

The biggest obstacle in development was the weight of the model and the electrical system combined. The motors I used are rated for 12V, although I only had 9V batteries on hand. Not wanting to go over the rated limit, I initially used 1 9V battery for each motor driver. Although the electrical system worked by itself, the speed of the whole system was quite slow, and turning left or right simply failed since turning required only 2 wheels to be powered, and the undersupplied motor drivers were not able to supply enough power to just 2 motors against the weight of the entire system. The only solution with the components I had on hand were to supply the motors with 18V (2 9V batteries each). In order to avoid damaging the motor driver logic circuits, I had to disconnect the internal 5V voltage regular and supply 5V externally for said logic circuitry via the Arduino's 5V output pin. The L298N driver also has 2V drop throughout its internal circuitry, so although it's still oversupplied, 16V is less than 18V. The benefit was that the motors now span much quicker. Driving forward was much faster and turning worked beautifully.
![schematic](https://github.com/chis456/Arduino-Wifi-Controlled-Bus/assets/55999720/42d22948-4e79-455f-bba1-7fb96c65fd6b)
Navigating to the NodeMCU's local IP in your browser, you can control the inputs to the vehicle 

![image](https://github.com/chis456/Arduino-Wifi-Controlled-Bus/assets/55999720/7d62f75d-1fe1-474d-bb1d-913882727077)


![20240501_183409](https://github.com/chis456/Arduino-Wifi-Controlled-Bus/assets/55999720/1e1719a7-c1a6-4c93-ac87-54457c55a314)
(also the smartphone is only there to power the NodeMCU since I didn't have an extra power bank, otherwise it doesn't interact with the system)

# Demo Footage

https://github.com/chis456/Arduino-Wifi-Controlled-Bus/assets/55999720/c1e5ea56-e373-4b7e-a3cd-5cd42d29aba9

https://github.com/chis456/Arduino-Wifi-Controlled-Bus/assets/55999720/364c2c03-bd94-4706-872e-732a4f2b6652

https://github.com/chis456/Arduino-Wifi-Controlled-Bus/assets/55999720/10aff73f-b79e-4bd4-bf4c-8bbd19d7d6ab


