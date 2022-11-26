#include "WoCItemGenerator.h"

bool WoCPlayer::HasWoCFlag(WoCFlags flag, const ItemTemplate* itemTemplate)
{
    return (itemTemplate->FlagsCu & flag) == flag;
}

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

uint32 GenerateEnchSuffixFactorFixed(uint32 item_id)
{
    ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(item_id);

    if (!itemProto)
        return 0;

    RandomPropertiesPointsEntry const* randomProperty = sRandomPropertiesPointsStore.LookupEntry(itemProto->ItemLevel);
    if (!randomProperty)
        return 0;

    uint32 suffixFactor;
    switch (itemProto->InventoryType)
    {
        // Items of that type don`t have points
    case INVTYPE_NON_EQUIP:
    case INVTYPE_BAG:
    case INVTYPE_TABARD:
    case INVTYPE_AMMO:
    case INVTYPE_QUIVER:
    case INVTYPE_RELIC:
        return 0;
        // Select point coefficient
    case INVTYPE_HEAD:
    case INVTYPE_BODY:
    case INVTYPE_CHEST:
    case INVTYPE_LEGS:
    case INVTYPE_2HWEAPON:
    case INVTYPE_ROBE:
        suffixFactor = 0;
        break;
    case INVTYPE_SHOULDERS:
    case INVTYPE_WAIST:
    case INVTYPE_FEET:
    case INVTYPE_HANDS:
    case INVTYPE_TRINKET:
        suffixFactor = 1;
        break;
    case INVTYPE_NECK:
    case INVTYPE_WRISTS:
    case INVTYPE_FINGER:
    case INVTYPE_SHIELD:
    case INVTYPE_CLOAK:
    case INVTYPE_HOLDABLE:
        suffixFactor = 2;
        break;
    case INVTYPE_WEAPON:
    case INVTYPE_WEAPONMAINHAND:
    case INVTYPE_WEAPONOFFHAND:
        suffixFactor = 3;
        break;
    case INVTYPE_RANGED:
    case INVTYPE_THROWN:
    case INVTYPE_RANGEDRIGHT:
        suffixFactor = 4;
        break;
    default:
        return 0;
    }
    // Select rare/epic modifier
    switch (itemProto->Quality)
    {
    case ITEM_QUALITY_NORMAL:
    case ITEM_QUALITY_UNCOMMON:
        return randomProperty->UncommonPropertiesPoints[suffixFactor];
    case ITEM_QUALITY_RARE:
        return randomProperty->RarePropertiesPoints[suffixFactor];
    case ITEM_QUALITY_EPIC:
        return randomProperty->EpicPropertiesPoints[suffixFactor];
    case ITEM_QUALITY_LEGENDARY:
    case ITEM_QUALITY_ARTIFACT:
        return 0;                                       // not have random properties
    default:
        break;
    }
    return 0;
}

void UpdateItemSuffixFactor(Item* item)
{
    uint32 suffixFactor = GenerateEnchSuffixFactorFixed(item->GetEntry());
    if (item->GetItemSuffixFactor() == suffixFactor)
        return;
    item->SetUInt32Value(ITEM_FIELD_PROPERTY_SEED, suffixFactor);
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
        UpdateItemSuffixFactor(item);
        item->SetState(ITEM_CHANGED, item->GetOwner());
    }
    else
    {
        LOG_INFO("module", "Failed ITEM_FIELD_RANDOM_PROPERTIES_ID & GetItemSuffixFactor check.");
        return;
    }

    for (uint32 i = PROP_ENCHANTMENT_SLOT_0; i < MAX_ENCHANTMENT_SLOT; ++i)
    {
        item->SetEnchantment(EnchantmentSlot(i), item_rand->Enchantment[i - PROP_ENCHANTMENT_SLOT_0], 0, 0);
    }
}

void WoCPlayer::OnEquip(Player* /*player*/, Item* item, uint8 /*bag*/, uint8 /*slot*/, bool /*update*/)
{
    auto itemTemplate = item->GetTemplate();

    LOG_INFO("module", "{} {} {} {}", item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT),
        item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_2),
        item->GetEnchantmentId(SOCK_ENCHANTMENT_SLOT_3),
        item->GetEnchantmentId(PRISMATIC_ENCHANTMENT_SLOT));

    //Not a WoC item
    if (!HasWoCFlag(WOC_FLAGS_ITEM, itemTemplate))
    {
        return;
    }

    //No needs to recalc the factor
    if (item->GetItemSuffixFactor() != 0)
    {
        return;
    }

    UpdateItemSuffixFactor(item);

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

    if (!HasWoCFlag(WOC_FLAGS_ITEM, itemTemplate))
    {
        return;
    }

    double roll = rand_chance();
    ChatHandler(player->GetSession()).SendSysMessage(Acore::StringFormat("Rolled"));
    if (roll > 50.0)
    {

        if (HasWoCFlag(WoCFlags::WOC_FLAGS_ITEM_PHYS, itemTemplate))
        {
            SetSuffix(item, 102);
        }
        else if (HasWoCFlag(WoCFlags::WOC_FLAGS_ITEM_SPELL, itemTemplate))
        {
            SetSuffix(item, 101);
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
