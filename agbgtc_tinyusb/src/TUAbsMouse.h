// Copyright 2022 Raymond Cardillo dba Cardillo's Creations, LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//////////
// TUAbsMouse.h
//////////
//
// TinyUSB Absolute Mouse utility helper.
//
// The goal is to be efficient and avoid delays as much as possible by default.
//
// The most basic usage is to call `home()` to get the mouse pointer to a known
// location of (0,0) and then the utility keeps track of the location and performs
// the delta movements required to get to the requested absolute mouse position.
// 
// NOTES:
// 1. Currently based on the Adafruit_TinyUSB library and tested on Seeeduino XIAO.
// 2. I have experimented with a custom mouse report for absolute positioning but it
//    requires a non-standard report format that is not compatible with all drivers.
// 3. I will probably break this out into a separate library for others to use.
//
// Developed and tested with:
// - Arduino IDE = v2.0.0-rc5
// - Seeeduino XIAO Board = v1.8.2
// - Adafruit_TinyUSB = v0.10.5 // DO NOT USE v1.x.x until Seeeduino updates the board library (breaking change)
//
// Original Author:
// Ray Cardillo / LongToothGamer
// https://LongToothGamer.com
// https://www.youtube.com/channel/UC8nJI40ZJ2C682oAsB16gCA
//
//////////

#ifndef TinyUSBAbsoluteMouse_h
#define TinyUSBAbsoluteMouse_h


#include <Adafruit_USBD_HID.h>


class TUAbsMouseClass {
  // The HID device poll interval to use when setting up HID device.
  const uint8_t POLL_INTERVAL = 2;

  // The default button delays to use. These also establishe the click duration.
  // Reasonable values are needed for the driver to be able to recognize the
  // button state change. These values were determined to be safe experimentally.
  const uint8_t DEFAULT_BUTTON_PRESS_DELAY   = 60;
  const uint8_t DEFAULT_BUTTON_RELEASE_DELAY = 60;

  // Make sure the driver sees the move when the button is pressed.
  const uint8_t DEFAULT_BUTTON_DRAG_DELAY = 30;
  
  // The default X resolution. Mainly needed to help with `home()` logic.
  const uint16_t DEFAULT_RESOLUTION_X = 1280;

  // The default Y resolution. Mainly needed to help with `home()` logic.
  const uint16_t DEFAULT_RESOLUTION_Y = 720;

  // The default maximum mouse move delta. The default is the max delta that an
  // 8-bit HID report can contain (max value for a signed `int8_t`).
  //
  // NOTE:
  // I've experimented with 16-bit reports (and absolute mode HID reports) but
  // discovered problems with drivers receiving these non-standard HID events.
  // So given that we need to perform delta moves, we want this to be the max
  // value for speed, but perhaps some may want smaller values for a smoother
  // looking response (but it would take longer).
  const int8_t DEFAULT_MAX_MOVE = 127;

  public:
  
    TUAbsMouseClass();

    // Must be called in your setup() to get the HID device ready for use.
    bool begin();

    // Should be called near the top of your loop() or whenever the device
    // may be suspended and may need to get ready again. This attempts to wakeup
    // the device if suspended (and if resume is supported). It also makes sure the
    // HID device is ready to be used.
    bool ready();

    // Should be called at least once before absolute positioning is expected.
    // This requires the screen resolution to be specified in advance and navigates
    // to (0,0) so the subsequent positioning can be absolute from there. As such,
    // it assumes a constrained environment. This is the normal case for users of
    // utilities like this so we're not penalizing others with an extra check.
    // If you're expecting to "fight" with the user or other devices for the mouse
    // position, then this type of utility cannot really solve that problem anyways.
    bool home();

    // Sets the screen resolution so `home()` knows the worst case to get to (0,0).
    void setScreenResolution(const uint16_t x, const uint16_t y);
    uint16_t getScreenResolutionX();
    uint16_t getScreenResolutionY();

