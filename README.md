<a name="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/JonasVanhulst/DepthMonitor">
    <img src="https://github.com/JonasVanhulst/IoT_Insights/assets/114076210/e8407dba-a210-47c9-b474-e5cfc447229c" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">DepthMonitor</h3>

  <p align="center">
    A GitHub project that utilizes an Arduino Nano 33 BLE sense processor along with an different distance sensors to precisely monitor the content of a watertank. 
    <br />
    <a href="https://github.com/JonasVanhulst/DepthMonitor/tree/main/Documentation"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/JonasVanhulst/DepthMonitor/tree/main/Presentation">View Demo</a>
    ·
    <a href="https://github.com/JonasVanhulst/DepthMonitor/issues">Report Bug</a>
    ·
    <a href="https://github.com/JonasVanhulst/DepthMonitor/issues">Request Feature</a>
  </p>
</div>

<!-- ABOUT THE PROJECT -->

## About The Project

This GitHub project is centered on utilizing an Arduino Nano 33 BLE Sense to monitor the content levels of a water tank with precision. The Arduino Nano 33 BLE Sense, known for its robust features and versatility, serves as the core of this project. To ensure accurate and reliable measurements, three of the best distance sensors were selected and connected to the Arduino.

The selection process involved evaluating various distance sensors, each with its own advantages and disadvantages. The goal was to identify the top-performing sensors that would offer the best accuracy, reliability, and ease of integration with the Arduino Nano 33 BLE Sense.

Features of the Arduino Nano 33 BLE Sense

The Arduino Nano 33 BLE Sense is equipped with a range of sensors and features that enhance its capabilities, making it an ideal choice for this project:

- Built-in IMU (Inertial Measurement Unit): Provides orientation and motion detection, useful for stabilizing measurements.
- Environmental sensors: Includes a temperature, humidity, and barometric pressure sensor, allowing for environmental monitoring that can influence distance measurements.
- Bluetooth LE Connectivity: Enables remote monitoring and data transmission, enhancing the versatility of the water tank monitoring system.
- Compact and energy-efficient design: Fits well within the limited space of embedded systems and is suitable for continuous operation with low power consumption.

Project Focus

The primary focus of this project was to explore and understand the different distance sensors to gain deeper insights into electronics and sensor integration. By evaluating the strengths and weaknesses of each sensor, the project aimed to build a robust system capable of accurately measuring the water level in a tank.

Through this process, the project not only achieved its practical goal of water level monitoring but also served as an educational tool for learning about sensor technology and embedded systems. The integration of the Arduino Nano 33 BLE Sense with carefully selected sensors exemplifies a practical application of electronic components, fostering a deeper understanding of both hardware and software aspects of IoT (Internet of Things) development.

### Built With

<!-- GETTING STARTED -->

[![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](<https://en.wikipedia.org/wiki/C_(programming_language)>)
[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)

## Getting Started

This section provides instructions on setting up the water tank monitoring project locally. Follow these simple steps to get a local copy up and running.

### Installation

Below are the instructions to install and set up the project using the Arduino IDE. This project does not rely on any external dependencies or services.

Install the Arduino IDE:
Download and install the Arduino IDE from here.
Follow the installation instructions provided on the website for your specific operating system.

1. Clone the Repository:
   Open a terminal or command prompt.
   Clone the project repository using Git:

   ```sh
    git clone https://github.com/your_username_/WaterTankMonitor.git
   ```

   Alternatively, download the ZIP file from the repository page and extract it to your desired location.

   Open the Project in Arduino IDE:
   Launch the Arduino IDE.
   Navigate to File > Open... and select the main .ino file from the cloned repository folder.

   Install Required Libraries.

Usage

Once the code is uploaded, the Arduino Nano 33 BLE Sense will start monitoring the water tank levels using the connected distance sensors. You can use a Bluetooth LE compatible device to remotely check the water level readings and ensure the system is functioning correctly.

For detailed instructions on the hardware setup and sensor connections, please refer to the project documentation in the repository.

<!-- ROADMAP -->

## Roadmap

- [x] Exploring the Arduino board
- [x] Exploring the different array of sensors
- [x] Testing the sensor with measurement tools
- [x] Developing demo code & setup
- [x] Developing final code with final setup
- [x] Creating application note

<!-- CONTRIBUTING -->

## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<!-- LICENSE -->

## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<!-- CONTACT -->

## Contact

Jonas Vanhulst - Jonas.Vanhulst@student.pxl.be
