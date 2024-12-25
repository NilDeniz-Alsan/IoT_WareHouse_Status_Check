# IoT WareHouse Status Check

![Hardware circuit ](https://github.com/user-attachments/assets/dbab188b-b18e-4fe9-b934-f8390c46ddb3)

1- Necessary Libraries

● WiFi.h: Required to use ESP32's Wi-Fi feature.
● HTTPClient.h: Used to send and receive data over HTTP.
● DHT.h: Used to communicate with the temperature and humidity sensor DHT11 or DHT22.
● LiquidCrystal.h: Used to control the LCD display.

2- Variable Definitions

● ssid and password: SSID (network name) and password used to connect to the Wi-Fi network.
● serverUrl: URL of the server used to send and receive data.
● ledPin: Pin defined to control an LED (GPIO2).
● lcd: Object used to control a 16x2 LCD screen.
● DHTPIN: GPIO pin (pin 15) to which the sensor is connected.
● DHTTYPE: Type of sensor used (DHT22).

3- Main Parts of Code:

void setup():
This function performs the initial setup of the device:
● Initializes the LCD screen and displays the startup message.
● Configures the LED pin.
● Connects to the Wi-Fi network and waits in a loop until the Wi-Fi connection is completed.
● Writes the IP address to the LCD when the connection is established.
● Initializes the DHT sensor.

void loop():
In the main loop, two operations are performed continuously:
● Data Sending: The sendData() function is called and the temperature-humidity data is sent to the server.
● Data Receiving: The fetchData() function is called and the data is received from the server.
● Waiting Time: 10 seconds is waited between each operation.

## Explanation of HTTP Requests:
sendData() Function: Sends sensor data to the server in XML format.
● Temperature and Humidity Data: For testing purposes, a
random temperature and humidity value is generated with the
random() function.In the real project, the
dht.readTemperature() and dht.readHumidity() functions can be used.
● XML Data Format:Data is prepared in XML format. For example:

![XMLData](https://github.com/user-attachments/assets/a4ba4659-6b44-4358-a349-dd0aa3984711)

HTTP POST Request:Data is sent to the server.If the HTTP response code is successful, the submission is considered successful.In case of an error, the error message is printed via the serial port and led will switched on during 2 seconds.

fetchData() Function: Gets data from the server and displays it on the LCD.
● HTTP GET Request:A GET request is sent to the server.If the response is successful, the received data is displayed on the serial port and the LCD and led will switched on during 2 seconds.
● Display on the LCD:The LCD screen can display only the first 16 characters of the data.

## Target Url:
![Ekran görüntüsü 2024-12-24 190108](https://github.com/user-attachments/assets/bc7cae02-9de1-43dc-94c9-85503bf7d936)

## Output
![Output](https://github.com/user-attachments/assets/6c3b41da-4537-4d70-86b4-2f240b515b57)

