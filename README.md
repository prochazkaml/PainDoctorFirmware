# PainDoctorFirmware

The firmware for the PainDoctor™, the ultimate fitness device. TL;DR: it zaps you everytime you stop moving during your exercise. Watch [the video](http://paindoctor.wz.cz/paindoctor.mp4) for more info.

![PainDoctor photo](https://user-images.githubusercontent.com/41787099/111153211-f3aebf80-8591-11eb-9d22-26e972d19110.png)

_The PainDoctor was created as a joke for our English project, but we were insane enough to make it into a real thing._

Inspired by the ElectroBOOM's [WorkoutOrF\*\*\*ingDie™](https://youtu.be/A0314QOklz8) weight loss device.

The PainDoctor™ uses an ESP-12E module, which contains an ESP-8266 CPU and 4 MB of Flash memory on a single package. An SSD1306 128x64 OLED display is used for displaying information and an MPU6050 accelerometer mounted on a spring from a pen is used for detecting motion. It is a very crude method of detecting motion, but it does the job well enough. A relay is used to turn on/off the bug zapper circuit, which is connected to 2 electrodes in the front.

Compile with the Arduino IDE and select NodeMCU 1.0 with default settings. Don't forget to add the ESP8266 package index in the Additional Board Manager URLs.
