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
// TUAbsMouse.cpp
//////////
//
// TinyUSB Absolute Mouse utility helper.
//
// See detailed comments in the header file.
//
// Original Author:
// Ray Cardillo / LongToothGamer
// https://LongToothGamer.com
// https://www.youtube.com/channel/UC8nJI40ZJ2C682oAsB16gCA
//
//////////

#include "TUAbsMouse.h"
#include <Arduino.h>
#include <Adafruit_TinyUSB.h>


#define MIN(X, Y)  ((X) < (Y) ? (X) : (Y))
#define MAX(X, Y)  ((X) > (Y) ? (X) : (Y))


uint8_t const desc_hid_report[] =
{
  TUD_HID_REPORT_DESC_MOUSE( HID_REPORT_ID(1) )
};


TUAbsMouseClass::TUAbsMouseClass() {
  buttonPressed       = false;
  buttonPressDelay    = DEFAULT_BUTTON_PRESS_DELAY;
  buttonReleaseDelay  = DEFAULT_BUTTON_RELEASE_DELAY;
  buttonDragDelay     = DEFAULT_BUTTON_DRAG_DELAY;
  
  screenResolutionX = DEFAULT_RESOLUTION_X;
  screenResolutionY = DEFAULT_RESOLUTION_Y;
  
  setMaxMoveDistance( DEFAULT_MAX_MOVE );
}


void TUAbsMouseClass::setScreenResolution(const uint16_t x, const uint16_t y) {
  screenResolutionX = x;
  screenResolutionY = y;
}


uint16_t TUAbsMouseClass::getScreenResolutionX() {
  return screenResolutionX;
}


uint16_t TUAbsMouseClass::getScreenResolutionY() {
  return screenResolutionY;
}


void TUAbsMouseClass::setMaxMoveDistance(const int8_t distance) {
  maxMoveDistance = distance;

  // maxMovesToTarget just establishes a rough upper limit as a defensive gaurd
  uint16_t maxMovesToTargetX = (screenResolutionX / maxMoveDistance) + 1;
  uint16_t maxMovesToTargetY = (screenResolutionY / maxMoveDistance) + 1;
  maxMovesToTarget = maxMovesToTargetX + maxMovesToTargetY;
}


int8_t TUAbsMouseClass::getMaxMoveDistance() {
  return maxMoveDistance;
}


uint8_t TUAbsMouseClass::getMaxMovesToTarget() {
  return maxMovesToTarget;
}


bool TUAbsMouseClass::isMouseButtonPressed() {
  return buttonPressed;
}

void TUAbsMouseClass::setButtonPressDelay(uint8_t delay) {
  buttonPressDelay = delay;
}


uint8_t TUAbsMouseClass::getButtonPressDelay() {
  return buttonPressDelay;
}


void TUAbsMouseClass::setButtonReleaseDelay(uint8_t delay) {
  buttonReleaseDelay = delay;
}


uint8_t TUAbsMouseClass::getButtonReleaseDelay() {
  return buttonReleaseDelay;
}


void TUAbsMouseClass::setButtonDragDelay(uint8_t delay) {
  buttonDragDelay = delay;
}


uint8_t TUAbsMouseClass::getButtonDragDelay() {
  return buttonDragDelay;
}


bool TUAbsMouseClass::begin() {
  usb_hid.setPollInterval(POLL_INTERVAL);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  
  return usb_hid.begin();
}


bool TUAbsMouseClass::ready() {
  // Remote wakeup if suspended (and if supported)
  // Note the the implementation already performs the required checks to verify.
  USBDevice.remoteWakeup();
  
  return usb_hid.ready();
}


bool TUAbsMouseClass::home() {
  // assume the worst
  positionX = screenResolutionX;
  positionY = screenResolutionY;
  return moveTo(0, 0);
}


void TUAbsMouseClass::setTarget(const uint16_t x, const uint16_t y) {
  // convert screen coordinates
  targetX = x;
  targetY = y;
}


