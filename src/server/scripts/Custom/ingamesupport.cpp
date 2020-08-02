/*
<--------------------------------------------------------------------------->
 - Developer(s): Ghostcrawler336
 - Complete: %100
 - ScriptName: 'Ingame Support NPC(npc_info)'
 - Comment: N/A
<--------------------------------------------------------------------------->
*/
#include "ScriptPCH.h"
 
class npc_info : public CreatureScript
{
        public:
                npc_info() : CreatureScript("npc_info")
                {
                }
 
                bool OnGossipHello(Player * pPlayer, Creature * pCreature)
                {
                        pPlayer->ADD_GOSSIP_ITEM(4, "", GOSSIP_SENDER_MAIN, 0);
                        pPlayer->ADD_GOSSIP_ITEM(4, "How do I make a ticket?", GOSSIP_SENDER_MAIN, 1);
                        pPlayer->ADD_GOSSIP_ITEM(4, "How do I gear up?", GOSSIP_SENDER_MAIN, 2);
                        pPlayer->ADD_GOSSIP_ITEM(0, "Nevermind...", GOSSIP_SENDER_MAIN, 3);
                        pPlayer->PlayerTalkClass->SendGossipMenu(9425, pCreature->GetGUID());
                        return true;
                }
 
                bool OnGossipSelect(Player * Player, Creature * Creature, uint32 /*uiSender*/, uint32 uiAction)
                {
                        if(!Player)
                                return true;
                       
                        switch(uiAction)
                        {
                                case 0: // This case will send the support message for "How Do I get Gold?"
                                        {
                                                ChatHandler(Player->GetSession()).PSendSysMessage("Message Here", Player->GetName());
                                                Player->PlayerTalkClass->SendCloseGossip();
                                        }break;
                                case 1: // This case will send the support message for "How Do I Make A Ticket?
                                        {
 
                                                ChatHandler(Player->GetSession()).PSendSysMessage("Message Here", Player->GetName());
                                                Player->PlayerTalkClass->SendCloseGossip();
                                        }break;
                                case 2: // This case will send the support message for "How Do I Gear Up?"
                                        {
                                                ChatHandler(Player->GetSession()).PSendSysMessage("Message Here", Player->GetName());
                                                Player->PlayerTalkClass->SendCloseGossip();
                                        }break;
                                case 3:
                                        {
                                                Player->PlayerTalkClass->SendCloseGossip();
                                        }break;
                        }
                        return true;
                }
 
};
 
void AddSC_npc_info()
{
        new npc_info();
}