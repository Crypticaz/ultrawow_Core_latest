#include "ScriptPCH.h"
#include "ScriptedCreature.h"


enum eNums
{
    SPELL_FROSTSHOCK = 23115,
	SPELL_CHILL      = 21098,
	SPELL_ICEBLOCK   = 41590,
};

class horde_boss : public CreatureScript
{
    public:
		horde_boss() : CreatureScript("hordeboss"){}
		
		CreatureAI * GetAI(Creature * pCreature) const
		{
		     return new horde_bossAI(pCreature);
		}

		struct horde_bossAI : public ScriptedAI
		{
			horde_bossAI(Creature *c) : ScriptedAI(c){}
						    
				 uint32 Frostshock_Timer;
				 uint32 Chill_Timer;		 
								
				 int phase;
				 int percentPassed;
			
			void Reset()
			{
			     me->SetHealth(me->GetMaxHealth());
			     phase = 1;
				 percentPassed = 0;			
			     Frostshock_Timer       = 8000;
				 Chill_Timer            = 3000;		 
			}
			void EnterCombat(Unit * /*who*/)
            {
			     percentPassed = 1;
            }
            void JustDied(Unit* pPlayer) 
			{
			    char msg[250];
		        snprintf(msg, 250, "|cffff0000[Event System]|r The |cff00ccff Alliance|r have won the Horde vs Alliance event! ", pPlayer->GetName());  // The message
		        sWorld->SendGlobalText(msg, NULL);
			}			
				void UpdateAI(const uint32 Diff)
			{
			    ScriptedAI::UpdateAI(Diff);
			
			     if (!UpdateVictim())
					return;
					
					if (Frostshock_Timer <= Diff)
	                    { 
                          DoCastVictim(SPELL_FROSTSHOCK);
		                  Frostshock_Timer = 15000;
	                    }
	                     else
		                  Frostshock_Timer -= Diff;
				          DoMeleeAttackIfReady();
						  
					if (Chill_Timer<= Diff)
	                    { 
                          DoCastVictim(SPELL_CHILL);
		                  Chill_Timer = 3000;
	                    }
	                     else
		                  Chill_Timer -= Diff;
				          DoMeleeAttackIfReady();
						  						  
		            if (me->GetHealthPct() <= 10 && percentPassed == 1)
				    {				
					    DoCast(me, SPELL_ICEBLOCK, true);
				        percentPassed = 2;
				    }
					
					switch (phase)
					{
					    case 1:
						    if (percentPassed == 2)							
							{								
								phase = 2;
							}
						    break;					                        
					}							   
            }
		};
};

void AddSC_hordeboss()
{
    new horde_boss();
}	