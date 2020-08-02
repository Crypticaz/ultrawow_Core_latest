# Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

file(GLOB_RECURSE scripts_Custom Custom/*.cpp Custom/*.h)
source_group(Custom FILES ${scripts_Custom})

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  ${scripts_Custom}
Custom/duelReset.cpp
Custom/CrossFaction_Battlegrounds.cpp
Custom/CrossFaction_Battlegrounds.h
Custom/morpher.cpp
Custom/npc_profession.cpp
Custom/npc_title.cpp
Custom/custom_commandscript.cpp
Custom/vipmall_security.cpp
Custom/npc_arena.cpp
Custom/npc_vip.cpp
Custom/chat_censor.cpp
Custom/alliance_boss.cpp
Custom/ultiame.cpp
Custom/horde_boss.cpp
Custom/tele_down.cpp
Custom/tele_up.cpp
Custom/buff.cpp
Custom/Teleporter.cpp
Custom/welcomenpc.cpp
Custom/Npc_Beastmaster.cpp
)

message("  -> Prepared: Custom")
