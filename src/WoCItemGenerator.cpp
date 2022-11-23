#include "WoCItemGenerator.h"

bool WoCPlayer::IsWoCItem(const ItemTemplate* itemTemplate)
{
    return (itemTemplate->FlagsCu & WOC_FLAGS_ITEM) == WOC_FLAGS_ITEM;
}

void WoCPlayer::OnStoreNewItem(Player* player, Item* item, uint32 /*count*/)
{
    auto itemTemplate = item->GetTemplate();

    if (!IsWoCItem(itemTemplate))
    {
        return;
    }

    if (rand_chance() > 50)
    {
        item->SetItemRandomProperties(-441101);
    }

	ChatHandler(player->GetSession()).SendSysMessage("Stored New Item.");
}

void AddWoCItemGeneratorScripts()
{
    new WoCPlayer();
}
