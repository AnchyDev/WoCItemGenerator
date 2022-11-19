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

    WoCItem* wocItem = new WoCItem(itemTemplate);
    wocItem->ItemId = currentId;
    wocItem->Name1 = Acore::StringFormat("{} +{}", wocItem->Name1, currentId);

    currentId += 1;

	ChatHandler(player->GetSession()).SendSysMessage("Stored New Item.");
}

void AddWoCItemGeneratorScripts()
{
    new WoCPlayer();
}
