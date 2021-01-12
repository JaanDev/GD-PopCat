#pragma once
#include <cocos2d.h>
#include "minhook/include/MinHook.h"

using namespace cocos2d;

namespace PlayLayer {
    // Original function
    inline bool(__thiscall* init)(CCLayer* self, void* GJGameLevel);

    // Hook function
    bool __fastcall initHook(CCLayer* self, int edx, void* GJGameLevel);

    // My function
    void __fastcall ChangeCat(int type);

    // Hook init function
    void mem_init();
}