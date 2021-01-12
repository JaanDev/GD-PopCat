#include "pch.h"
#include "PlayerObject.h"
#include "PlayLayer.h"

bool __fastcall PlayerObject::pushButtonHook(void* self, int edx, void* PlayerButton) {
    // Pop Cat
    PlayLayer::ChangeCat(1);

    // Call the original function
    return PlayerObject::pushButton(self, PlayerButton);
}

bool __fastcall PlayerObject::releaseButtonHook(void* self, int edx, void* PlayerButton) {
    // Unpop Cat
    PlayLayer::ChangeCat(0);

    // Call the original function
    return PlayerObject::releaseButton(self, PlayerButton);
}

void PlayerObject::mem_init()
{
    // Hooks
    size_t base = reinterpret_cast<size_t>(GetModuleHandle(0));

    MH_CreateHook(
        (PVOID)(base + 0x1F4E40),
        PlayerObject::pushButtonHook,
        (LPVOID*)&PlayerObject::pushButton
    );

    MH_CreateHook(
        (PVOID)(base + 0x1F4F70),
        PlayerObject::releaseButtonHook,
        (LPVOID*)&PlayerObject::releaseButton
    );
}