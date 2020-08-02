#include "ScriptPCH.h"
#include "ScriptedCreature.h"

enum eNums
{
    SPELL_FROSTSHOCK = 23115,
	SPELL_CHILL      = 21098,
	SPELL_ICEBLOCK   = 41590,
};

class hordeboss : public CreatureScript
{
    public:
		hordeboss() : CreatureScript("hordeboss"){}
		
		CreatureAI * GetAI(Creature * pCreature) const
		{
		     return new hordebossAI(pCreature);
		}

		struct hordebossAI : public ScriptedAI
		{
			hordebossAI(Creature *c) : ScriptedAI(c){}
						    
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
		        snprintf(msg, 250, "|cffff0000[Event System]|r The|cffff6060 Alliance|r have won the Horde vs Alliance event! ", pPlayer->GetName());  // The message
		        sWorld->SendGlobalText(msg, NULL);
			}			
				void UpdateAI(uint32 diff) 
			{
		
			
			     if (!UpdateVictim())
					return;
					
					if (Frostshock_Timer <= diff)
	                    { 
                          DoCastVictim(SPELL_FROSTSHOCK);
		                  Frostshock_Timer = 15000;
	                    }
	                     else
		                  Frostshock_Timer -= diff;
				          DoMeleeAttackIfReady();
						  
					if (Chill_Timer<= diff)
	                    { 
                          DoCastVictim(SPELL_CHILL);
		                  Chill_Timer = 3000;
	                    }
	                     else
		                  Chill_Timer -= diff;
				          DoMeleeAttackIfReady();
						  						  
		            if (me->GetHealthPct() <= 10 && percentPassed == 1)
				    {				
						DoCast(me, SPELL_ICEBLOCK);
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
    new hordeboss();
}	