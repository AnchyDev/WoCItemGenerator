#include "WoCItemGenerator.h"

void WoCPlayer::OnStoreNewItem(Player* player, Item* /*item*/, uint32 /*count*/)
{
	ChatHandler(player->GetSession()).SendSysMessage("Stored New Item.");
}

void AddWoCItemGeneratorScripts()
{
    new WoCPlayer();
}
