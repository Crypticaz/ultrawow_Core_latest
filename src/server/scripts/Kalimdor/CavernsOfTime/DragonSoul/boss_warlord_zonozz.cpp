#include "ScriptPCH.h"
#include "dragon_soul.h"
 

enum Events
{
    EVENT_FOCUSEF_ANGER              = 1,
    EVENT_PSYCHIC_DRAIN              = 2,
    EVENT_DISRUPTING_SHADOWS         = 3,
	EVENT_SUM_VOID                   = 4,
	EVENT_NORMAL                     = 5,
	EVENT_BERSERK                    = 10,
	
	EVENT_SHADHOW_GAZE               = 15,
	EVENT_OOZE_SPIT                  = 16,
	EVENT_SLUDGE_SPEW                = 17,
	EVENT_WILD_FLAIL               	 = 18,
	
	//Void
	EVENT_MOVE_BOSS                  = 20,
	EVENT_MOVE_PLAYER                = 21,
	EVENT_BB_GORATH                  = 22, 
	EVENT_CHECK_COUNT                = 24,
	EVENT_VOID_MARKET                = 25,
	
};

enum Spells
{
    SPELL_FOCUSED_ANGER            = 104543,
    SPELL_PSYCHIC_DRAIN            = 104323,
    SPELL_DISRUPTING_SHADOWS       = 103434,
	SPELL_BLACK_BLOOD_ERUP         = 108799,
	SPELL_ENRAGE                   = 47008,
	SPELL_TANTRUM                  = 103955,
	SPELL_SHADHOW_GAZE             = 104602,
	//SPELL_OOZE_SPIT                = 109396,
	SPELL_SLUDGE_SPEW              = 110297,
	SPELL_WILD_FLAIL               = 109199,
	SPELL_BBOG                     = 104378,
	SPELL_MIST                     = 50203,
	 
	//Void
	SEPLL_VOID_DIFF_SELF           = 106836,
	SEPLL_VOID_DIFF_PLR            = 104031,
	SPELL_VOID_MARKET              = 103521,
};

enum EncounterActions
{
    ACTION_MOVE_BOSS             = 1,
	ACTION_MOVE_PLAYER           = 2,
	ACTION_FOCUSED               = 3,
	ACTION_BB_GORATH             = 4,
	ACTION_SUM_VOID              = 5,
};

Position const EyePosition[8] =
{
	{-1791.61f,-1990.59f,-221.221f,1.50489f},
	{-1834.16f,-1951.64f,-221.505f,1.57689f},
	{-1840.39f,-1894.65f,-221.328f,5.83733f},
	{-1734.92f,-1984.88f,-221.433f,2.12027f},
	{-1696.27f,-1941.24f,-221.3f,3.09677f},
	{-1700.08f,-1883.52f,-221.315f,3.7741f},
	{-1745.09f,-1845.52f,-221.281f,4.49185f},
	{-1802.65f,-1850.27f,-221.311f,5.28948f},
};

Position const FlailPosition[4] =
{
	{-1787.17f,-1889.81f,-226.342f,4.63677f},
	{-1738.97f,-1906.22f,-226.34f,4.10352f},
	{-1793.79f,-1932.99f,-226.342f,1.14604f},
	{-1762.59f,-1946.64f,-226.297f,1.00092f},

};

Position const ClawPosition[2] =
{
	{-1756.89f,-1881.7f,-226.708f,4.40952f},
	{-1780.16f,-1948.77f,-226.378f,1.25742f},
};


