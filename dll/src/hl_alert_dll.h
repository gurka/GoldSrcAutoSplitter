#ifndef HL_ALERT_DLL_H_
#define HL_ALERT_DLL_H_

#define DLL_EXPORT __declspec(dllexport)

void our_alert(int alert_type, char* formatString, ...);
void pressSplitHotkey();
void dllThreadFunc(HMODULE dllModule);

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);

#endif  // HL_ALERT_DLL_H_
