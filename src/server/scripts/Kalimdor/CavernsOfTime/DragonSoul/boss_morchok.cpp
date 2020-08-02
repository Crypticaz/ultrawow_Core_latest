#include "ScriptPCH.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "InstanceScript.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "GridNotifiers.h"
#include "Player.h"
#include "ObjectAccessor.h"
#include "dragon_soul.h"


Position const bboeposition[41] = 
{
						{-1955.67f, -2409.32f, 68.4433f,1.0f},
						{-1959.57f, -2413.82f, 68.4599f,1.0f},
						{-1964.31f, -2418.22f, 68.5014f,1.0f},
						{-2017.67f, -2413.14f, 70.3191f,1.0f},
						{-1982.76f, -2387.85f, 69.5097f,1.0f},
						{-2015.97f, -2419.44f, 70.1792f,1.0f},
						{-1993.11f, -2393.05f, 70.3255f,1.0f},
						{-1970.72f, -2417.7f, 68.835f,1.0f},
						{-1995.21f, -2391.81f, 70.3735f,1.0f},
						{-2002.24f, -2387.69f, 68.7131f,1.0f},
						{-1970.72f, -2417.7f, 68.835f,1.0f},
						{-2001.13f, -2394.48f, 70.1488f,1.0f},
						{-1967.8f, -2410.4f, 68.6435f,1.0f},
						{-1962.84f, -2406.13f, 68.5935f,1.0f},
						{-1961.06f, -2399.19f, 68.5155f,1.0f},
						{-1966.94f, -2396.9f, 68.5056f,1.0f},
						{-1969.68f, -2402.68f, 68.5344f,1.0f},
						{-1974.87f, -2396.22f, 68.7542f,1.0f},
						{-1973.34f, -2390.73f, 68.6036f,1.0f},
						{-1976.91f, -2409.75f, 68.7612f,1.0f},
						{-1980.65f, -2415.67f, 69.144f,1.0f},
						{-1979.22f, -2423.04f, 69.0664f,1.0f},
						{-1976.14f, -2379.66f, 68.245f,1.0f},
						{-1993.25f, -2417.39f, 69.5709f,1.0f},
						{-2000.47f, -2420.98f, 69.663f,1.0f},
						{-2004.91f, -2415.74f, 69.9381f,1.0f},
						{-1998.8f, -2411.79f, 69.9466f,1.0f},
						{-1987.29f, -2406.21f, 69.7072f,1.0f},
						{-2011.19f, -2415.3f, 70.0899f,1.0f},
						{-1988.02f, -2394.24f, 70.1543f,1.0f},
						{-1998.63f, -2401.05f, 70.3123f,1.0f},
						{-2004.13f, -2404.55f, 70.3951f,1.0f},
						{-1974.04f, -2429.38f, 68.5066f,1.0f},
						{-1978.1f, -2434.36f, 68.3518f,1.0f},
						{-1968.48f, -2433.27f, 67.6179f,1.0f},
						{-1954.7f, -2394.31f, 68.4517f,1.0f},
						{-1967.64f, -2380.05f, 67.6358f,1.0f},
						{-1972.65f, -2384.94f, 68.1965f,1.0f},
						{-1981.86f, -2402.1f, 69.2897f,1.0f},
						{-2015.68f, -2407.18f, 70.4905f,1.0f},
						{-2010.52f, -2403.47f, 70.5618f,1.0f},
};

Position const korbboeposition[17] = 
{
{-2036.23f,-2392.81f,72.327f,1.0f},
{-2039.52f,-2413.62f,72.5478f,1.0f},
{-2044.94f,-2398.76f,73.1428f,1.0f},
{-2053.12f,-2408.58f,73.14f,1.0f},
{-2047.53f,-2414.55f,72.9277f,1.0f},
{-2022.31f,-2394.6f,71.2988f,1.0f},
{-2025.09f,-2412.28f,71.2508f,1.0f},
{-2027.74f,-2421.95f,71.0532f,1.0f},
{-2034.22f,-2405.69f,72.4391f,1.0f},
{-2015.84f,-2404.23f,70.6557f,1.0f},
{-2015.08f,-2414.7f,70.1761f,1.0f},
{-2016.73f,-2427.07f,70.3176f,1.0f},
{-2053.81f,-2399.27f,73.4551f,1.0f},
{-2044.86f,-2385.35f,72.7415f,1.0f},
{-2037.21f,-2384.05f,72.4216f,1.0f},
{-2016.7f,-2389.01f,70.796f,1.0f},
{-2043.03f,-2425.54f,72.8298f,1.0f},
};