class boss_warlord : public CreatureScript
{
public:
    boss_warlord() : CreatureScript("boss_warlord") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return GetDragonSoulAI<boss_warlordAI>(creature);
    }

    struct boss_warlordAI: public BossAI
    {
        boss_warlordAI(Creature* creature) : BossAI(creature, BOSS_WARLORD)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;
		uint32 WarlordHealth;
        uint32 Raid10N;
        uint32 Raid10H;
        uint32 Raid25N;
        uint32 Raid25H;

        void Reset()
        {
			//me->GetMotionMaster()->MovePoint (1,-1771.24f,-1919.59f,-226.362f);
            _Reset();
			events.Reset();
            instance->SetBossState(DATA_PORTALS_ON_OFF, DONE);
            me->RemoveAura(SPELL_FOCUSED_ANGER);
			Raid10N = 44328860;
            Raid10H = 56220608;
			Raid25N = 132763256;
            Raid25H = 168661824;
            WarlordHealth = RAID_MODE(Raid10N, Raid25N, Raid10H, Raid25H);
            me->SetMaxHealth(WarlordHealth);
            me->SetFullHealth();
        }

		void DoAction(int32 const action)  
		{
			switch (action)
            {
				case ACTION_SUM_VOID:
					events.ScheduleEvent(EVENT_SUM_VOID,15000);
					break;
				case ACTION_FOCUSED:
					DoCast(me, SPELL_FOCUSED_ANGER);
					break;
				case ACTION_BB_GORATH:
				{
					DoCastAOE (SPELL_BBOG);
				//	me->GetMotionMaster()->MovePoint (0,-1771.24f,-1919.59f,-226.362f);
					// Summon Eye of Go'rath 
					if (me->GetMap()->Is25ManRaid())
						for (int i = 0; i < 8; i++)
							me->SummonCreature(NPC_EYE, EyePosition[i]);
					else
						for (int i = 0; i < 5; i++)
							me->SummonCreature(NPC_EYE, EyePosition[i]);
					// Summon Flail of Go'rath 
					if (me->GetMap()->Is25ManRaid())
						for (int i = 0; i < 4; i++)
							me->SummonCreature(NPC_FLAIL, FlailPosition[i]);
					else
					{
						me->SummonCreature(NPC_FLAIL, FlailPosition[0]);
						me->SummonCreature(NPC_FLAIL, FlailPosition[1]);
					}
							
					// Summon Claw of Go'rath 
					if (me->GetMap()->Is25ManRaid())
					{
						me->SummonCreature(NPC_CLAW, ClawPosition[0]);
						me->SummonCreature(NPC_CLAW, ClawPosition[1]);
					}
					else
						me->SummonCreature(NPC_CLAW, ClawPosition[0]);
					
					DoCastAOE (SPELL_TANTRUM);
					events.ScheduleEvent(EVENT_NORMAL,30000); 
					break;
				}
				default:
					break;
			}
		}
		
        void EnterCombat(Unit* /*who*/)
        {
			//Talk(SAY_AGGRO);
            events.ScheduleEvent(EVENT_SUM_VOID,5000);
            events.ScheduleEvent(EVENT_PSYCHIC_DRAIN,13000);
            events.ScheduleEvent(EVENT_DISRUPTING_SHADOWS,23000);
			events.ScheduleEvent(EVENT_BERSERK,360000);
            instance->SetBossState(BOSS_WARLORD, IN_PROGRESS);
            instance->SetBossState(DATA_PORTALS_ON_OFF, IN_PROGRESS);
            _EnterCombat();
        }

        void UpdateAI(uint32 const diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
					case EVENT_SUM_VOID:
                        if(Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 100, true))
						{
							float x,y;
							x = (target->GetPositionX()+me->GetPositionX()) / 2;
							y = (target->GetPositionY()+me->GetPositionY()) / 2;
							me->SummonCreature(NPC_VOID,x,y,target->GetPositionZ()+2,target->GetOrientation());
						}
						
						if (Creature* market = me->FindNearestCreature(NPC_VOID, 100.0f))
						{
							market->AI()->DoAction(ACTION_MOVE_PLAYER);
						}
						
						break;
					
					case EVENT_PSYCHIC_DRAIN:
						DoCastVictim(SPELL_PSYCHIC_DRAIN);
						events.ScheduleEvent(EVENT_PSYCHIC_DRAIN, urand (80000,120000));
						break;

					case EVENT_DISRUPTING_SHADOWS:
						if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
							DoCast(target, SPELL_DISRUPTING_SHADOWS);
						events.ScheduleEvent(EVENT_DISRUPTING_SHADOWS, urand(40000,80000));
						break;
					case EVENT_NORMAL:
					{
						me->RemoveAllAuras();
						summons.DespawnAll();
						events.ScheduleEvent(EVENT_SUM_VOID,15000);
						break;
					}
					case EVENT_BERSERK:
						DoCast(me, SPELL_ENRAGE);
						break;
						
					default:
						break;
                }
            }		

            DoMeleeAttackIfReady();
        }

        void JustReachedHome()
        {
            _JustReachedHome();
            instance->SetBossState(BOSS_WARLORD, FAIL);
        }
		
		void EnterEvadeMode()
		{
			me->GetMotionMaster()->MovePoint (0,-1771.24f,-1919.59f,-226.362f);
			_Reset();
			_EnterEvadeMode();
			summons.DespawnAll();
		}

        void JustDied(Unit* /*killer*/)
        {
			//Talk(SAY_DEATH);
			summons.DespawnAll();
            instance->SetBossState(BOSS_WARLORD, DONE);
            instance->SetBossState(DATA_PORTALS_ON_OFF, DONE);
			if (Creature* market = me->FindNearestCreature(NPC_VOID, 100.0f))
				market->DespawnOrUnsummon();
        }
    };
};


