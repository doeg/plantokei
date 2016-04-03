<p align="center">
  <img width=420 src="https://pbs.twimg.com/media/Ce-ti2uUAAAjRpa.jpg:large">
</p>
<p align="center">:sparkles: :floppy_disk: :herb: <b>プランとけい</b> // <i>plantokei</i> :herb: :floppy_disk: :sparkles:</p>

#プランとけい
Plantokei is a golem made up of:
- An [Arduino Uno](https://www.arduino.cc/en/Main/ArduinoBoardUno)
- A [SainSmart ST7735](http://www.sainsmart.com/sainsmart-1-8-spi-lcd-module-with-microsd-led-backlight-for-arduino-mega-atmel-atmega.html) LCD
- A simple [photocell](https://learn.adafruit.com/photocells/overview)
- A plant! :3

The following I/O is in the works:
- Soil moisture
- Nearby motion
- Humidity and temperature
- Photosynthetically active radiation (a.k.a. PAR)
- Bluetooth/wifi/Xbee perhaps?

I post lots of photos & updates on Twitter with the <a href="https://twitter.com/search?f=tweets&q=%23plantokei%20from%3Adoeg&src=typd" target="_blank">`#plantokei`</a> hashtag!

## Developing
### Easy Mode
The easiest way to get going with Plantokei is to load up `plantokei.ino` in the
[Arduino IDE](https://www.arduino.cc/en/Main/Software). You'll need to download
the two libraries for the LCD screen, `Adafruit_GFX.zip` and `Adafruit_ST3775.zip`, available in [this helpful tutorial](http://www.tweaking4all.com/hardware/arduino/sainsmart-arduino-color-display/) along with instructions to install said libraries.

### Slightly-Less-Easy Mode
If you're like me and you value text editor shortcuts over your own happiness,
then congratulations! You can build and upload the plantokei source yourself.

NOTE: plantokei's build process depends on the excellent Arduino-Makefile project. If you're on a system other than OS X or if these instructions don't work out of the box, check out the similarly great [Bare Arduino Project](https://github.com/ladislas/Bare-Arduino-Project) for instructions on setting up Arduino-Makefile for other systems like Linux and Windows.

1. Install the dependencies:
```Bash
$ brew tap osx-cross/avr
$ brew install avr-libc
$ brew install avrdude
$ pip install pyserial
```

2. After cloning the plantokei repo, install the git submodules. This includes the Arduino-Makefile dependency, as well as all of the Arduino libraries:
```Bash
git submodule init && git submodule update
```

3. Make sure your Arduino is plugged in, then compile and upload the program:
```Bash
$ make && make upload
```

4. (Optional) Open up the serial monitor. To quit: `<^A+k>`
```Bash
$ make monitor
```

## Acknowledgements
- Many thanks to <a href="https://twitter.com/vogon" target="_blank">@vogon</a> for the cute name!
- [Natalie Silvanovich's](http://natashenka.ca/) Tamagotchi-hacking work has been invaluable (and cool as heck)
- mrt-prodz did [a great write-up](http://www.mrt-prodz.com/blog/view/2015/03/flappy-bird-clone-on-the-atmega328-arduino-uno) on a Flappy Bird clone using the ST7735
- Jasper van Loenen's awesome [image2cpp](http://javl.github.io/image2cpp/) tool is great for sprite creation
- Tweaking4all.com's has a great [write-up on the on the ST7735](http://www.tweaking4all.com/hardware/arduino/sainsmart-arduino-color-display/) 
