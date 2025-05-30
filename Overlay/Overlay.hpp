#pragma once
#include "../framework/settings/functions.h"
#include "../framework/data/font.h"
#include "../framework/data/imgui_freetype.h"
#include "../framework/data/texture.h"

#define ALPHA    (ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar)
#define NO_ALPHA (ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar)
inline int FetSe = 0;
inline int GameSelection = 0;

using namespace ImGui;

inline Player Init;

inline int Segments = 10;
inline HWND window_handle;

inline ID3D11Device* d3d_device;
inline ID3D11DeviceContext* d3d_device_ctx;
inline IDXGISwapChain* d3d_swap_chain;
inline ID3D11RenderTargetView* d3d_render_target;
inline D3DPRESENT_PARAMETERS d3d_present_params;

inline HWND hwnd;
inline ImFont* DefeatureFont;
inline ImFont* Russian;


enum RENDER_INFORMATION : int {
    RENDER_HIJACK_FAILED = 0,
    RENDER_IMGUI_FAILED = 1,
    RENDER_DRAW_FAILED = 2,
    RENDER_SETUP_SUCCESSFUL = 3,
    RENDER_COD_FAILED = 4,
};

enum heads {
    target, sword, car, eye, people, earth, tools, scripts, settings
};

enum subheads {
    aim, rage, other
};

inline bool expand = false;
inline float anim = 0.0f, expand_anim = 0.0f;
inline float accent_c[3] = { 32 / 255.0f, 105 / 255.0f, 244 / 255.0f };

inline ID3D11ShaderResourceView* valomodel = nullptr;

inline ID3D11ShaderResourceView* xexTexture = nullptr;

namespace Overlay {
    class OverlayRender {

        HWND Apex_Window = { };

    public:

        RECT rect;

        bool StartCheat = false;

        int Slec = 0;

        bool render_Menu = false;

        bool DoOnce = false;

        auto Setup() -> RENDER_INFORMATION;

        auto get_screen_status() -> bool;
       
        auto Render() -> bool;

        auto ImGui() -> bool;

        HWND find_window(const char* classname, const char* windowname = NULL, int instance = 1);
          
        bool DoesFileExist(const wchar_t* filePath);

        bool StartWindow();

        auto Hijack() -> bool;

        auto Menu() -> void;


        auto Draw() -> void;
    };
} static Overlay::OverlayRender* Renderer = new Overlay::OverlayRender();

inline void __fastcall BeginCheat()
{
    LOG(_("Starting Overlay\n"));
    if (Renderer->Setup() != RENDER_INFORMATION::RENDER_SETUP_SUCCESSFUL)
        LOG(_("Failed To Create Overlay\n "));
    SleepEx(2500, false);
    Renderer->Render();
}
inline float BOG_TO_GRD(float BOG) {
    return (180 / M_PI) * BOG;
}

inline float GRD_TO_BOG(float GRD) {
    return (M_PI / 180) * GRD;
}
inline int faken_rot = 100;
inline void SwastikaCrosshair(ImColor color)
{

    Vector2 Screen; int oodofdfo, jbjfdbdsf; oodofdfo = GetSystemMetrics(0); jbjfdbdsf = GetSystemMetrics(1); Screen.x = oodofdfo; Screen.y = jbjfdbdsf;
    //Middle POINT
    Vector2 Middle; Middle.x = (int)(Screen.x / 2); Middle.y = (int)(Screen.y / 2);
    int a = (int)(Screen.y / 2 / 30);
    float gamma = atan(a / a);

    int Drehungswinkel = faken_rot;

    int i = 0;
    while (i < 4)
    {
        std::vector <int> p;
        p.push_back(a * sin(GRD_TO_BOG(Drehungswinkel + (i * 90))));									//p[0]		p0_A.x
        p.push_back(a * cos(GRD_TO_BOG(Drehungswinkel + (i * 90))));									//p[1]		p0_A.y
        p.push_back((a / cos(gamma)) * sin(GRD_TO_BOG(Drehungswinkel + (i * 90) + BOG_TO_GRD(gamma))));	//p[2]		p0_B.x
        p.push_back((a / cos(gamma)) * cos(GRD_TO_BOG(Drehungswinkel + (i * 90) + BOG_TO_GRD(gamma))));	//p[3]		p0_B.y

        Draw::esp->AddLine({ Middle.x, Middle.y }, { Middle.x + p[0], Middle.y - p[1] },color, 1.f);
        Draw::esp->AddLine({ Middle.x + p[0], Middle.y - p[1] }, { Middle.x + p[2], Middle.y - p[3] }, color, 1.f);

        i++;
    }
}
inline int kappa_x = 0;
inline void __stdcall koordinateswitch() {
    while (true) {
        kappa_x++;
        if ((int)faken_rot > 89) { faken_rot = (float)0; }
        faken_rot++;
        Sleep(1);
    }
}