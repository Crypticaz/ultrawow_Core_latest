#include "Player.h"
#include "AccountMgr.h"
#include "AchievementMgr.h"
#include "ArenaTeam.h"
#include "ArenaTeamMgr.h"
#include "Battlefield.h"
#include "BattlefieldMgr.h"
#include "BattlefieldWG.h"
#include "BattlegroundAV.h"
#include "Battleground.h"
#include "BattlegroundMgr.h"
#include "CellImpl.h"
#include "Channel.h"
#include "ChannelMgr.h"
#include "CharacterDatabaseCleaner.h"
#include "Chat.h"
#include <cmath>
#include "Common.h"
#include "ConditionMgr.h"
#include "CreatureAI.h"
#include "DatabaseEnv.h"
#include "DB2Stores.h"
#include "DisableMgr.h"
#include "Formulas.h"
#include "GameEventMgr.h"
#include "GossipDef.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Group.h"
#include "GroupMgr.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "InstanceSaveMgr.h"
#include "InstanceScript.h"
#include "Language.h"
#include "LFGMgr.h"
#include "Log.h"
#include "MapInstanced.h"
#include "MapManager.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "OutdoorPvP.h"
#include "OutdoorPvPMgr.h"
#include "ReputationMgr.h"
#include "Pet.h"
#include "QuestDef.h"
#include "SkillDiscovery.h"
#include "SocialMgr.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"
#include "Spell.h"
#include "SpellMgr.h"
#include "Transport.h"
#include "UpdateData.h"
#include "UpdateMask.h"
#include "Util.h"
#include "Vehicle.h"
#include "Weather.h"
#include "WeatherMgr.h"
#include "World.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "DBCStores.h"

class System_Censure : public PlayerScript
{
public:
        System_Censure() : PlayerScript("System_Censure") {}

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg)
        {
                CheckMessage(player, msg, lang, NULL, NULL, NULL, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Player* receiver)
        {
                CheckMessage(player, msg, lang, receiver, NULL, NULL, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Group* group)
        {
                CheckMessage(player, msg, lang, NULL, group, NULL, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Guild* guild)
        {
                CheckMessage(player, msg, lang, NULL, NULL, guild, NULL);
        }

        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Channel* channel)
        {
                CheckMessage(player, msg, lang, NULL, NULL, NULL, channel);
        }

void CheckMessage(Player* player, std::string& msg, uint32 lang, Player* /*receiver*/, Group* /*group*/, Guild* /*guild*/, Channel* channel)
{
    //if (player->isGameMaster() || lang == LANG_ADDON)
            //return;

    // transform to lowercase (for simpler checking)
    std::string lower = msg;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    uint8 cheksSize = 120;//Change these if you want to add more words to the array.
    std::string checks[120];//Change these if you want to add more words to the array.
	for (int i = 0; i < cheksSize; ++i)
	{
		checks[i] = "persian";
	}
    // Strony (Sites)
    checks[0] ="w.o.w";
    checks[1] ="w,o,w";
    checks[2] ="w'o'w";
    checks[3] ="w o w";
    checks[4] ="s'i'a";
    checks[5] =".org";
    checks[6] =".tk";
    checks[7] =".ir";
    checks[8] =".com";
    checks[9] =".pl";
	checks[10] ="games";
	checks[11] ="jahangames";
	checks[12] ="j ahan";
	checks[13] ="j a han";
	checks[14] ="j a h an";
	checks[15] ="j a h a n";
	checks[16] ="j-ahan";
	checks[17] ="j-a-han";
	checks[18] ="j-a-h-an";
	checks[19] ="j-a-h-a-n";
	checks[20] ="j_ahan";
	checks[21] ="j_a_han";
	checks[22] ="j_a_h_an";
	checks[23] ="j_a_h_a_n";
	checks[24] ="jahan";
	checks[25] ="j.ahan";
	checks[26] ="j.a.han";
	checks[27] ="j.a.h.an";
	checks[28] ="j.a.h.a.n";
	checks[29] ="jaha n";
	checks[30] ="jah an";
	checks[31] ="ja han";
	checks[32] ="jaha.n";
	checks[33] ="jah.a.n";
	checks[34] ="ja.h.a.n";
	checks[35] ="jaha_n";
	checks[36] ="jah_a_n";
	checks[37] ="ja_h_a_n";
	checks[38] ="jaha-n";
	checks[39] ="jah-a-n";
	checks[40] ="j,a,h,a,n";
	checks[41] ="ja,h,a,n";
	checks[42] ="jah,a,n";
	checks[43] ="jaha,n";
	checks[44] ="j,a,h,an";
	checks[45] ="j,a,han";
	checks[46] ="j,ahan";
	checks[49] ="jaa";
	checks[50] ="siaa";
	checks[51] ="0ne";
	checks[52] ="game-one";
	checks[53] ="rg1";
	checks[54] ="irg";
	checks[55] ="game1";
	checks[56] ="gameone";
	checks[57] ="jaaa";
	checks[58] ="haaa";
	checks[59] ="ssia";
	checks[60] ="pper";
	checks[61] ="p e r s";
	checks[62] ="p-e-r";
	checks[63] ="p-r";
	checks[64] ="w-o-w";
	checks[65] ="madar";
	checks[66] ="P'e'r";
	checks[67] ="mihan";
	checks[68] ="p/e/r";
	checks[69] ="j/a/h";
	checks[70] ="j'a'h";
	checks[71] ="apa";
	checks[72] ="apa-dana";
	checks[73] ="pandawow";
	checks[74] ="pandarian";
	checks[75] ="moltenwow";
	checks[76] ="realm";
	checks[77] ="G@";
	checks[78] ="h@";
	checks[79] =".c0m";
	checks[80] ="www";
	checks[81] ="p,e";	
	checks[82] ="p.e";	 
	checks[83] ="wow";
	checks[84] ="persianwow";
	checks[85] ="i@";
	checks[86] ="Ä";
	checks[87] ="Å";
	checks[88] ="Ã";
	checks[89] ="Á";
	checks[90] ="Â";
	checks[91] ="å";
	checks[92] ="ã";
	checks[93] ="á";
	checks[94] ="á";
	checks[95] ="Ñ";
	checks[96] ="Æ";
	checks[97] ="æ";
	checks[98] ="ã";
	checks[99] ="J.@";
	checks[100] ="P.E";
	checks[101] ="G,A";
	checks[102] ="E.$";
	checks[103] ="r,$";	
	
    for (int i = 0; i < cheksSize; ++i)
        if (lower.find(checks[i]) != std::string::npos)
			if (!player->isGameMaster() )
			{
				msg = "WWW.ULTRAWOW.IR";
				std::stringstream ss;
				ss <<  "Player  "<< player->GetName() << "  Sari'an Check Shavad. Dar Hale Tabligh Mibashad." ;
				ChatHandler(NULL).SendGlobalGMSysMessage(ss.str().c_str());
				ChatHandler(player->GetSession()).PSendSysMessage("Tabligh Dar Server Mojaz Nist!");
				//player->AddAura(9454, player);

			
				return;
			}
}
};

void AddSC_System_Censure()
{
    new System_Censure();
}