#include "Cacha.hpp"

void EntityCacha::EntityThread()
{
    static int searchsize = 600000;
    while (true)
    {
        sdk.LocalPlayer = Read<SDK::Entity*>(sdk.R5Apex + Offsets::Misc::m_LocalPlayer);

        if (!sdk.LocalPlayer) {
            continue;
        }

       /* auto mapname = read_wstr(sdk.R5Apex + Offsets::Misc::m_LevelName);
        if (mapname == _("m_ob") || mapname.empty()) {
            inMatch = false;
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
            continue;
        }
        else if (mapname == _("m_rcnolnssaigm1"))
            searchsize = 55000;
        else
            searchsize = 80;*/

        std::uintptr_t render = Read<std::uintptr_t>(sdk.R5Apex + Offsets::Misc::m_ViewRender);

        if (!render)continue;

        sdk.mtrix = Read<std::uintptr_t>(Offsets::Misc::m_ViewMatrix + render);

        std::vector<PlayerData> list;
        std::vector<std::string> slist;
        std::vector<std::string> speclist;
        std::vector<SDK::Entity*> deathboxTemp;

        for (int i = 0; i <= searchsize; ++i) {

            SDK::Entity* Entity = Read<SDK::Entity*>(sdk.R5Apex + Offsets::Misc::m_EntityList + (i << 5));

            if (!Entity) continue;


            if (Entity->getAddress() == sdk.LocalPlayer->getAddress()) continue;
            
            std::string Script = Entity->getSignifierName();

            if (Script == _("prop_death_box"))
                deathboxTemp.push_back(Entity);

            if (Script.empty() || (Script != _("player") && Script != _("npc_dummie"))) continue;
            std::string playerName = Entity->GetName(i);
            if (Entity->Is_Spectating())
                speclist.push_back(playerName);
#ifdef developer
            if (playerName.find(_("ttv")) != std::string::npos || playerName.find(_("TTV")) != std::string::npos
                || playerName.find(_("Twitch")) != std::string::npos)
                slist.push_back(playerName);
#endif
            PlayerData data;
            data.ClassAccess = Entity;
            data.name = playerName;
            list.push_back(data);
        }
        inMatch = true;
        EntList.swap(list);
#ifdef developer
        StreamerList.swap(slist);
#endif
        SpectatorList.swap(speclist);
        DeathboxList.swap(deathboxTemp);

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

