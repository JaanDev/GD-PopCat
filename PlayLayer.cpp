#include "PlayLayer.h"
#include "CCDirectorModified.h"
#include "GameManager.h"

bool __fastcall PlayLayer::initHook(CCLayer* self, int edx, void* GJGameLevel) {
    // Idk why I need to hook it ._.
    bool ret = PlayLayer::init(self, GJGameLevel);

    void* gm = GameManager::getSharedState();
    if (GameManager::getGameVariable(gm, "pop-cat-go"))
        PlayLayer::ChangeCat(0);

    return ret;
}

void __fastcall PlayLayer::ChangeCat(int type) {
    void* gm = GameManager::getSharedState();

    // Check if user activated our setting
    if (GameManager::getGameVariable(gm, "pop-cat-go")) {

        // Get current scene
        CCDirectorModified* director = (CCDirectorModified*)CCDirectorModified::sharedDirector();
        CCScene* scene = director->getRunningScene();

        // Remove an existing cat
        scene->removeChildByTag(941);

        // Create a sprite
        auto catspr = CCSprite::create();
        if (type == 1) {
            // Play the pop sound
            PlaySound(L"Resources\\PopCat.wav", NULL, SND_FILENAME | SND_ASYNC);

            catspr = CCSprite::create("Resources\\GJ_PopCat01.png");
        }
        else {
            catspr = CCSprite::create("Resources\\GJ_PopCat00.png");
        }

        // Create a new cat
        auto cat = CCMenuItemSpriteExtra::create(catspr, catspr, scene, nullptr);

        // Set up the new cat
        cat->setAnchorPoint({ 0, 0 });
        cat->setPosition({ 0, 0 });
        cat->setScale(1.f);
        cat->setTag(941);

        // Add the new cat
        scene->addChild(cat, 98);
    }
}

void PlayLayer::mem_init()
{
    // Hook
    size_t base = reinterpret_cast<size_t>(GetModuleHandle(0));

    MH_CreateHook(
        (PVOID)(base + 0x01FB780),
        PlayLayer::initHook,
        (LPVOID*)&PlayLayer::init
    );
}