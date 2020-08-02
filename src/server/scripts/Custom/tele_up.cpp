#include "ScriptPCH.h"

class tele_up : public CreatureScript

{
	public:
		tele_up() : CreatureScript("tele_up") { }
		
		bool OnGossipHello(Player * player, Creature * creature)
		{
			
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport Above", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Close Menu...", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
			player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
			return true;
			}
			
			bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 actions)
			{
				player->PlayerTalkClass->ClearMenus();
				
				if (sender != GOSSIP_SENDER_MAIN)
				return false;
				
				switch (actions)
				{
					case GOSSIP_ACTION_INFO_DEF+1:
					player->TeleportTo(530, -4128.13234f, 1140.367188f, 62.040733f, 1.080897f);
					player->GetSession()->SendAreaTriggerMessage("You have teleported! (1001)!");
					player->PlayerTalkClass->SendCloseGossip();
					break;
					
					case GOSSIP_ACTION_INFO_DEF+2:
						player->PlayerTalkClass->SendCloseGossip();
						break;
				}
				return true;
			}
		
};

void AddSC_tele_up()
{
	new tele_up();
}