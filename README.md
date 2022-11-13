## Introduction

Programming in Arduino needs some basic understanding of C/C++. The projects included here are developed as my hobby projects and I enjoyed and learned alot!

## Compile and Upload Code

You can have lots of documents and tutorials on how to write code for Arduino. After you have written an Arduino program (*.ino extension), you have to compile it and upload it in the controller. 

Because you can't connect and write directly into Arduino, you have to compile it in your machine and upload the compile file into Arduino. 

* **Using Official IDE** 

    This is the simple one, we can download the IDE from arduino official website and install in you local system. Then, after some settings (serial port, board type etc), you can write, compile and upload your code into arduino. (so straightforward!)

* **Using VSCode**

    I found official Arduino IDE not so user-friendly, actually the auto-completion in VSCode helps alot to get faster programming. VSCode is very popular general purpose IDE and you feel pretty comfortable with it. There are shortcut commands for that for compiling and uploading. 

* **Using Command Line** 

    I recently learned how to compile and upload Arduino code using command line (in terminal). This feature I found very good to code Arduino in remote system and upload from there into Arduino. A good scenerio would be connecting Arduino in Raspberry-PI. 
    
    We can write program in Raspberry-PI and compile/upload fromt there into Arduino. Using this method, you can use VSCode and write files into your remote machine. Then use terminal from remote machine you can compile and upload the source into Arduino.

    For my case, I found it very helpful. I have powered Arduino from Raspberry PI. Both the devices are located somewhere. I can write programs in Raspberry PI and upload into Arduino. Note that Arduino is already connected to some other hardware(such as LED Strip, sensors). So, I can test directly without disconnecting arduino.

1. **Install arduino-cli**

    Go into Arduino installation directly and run this command. Arduino client will be intalled in the bin directory. 

    `curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sudo sh`

    If you want to provide the custom bin directory, run this command.

    `curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=~/local/bin sudo sh`

    Full Docu: https://arduino.github.io/arduino-cli/0.19/installation/

    After installation, don't to update the PATH environment variable.

    For example: 

    export PATH=[arduino-cli-path]:$PATH

2. **Getting Board Info**

    Find the board if connected 

    `arduino-cli board list`  (alternative: `arduino-cli board listall`)

    | Port     | Protocol | Type    |           Board Name  | FQBN |   Core|
    -----------|----------|---------|-----------------------|-------|------|    
    | /dev/ttyACM0 | serial  | Serial Port (USB) | Arduino Uno | arduino:avr:uno |arduino:avr |
    
    The above output gives the information about the board. Now, we know , which port is being used for board, including the board name and FQBN and core. These information are needed when we compile and uplaod.
   
3. **Install Board**

    `arduino-cli core install arduino:avr`

    This is another important step where we install the board. Its like board manager in IDE.

4. **Compile & Upload**

    Now, the final step is to compile and upload. Please note that, we can upload only after compilation. 

    `arduino-cli compile -p /dev/ttyACM0 -b arduino:avr:uno Sample.ino`
    
    `arduino-cli upload -p /dev/ttyACM0 -b arduino:avr:uno Sample.ino`

5. **Installing Libraries**
   
    Last but not least, if we need additional libraries, we have to install those. First of all we need to search the libraries:

    `arduino-cli lib search adafruit neopixel`
    
    This will search and provide you a list of libraries. You need to find out the name of the library if it is there. Then install it:

    `arduino-cli lib install "Adafruit NeoPixel"`    

## References:

https://arduino.github.io/arduino-cli/0.19/installation/

https://medium.com/microsoft-makers/first-impressions-arduino-cli-d9e2b45b69


**NOTE**
The TinkerKit libraries are not directly installable from Arduino IDE or arduino-cli. It is available in git 

https://github.com/TinkerKit/TinkerKit 

I have copied the two headerfiles from there. 
