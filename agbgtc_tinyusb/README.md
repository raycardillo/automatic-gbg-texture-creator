# Seeeduino XIAO Mouse Controller

This variant was specifically developed for and tested on a **Seeeduino XIAO** microprocessor board.

It is currently dependent upon the **Adafruit_TinyUSB** library, but should be easy to adapt to any **TinyUSB** based environment in the future.

## Setup and Build:

Abbreviated instructions for installing and setting up Arduino IDE **v2.0.0-rc5** or greater for development.

1. Install [Arduino IDE](https://www.arduino.cc/en/software) `v2.0.0-rc5` or greater (`v1.8.x` may also work but you will not see the `src` folder that contains the mouse helper utility class).
1. Copy this `agbgtc_tinyusb` folder into your `Arduino` project folder.
1. Open the `agbgtc_tinyusb.ino` file in the Arduino IDE. Notice that the `src` files must be retained in tact because there are relative references to it in the program.
1. Add the [Seeed Studio](https://wiki.seeedstudio.com/Seeeduino-XIAO/) board package definitions using `File ⮕ Preferences` and adding the URL: `https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json`
1. Download the `Seeeduino` board drivers using `Tools ⮕ Board Manager`.
1. Download the `Adafruit_TinyUSB` version `0.10.5` using `Tools ⮕ Manage Libraries`. You must select version `0.10.5` until Seeeduino releases an update (due to a breaking change in the `1.x` release).

## Convert Image Data
_For your first run, you can skip this step and use the default example texture. This allows you to verify your initial setup before creating your own textures._
  1. Use the `GBG_Texture_Builder` utility to convert your image to a CSV representing the texture pixel data.
  1. Copy the CSV numbers into the image data array (`images[][IMAGE_DATA_LEN]`) in the program. If you're on a Mac the `pbcopy` utility is a quick way to copy the CSV data into your pasteboard (e.g., `pbcopy < file.csv` and then `⌘ Command + V` to paste).
  1. Delete any example image data that you don't want.
  1. I've created more than 10 images in one session so it's just limited to the amount of `PROGMEM` that is available on your board (and how long you want to wait).

## Upload Program to Board
  1. Plugin the device to the computer.
  1. Select the `Seeeduino XIAO` **Board** and **Port** using the `Tools` menu.
  1. Select the `TinyUSB` **Stack** using `Tools ⮕ USB Stack`.
  1. Upload the program to the board.
  1. Unplug the XIAO board from the computer.

## Running on Device
  1. Plug the Board into the Nintendo Switch USB-C port.
  1. Bring up a Game Builder Garage game and open programming mode.
  1. Trigger (or jump the start pin) to start creating the textures. By default this is pin 2. You can change this later or use a breadboard with a switch, etc. Be careful to only use **3.3V** to jump the input pin signal because the inputs on this board can only tolerate 3.3V even though they provide a 5v converter pin as well.
  1. The light will stay solid while it's creating textures. Do not disturb the mouse or touch screen while it's working.
  1. Unplug when complete and the LED is alternating.

## Useful References:
- https://www.arduino.cc/en/software
- https://wiki.seeedstudio.com/Seeeduino-XIAO/
- https://github.com/adafruit/Adafruit_TinyUSB_Arduino/releases/tag/0.10.5
