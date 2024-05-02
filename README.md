# Wifi Controlled Mini Bus
An RC car built with an Arduino and a NodeMCU controllable over wifi and modelled after Translink's Double Decker Bus
![20240501_182652](https://github.com/chis456/Arduino-Wifi-Controlled-Bus/assets/55999720/176f5731-4a3b-4ac5-8a80-4bffefd60732)

# Components Used
- Arduino Uno Rev3
- NodeMCU ESP8266
- x4 12V DC Motors
- x2 L298N Motor Drivers

# How it works
In order to have a long range coverage of controllability, I decided to use wifi as the medium to control the system.
First, the NodeMCU and Arduino are connected in such a way that they can send data to eachother. The NodeMCU first creates a
webserver on whichever network it is currently connected to, and the user can then navigate to that webserver and input their controls.
If the user for example presses "W" to move the bus forward, the NodeMCU will send that data to the Arduino which will then control the 
motors accordingly. Although the motors and the motor drivers are rated for 12V, I supplied them with 18V due to the weight of the system.
![schematic](https://github.com/chis456/Arduino-Wifi-Controlled-Bus/assets/55999720/42d22948-4e79-455f-bba1-7fb96c65fd6b)
Navigating to the NodeMCU's local IP in your browser, you can control the inputs to the vehicle 

![image](https://github.com/chis456/Arduino-Wifi-Controlled-Bus/assets/55999720/7d62f75d-1fe1-474d-bb1d-913882727077)


![20240501_183409](https://github.com/chis456/Arduino-Wifi-Controlled-Bus/assets/55999720/1e1719a7-c1a6-4c93-ac87-54457c55a314)
(also the smartphone is only there to power the NodeMCU since I didn't have an extra power bank, otherwise it doesn't interact with the system)

# Demo Footage

https://github.com/chis456/Arduino-Wifi-Controlled-Bus/assets/55999720/c1e5ea56-e373-4b7e-a3cd-5cd42d29aba9

https://github.com/chis456/Arduino-Wifi-Controlled-Bus/assets/55999720/364c2c03-bd94-4706-872e-732a4f2b6652

https://github.com/chis456/Arduino-Wifi-Controlled-Bus/assets/55999720/10aff73f-b79e-4bd4-bf4c-8bbd19d7d6ab