    // Sets the max move distance delta if the fast `DEFAULT_MAX_MOVE` is not preferred. 
    void setMaxMoveDistance(const int8_t distance);
    int8_t getMaxMoveDistance();
    uint8_t getMaxMovesToTarget();

    // Sets the amount of time to delay after sending a mouse press event. 
    void setButtonPressDelay(const uint8_t delay);
    uint8_t getButtonPressDelay();

    // Sets the amount of time to delay after sending a mouse release event. 
    void setButtonReleaseDelay(const uint8_t delay);
    uint8_t getButtonReleaseDelay();

    // Sets the amount of time to delay while dragging the mouse pointer. 
    void setButtonDragDelay(const uint8_t delay);
    uint8_t getButtonDragDelay();

    // Sets the intended target (but does not perform any move operations).
    // See `moveTo()` for a more convenient way to set the target and perform the move.
    void setTarget(const uint16_t x, const uint16_t y);

    // Next target for the X position (may require multiple moves).
    uint16_t getTargetX();

    // Next target for the Y position (may require multiple moves).
    uint16_t getTargetY();

    // Current X position of the mouse pointer.
    uint16_t getPositionX();

    // Current Y position of the mouse pointer.
    uint16_t getPositionY();

    // Wait until the HID device is ready for more input. This is used internally to
    // avoid introducing arbitrary delays, but it may be generally helpful as well.
    // Returns `true` when the HID device is ready to be used.
    bool waitUntilReady();

    // Calls `waitUntilReady()` and then aggressively tries to move to that new position.
    // This function has the potential to get stuck in an infinite loop beause it
    // will keep waiting for the device to be ready and keep trying to perform the
    // move operation (send an HID move report) until both operations succeed.
    // It will either succeed or get stuck trying.
    void moveMouseWhenReady(const uint16_t x, const uint16_t y);

    // Moves the mouse pointer towards the target as much as possible in one step.
    // Set the target first (or use another helper that does that for you).
    // Returns `true` if the move resulted in the position being at the target.
    bool moveOneStep();

    // Aggressively tries to move to the previously specified target position.
    // This function also has the potential to get stuck in an infinite loop beause
    // it uses `moveMouseWhenReady()` to perform the move operation.
    // Will also delay for `buttonPressDelay` if pressed to make sure driver sees it.
    // Returns `true` if the move resulted in the position being at the target.
    bool moveToTarget();

    // Sets the new target and aggressively tries to move to that new position.
    // This function also has the potential to get stuck in an infinite loop beause
    // it uses `moveToTarget()` to perform the move operation.
    // Will also delay for `buttonPressDelay` if pressed to make sure driver sees it.
    // Returns `true` if the move resulted in the position being at the target.
    bool moveTo(const uint16_t x, const uint16_t y);

    // Returns true if the mouse is currently pressed.
    bool isMouseButtonPressed();
    
    // Press the mouse button at the current mouse position.
    // Returns `true` if the state changed and `false` otherwise.
    bool mouseButtonPress();

    // Press the mouse button at the current mouse position.
    // Returns `true` if the state changed and `false` otherwise.
    bool mouseButtonRelease();

    // Press or Release the mouse button at the current mouse position
    // according to the boolean state argument.
    // Returns `true` if the state changed and `false` otherwise.
    bool setButtonPressState(bool pressed);

    // Press the mouse button and release it at the current mouse position.
    void clickMouse();

    // Move to the specified mouse position and then press and release the mouse button.
    void clickMouse(uint16_t x, uint16_t y);

  private:

    Adafruit_USBD_HID usb_hid;

    int8_t maxMoveDistance;
    uint8_t maxMovesToTarget;

    bool buttonPressed;
    uint8_t buttonPressDelay;
    uint8_t buttonReleaseDelay;
    uint8_t buttonDragDelay;

    uint16_t screenResolutionX;
    uint16_t screenResolutionY;

    uint16_t positionX;
    uint16_t positionY;

    uint16_t targetX;
    uint16_t targetY;
};


// Global instance for convenience.
extern TUAbsMouseClass TUAbsMouse;


#endif // TinyUSBAbsoluteMouse_h
