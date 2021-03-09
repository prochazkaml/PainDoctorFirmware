# PainDoctorFirmware

The firmware for the PainDoctor™, the ultimate fitness device. TL;DR: it zaps you everytime you stop moving during your exercise. Watch the video on the website for more info.

_The PainDoctor was created as a joke for our English project, but we were insane enough to make it into a real thing._

The PainDoctor™ uses an ESP-12E module, which contains an ESP-8266 CPU and 4 MB of Flash memory on a single package. An SSD1306 128x64 OLED display is used for displaying information and an MPU6050 accelerometer mounted on a spring from a pen is used for detecting motion. It is a very crude method of detecting motion, but it does the job well enough.

Compile with the Arduino IDE and select NodeMCU 1.0 with default settings. Don't forget to add the ESP8266 package index in the Additional Board Manager URLs.