#define SAY_AGGRO "You seek to halt an avalanche. I will bury you."
#define SAY_ORB "Flee, and die."
#define SAY_GROUND "The stone calls..."
#define SAT_GROUND2 "...and the black blood of the earth consumes you."
#define SAY_KILL "I am unstoppable."
#define SAY_DEATH "Impossible. This cannot be. The tower... must... fall..."


enum Spells
{
	SPELL_CLEAR_DEBUFFS     		= 34098,
	SPELL_BBOTE_CAST				= 103851,
	SPELL_BLACK_BLOOD_ANI   		= 103180,
	SPELL_CRUSH						= 103687,
	SPELL_FALLING_CAST				= 103176,
	SPELL_FALLING_FRAG				= 103178,
	SPELL_VORTEX					= 103821,
	SPELL_FURIOUS					= 103846,
	SPELL_STOMP						= 109033,
	SPELL_SUMMON					= 109017,
	SPELL_FAR						= 103534,
	SPELL_RESONATING_CRYSTAL_SUM    = 103640,
	SPELL_RESONATING_CRYSTAL_EX     = 110041,
    SPELL_RESONATING_CRYSTAL_AURA   = 103494,
	SPELL_WARNING                   = 103536,
    SPELL_SAFE                      = 103541,
    SPELL_DANGER                    = 103534,
	SPELL_MAGNETIC                  = 28337,
	SPELL_BERSERK                   = 82395,
};

enum Events
{
	EVENT_CRUSH				= 1,
	EVENT_STOMP				= 2,
	EVENT_VORTEX			= 3,
	EVENT_SUMMON			= 4,
	EVENT_FURIOUS 			= 5,
	EVENT_RESONATING    	= 6,
	EVENT_SHARD 			= 7,
	EVENT_GET_HP			= 8,
	EVENT_FALL_FRAG 		= 9,
	EVENT_CLEAN_FRAG        = 10,
	EVENT_BBOT_CAST         = 11,
	EVENT_BBOT              = 12,
	EVENT_DES               = 13,
	EVENT_RESO              = 14,
	EVENT_NPC_BBOE          = 15,
	EVENT_NPC_BBOE_DES      = 16,
	EVENT_RESO_PLAYER       = 17,
	EVENT_STOMP_KOH         = 18,
	EVENT_CRUSH_KOH         = 19,
	EVENT_FALL_KOH          = 20,
	EVENT_BBOT_KOH          = 21,
	EVENT_BBOT_CAST_KOH     = 22,
	EVENT_CLEAN_FRAG_KOH    = 23,
	EVENT_RESONATING_KOH    = 24,
	EVENT_BERESERK          = 25,
};

enum Actions
{
	ACTION_INTRO 			= 0,
	ACTION_SUMMON			= 1,
	ACTION_SUMMON_ORB		= 2,
	ACTION_START            = 3,
	ACTION_BBOE             = 4,
};

enum Phases
{
	PHASE_INTRO				= 0,
	PHASE_COMBAT			= 1
};

enum NPCs
{
	NPC_BBOE_POS           = 70051,
	NPC_KOH_POS            = 70052,
	NPC_FRAG_POS_KOR       = 70053,
};

Position const MorchokSpawnPos = {-1986.09f, -2407.83f, 69.533f, 3.09272f};
Position const KohcromSpawnPos = {-1986.8f, -2407.83f, 69.53f, 3.09272f};

class boss_morchok : public CreatureScript
{
	public:
		boss_morchok() : CreatureScript("boss_morchok") { }

