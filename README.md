#Garage Server
##About

This is a program written to control my garage doors using a Raspberry Pi and an iOS or Android phone app. My PiServer library handles all of the socket connections and message parsing. This project used [Google Protocol Buffers][] to communicate with clients, and the [WiringPi][] library to use the GPIO pins on the RaspberryPi. The server also uses an [sqlite][] database to keep track of every time the garage door is opened or closed.

###Detecting Door Status
Each garage door has a sensor on it that completes a circuit when the door is closed. By sending 3.3 volts through the wire, I can use the Raspberry Pi GPIO pins to detect when the doors are closed.

###Operating a Door
In addition to the sensor input, the server can also trigger a garage door, causing it to open, stop, or close. In order to do this, I ran a wire from the physical garage door button to a relay which was normaly open to ground. All the button does is connect it's input on the garage controller to ground. This means when the relay is momentarily closed, the garage door is triggered.

###Installation
With some modification, this project can be configured for other garage doors. There is some simple knowledge of electronics that is necessary to implement the project. I plan on eventually releasing a tutorial on the entire implementation eventually. For systems similar to mine, here are the important parts:

####Connecting Garage Doors
Each garage door should have a controller pin and a sensor pin. 
The sensor pin should read HIGH when the door is closed, and LOW when the door is open. If your sensor is opposite, this can easily be changed in the `garageIsClosed(int)` function located in the GarageDoorBridge.cc file. 
The controller pin is used to trigger a garage door. You may need to modify the `triggerGarageDoor(int)` function in the GarageDoorBridge.cc file depending on the type of relay you are using.

Garage doors are added in the GarageServer.cc file. Each door is constructed with a name, sensor pin, and controller pin. They are added to the doors vector, which is passed to the GarageDoorBridge object. If you have a similar wiring setup, you should be able to just add your garage doors to the `doors` vector in the GarageServer.cc file.
Currently, the doors are hardcoded into the program, but in the future I may add a config file. 

###Client App
I have a working [client app][] for Android devices that is being actively developed. This is built off of my PiClientAndroid library. There is also a PiClient iOS library which hasn't been well tested. If you want to use an iPhone for a garage door opener, you should be able to use that library as a base for the app. 

The client app will display the current garage status, trigger the garage doors, and display the garage door open/close history.

###Contributing
If you plan to use this project and have ideas for improvements, send me a pull request. Let me know if you find any bugs in the server. If you have any questions, I would also be happy to help.

###Libraries Used
- As mentioned before, this project uses [Google Protocol Buffers][] in order to send data to clients. This project is licensed under the [New BSD License][]
- This project also used the [WiringPi][] library, which is released under the [GNU LGPLv3][] license.
- The [sqlite][] library is released into the public domain.

[Google Protocol Buffers]: https://developers.google.com/protocol-buffers/
[New BSD License]: http://opensource.org/licenses/BSD-3-Clause/

[WiringPi]: https://github.com/WiringPi/WiringPi/
[GNU LGPLv3]: http://www.gnu.org/copyleft/lesser.html

[sqlite]: http://www.sqlite.org

[client app]: https://github.com/kylekewley/GarageDoorOpener
