 #include "ScriptPCH.h"
     
    class Morph_npc : public CreatureScript
    {
    public:
        Morph_npc() : CreatureScript("Morph_npc") { }
     
     
        bool OnGossipHello(Player* player, Creature* creature)
        {
                    if (player->isInCombat())
                    {
                                            player->GetSession()->SendNotification(" You are in combat!");
                                            player->CLOSE_GOSSIP_MENU();
                                            return false;
                    }
     
                    player->ADD_GOSSIP_ITEM(6, "Garrosh Hellscream", GOSSIP_SENDER_MAIN, 1);
                                    player->ADD_GOSSIP_ITEM(6, "Tyrande Whisperwind", GOSSIP_SENDER_MAIN, 2);
                                    player->ADD_GOSSIP_ITEM(6, "Prophet Velen", GOSSIP_SENDER_MAIN, 3);
                                    player->ADD_GOSSIP_ITEM(6, "Thrall", GOSSIP_SENDER_MAIN, 4);
                                    player->ADD_GOSSIP_ITEM(6, "Lady sylvanas windrunner", GOSSIP_SENDER_MAIN, 5);
                                    player->ADD_GOSSIP_ITEM(6, "Silthreen Guard", GOSSIP_SENDER_MAIN, 6);
									player->ADD_GOSSIP_ITEM(6, "Maiev Shadowsong", GOSSIP_SENDER_MAIN, 7);
									player->ADD_GOSSIP_ITEM(6, "Gondar The Bounty Hunter", GOSSIP_SENDER_MAIN, 8);
									player->ADD_GOSSIP_ITEM(6, "Murloc", GOSSIP_SENDER_MAIN, 9);
									player->ADD_GOSSIP_ITEM(6, "Malfurion Stormrage", GOSSIP_SENDER_MAIN, 10);
									player->ADD_GOSSIP_ITEM(6, "DeMorph", GOSSIP_SENDER_MAIN, 11);
                    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,creature->GetGUID());
                    return true;
            }
           
            bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 action)
            {
     
                    switch (action)
            {
                case 1:
                    player->CLOSE_GOSSIP_MENU();
                    player->SetDisplayId(32907);
                    break;
                case 2:
                    player->CLOSE_GOSSIP_MENU();
                    player->SetDisplayId(39620);
                    break;
                case 3:
                    player->CLOSE_GOSSIP_MENU();
                    player->SetDisplayId(17822);
                    break;
                case 4:
                    player->CLOSE_GOSSIP_MENU();
                    player->SetDisplayId(39145);
                    break;
                case 5:
                    player->CLOSE_GOSSIP_MENU();
                    player->SetDisplayId(28213);
                    break;
				case 6:
                    player->CLOSE_GOSSIP_MENU();
                    player->SetDisplayId(31811);
                    break;	
				case 7:
                    player->CLOSE_GOSSIP_MENU();
                    player->SetDisplayId(20628);
                    break;	
				case 8:
                    player->CLOSE_GOSSIP_MENU();
                    player->SetDisplayId(18425);
                    break;	
				case 9:
                    player->CLOSE_GOSSIP_MENU();
                    player->SetDisplayId(34352);
                    break;	
				case 10:
                    player->CLOSE_GOSSIP_MENU();
                    player->SetDisplayId(35095);
                    break;						
                case 11:
                    player->CLOSE_GOSSIP_MENU();
                    player->DeMorph();
                    break;
                    }
                    return true;
            }
    };
     
    void AddSC_Morph_npc()
    {
            new Morph_npc();
    }  