		struct boss_morchokAI : public BossAI
		{
			boss_morchokAI(Creature* creature) : BossAI(creature, BOSS_MORCHOK)
			{
				InstanceScript* instance;
				instance = creature->GetInstanceScript();
			}
			uint32 Raid10N;
			uint32 Raid10H;
			uint32 Raid25N;
			uint32 Raid25H;
			uint32 MorchokHealth;
			uint32 KohcromGUID;
			bool mobsummoned;

			void Reset()  
			{
				Raid10N = 36000200;
				Raid10H = 21473000;
				Raid25N = 66299996;
				Raid25H = 90202096;
				MorchokHealth = RAID_MODE(Raid10N, Raid25N, Raid10H, Raid25H);
				me->SetMaxHealth(MorchokHealth);
				me->SetFullHealth();
				me->SetHomePosition(MorchokSpawnPos);
                me->GetMotionMaster()->MoveTargetedHome();
				mobsummoned = false;
			}

			void EnterCombat(Unit* /*who*/)  
			{
				_EnterCombat();
				me->MonsterYell(SAY_AGGRO, 0, 0);
				events.Reset();
				events.SetPhase(PHASE_COMBAT);
				events.ScheduleEvent(EVENT_BERESERK, 420000, 0, PHASE_COMBAT);
                events.ScheduleEvent(EVENT_STOMP, 12000, 0, PHASE_COMBAT);
                events.ScheduleEvent(EVENT_CRUSH, 13000, 0, PHASE_COMBAT);
				events.ScheduleEvent(EVENT_RESONATING, 19000, 0, PHASE_COMBAT);
                events.ScheduleEvent(EVENT_FALL_FRAG, 50000, 0, PHASE_COMBAT);
                instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me, 1);
                instance->SetBossState(DATA_MORCHOK, IN_PROGRESS);
			}

