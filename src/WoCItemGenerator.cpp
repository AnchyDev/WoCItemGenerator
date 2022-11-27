#include "WoCItemGenerator.h"

void EnchantItem(Player* player, Item* item, EnchantmentSlot slot, uint32 enchantId, bool overwrite)
{
    if (item->GetEnchantmentId(slot) && !overwrite)
    {
        return;
    }

    player->ApplyEnchantment(item, false);
    item->SetEnchantment(EnchantmentSlot(slot), enchantId, 0, 0);
    player->ApplyEnchantment(item, true);

    return;
}

void WoCPlayer::OnEquip(Player* /*player*/, Item* item, uint8 /*bag*/, uint8 /*slot*/, bool /*update*/)
{
    auto itemTemplate = item->GetTemplate();

    LOG_INFO("module", "{} {} {} {}", item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT),
        item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_2),
        item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_3),
        item->GetEnchantmentId(PRISMATIC_ENCHANTMENT_SLOT));

    LOG_INFO("module", "RandomSuffixId {} : Factor: {}", item->GetItemRandomPropertyId(), item->GetItemSuffixFactor());

    for (uint32 i = PROP_ENCHANTMENT_SLOT_0; i < MAX_ENCHANTMENT_SLOT; ++i)
    {
        uint32 enchant = item->GetEnchantmentId(EnchantmentSlot(i));
        LOG_INFO("module", "Enchant({}) {}", i, enchant);
    }
}

void WoCPlayer::OnStoreNewItem(Player* player, Item* item, uint32 /*count*/)
{
    auto itemTemplate = item->GetTemplate();

    if (!itemTemplate->HasWoCFlag(WOC_FLAGS_ITEM))
    {
        return;
    }

    double roll = rand_chance();
    ChatHandler(player->GetSession()).SendSysMessage(Acore::StringFormat("Rolled"));
    if (roll > 50.0)
    {

        if (itemTemplate->HasWoCFlag(WOC_FLAGS_ITEM_PHYS))
        {
            item->SetItemRandomProperties(urand(100, 108));
        }
        
        ChatHandler(player->GetSession()).SendSysMessage("Won roll");

        //EnchantItem(player, item, PRISMATIC_ENCHANTMENT_SLOT, 3884, true);

        LOG_INFO("module", "RandomSuffixId {}", item->GetItemRandomPropertyId());
    }
}

void AddWoCItemGeneratorScripts()
{
    new WoCPlayer();
}
