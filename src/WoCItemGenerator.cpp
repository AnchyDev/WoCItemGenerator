#include "WoCItemGenerator.h"

bool WoCPlayer::IsWoCItem(const ItemTemplate* itemTemplate)
{
    return (itemTemplate->FlagsCu & WOC_FLAGS_ITEM) == WOC_FLAGS_ITEM;
}

void SetSuffix(Item* item, int32 randomPropId)
{
    ItemRandomSuffixEntry const* item_rand = sItemRandomSuffixStore.LookupEntry(randomPropId);

    if (!item_rand)
    {
        LOG_INFO("module", "Could not find Random Suffix: {} from sItemRandomSuffixStore.", randomPropId);
        return;
    }

    if (item->GetInt32Value(ITEM_FIELD_RANDOM_PROPERTIES_ID) != -int32(item_rand->ID) ||
        !item->GetItemSuffixFactor())
    {
        item->SetInt32Value(ITEM_FIELD_RANDOM_PROPERTIES_ID, -int32(item_rand->ID));
        item->UpdateItemSuffixFactor();
        item->SetState(ITEM_CHANGED, item->GetOwner());
    }
    else
    {
        LOG_INFO("module", "Failed ITEM_FIELD_RANDOM_PROPERTIES_ID & GetItemSuffixFactor check.");
        return;
    }

    for (uint32 i = PROP_ENCHANTMENT_SLOT_0; i < MAX_ENCHANTMENT_SLOT; ++i)
        item->SetEnchantment(EnchantmentSlot(i), item_rand->Enchantment[i - PROP_ENCHANTMENT_SLOT_0], 0, 0);
}

void WoCPlayer::OnStoreNewItem(Player* player, Item* item, uint32 /*count*/)
{
    auto itemTemplate = item->GetTemplate();

    if (!IsWoCItem(itemTemplate))
    {
        return;
    }

    double roll = rand_chance();
    ChatHandler(player->GetSession()).SendSysMessage(Acore::StringFormat("Rolled {}", roll));
    if (roll > 50.0)
    {
        SetSuffix(item, 100);
        //item->SetItemRandomProperties(-441101);
        ChatHandler(player->GetSession()).SendSysMessage("Won roll");
    }

	ChatHandler(player->GetSession()).SendSysMessage("Stored New Item.");
}

void AddWoCItemGeneratorScripts()
{
    new WoCPlayer();
}