			void EnterEvadeMode()
            {
            	events.Reset();
                summons.DespawnAll();
                me->GetMotionMaster()->MoveTargetedHome();
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me, 1);
				me->SetObjectScale(1);
                _EnterEvadeMode();
            }

			void KilledUnit(Unit* who)  
			{
				if (who->GetTypeId() == TYPEID_PLAYER)
					me->MonsterYell(SAY_KILL, 0, 0);
			}

			void JustSummoned(Creature* summoned)  
			{
				summons.Summon(summoned);

				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
				{
					summoned->AI()->AttackStart(target);
					summoned->AddThreat(target, 250.0f);
					DoZoneInCombat(summoned);
				}

				if (summoned->GetEntry() == NPC_KOHCROM)
				{
					if (!summoned->isInCombat() && me->GetVictim())
						summoned->AI()->AttackStart(me->GetVictim());
						summoned->setActive(true);
						summoned->setFaction(14);

					DoZoneInCombat(summoned);
				}
			}

			void DoAction(int32 const action)  
			{
				switch (action)
				{
					case ACTION_SUMMON:
						DoCast(me, SPELL_CLEAR_DEBUFFS);
						DoCast(me, SPELL_SUMMON);
						break;
					
					case ACTION_BBOE:
						for (int i = 1; i <=17; i++)
							me->SummonCreature(NPC_BBOE_POS, korbboeposition[i]);
						break;
					default:
						break;
				}
			}

			void DamageTaken(Unit* /*attacker*/, uint32& damage)  
			{
				if(IsHeroic())
				{
					if (me->HealthBelowPctDamaged(90, damage) && !mobsummoned)
					{
						DoAction(ACTION_SUMMON);
						mobsummoned = true;
					}
				}
				
				if (me->HealthBelowPct(80) && me->HealthAbovePct(71) )
                {
                	me->SetObjectScale(0.7f);
                }
                else if(me->HealthBelowPct(70) && me->HealthAbovePct(61))
                {
                	me->SetObjectScale(0.6f);
                }
                else if(me->HealthBelowPct(60) && me->HealthAbovePct(51))
                {
                	me->SetObjectScale(0.5f);
                }
                else if(me->HealthBelowPct(50) && me->HealthAbovePct(41))
                {
                	me->SetObjectScale(0.4f);
                }
                else if(me->HealthBelowPct(40) && me->HealthAbovePct(31))
                {
					me->SetObjectScale(0.3f);
                }
                else if(me->HealthBelowPct(20))
                {
                	DoCast(me, SPELL_FURIOUS);
                }
			}

			void JustDied(Unit* /*killer*/)  
			{
				_JustDied();
				instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                instance->SetBossState(DATA_MORCHOK, DONE);
				me->MonsterYell(SAY_DEATH, 0, 0);
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
						case EVENT_STOMP:
							DoCastAOE(SPELL_STOMP);
							events.ScheduleEvent(EVENT_STOMP, 15000, 0, PHASE_COMBAT);
							break;

						case EVENT_CRUSH:
							DoCastVictim(SPELL_CRUSH);
							events.ScheduleEvent(EVENT_CRUSH, 15000, 0, PHASE_COMBAT);
							break;
							
						case EVENT_RESONATING:
							if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
								DoCast(target, SPELL_RESONATING_CRYSTAL_SUM);
							me->MonsterYell(SAY_ORB, 0, 0);
							events.ScheduleEvent(EVENT_RESONATING, 35000, 0, PHASE_COMBAT);
							break;

						case EVENT_FALL_FRAG:
						{	
							me->MonsterYell(SAY_GROUND, 0, 0);
							events.CancelEvent(EVENT_RESONATING);
							events.CancelEvent(EVENT_STOMP);
							events.CancelEvent(EVENT_CRUSH);
							DoCast(me, SPELL_FALLING_CAST);
							std::list<Creature*> pos;
							GetCreatureListWithEntryInGrid(pos, me, 70050, 200.0f);
							for (std::list<Creature*>::iterator iter = pos.begin(); iter != pos.end(); ++iter)
								(*iter)->CastSpell(*iter,SPELL_FALLING_FRAG,true);
							events.ScheduleEvent(EVENT_BBOT, 1000, 0, PHASE_COMBAT); //Summon BBOE NPC
							events.ScheduleEvent(EVENT_BBOT_CAST, 5000, 0, PHASE_COMBAT); //Cast the Spell and hit damage
							events.ScheduleEvent(EVENT_CLEAN_FRAG, 15000, 0, PHASE_COMBAT); //Remove Fragments
							events.ScheduleEvent(EVENT_FALL_FRAG, 50000, 0, PHASE_COMBAT);
							break;
						}
						
						case EVENT_BBOT:
						{
							me->MonsterYell(SAT_GROUND2, 0, 0);
							for (int i = 1; i <=41; i++)
								me->SummonCreature(NPC_BBOE_POS, bboeposition[i]);
							
							Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
							if (!PlayerList.isEmpty())
								for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
									if (i->getSource()->isAlive())
										if (me->GetExactDist(i->getSource()) < 30.0f)
											DoCast(i->getSource(),SPELL_MAGNETIC);
                    								
							break;
						}
						
						case EVENT_BBOT_CAST:
							DoCast(me, SPELL_BBOTE_CAST);
							break;
						
						case EVENT_CLEAN_FRAG:
						{
							std::list<GameObject*> gameobjects;
							GetGameObjectListWithEntryInGrid(gameobjects, me, 209596, 50.0f);
							if (gameobjects.empty())
								return;
							for (std::list<GameObject*>::iterator iter = gameobjects.begin(); iter != gameobjects.end(); ++iter)
								(*iter)->RemoveFromWorld();
							events.ScheduleEvent(EVENT_RESONATING, 10000, 0, PHASE_COMBAT);
							events.ScheduleEvent(EVENT_STOMP, 1000, 0, PHASE_COMBAT);
							events.ScheduleEvent(EVENT_CRUSH, 2000, 0, PHASE_COMBAT);
							break;
						}
						case EVENT_BERESERK:
							DoCast (me,SPELL_BERSERK);
							break;
						default:
							break;
					}
				}

				DoMeleeAttackIfReady();
			}


		};

		CreatureAI* GetAI(Creature* creature) const  
        {
        	return GetDragonSoulAI<boss_morchokAI>(creature);
        }
};

class BlackBloodOfEarthFilter
{
	public:
		explicit BlackBloodOfEarthFilter(Unit* caster) : _caster(caster) { }