class npc_void : public CreatureScript
{
    public:
        npc_void() : CreatureScript("npc_void") { }

        struct npc_voidAI : public ScriptedAI
        {
            npc_voidAI(Creature* creature) : ScriptedAI(creature)
            {
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            }
			
			std::string Convert (float number){
				std::ostringstream buff;
				buff<<number;
				return buff.str();   
			}
            void DoAction(int32 const action)  
            {
                switch (action)
                {
                    case ACTION_MOVE_BOSS:
						if (Creature* boss = me->FindNearestCreature(NPC_WARLORD, 500.0f))
							me->GetMotionMaster()->MovePoint (1,boss->GetPositionX(),boss->GetPositionY(),boss->GetPositionZ());							
						break;
					
					case ACTION_MOVE_PLAYER:
						if(Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 100, true))
						{
							if (Creature* wall= target->FindNearestCreature(NPC_WALL, 500.0f))
							{
								me->GetMotionMaster()->MovePoint (0,wall->GetPositionX() ,wall->GetPositionY(),wall->GetPositionZ());
							}
						}
						events.ScheduleEvent(EVENT_MOVE_PLAYER, 100);
						break;
					
                    default:
						break;
                }
            }
			
			bool toBoss;
			bool void_diff;
			bool flag;
			bool bbe_flag;
			bool sum;
			bool check_count;
			int count;
			
			void Reset()
			{
				events.Reset();
				toBoss = false;
				void_diff = true;
				flag = true;
				bbe_flag = true;
				sum = true;
				check_count = true;
				count = 0;
			}
			
			
			void UpdateAI(uint32 const diff)  
			{
				if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
				
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
						case EVENT_MOVE_BOSS:
						{
							if (toBoss)
							{
								if (SelectTarget(SELECT_TARGET_NEAREST, 0, 500, true)->GetDistance(me) <= 0.5)
									if (void_diff)
									{
										flag = true;
										void_diff = false;
										toBoss = false;
										me->AI()->DoAction(ACTION_MOVE_PLAYER);
										events.CancelEvent(EVENT_MOVE_PLAYER);
										events.ScheduleEvent(EVENT_MOVE_PLAYER, 3000);
																					 
										if (Creature* boss = me->FindNearestCreature(NPC_WARLORD, 500.0f))
										{
											me->AddAura(SEPLL_VOID_DIFF_PLR,boss);
											me->AddAura(SEPLL_VOID_DIFF_PLR,boss);
											me->AddAura(SEPLL_VOID_DIFF_PLR,boss);
											me->AddAura(SEPLL_VOID_DIFF_PLR,boss);
										}
									}
									
									if ((me->FindNearestCreature(NPC_WARLORD, 500.0f))->GetDistance(me) < 0.1)
									{
										toBoss = false;
										DoCastAOE (SPELL_TANTRUM);
										events.ScheduleEvent(EVENT_BB_GORATH, 2000);
									}
								events.ScheduleEvent(EVENT_MOVE_BOSS, 500);
							}
                            break;
						}
						case EVENT_MOVE_PLAYER:
						{
							if (!toBoss)
							{	
								if (SelectTarget(SELECT_TARGET_NEAREST, 0, 500, true)->GetDistance(me) <= 0.5)
									if (flag)
									{
										DoCast(me, SEPLL_VOID_DIFF_SELF);
										DoCast(me, SEPLL_VOID_DIFF_PLR);
										flag = false;
										void_diff = true;
										toBoss = true;
										me->AI()->DoAction(ACTION_MOVE_BOSS);
										events.CancelEvent(EVENT_MOVE_BOSS);
										events.ScheduleEvent(EVENT_MOVE_BOSS, 3000);
										count++;
										
										if (count >= 10) 
											events.ScheduleEvent(EVENT_CHECK_COUNT, 100);
											
										if (Creature* boss = me->FindNearestCreature(NPC_WARLORD, 500.0f))
										{
											me->AddAura(SEPLL_VOID_DIFF_PLR,boss);
											me->AddAura(SEPLL_VOID_DIFF_PLR,boss);
											//Cast Focused Anger On Bosss
											boss->AI()->DoAction(ACTION_FOCUSED);
										}
									}
							//	if (me->FindNearestCreature(NPC_WALL, 500.0f)->GetDistance(me) <= 5)
									if (me->FindNearestCreature(NPC_WALL, 500.0f, true))
								{
									me->StopMoving();
									Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
									if (!PlayerList.isEmpty())
										for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
											if (i->getSource()->isAlive() && bbe_flag)
											{	
												DoCast(i->getSource(),SPELL_BLACK_BLOOD_ERUP);
												bbe_flag = false;
											}
									
									if (Creature* boss = me->FindNearestCreature(NPC_WARLORD, 500.0f))
										if (sum)
										{
											boss->AI()->DoAction(ACTION_SUM_VOID);
											sum = false;
										}
									me->DespawnOrUnsummon(5000);
								}
								
							}
							events.ScheduleEvent(EVENT_MOVE_PLAYER, 500);
							break;
						}
						case EVENT_BB_GORATH:
						{
							events.CancelEvent(EVENT_CHECK_COUNT);
							events.CancelEvent(EVENT_MOVE_BOSS);
							events.CancelEvent(EVENT_MOVE_PLAYER);
							
							if (Creature* boss = me->FindNearestCreature(NPC_WARLORD, 500.0f))
							{
								boss->RemoveAurasDueToSpell(SPELL_FOCUSED_ANGER);
								boss->AI()->DoAction(ACTION_BB_GORATH);
							}
							me->DespawnOrUnsummon(1000);
						}
						
						case EVENT_CHECK_COUNT:
						{
							events.CancelEvent(EVENT_MOVE_BOSS);
							events.CancelEvent(EVENT_MOVE_PLAYER);
							me->AI()->DoAction(ACTION_MOVE_BOSS);
							
							if ((me->FindNearestCreature(NPC_WARLORD, 500.0f))->GetDistance(me) < 0.1 && check_count)
							{
								check_count = false;
								DoCastAOE (SPELL_TANTRUM);
								events.ScheduleEvent(EVENT_BB_GORATH, 2000);
							}
							
							events.ScheduleEvent(EVENT_CHECK_COUNT, 500);	
							break;
						}
						
						default:
							break;
					}
				}
			}
			
			
        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const  
        {
            return new npc_voidAI(creature);
        }
};


