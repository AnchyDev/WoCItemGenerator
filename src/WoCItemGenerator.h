#ifndef MODULE_WOCITEMGENERATOR
#define MODULE_WOCITEMGENERATOR

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include <AI/ScriptedAI/ScriptedGossip.h>

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

/*class WoCItemLevelUpgradeCreature : public CreatureScript
{
public:
    WoCItemLevelUpgradeCreature() : CreatureScript("WoCItemLevelUpgradeCreature") { }

private:
    enum ItemLevelGossips
    {
        ITEMLEVEL_MAINMENU_GREET = 410001,
        ITEMLEVEL_UPGRADE_GREET = 410002,

        ITEMLEVEL_UPGRADE_START = 1001,
        ITEMLEVEL_MAINMENU_GOODBYE = 1500
    };

    void SayGoodbye(Player* player, Creature* creature)
    {
        CloseGossipMenuFor(player);
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I would like to upgrade the level of an item.", GOSSIP_SENDER_MAIN, ITEMLEVEL_UPGRADE_START);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Goodbye.", GOSSIP_SENDER_MAIN, ITEMLEVEL_MAINMENU_GOODBYE);
        SendGossipMenuFor(player, ITEMLEVEL_MAINMENU_GREET, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (sender != GOSSIP_SENDER_MAIN)
        {
            return false;
        }

        switch (action)
        {
        case ITEMLEVEL_UPGRADE_START:
            for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
            {
                Item* equipItem = player->GetItemByPos(i);

                if (!equipItem)
                {
                    continue;
                }

                if (!((equipItem->GetTemplate()->FlagsCu & 16) == 16))
                {
                    continue;
                }

                switch (i)
                {
                case EQUIPMENT_SLOT_HEAD:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Head", GOSSIP_SENDER_MAIN, ITEMLEVEL_MAINMENU_GOODBYE);
                    break;
                case EQUIPMENT_SLOT_NECK:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Necklace", GOSSIP_SENDER_MAIN, ITEMLEVEL_MAINMENU_GOODBYE);
                    break;
                case EQUIPMENT_SLOT_SHOULDERS:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Shoulders", GOSSIP_SENDER_MAIN, ITEMLEVEL_MAINMENU_GOODBYE);
                    break;
                case EQUIPMENT_SLOT_BACK:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Cape", GOSSIP_SENDER_MAIN, ITEMLEVEL_MAINMENU_GOODBYE);
                    break;
                case EQUIPMENT_SLOT_CHEST:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Chest", GOSSIP_SENDER_MAIN, ITEMLEVEL_MAINMENU_GOODBYE);
                    break;
                case EQUIPMENT_SLOT_WRISTS:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Wrists", GOSSIP_SENDER_MAIN, ITEMLEVEL_MAINMENU_GOODBYE);
                    break;
                case EQUIPMENT_SLOT_HANDS:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Hands", GOSSIP_SENDER_MAIN, ITEMLEVEL_MAINMENU_GOODBYE);
                    break;
                case EQUIPMENT_SLOT_WAIST:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Waist", GOSSIP_SENDER_MAIN, ITEMLEVEL_MAINMENU_GOODBYE);
                    break;
                case EQUIPMENT_SLOT_LEGS:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Legs", GOSSIP_SENDER_MAIN, ITEMLEVEL_MAINMENU_GOODBYE);
                    break;
                case EQUIPMENT_SLOT_FEET:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Feet", GOSSIP_SENDER_MAIN, ITEMLEVEL_MAINMENU_GOODBYE);
                    break;
                case EQUIPMENT_SLOT_FINGER1:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Ring 1", GOSSIP_SENDER_MAIN, ITEMLEVEL_MAINMENU_GOODBYE);
                    break;
                case EQUIPMENT_SLOT_FINGER2:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Ring 2", GOSSIP_SENDER_MAIN, ITEMLEVEL_MAINMENU_GOODBYE);
                    break;
                case EQUIPMENT_SLOT_TRINKET1:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Trinket 1", GOSSIP_SENDER_MAIN, ITEMLEVEL_MAINMENU_GOODBYE);
                    break;
                case EQUIPMENT_SLOT_TRINKET2:
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Trinket 2", GOSSIP_SENDER_MAIN, ITEMLEVEL_MAINMENU_GOODBYE);
                    break;
                }
            }
            SendGossipMenuFor(player, ITEMLEVEL_UPGRADE_GREET, creature->GetGUID());
            break;

        case ITEMLEVEL_MAINMENU_GOODBYE:
            SayGoodbye(player, creature);
            break;
        }

        return true;
    }
};*/

#endif