		bool operator()(WorldObject* unit) const
		{
			return !unit->IsWithinLOSInMap(_caster);
		}
	private:
		Unit* _caster;
};

class spell_morchok_bboe : public SpellScriptLoader
{
    public:
        spell_morchok_bboe() : SpellScriptLoader("spell_morchok_bboe") { }

        class spell_morchok_bboe_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_morchok_bboe_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(BlackBloodOfEarthFilter(GetCaster()));
            }

            void Register()  
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_morchok_bboe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const  
        {
            return new spell_morchok_bboe_SpellScript();
        }
};

class npc_resonating_crystal : public CreatureScript
{
    public:
        npc_resonating_crystal() : CreatureScript("npc_resonating_crystal") { }

        struct npc_resonating_crystalAI : public ScriptedAI
        {
            npc_resonating_crystalAI(Creature* creature) : ScriptedAI(creature)
            {
				me->AttackStop();
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            }
			int32 count;
			int32 playercount;
			bool flag;
			bool danger;
			
			void Reset()  
            {
                events.Reset();
				events.ScheduleEvent(EVENT_RESO, 500);
				events.ScheduleEvent(EVENT_DES, 12000);
				count = 0;
				playercount = 0;
				flag = true;
				danger = true;
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
						case EVENT_RESO:
						{
							DoCast(me, SPELL_RESONATING_CRYSTAL_AURA);
							
							playercount = 0;
							Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
							if (!PlayerList.isEmpty())
							{
								for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
								{
									if ((i->getSource()->isAlive()) && !(i->getSource()->isGameMaster()))
									{								
										playercount++;										
									}
								}
							}
							
							count = 0;
						
							while ((count < playercount) && flag)
							{
								if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
								{
									if (!target->HasAura(SPELL_DANGER))
									{
										DoCast(target, SPELL_DANGER);
										count++;
									}
								}
								if (count == 2)
									flag = false;
							}	
							events.ScheduleEvent(EVENT_RESO_PLAYER, 500);
							break;
						}
						
						case EVENT_RESO_PLAYER:
						{
							Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
							if (!PlayerList.isEmpty())
							{
								for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
								{
									if (i->getSource()->HasAura(SPELL_DANGER) || (i->getSource()->HasAura(SPELL_WARNING)) || (i->getSource()->HasAura(SPELL_SAFE)))
										if (me->GetExactDist(i->getSource()) < 4.0f)
										{
											i->getSource()->RemoveAurasDueToSpell(SPELL_WARNING);
											i->getSource()->RemoveAurasDueToSpell(SPELL_DANGER);
											DoCast(i->getSource(), SPELL_SAFE);
										}
										else if ((me->GetExactDist(i->getSource()) < 13.0f) && me->GetExactDist(i->getSource()) > 4.0f)
										{
											i->getSource()->RemoveAurasDueToSpell(SPELL_DANGER);
											i->getSource()->RemoveAurasDueToSpell(SPELL_SAFE);
											DoCast(i->getSource(), SPELL_WARNING);
										}
										else if (me->GetExactDist(i->getSource()) > 13.0f)
										{
											i->getSource()->RemoveAurasDueToSpell(SPELL_WARNING);
											i->getSource()->RemoveAurasDueToSpell(SPELL_SAFE);
											DoCast(i->getSource(), SPELL_DANGER);
										}
								}
							}
							events.ScheduleEvent(EVENT_RESO_PLAYER, 500);
							break;
						}
						case EVENT_DES:
						{	
							danger = true;
							Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
							if (!PlayerList.isEmpty())
							{
								for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
								{
									if (i->getSource()->isAlive())
									{
										if (i->getSource()->HasAura(SPELL_DANGER))
										{
											me->CastSpell(me,SPELL_RESONATING_CRYSTAL_EX,true);
											danger = false;
										}
										
										if ((i->getSource()->HasAura(SPELL_WARNING)) && danger)
											i->getSource()->CastSpell(i->getSource(),108343,true);
								
										i->getSource()->RemoveAurasDueToSpell(SPELL_SAFE);
										i->getSource()->RemoveAurasDueToSpell(SPELL_WARNING);
										i->getSource()->RemoveAurasDueToSpell(SPELL_DANGER);									
									}
								}
							}
							me->DespawnOrUnsummon();
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
            return new npc_resonating_crystalAI(creature);
        }
};


class npc_bboe : public CreatureScript
{
    public:
        npc_bboe() : CreatureScript("npc_bboe") { }

