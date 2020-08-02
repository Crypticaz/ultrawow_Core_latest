#include "ScriptPCH.h"
#include "Creature.h"
#include "ScriptedCreature.h"


enum Spells
{
	SPELL_LIGHTNINGBOLT = 97475,
	SPELL_HEALINGWAVE = 79924,
	SPELL_FLAMESHOCK = 28323,

};

enum Events
{
	EVENT_LIGHTNINGBOLT = 1,
	EVENT_HEALINGWAVE = 2,
	EVENT_FLAMESHOCK = 3,
	EVENT_SPAWNCREATURE = 4,
};

enum Phases
{
	PHASE_ONE = 1,
	PHASE_TWO = 2,
};

class ultiame : public CreatureScript
{
public:
	ultiame() : CreatureScript("ultiame") { }
	CreatureAI* GetAI(Creature* creature) const
	{
		return new ultiameAI(creature);
	}

	struct ultiameAI : public BossAI
	{
		ultiameAI(Creature* creature) : BossAI(creature, 0)
		{

		}

		void Reset() 
		{
			summons.DespawnAll();
			Reset();
		}

			void EnterCombat(Unit* /*who*/) 
		{
			events.ScheduleEvent(EVENT_LIGHTNINGBOLT, 8000);
			events.ScheduleEvent(EVENT_HEALINGWAVE, 12000);
			events.ScheduleEvent(EVENT_FLAMESHOCK, 40000);
			events.ScheduleEvent(EVENT_SPAWNCREATURE, 20000);
			events.SetPhase(PHASE_ONE);

		}
			void JustSummoned(Creature* summoned)
		{
			summons.Summon(summoned);

			if (Unit * target = me->SelectNearbyTarget())
			{
				if (target && target->IsInWorld())
				{
					summoned->AddThreat(target, 100.0f);
					summoned->GetMotionMaster()->MoveChase(target, 45.0f);
				}
			}

		}


		void KilledUnit(Unit * /*victim*/) 
		{
		}

			void JustDied(Unit * victim) 
		{
			summons.DespawnAll();
			BossAI::JustDied(victim);
		}


			void UpdateAI(const uint32 diff) 
		{
			if (!UpdateVictim())
			return;

			events.Update(diff);

			if (me->HasUnitState(UNIT_STATE_CASTING))
				return;
			if (!HealthAbovePct(50))
			{
				events.SetPhase(PHASE_TWO);
				events.ScheduleEvent(EVENT_LIGHTNINGBOLT, 8000, PHASE_TWO);
				events.ScheduleEvent(EVENT_HEALINGWAVE, 12000, PHASE_TWO);
				events.ScheduleEvent(EVENT_FLAMESHOCK, 4000, 0, PHASE_TWO);
				events.ScheduleEvent(EVENT_SPAWNCREATURE, 20000, 0, PHASE_TWO);
			};

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_LIGHTNINGBOLT:
					DoCastVictim(SPELL_LIGHTNINGBOLT); //Will case the spell on the victim (AKA main tank)
					events.ScheduleEvent(EVENT_LIGHTNINGBOLT, 8000); //Executes event again every 8 seconds
					break;
				case EVENT_HEALINGWAVE:
					DoCast(me, SPELL_HEALINGWAVE);
					events.ScheduleEvent(EVENT_HEALINGWAVE, 21000); //Will cast spell on self again every 21 seconds
					break;
				case EVENT_FLAMESHOCK:
					if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
						DoCast(target, SPELL_FLAMESHOCK);
					events.ScheduleEvent(EVENT_FLAMESHOCK, 40000);
					break;
				case EVENT_SPAWNCREATURE:
					me->SummonCreature(600000, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 15000);
					events.ScheduleEvent(EVENT_SPAWNCREATURE, 25000);
					break;
					
				default:
					break;
				}
			}

			DoMeleeAttackIfReady();
		}
	};

	
};

void AddSC_ultiame()
{
	new ultiame();
}