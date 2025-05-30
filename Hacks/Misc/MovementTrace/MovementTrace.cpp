#include "MovementTrace.hpp"

void MovementTrace::Update(float deltaTime) {
    auto now = std::chrono::steady_clock::now();
    lines.erase(
        std::remove_if(lines.begin(), lines.end(), [now](const Line& line) {
            return std::chrono::duration_cast<std::chrono::seconds>(now - line.timestamp).count() > 5;
            }),
        lines.end()
    );
}

void MovementTrace::AddPosition(const Vector3& newPosition) {
    if (!positions.empty()) {
        DrawLine(positions.back(), newPosition);
    }
    positions.push_back(newPosition);
    if (positions.size() > 1) {
        lines.push_back(Line{ positions[positions.size() - 2], positions.back(), std::chrono::steady_clock::now() });
    }
}

void MovementTrace::doMovementTrace(SDK::Entity* player) {
    static auto lastUpdateTime = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    float deltaTime = std::chrono::duration<float>(now - lastUpdateTime).count();
    lastUpdateTime = now;

    Update(deltaTime);

    Vector3 currentPosition = W2S(player->Get_Position());
    AddPosition(currentPosition);

    DrawAll();
}

void MovementTrace::DrawAll() {
    for (const auto& line : lines) {
        DrawLine(line.start, line.end);
    }
}
void MovementTrace::DrawLine(const Vector3& start, const Vector3& end) {
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(start.x, start.y), ImVec2(end.x, end.y), ImColor(255, 255, 255, 255), 12.f);
}