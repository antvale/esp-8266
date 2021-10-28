# Programming ESP-01 (ESP8266) made easy

You have probably heard about IoT (Internet of Things), a world of little useful things that interacting with the surrounding environment are able to communicate each other and sometimes with the human beings. The popular ESP8266 along with the modules of ESP-XX family find a right place in the IoT world due to their smaller size and cheaper cost compared to other similar board like Arduino. So if you want to learn how to program this amazing micro-controller, then...good reading. 

This post focuses on setting up a simple development environment to program the ESP-01 module. Indeed, this module does not include  any micro-usb connector out-of-box requiring instead to add  few additional components to program it. On the market there are also some development boards, like NodeMCU for example which includes all the necessary built directly in the module as well as a micro-usb connector to easily connect the board to laptop. But typically these boards are larger than ESP-01 and can't be plugged in already existing modules built around the ESP-01 such as the relay modules used in the home automation domain.

Thus, to develop with ESP-01 module without having to do a complicated breakout board or a breadboard with many flying jumpers then you need at least the following bill of materials: ESP-01 (obviously), an USB-to-UART bridge, a 3.3 volt power regulator, a resistor, a SDK and an IoT platform. Obviously several options exist for each above components, in this post I've chosen a programmer adapter based on CH340 chipset, Arduino IDE as language and Blynk as IoT Platform.

