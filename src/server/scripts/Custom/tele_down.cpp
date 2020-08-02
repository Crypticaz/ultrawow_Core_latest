#include "ScriptPCH.h"

class tele_down : public CreatureScript

{
	public:
		tele_down() : CreatureScript("tele_down") { }
		
		bool OnGossipHello(Player * player, Creature * creature)
		{
			
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Teleport Below", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
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
					player->TeleportTo(530, -4138.987305f, 1122.728027f, 53.929443f, 4.176939f);
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

void AddSC_tele_down()
{
	new tele_down();
}