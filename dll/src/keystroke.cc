#include "keystroke.h"

bool KeyStroke::isInitialized;
INPUT KeyStroke::input;

void KeyStroke::init()
{
  if (!isInitialized)
  {
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = 0;
    input.ki.wScan = 0;
    input.ki.dwFlags = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    isInitialized = true;
  }
}

void KeyStroke::pressKey(WORD vkCode)
{
  init();

  input.ki.wVk = vkCode;
  input.ki.dwFlags = 0;

  SendInput(1, &input, sizeof(input));
}

void KeyStroke::releaseKey(WORD vkCode)
{
  init();

  input.ki.wVk = vkCode;
  input.ki.dwFlags = KEYEVENTF_KEYUP;

  SendInput(1, &input, sizeof(input));
}

void KeyStroke::pressAndRelease(WORD vkCode)
{
  pressKey(vkCode);
  releaseKey(vkCode);
}
