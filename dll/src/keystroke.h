#ifndef KEYSTROKE_H_
#define KEYSTROKE_H_

#include <windows.h>

class KeyStroke
{
 public:
  static void init();
  static void pressKey(WORD vkCode);
  static void releaseKey(WORD vkCode);
  static void pressAndRelease(WORD vkCode);

 private:
  static bool isInitialized;
  static INPUT input;
};

#endif  // KEYSTROKE_H_
