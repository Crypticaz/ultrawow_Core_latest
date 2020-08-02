/*
	<--------------------------------------------------------------------------->
    - Developer(s): JessiqueBA
    - Complete: %100
    - ScriptName: 'vipmall_security'
    - Comment: Untested.
    - Shared for:Emudevs by Synth
    <--------------------------------------------------------------------------->
*/
     
    enum ForbiddenAreas
    {
	
	    AREA_VIP               		    = 4824, // VIP MALL
        AREA_GM_ISLAND   				= 876, // gm island
    };
         
    class vipmall_security : public PlayerScript
    {
    public:
        vipmall_security() : PlayerScript("vipmall_security") {}
         
        void OnUpdateZone(Player* player, uint32 newZone, uint32 newArea)
        {
            switch (newArea)
            {
                case AREA_VIP:
                    // if player is vip and reach the vipmall..
                    if (player->GetSession()->GetSecurity() >= 1)

                        return;
					player->TeleportTo(1, -11100.1f, -1696.54f, 3.65923f, 0.740419f);   //tele to mall
                    break;
				
				
                case AREA_GM_ISLAND:
                    // Allow acces to GM island only for staff members
                    if (player->GetSession()->GetSecurity() >= 2) // Or RBAC 'HasPermission(rbac::PERMISSION_NAME);'

                        return;
                    player->TeleportTo(1, -11100.1f, -1696.54f, 3.65923f, 0.740419f); 
                    break;

            }
        }
    };
         
    void AddSC_vipmall_security()
    {
        new vipmall_security();
    }

