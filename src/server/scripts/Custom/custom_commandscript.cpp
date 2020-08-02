#include "ScriptPCH.h"
#include "Chat.h"



class custom_commandscript : public CommandScript
{
public:
	custom_commandscript() : CommandScript("custom_commandscript") { }

	ChatCommand* GetCommands() const
	{
		static ChatCommand IngameCommandTable[] =
		{
			{ "mall", SEC_PLAYER, false, &HandlemallCommand, "", NULL },
			{ "duel", SEC_PLAYER, false, &HandleduelCommand, "", NULL },
			{ "vip", SEC_PLAYER, false, &HandlevipCommand, "", NULL },
			{ NULL, 0, false, NULL, "", NULL }
		};
		return IngameCommandTable;
	}

	static bool HandlemallCommand(ChatHandler * handler, const char * args)
	{
		Player * me = handler->GetSession()->GetPlayer();

		if (me->isInCombat())
		{
			handler->SendSysMessage(LANG_YOU_IN_COMBAT);
			handler->SetSentErrorMessage(true);
			return false;

		}
		else
		{

			me->TeleportTo(1, -11100.1f, -1696.54f, 3.65923f, 0.740419f);
			handler->PSendSysMessage("Be Mall Khosh Amadid |cff00ff00(Ultra WoW)");
			return true;
		}

	}

	static bool HandleduelCommand(ChatHandler * handler, const char * args)
	{
		Player * me = handler->GetSession()->GetPlayer();

		if (me->isInCombat())
		{
			handler->SendSysMessage(LANG_YOU_IN_COMBAT);
			handler->SetSentErrorMessage(true);
			return false;

		}
		else
		{
			me->TeleportTo(1, -8930.77f, -1699.59f, 94.4739f, 3.12488f);
			handler->PSendSysMessage("Be Duel Zone Khosh Amadid |cff00ff00(Ultra WoW)");

			return true;

		}

	}

	static bool HandlevipCommand(ChatHandler * handler, const char * args)
	{
		Player * me = handler->GetSession()->GetPlayer();

		if (me->isInCombat())
		{
			handler->SendSysMessage(LANG_YOU_IN_COMBAT);
			handler->SetSentErrorMessage(true);
			return false;

		}
		else
		{
			me->TeleportTo(1, 3362.89f, -4496.69f, 268.338f, 3.66999f);
			handler->PSendSysMessage("Be V.I.P Mall Khosh Amadid |cff00ff00(Ultra WoW)");

			return true;
		}

	}

};

void AddSC_Ingame_commandscript()
{
	new custom_commandscript();
}