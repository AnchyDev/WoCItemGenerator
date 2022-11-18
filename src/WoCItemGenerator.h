#ifndef MODULE_WOCITEMGENERATOR
#define MODULE_WOCITEMGENERATOR

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

class WoCPlayer : public PlayerScript
{
public:
    WoCPlayer() : PlayerScript("WoCPlayer") { }

private:
    void OnStoreNewItem(Player* player, Item* /*item*/, uint32 /*count*/) override;
};

#endif