What is ESP-01?
ESP-01 is a small module that integrates the MCU (Micro-Controller  Unit) ESP8266EX sold by Espressif, a Chinese company. The ESP8266EX is built on top of the Tensilica L106 32-bit risc processor and a 2.4GHz WiFi radio making easy and fast to connect this device over internet and in general with the cloud. In addition to internal RAM to run the program instructions, the module integrates also a SPI flash memory where storing the program code. The ESP version used in this post hosts a maximum of 1MB external flash memory based on P25Q80H  SPI flash.
ESP-01 6-pins board shows clearly the MCU, the SPI flash memory and the antenna. The size of this device is 2.427x1.45cm making it an ideal option to build amazing IoT prototyping. When powering this device remember to use 3.3 volts, and not 5 volts as per Arduino. Don't forget this constraint if you don't want to burn anything on the board.
![image](https://user-images.githubusercontent.com/21111325/139257636-45832c84-ad6d-48c6-b1f5-7987757673ae.png)

Connect ESP-01 to laptop
As said in the introduction, in contrast to ESP-12 and more recent ESP-32, the ESP-01 hasn't any usb connector on board as consequences to connect this module to a laptop a programmer adapter usb to serial (UART) is required.

The market offers some off-the-shelf adapters like FTDI232 for example, but if you wish to start soon with prototyping something then the option to utilize the adapter based on the chipset CH340 may be a valid alternative. The adapter is depicted on right side and provides the required 3.3 volts.
![image](https://user-images.githubusercontent.com/21111325/139257990-6bd5593b-4475-4a8b-b80e-92c27a393fc5.png)

The advantage of this adapter is the possibility to easily plug in the ESP-01 to start with developing quite soon without the necessity for jumping components on the breakout or breadboard. You may buy it on line often combined with the ESP-01 for a few euros. 

Install CH340 driver
Here is described how to download and install the driver for Mac OS (installed by myself on High Sierra 10.13.3) while for other kind of operating system, please, look this link.
After having completed the installation, restart the laptop, put the adapted in the usb outlet and plug the ESP-01 in the adapter, then open a terminal and prompt the following command:

$ screen /dev/tty.wchusbserial14610 115200

Enter AT followed by control+M and control+J if as results an OK message appears on the console then everything works fine.


Set up ESP-01 in programming mode
To program the ESP-01 board there is a preliminary set up that you have to realize having to switch the board in programming mode. Indeed, the board can work in two different modes:

Programming mode - in this mode you are able to upload the program to board. To enable it the GPIO0 has to be low and GPIO2 high 
Boot mode - this is the normal operational or flash mode enabling the micro-controller to load the program from the flash to RAM and execute it on the startup. To enable this mode both GPIO1 and GPIO2 are high.

There are several ways to handle these two different modes with the programmer adapter and each one, from more complicated to simpler, requires to use at least a resistor and a little switch. Unless you want to spend some time to prepare a breakout board or jump all the pins to a breadboard, you could just solder between GPIO0 and ground pins of the adapter a pull-down resistor in series with a little slide switch. In this way you can switch from programming to boot mode easily leveraging the slide switch.
![image](https://user-images.githubusercontent.com/21111325/139258311-6bc255ce-d69f-448d-a555-bd04e892a6dc.png)



How to set up the adapter to work in programming mode
Set up the adapter in programmer mode
For the purpose of this post it is enough to solder a 3,9kΩ resistor as illustrated on the left side with the intent to use the adapter only as a programming board.



In a next post I'll explain how to prepare a breadboard to power the ESP-01 with a voltage regulator and a battery or alternately a USB cable.

Install ESP8266 library in Arduino IDE
Some options exist to program the ESP-01 like Mongoose OS and Arduino/Genuino IDE as well.  We're going to use the second option especially because Arduino IDE is widely used in the world of DIY prototyping. So download and install the latest version of Arduino IDE from official site and follow below instructions to install ESP8266 library for Arduino.
Open the IDE and select Arduino->Preferences then paste in "Additional Boards Manager URLs the following link:  http://arduino.esp8266.com/stable/package_esp8266com_index.json
Go to the Tools->Board>Boards Manager and enter "esp" in the search box, select esp8266 Community and install it.
Once the installation is finished, go to Tools->Board and select "Generic ESP8266 Module"
Set Tools->Flash Size to 1M (512 SPIFFS)
Plug the ESP-01 in the programmer adapter and select the port in Arduino IDE. On my Mac it appears as:
![image](https://user-images.githubusercontent.com/21111325/139258486-2c49d04e-2572-418e-ac62-325acec2f5a6.png)


(More information about above installation and different settings is available here)

Install Blynk library in Arduino IDE
Blynk is an IoT platform that provides features to create and manage Android and iOS apps to control remotely several type of devices as the ESP8266. Make an app with this platform is really ease and generally requires three main steps: 

Install Blynk app on you smartphone
Create an app with the widgets provided by Blynk
Install the Blynk library in Arduino IDE
Write an Arduino sketch using the Blynk API

To install the Blynk libraries go to Blynk Getting Started page, download the "Download Blynk Library" and follow the steps as described here (where there is also a video).

Create a simple Blynk project
Go to Google Play Store or iOS App Store and look for the "Blynk - Arduino, ESP8266, RPI" app, download and install it.
Open the Blynk app and create a new account.
Login to the Blynk app
Create a "New Project" choosing the ESP8266 as device. A new secure token will be sent to your email account that you should use in the Arduino sketch to communicate with Blynk server in the cloud.
Look for a led widget and add it to your project. Select the led and set the input PIN to V1 (virtual channel 1). Be careful that Blynk is not completely free and makes use of a sort of energy battery to limit the number of the widgets you can copy and paste in your app. 

Ready to code
Go to Blynk Examples site and select the board ESP8266, the WiFi Connection and the simple led blink example. 
Click on "Copy Example" link and past the clipboard content in a new Arduino sketch.
Configure the access token entering what you've received by mail.
    // You should get Auth Token in the Blynk App.
    // Go to the Project Settings (nut icon).
    char auth[] = "enter here the access token";
Configure properly the wifi access entering ssid and password to connect to your home wifi router or hotspot.
    // Your WiFi credentials.
    // Set password to "" for open networks.
    char ssid[] = "enter here the ssid of your wifi network";
    char pass[] = "enter here the wifi password";
Compile the sketch
Reset the ESP-01 using a jumper between the RST and GND pins on the board. Alternatively you can solder a small push button on the adapter to reset when required
Upload the code to ESP-01 module (using upload icon). Below what should appear in Arduino console on successful upload.
![image](https://user-images.githubusercontent.com/21111325/139258559-530a9084-9d31-48fe-94cb-73c6695dda4b.png)


Start the Blynk project on the smartphone (select start icon)
The led on the app should start to blink as the blue led on the ESP-01 board as shown in the below picture.


![image](https://user-images.githubusercontent.com/21111325/139258588-ff71e99a-2140-4841-b09e-b213494214c6.png)



Finally
{
What described in this post is just a quick and easy way to start with the programming of ESP-8266 when delivered through the very small EAS-01 module. I leave to your imagination to figure out how to use this small board to build  amazing prototyping.
}