        struct npc_bboeAI : public ScriptedAI
        {
            npc_bboeAI(Creature* creature) : ScriptedAI(creature)
            {
				me->AttackStop();
            }
			void Reset()  
            {
                events.Reset();
				events.ScheduleEvent(EVENT_NPC_BBOE, 500);
				events.ScheduleEvent(EVENT_NPC_BBOE_DES, 15000);
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
						case EVENT_NPC_BBOE:
						{	
							DoCast(me, SPELL_BLACK_BLOOD_ANI);
							events.ScheduleEvent(EVENT_NPC_BBOE, 3500);
							break;
						}
						case EVENT_NPC_BBOE_DES:
							me->DespawnOrUnsummon();
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
            return new npc_bboeAI(creature);
        }
};


class spell_morchok_stomp : public SpellScriptLoader
{
public:
    spell_morchok_stomp() : SpellScriptLoader("spell_morchok_stomp") { }

    class spell_morchok_stomp_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_morchok_stomp_SpellScript);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            int32 damage;
            int32 count = 1;
            damage = 1;

            if (caster->GetMap()->IsHeroic())
            {
                if (caster->GetMap()->Is25ManRaid())
                    damage = 70000 * 2;
                else
                    damage = 60000 * 2;
            }
            else
            {
                if (caster->GetMap()->Is25ManRaid())
                    damage = 60000 * 2;
                else
                    damage = 50000 * 2;
            }

            Map::PlayerList const &PlayerList = caster->GetMap()->GetPlayers();
            if (!PlayerList.isEmpty())
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    if (i->getSource()->isAlive())
                    {
                        if (caster->GetExactDist(i->getSource()) < 500.0f)
                        {
                            count++;
                        }
                    }
			SetHitDamage(damage);

        }

        void Register()
        {
            OnHit += SpellHitFn(spell_morchok_stomp_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_morchok_stomp_SpellScript();
    }

};


class npc_kohcrom : public CreatureScript
{
	public:
		npc_kohcrom() : CreatureScript("npc_kohcrom") { }

		struct npc_kohcromAI : public ScriptedAI
		{
			npc_kohcromAI(Creature* creature) : ScriptedAI(creature)
			{
				_instance = creature->GetInstanceScript();
			}

			uint32 MorchokGUID;
			uint32 Raid10N;
			uint32 Raid10H;
			uint32 Raid25N;
			uint32 Raid25H;
			uint32 KorchomHealth;
			
			void Reset()  
            {
				_events.Reset();
				Raid10N = 36000200;
				Raid10H = 21473000;
				Raid25N = 66299996;
				Raid25H = 90202096;
				KorchomHealth = RAID_MODE(Raid10N, Raid25N, Raid10H, Raid25H);
				me->SetMaxHealth(KorchomHealth);
				me->SetFullHealth();
			}

			void EnterCombat(Unit* /*who*/)
            {
            	DoZoneInCombat();
            	_events.Reset();
            	_events.ScheduleEvent(EVENT_STOMP_KOH, 12000);
            	_events.ScheduleEvent(EVENT_CRUSH_KOH, 13000);
				_events.ScheduleEvent(EVENT_RESONATING_KOH, 35000);
            	_events.ScheduleEvent(EVENT_FALL_KOH, 45000);
            	_instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me, 1);

            	// Beta
            }

