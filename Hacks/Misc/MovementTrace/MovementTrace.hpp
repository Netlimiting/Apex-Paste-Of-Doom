#include "../../SDK/SDK.hpp"
#include "../../Overlay/Drawing/Draw.hpp"
#include <mmsystem.h>
//chat generated
// To fix this update(worldtoscreen) the list of previous positions at real time
class MovementTrace {
public:
    void Update(float deltaTime);
    void AddPosition(const Vector3& newPosition);
    void doMovementTrace(SDK::Entity* player);
    void DrawAll();
private:
    struct Line {
        Vector3 start;
        Vector3 end;
        std::chrono::steady_clock::time_point timestamp;

        Line(const Vector3& s, const Vector3& e, std::chrono::steady_clock::time_point t)
            : start(s), end(e), timestamp(t) {}
    };
    std::vector<Vector3> positions;
    std::vector<Line> lines;
    void DrawLine(const Vector3& start, const Vector3& end);
};

inline MovementTrace Trace;