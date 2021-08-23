#include "Main.h"

bool mouseDown = true;
float heldTime = 0;

bool __fastcall PlayLayer::initHook(CCLayer* self, int, void* GJGameLevel) {
	auto result = init(self, GJGameLevel);
	if (!result) return result;
	return result;
}

void __fastcall PlayLayer::updateHook(gd::PlayLayer* self, int, float deltaTime) {
	update(self, deltaTime);

	auto menu = reinterpret_cast<CCMenu*>(self->getChildByTag(1));

	if (mouseDown) {
		heldTime = heldTime + deltaTime;
		if (heldTime > 1) {
			auto Player = self->m_pPlayer1;
			Player->position.y = 100000000;
			Player->position.x = -100000000;
		}
	}
	else {
		heldTime = 0;
	}
}

bool __fastcall PlayLayer::pushButtonHook(CCLayer* self, uintptr_t, int state, bool player) {
	pushButton(self, state, player);
	mouseDown = true;
	return true;
}
bool __fastcall PlayLayer::releaseButtonHook(CCLayer* self, uintptr_t, int state, bool player) {
	releaseButton(self, state, player);
	mouseDown = false;
	return true;
}

void Main::mem_init() {
	size_t base = reinterpret_cast<size_t>(GetModuleHandle(0));
	MH_CreateHook(
		(PVOID)(base + 0x01FB780),
		PlayLayer::initHook,
		(LPVOID*)&PlayLayer::init
	);

	MH_CreateHook(
		(PVOID)(base + 0x2029C0),
		PlayLayer::updateHook,
		(LPVOID*)&PlayLayer::update
	);

	MH_CreateHook(
		(PVOID)(base + 0x111500),
		PlayLayer::pushButtonHook,
		(LPVOID*)&PlayLayer::pushButton
	);

	MH_CreateHook(
		(PVOID)(base + 0x111660),
		PlayLayer::releaseButtonHook,
		(LPVOID*)&PlayLayer::releaseButton
	);
}