class npc_eye : public CreatureScript
{
    public:
        npc_eye() : CreatureScript("npc_eye") { }

        struct npc_eyeAI : public ScriptedAI
        {
            npc_eyeAI(Creature* creature) : ScriptedAI(creature)
            {}
			
            
			void Reset()
			{
				events.Reset();
				events.ScheduleEvent(EVENT_SHADHOW_GAZE,urand (1000,25000));
			}
			
			
			void UpdateAI(uint32 const diff)  
			{
				if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
				
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
						case EVENT_SHADHOW_GAZE:
							if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
								DoCast(target, SPELL_SHADHOW_GAZE);
						default:
							break;
					}
				}
			}
			
			
        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const  
        {
            return new npc_eyeAI(creature);
        }
};


/* class npc_claw : public CreatureScript
{
    public:
        npc_claw() : CreatureScript("npc_claw") { }

        struct npc_clawAI : public ScriptedAI
        {
            npc_clawAI(Creature* creature) : ScriptedAI(creature)
            {
			}
			
			void Reset()
			{
				events.Reset();
				events.ScheduleEvent(EVENT_OOZE_SPIT, 1000);
			}
			
			
			void UpdateAI(uint32 const diff)  
			{
				if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
				
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
						case EVENT_OOZE_SPIT:
							if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
								DoCast(target, SPELL_OOZE_SPIT);
							events.ScheduleEvent(EVENT_OOZE_SPIT,3000);
						default:
							break;
					}
				}
			}
			
			
        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const  
        {
            return new npc_clawAI(creature);
        }
}; */

class npc_flail : public CreatureScript
{
    public:
        npc_flail() : CreatureScript("npc_flail") { }

        struct npc_flailAI : public ScriptedAI
        {
            npc_flailAI(Creature* creature) : ScriptedAI(creature)
            {}
			
            
			void Reset()
			{
				events.Reset();
				events.ScheduleEvent(EVENT_SLUDGE_SPEW, 3000);
				events.ScheduleEvent(EVENT_WILD_FLAIL, 1000);
			}
			
			
			void UpdateAI(uint32 const diff)  
			{
				if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
				
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
					/*	case EVENT_SLUDGE_SPEW:
							if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
								DoCast(target, SPELL_OOZE_SPIT);
							events.ScheduleEvent(EVENT_SLUDGE_SPEW, urand(3000,5000));
							break; */
						case EVENT_WILD_FLAIL:
							if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
								DoCast(target, SPELL_WILD_FLAIL);
							events.ScheduleEvent(EVENT_WILD_FLAIL, urand(3000,5000)); 
							break;
							
						default:
							break;
					}
				}
			}
			
			
        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const  
        {
            return new npc_flailAI(creature);
        }
};

void AddSC_boss_warlord()
{
    new boss_warlord();
	new npc_void (); 
	new npc_eye();
//	new npc_claw();
	new npc_flail();
}