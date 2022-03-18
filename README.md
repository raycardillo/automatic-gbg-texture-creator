# automatic-gbg-texture-creator

Automatic Game Builder Garage Texture Creator.

This is based upon some great work that has been done by **VideoDojo** community
members (mainly **Scrubz** and **Borri** to my knowledge).
There are two main parts to the solution: **Image Analysis** and **Mouse Contoller**.

Their solution was developed on an **Arduino Leonardo** board, but I had some spare
**Seeeduino XIAO** boards sitting around and wanted to use them for this purpose.
They're inexpensive but very capable tiny little microprocessor boards.
However, it did not turn out to be as simple a task as I originally thought because
it requires the use of a special TinyUSB library so I almost had to start over.
See the `agbgtc_tinyusb` description below. I may add more variants later.

### Image Analysis
The image analysis utility is required to create the texture data CSV representing the color of each pixel.

Right now, I've just copied their latest HTML helper utils for convenience here.
If you want to see the latest they're working on, see the VideoDojo YouTube
channel or visit the [VideoDojo community Discord](https://discord.com/channels/851450528944357437/941124085595910174)
and look at the pinned messages for the latest developments.

### Mouse Controller
The mouse controller program simulates mouse clicks required to create the textures.

- **[agbgtc_tinyusb](./agbgtc_tinyusb)** - This is a variant I created with the
intention of supporting any TinyUSB device but it currently depends on the
`Adafruit_TinyUSB` library (version `0.10.5`). It also includes a special mouse
utility helper that I created specifically for this project.

## Useful References:
- USB HID related specifications
  - https://www.usb.org/sites/default/files/documents/hid1_11.pdf
  - https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