            void DamageTaken(Unit* /*attacker*/, uint32& damage)
            {

                if (me->HealthBelowPct(80) && me->HealthAbovePct(71) )
                {
                	me->SetObjectScale(0.7f);
                }
                else if(me->HealthBelowPct(70) && me->HealthAbovePct(61))
                {
                	me->SetObjectScale(0.6f);
                }
                else if(me->HealthBelowPct(60) && me->HealthAbovePct(51))
                {
                	me->SetObjectScale(0.5f);
                }
                else if(me->HealthBelowPct(50) && me->HealthAbovePct(41))
                {
                	me->SetObjectScale(0.4f);
                }
                else if(me->HealthBelowPct(40) && me->HealthAbovePct(31))
                {
					me->SetObjectScale(0.3f);
                }
                else if(me->HealthBelowPct(20))
                {
                	DoCast(me, SPELL_FURIOUS);
				}
            }

            void JustDied(Unit* killer)
            {
            	_instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            }

            void UpdateAI(uint32 const diff)
			{
				if (!UpdateVictim())
					return;

				
				_events.Update(diff);

				if (me->HasUnitState(UNIT_STATE_CASTING))
					return;

				while (uint32 eventId = _events.ExecuteEvent())
				{
					switch (eventId)
					{
						case EVENT_STOMP_KOH:
							DoCastAOE(SPELL_STOMP);
							_events.ScheduleEvent(EVENT_STOMP_KOH, 14000, 0, PHASE_COMBAT);
							break;
							
						case EVENT_CRUSH_KOH:
							DoCastVictim(SPELL_CRUSH);
							_events.ScheduleEvent(EVENT_CRUSH_KOH, 14000);
							break;
						case EVENT_RESONATING_KOH:
							if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
								DoCast(target, SPELL_RESONATING_CRYSTAL_SUM);
							_events.ScheduleEvent(EVENT_CRUSH_KOH, 35000);
							break;
						case EVENT_FALL_KOH:
						{	
							_events.CancelEvent(EVENT_RESONATING_KOH);
							_events.CancelEvent(EVENT_STOMP_KOH);
							_events.CancelEvent(EVENT_CRUSH_KOH);
							DoCast(me, SPELL_FALLING_CAST);
							std::list<Creature*> pos;
							GetCreatureListWithEntryInGrid(pos, me, 70053, 500.0f);
							for (std::list<Creature*>::iterator iter = pos.begin(); iter != pos.end(); ++iter)
								(*iter)->CastSpell(*iter,SPELL_FALLING_FRAG,true);
							_events.ScheduleEvent(EVENT_BBOT_KOH, 1000);
							_events.ScheduleEvent(EVENT_BBOT_CAST_KOH, 5000);
							_events.ScheduleEvent(EVENT_FALL_KOH, 50000);
							break;
						}
						case EVENT_BBOT_KOH:
						{
							if(Creature * boss = me->FindNearestCreature(55265, 500.0f))							
								boss->AI()->DoAction(ACTION_BBOE);
							
							Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
							if (!PlayerList.isEmpty())
								for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
									if (i->getSource()->isAlive())
										if (me->GetExactDist(i->getSource()) < 30.0f)
											DoCast(i->getSource(),SPELL_MAGNETIC);
                    		
							break;
						}
						
						case EVENT_BBOT_CAST_KOH:
							DoCast(me, SPELL_BBOTE_CAST);
							break;
						
						case EVENT_CLEAN_FRAG_KOH:
						{
							std::list<GameObject*> gameobjects;
							GetGameObjectListWithEntryInGrid(gameobjects, me, 209596, 50.0f);
							if (gameobjects.empty())
								return;
							for (std::list<GameObject*>::iterator iter = gameobjects.begin(); iter != gameobjects.end(); ++iter)
								(*iter)->RemoveFromWorld();
								
							_events.ScheduleEvent(EVENT_STOMP_KOH, 1000);
							_events.ScheduleEvent(EVENT_CRUSH_KOH, 2000);
							_events.ScheduleEvent(EVENT_RESONATING_KOH, 10000);
							break;
						}
						
					default:
						break;
					}
				}

				DoMeleeAttackIfReady();
			}

		private:
        	EventMap _events;
        	InstanceScript* _instance;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
        	return GetDragonSoulAI<npc_kohcromAI>(creature);
        }
};


void AddSC_boss_morchok()
{
	new boss_morchok();
	new npc_kohcrom();
	new spell_morchok_bboe();
	new npc_resonating_crystal();
	new npc_bboe();
	new spell_morchok_stomp();
}