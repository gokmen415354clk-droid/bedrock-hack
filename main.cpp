#include <windows.h>
#include <iostream>

bool bSpeed = false;

void Cleanup(HMODULE hModule, FILE* f) {
    if (f) fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}

DWORD WINAPI CheatThread(HMODULE hModule) {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "=== HackerGamer1545 Bedrock Hack ===" << std::endl;
    std::cout << "[NUMPAD 1] Speed Hack (Ac/Kapat)" << std::endl;
    std::cout << "[END] Hileyi Kapat ve DLL'i Sok" << std::endl;

    uintptr_t baseAddress = (uintptr_t)GetModuleHandleA("Minecraft.Windows.exe");
    std::cout << "[+] Oyun Base Adresi: 0x" << std::hex << baseAddress << std::dec << std::endl;

    while (!GetAsyncKeyState(VK_END)) {
        if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
            bSpeed = !bSpeed;
            std::cout << "[>] Speed Hack: " << (bSpeed ? "AKTIF" : "PASIF") << std::endl;
            Beep(bSpeed ? 800 : 500, 200);
        }
        Sleep(30); 
    }

    std::cout << "[-] Hile kapatiliyor..." << std::endl;
    Sleep(1000);
    Cleanup(hModule, f);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)CheatThread, hModule, 0, nullptr));
        break;
    }
    return TRUE;
}