uint16_t TUAbsMouseClass::getTargetX() {
  return targetX;
}


uint16_t TUAbsMouseClass::getTargetY() {
  return targetY;
}


uint16_t TUAbsMouseClass::getPositionX() {
  return positionX;
}


uint16_t TUAbsMouseClass::getPositionY() {
  return positionY;
}


bool TUAbsMouseClass::waitUntilReady() {
  // wait until the HID is ready and not busy (instead of using a static delay)
  // but protect with an upper limit in case something is stuck or hung
  for (int i=0; i<1000; i++) {
    if (usb_hid.ready()) {
      return true;
    }
    delay(1);
  }
  return false;
}


void TUAbsMouseClass::moveMouseWhenReady(const uint16_t x, const uint16_t y) {
  // this function really needs to complete because other logic assumes it worked
  while (!waitUntilReady()) {
    delay(1);
  }
  
  while (!usb_hid.mouseMove(1, x, y)) {
    delay(1);
  }
}


bool TUAbsMouseClass::moveOneStep() {
  uint16_t moveX = 0;
  if (positionX != targetX) {
    moveX = targetX > positionX ? MIN(maxMoveDistance, targetX - positionX) : MAX(-maxMoveDistance, targetX - positionX);
    positionX += moveX;
  }

  uint16_t moveY = 0;
  if (positionY != targetY) {
    moveY = targetY > positionY ? MIN(maxMoveDistance, targetY - positionY) : MAX(-maxMoveDistance, targetY - positionY);
    positionY += moveY;
  }

  if (moveX != 0 || moveY != 0) {
    moveMouseWhenReady(moveX, moveY);
  }

  return (positionX == targetX && positionY == targetY);
}


bool TUAbsMouseClass::moveToTarget() {
  for (int i=0; i<maxMovesToTarget; i++) {
    if (moveOneStep()) {
      // we're at the destination...
      if (buttonPressed) {
        // add a drag delay if the button is pressed during the move
        delay(buttonDragDelay);
      }
      return true;
    }
  }
  return false;
}


bool TUAbsMouseClass::moveTo(const uint16_t x, const uint16_t y) {
  setTarget(x, y);
  return moveToTarget();
}


bool TUAbsMouseClass::mouseButtonPress() {
  // don't send another mouse report if the button is already pressed
  if (buttonPressed) {
    return false;
  }
  
  buttonPressed = true;
  
  // this function really needs to complete because other logic assumes it worked
  while (!waitUntilReady()) {
    delay(1);
  }
  
  // calling report directly here - otherwise the class does not cache the button state properly
  while (!usb_hid.mouseReport(1, MOUSE_BUTTON_LEFT, 0, 0, 0, 0)) {
    delay(1);
  }
  
  delay(buttonPressDelay);

  return true;
}


bool TUAbsMouseClass::mouseButtonRelease() {
  // don't send another mouse report if the button is already released
  if (!buttonPressed) {
    return false;
  }
  
  buttonPressed = false;

  // this function really needs to complete because other logic assumes it worked
  while (!waitUntilReady()) {
    delay(1);
  }
  
  // calling report directly here - otherwise the class does not cache the button state properly
  while (!usb_hid.mouseReport(1, 0, 0, 0, 0, 0)) {
    delay(1);
  }
  
  delay(buttonReleaseDelay);

  return true;
}


bool TUAbsMouseClass::setButtonPressState(bool pressed) {
  return pressed ? mouseButtonPress() : mouseButtonRelease();
}


void TUAbsMouseClass::clickMouse() {
  mouseButtonPress();
  mouseButtonRelease();
}


void TUAbsMouseClass::clickMouse(uint16_t x, uint16_t y) {
  moveTo(x, y);
  clickMouse();  
}


// Global instance for convenience.
TUAbsMouseClass TUAbsMouse;
