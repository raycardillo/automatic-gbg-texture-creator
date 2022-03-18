# Usage Notes

This was specifically developed for and tested on a **Seeeduino XIAO** microprocessor board.
It is currently dependent upon the **Adafruit_TinyUSB** library, but should be easy to adapt to any **TinyUSB** based environment.

## Setup and Build:

Abbreviated instructions for installing and setting up Arduino IDE **v2.0.0-rc5** or greater for XIAO development.

1. Install Arduino IDE `v2.0.0-rc5` (`v1.8.x` may also work but you will not see the `src` folder helper class).
1. Copy this `agbgtc_tinyusb` folder into your `Arduino` project folder.
1. Open the `agbgtc_tinyusb.ino` file in the Arduino IDE. Notice that the `src` files must be retained in tact because there are relative references to it.
1. Add the [Seeed Studio](https://wiki.seeedstudio.com/Seeeduino-XIAO/) board package definitions using `File ⮕ Preferences` and adding the URL: `https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json`
1. Download the `Seeeduino` board drivers using `Tools ⮕ Board Manager`.
1. Download the `Adafruit_TinyUSB` version `0.10.5` using `Tools ⮕ Manage Libraries`. You must select version `0.10.5` until Seeeduino releases an update due to a breaking change.

## Convert Image Data
  1. _You can skip this step and verify your initial setup using the default example images instead._
  1. Use the `GBG_Texture_Builder` utility to convert your image to image data CSV.
  1. Copy the CSV numbers into the image data array in the program.
  1. Delete any image data you don't want.

## Upload Program to XIAO Board
  1. Plugin the device to the computer and select the port.
  1. Select the `Seeeduino XIAO` *Board* and *Port* using `Tools` menu.
  1. Select the `TinyUSB` stack using `Tools ⮕ USB Stack`.
  1. Upload this program to the board.
  1. Unplug the XIAO board

## Running on Device
  1. Plug the XIAO Board into the Nintento Switch USB port.
  1. Bring up a Game Builder Garage game in programming mode.
  1. Trigger or jump the start pin to start running (pin 2 by default or can be jumped to a switch). Use the **3.3V** output pin for this because the inputs can only tolerate 3.3V.
  1. Do not disturb the mouse or touch screen while it's working.
  1. Unplug when complete.

## Useful References:
- https://wiki.seeedstudio.com/Seeeduino-XIAO/
- https://github.com/adafruit/Adafruit_TinyUSB_Arduino/releases/tag/0.10.5
