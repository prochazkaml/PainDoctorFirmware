# PainDoctorFirmware

The firmware for the PainDoctor™, the ultimate fitness device. TL;DR: it zaps you everytime you stop moving during your exercise. Watch [the video](http://paindoctor.wz.cz/paindoctor.mp4) for more info.

![PainDoctor photo](https://user-images.githubusercontent.com/41787099/111153211-f3aebf80-8591-11eb-9d22-26e972d19110.png)

Inspired by the ElectroBOOM's [WorkoutOrF\*\*\*ingDie™](https://youtu.be/A0314QOklz8) weight loss device.

_The PainDoctor™ was created as a joke for our English project, but we were insane enough to make it into a real thing._ If we were serious about it and didn't have a single week to finish the project, it would be much nicer (eg. a plastic housing instead of black-painted cardboard, a custom PCB containing both the logic and the high-voltage generator, a bigger display, a real motion detector, a rechargeable battery, not requiring the stupid app etc.)

Oh, yeah, you'll need [the app](https://github.com/prochazkaml/PainDoctorCompanion) to even use this thing.

The PainDoctor™ uses an ESP-12E module, which gives the device WiFi capabilities. An SSD1306 128x64 OLED display is used for displaying information and an MPU6050 accelerometer mounted on a spring from a pen is used for detecting motion. It is a very crude method of detecting motion, but it does the job well enough. A relay is used to turn on/off the high-voltage generator circuit extracted from a bug zapper racket, which is connected to the 2 electrodes on the front of the PainDoctor™.

Compile with the Arduino IDE and select NodeMCU 1.0 with default settings. Don't forget to add the ESP8266 package index in the Additional Board Manager URLs.

The schematic is beyond simple, it is just an SSD1306 display and an MPU6050 accelerometer connected to the ESP-12E's I2C lines (pins 4 (SDA) and 5 (SCL)) and a relay connected to pin 14. I might publish the actual schematic sometime later.
