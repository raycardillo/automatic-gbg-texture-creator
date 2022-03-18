---
layout: default
---

<!--
Copyright 2022 Raymond Cardillo dba Cardillo's Creations, LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
-->

This is a companion web page for the [{{ site.github.repository_name }}]({{ site.github.repository_url }})
project. It is intended to provide a **quick start** overview to help you get
started creating your own custom Texture Nodons with a **Seeeduino XIAO**
(or other TinyUSB) board.


**YouTube video coming that demonstrates everything you need to know.**


# Overview
The basic process is to convert an image and extract pixel data and then paste
that data into the mouse controller program, upload it to a board, and then run
the program when attached to the Nintendo Switch.

<img alt="AGBGTC Examples" src="{{ site.github.repository_url }}/raw/main/images/AGBGTC-Examples.jpg" style="max-width: 100%;">

## Image Extraction Utilities
These utilities convert an image into data that is used by the mouse controller program.

_They are hosted here for convenience but I did not write them. They were written
by **Scrubz** from the **VideoDojo** community. Review the GitHub project
**README** files for more background and full attribution._

[GBG_Texture_Builder_v1.2.html](./utils/GBG_Texture_Builder_v1.2.html)
: Converts images to texture data with several conversion options.

[Import_Textures_From_GBG_v1.1.html](./utils/Import_Textures_From_GBG_v1.1.html)
: Allows the extraction of any texture using only a screenshot of the GBG texture screen.


## Mouse Controller Program
The mouse controller program is uploaded to an Arduino or Seeeduino board and
uses the extracted image data to simulate mouse movements to automatically
create and draw Texture Nodons.

### Seeeduino XIAO
Download this repo and follow the README in the [agbgtc_tinyusb]({{ site.github.repository_url }}/tree/main/agbgtc_tinyusb) folder.

<figure>
  <img alt="Seeeduino XIAO" src="{{ site.github.repository_url }}/raw/main/images/Seeeduino-XIAO.jpg" style="width:400px;height:300px;">
  <figcaption style="font-style:italic;font-weight:300;">Photo Credit: Ray Cardillo / LongToothGamer</figcaption>
</figure>

### Arduino Leonardo
See notes in the README and visit the [VideoDojo community discord](https://discord.com/channels/851450528944357437/941124085595910174)
for more information about this version.

<figure>
  <img alt="Arduino Leonardo" src="{{ site.github.repository_url }}/raw/main/images/Arduino-Leonardo.jpg" style="width:400px;height:300px;">
  <figcaption style="font-style:italic;font-weight:300;">Photo Credit: Becky Stern - Flickr: Arduino Leonardo</figcaption>
</figure>
