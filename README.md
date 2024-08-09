# Smart Home System with ESP32


## Project Overview

Global warming is leading to more frequent and severe heatwaves, increasing reliance on air conditioning systems and, consequently, energy consumption and greenhouse gas emissions. To address this, the Smart Light-Reactive Blinds System is designed to help maintain cooler indoor temperatures while reducing energy use.

### Problem Statement
The project explores how light-reactive blinds can be designed to effectively maintain cooler indoor temperatures and reduce energy consumption in response to global warming.

### Project Description
This project involves the development of a Smart Home Device using an ESP32 microcontroller. The device hosts an HTML webpage that displays real-time indoor conditions by measuring light intensity using a light sensor. The webpage includes a JavaScript simulation that visually demonstrates how the blinds adjust to different light conditions, aiming to reduce the need for artificial cooling by regulating sunlight exposure.

### System Components
- **ESP32 Microcontroller**: Collects light intensity data and hosts the web server.
- **Light Sensor**: Measures light levels and sends the data to the ESP32.
- **Web Server**: Hosted on the ESP32, it visualizes sensor data and simulates a room.
- **WebSocket Communication**: Ensures real-time data transfer between the ESP32 and the web client.

## Environment Setup: VS Code with PlatformIO Extension

To run the Smart Light-Reactive Blinds System, Visual Studio Code (VS Code) with the PlatformIO IDE extension is used. Follow the steps below to set up the environment:

1. **Install PlatformIO Extension**:
   - Open VS Code and navigate to the Extensions marketplace.
   - Search for "PlatformIO IDE" and install the extension.

2. **Create a New Project**:
   - Once the PlatformIO extension is activated, create a new project within the PlatformIO environment.

3. **Add Required Libraries**:
   - Within the PlatformIO environment, add the `WebSocketsServer` library by Markus Sattler to your project.

4. **Set Up Project Structure**:
   - Create a `data/` folder in your project directory.
   - Inside the `data/` folder, add the `index.html` and `script.js` files containing your code.
   - Update the `src/main.cpp` file with the appropriate code provided in this repository.

5. **Install ESP32 Drivers**:
   - Ensure that the general drivers for the ESP32 are installed on your device to allow proper communication with the microcontroller.

6. **Execute the Program**:
   - After setting up the environment and adding the necessary files and code, you can execute the program to start the web server and view the real-time data visualization.

## ESP32 Setup

### Connecting the LDR Sensor to ESP32

The light sensor is connected to the ESP32 to measure light intensity:

- **Connections**:
  - Connect the LDR VCC pin to the 3.3V pin on ESP32
  - COnnect GND on the ESP32 and LDR.
  - Connect the output of LDR (A0 pin) of the sensor to the analog input pin (34 in our case) on the ESP32.
 


## Created by:

- **Vladyslav Horbatenko** - [GitHub](https://github.com/rifolio)
- **Salar Komeyshi** - [GitHub](https://github.com/SalarKo)
- **Kacper Hvid** - [GitHub](https://github.com/KacperPuzniak)
---
