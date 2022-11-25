#ifndef MODULE_WOCITEMGENERATOR
#define MODULE_WOCITEMGENERATOR

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

class WoCItem : public ItemTemplate
{
public:
    WoCItem(ItemTemplate const* base) : ItemTemplate(*base) { }
};

class WoCPlayer : public PlayerScript
{
public:
    WoCPlayer() : PlayerScript("WoCPlayer") { }

private:
    enum WoCFlags
    {
        WOC_FLAGS_ITEM = 16,
        WOC_FLAGS_ITEM_PHYS = 32,
        WOC_FLAGS_ITEM_SPELL = 64,
        WOC_FLAGS_ITEM_TANK = 128
    };
    bool HasWoCFlag(WoCFlags /*flag*/, const ItemTemplate* /*itemTemplate*/);
    void OnStoreNewItem(Player* /*player*/, Item* /*item*/, uint32 /*count*/) override;
    void OnEquip(Player* /*player*/, Item* /*item*/, uint8 /*bag*/, uint8 /*slot*/, bool /*update*/) override;
};

#endif
