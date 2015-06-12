#include <cstdio>
#include <windows.h>

#include "hl_alert_dll.h"
#include "console.h"
#include "keystroke.h"
#include "route.h"

// Handle to the thread
static HANDLE dllThread;

// Function pointer to our alert function
static DWORD_PTR our_alert_ptr = (DWORD_PTR)&our_alert;

// Console
static Console console;

// Route
static Route route;

void our_alert(int alert_type, char* formatString, ...)
{
  // Extract variadic function arguments
  va_list args;
  va_start(args, formatString);  // Start to extract after the "formatString"-argument
  char temp[1024];
  vsnprintf(temp, sizeof(temp), formatString, args);
  va_end(args);

  std::string message(temp);
  if (message.substr(0, 14) == "CHANGE LEVEL: ")
  {
    // Extract level from message
    std::string levelAndLandmark(message.substr(14));
    std::string level(levelAndLandmark.substr(0, levelAndLandmark.find(' ')));

    //console.write("message: [%s] levelAndLandmark: [%s] level: [%s]\n", message.c_str(), levelAndLandmark.c_str(), level.c_str());
    if (route.checkNextLevelInRoute(level))
    {
      console.write("Changing level to: %s - Next level in route, pressing hotkey!\n", level.c_str());

      // We need to release modifier keys for some reason
      KeyStroke::releaseKey(VK_SHIFT);
      KeyStroke::releaseKey(VK_CONTROL);
      KeyStroke::releaseKey(VK_MENU);

      // Then press our hotkey
      KeyStroke::pressAndRelease(VK_ADD);
    }
    else
    {
      console.write("Changing level to: %s - Not next level in route!\n", level.c_str());
    }
  }
}

void dllThreadFunc(HMODULE dllModule)
{
  if (!console.init())
  {
    OutputDebugStringA("Could not initialize console, aborting!");
    return;
  }
  console.write("HL Alert DLL started!\n");

  // Get the base address of hl.dll (if it's loaded.. hopefully it is)
  DWORD_PTR hlDllHandle = reinterpret_cast<DWORD_PTR>(GetModuleHandle("hl.dll"));
  if (hlDllHandle == 0)
  {
    console.write("Could not find handle for hl.dll, aborting!");
    return;
  }

  // hl.dll has a function pointer to the alert function in hw.dll
  // This is where this pointer is located
  DWORD_PTR realAlertFuncPtr = hlDllHandle + 0xD75B4;
  console.write("Found memory address of ALERT-function pointer: 0x%lX\n", realAlertFuncPtr);

  // Overwrite the function pointer with a pointer to our own function
  DWORD dwOldProtect;
  DWORD dwNewProtect;
  VirtualProtect((PVOID)realAlertFuncPtr, 4, PAGE_READWRITE, &dwOldProtect);
  memcpy((PVOID)realAlertFuncPtr, &our_alert_ptr, 4);
  VirtualProtect((PVOID)realAlertFuncPtr, 4, dwOldProtect, &dwNewProtect);
  console.write("Replaced function pointer with our function pointer!\n");
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      dllThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)dllThreadFunc, hinstDLL, 0, NULL);
      break;
    case DLL_PROCESS_DETACH:
      TerminateThread(dllThread, EXIT_SUCCESS);
      break;
  }
  return TRUE;
}
