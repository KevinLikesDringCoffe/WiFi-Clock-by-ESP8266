# WiFi-Clock-by-ESP8266
A simple WiFi clock implemented by ESP8266/NodeMCU using Arduino IDE. The clock can grab online time using Sunning time spi, monitor the WiFi signal strength and display it on the 12864 oled screen.
## Features
- Online time getting
- Realtime signal strength monitoring
## Demo
![demo](/demo.jpg)
## Usage
To use the program you must have the Arduino IDE and install the library provided in this github link:   
<https://github.com/ThingPulse/esp8266-oled-ssd1306>  
To get connected to your own WiFi AP, you should modify the SSID and password in this code segment:   
```
const char* ssid = "TP-LINK_6B7F";
const char* password = " ";
```

To use other time api you want, please modify this code segment:   
```
const char* url = "http://quan.suning.com/getSysTime.do";
```
## Contact imformation
Emali: 1120170664@bit.edu.cn