## ConsentiumThingsDalton

**Version:** v0.0.8

**Description:**

This project provides a simple example of how to use the ConsentiumThingsDalton IoT board to read sensor data and send it over HTTPS (only ESP32 supported) to the ConsentiumThings cloud.

**How to use:**

1. Clone this repository to your local machine.
2. Install the Arduino IDE.
3. Connect the ConsentiumThingsDalton board to your computer using a USB cable.
4. Open the Arduino IDE and open the `ThingsUpdate.ino` file.
5. Enter your WiFi SSID and password in the `ssid` and `pass` variables, respectively.
6. Enter your ConsentiumThings API key in the `ApiKey` variable.
7. Enter your ConsentiumThings board API key in the `BoardApiKey` variable.
8. Upload the code to the ConsentiumThingsDalton board.
9. The board will start reading sensor data and sending it over REST to the ConsentiumThings cloud every 7 seconds.

**Notes:**

* You can change the sampling interval by changing the `interval` variable.
* You can change the precision of the data sent over REST by changing the `pre` variable.
* You can add additional sensors to the board by connecting them to the appropriate pins and updating the `sensorCount` variable and the `sensorValues` and `sensorInfo` arrays.

**License:**

This project is licensed under the MIT License.

**Badges:**

[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

**Contributing:**

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
