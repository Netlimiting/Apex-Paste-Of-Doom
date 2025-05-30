#include "Radar.hpp"
//chat generated
void Radar::doRadar()
{
    float radarSize = Cheat_Private::ESP::RadarSize * 80;
    std::map<int, std::string> teamMap;
    char teamLabel = 'A';

    ImGui::SetNextWindowSize(ImVec2(radarSize, radarSize));
    ImGui::Begin("##Radar", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground);

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 windowPos = ImGui::GetWindowPos();
    float radarCenterX = windowPos.x + radarSize / 2.0f;
    float radarCenterY = windowPos.y + radarSize / 2.0f;

    ImVec2 topLeft = ImVec2(windowPos.x, windowPos.y);
    ImVec2 bottomRight = ImVec2(windowPos.x + radarSize, windowPos.y + radarSize);
    drawList->AddRectFilled(topLeft, bottomRight, ImColor(20, 20, 20, static_cast<int>(Cheat_Private::ESP::transparency)));
    drawList->AddRect(topLeft, bottomRight, ImColor(255, 255, 255, 50), 0, 0, 2.0f);

    int gridSize = 4;
    float cellSize = radarSize / gridSize;
    for (int i = 1; i < gridSize; i++) {
        float offset = i * cellSize;
        drawList->AddLine(ImVec2(windowPos.x + offset, windowPos.y), ImVec2(windowPos.x + offset, windowPos.y + radarSize), ImColor(255, 255, 255, 30), 1.0f);
        drawList->AddLine(ImVec2(windowPos.x, windowPos.y + offset), ImVec2(windowPos.x + radarSize, windowPos.y + offset), ImColor(255, 255, 255, 30), 1.0f);
    }

    drawList->AddTriangleFilled(
        ImVec2(radarCenterX, radarCenterY - 6),
        ImVec2(radarCenterX - 5, radarCenterY + 5),
        ImVec2(radarCenterX + 5, radarCenterY + 5),
        ImColor(0, 255, 0, 255)
    );

    Vector3 ViewAngles = sdk.LocalPlayer->ViewAngles();
    for (const PlayerData& Entity : EntList) {
        Vector3 LocalPos = sdk.LocalPlayer->GetBonePositionByHitBox(0);
        Vector3 BasePos = Entity.ClassAccess->Get_Position();
        bool isVisible = (Entity.ClassAccess->Get_LastVisibleTime() + 0.2f) >= sdk.LocalPlayer->Get_WorldTime();

        float screenPos[2] = {
            (LocalPos.x - BasePos.x) / 10.0f * -1 + radarCenterX,
            (LocalPos.y - BasePos.y) / 10.0f + radarCenterY
        };

        float rotatedPoint[2];
        RotatePoint(screenPos, new float[2] { radarCenterX, radarCenterY }, ViewAngles.y - 90, rotatedPoint);

        float radarRadius = radarSize / 2.0f - 10.0f;
        float dx = rotatedPoint[0] - radarCenterX;
        float dy = rotatedPoint[1] - radarCenterY;
        float dist = sqrt(dx * dx + dy * dy);
        if (dist > radarRadius) {
            rotatedPoint[0] = radarCenterX + (dx / dist) * radarRadius;
            rotatedPoint[1] = radarCenterY + (dy / dist) * radarRadius;
        }

        float enemySize = 6.0f;
        ImVec2 enemyBlip(rotatedPoint[0], rotatedPoint[1]);
        ImColor enemyColor = isVisible
            ? ImColor(Cheat_Private::ESP::VisColor[0], Cheat_Private::ESP::VisColor[1], Cheat_Private::ESP::VisColor[2], Cheat_Private::ESP::VisColor[3])
            : ImColor(Cheat_Private::ESP::NonVisColor[0], Cheat_Private::ESP::NonVisColor[1], Cheat_Private::ESP::NonVisColor[2], Cheat_Private::ESP::NonVisColor[3]);

        drawList->AddCircleFilled(enemyBlip, enemySize * 1.2f, ImColor(255, 255, 255, 255));
        drawList->AddCircleFilled(enemyBlip, enemySize, enemyColor);

        if (Cheat_Private::ESP::RadarName) {
            std::string name = Entity.name;
            ImVec2 textSize = ImGui::CalcTextSize(name.c_str());
            ImVec2 textPos(enemyBlip.x - (textSize.x / 2), enemyBlip.y - (textSize.y / 2) - 10);
            drawList->AddText(textPos, enemyColor, name.c_str());
        }
        if (Cheat_Private::ESP::TeamID) {
            int teamID = Entity.ClassAccess->Get_TeamNum();
            if (teamMap.find(teamID) == teamMap.end() && teamLabel <= 'P') {
                teamMap[teamID] = std::string(1, teamLabel++);
            }

            std::string teamName = teamMap[teamID];
            ImVec2 teamTextSize = ImGui::CalcTextSize(teamName.c_str());
            ImVec2 teamTextPos(enemyBlip.x - (teamTextSize.x / 2), enemyBlip.y + (enemySize * 1.2f) + 5);
            drawList->AddText(teamTextPos, ImColor(255, 255, 255, 255), teamName.c_str());
        }
    }

    ImGui::End();

}