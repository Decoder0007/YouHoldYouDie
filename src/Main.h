#pragma once
#include <cocos2d.h>
#include "MinHook.h"
#include "gd.h"

using namespace cocos2d;

namespace PlayLayer {
    inline bool(__thiscall* init)(CCLayer* self, void* GJGameLevel);
    bool __fastcall initHook(CCLayer* self, int edx, void* GJGameLevel);

    inline void(__thiscall* update)(gd::PlayLayer* self, float deltatime);
    void __fastcall updateHook(gd::PlayLayer* self, int edx, float deltatime);

    inline bool(__thiscall* pushButton)(CCLayer* self, int state, bool player);
    bool __fastcall pushButtonHook(CCLayer* self, uintptr_t, int state, bool player);

    inline bool(__thiscall* releaseButton)(CCLayer* self, int state, bool player);
    bool __fastcall releaseButtonHook(CCLayer* self, uintptr_t, int state, bool player);

}

namespace Main {
    void mem_init();
}