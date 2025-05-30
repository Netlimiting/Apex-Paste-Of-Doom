#include "Overlay.hpp"

auto Overlay::OverlayRender::Setup() ->RENDER_INFORMATION {
    Apex_Window = FindWindowA((_("Respawn001")), (_("Apex Legends")));
    if (!Apex_Window) {
        LOG(_("Fail to Get Window\n"));
        return RENDER_COD_FAILED;
    }

    if (!Overlay::OverlayRender::Hijack()) return RENDER_HIJACK_FAILED;

    if (!Overlay::OverlayRender::ImGui()) return RENDER_IMGUI_FAILED;
    LI_FN(system)(_("cls"));
    return RENDER_SETUP_SUCCESSFUL;
}
auto Overlay::OverlayRender::get_screen_status() -> bool {
    if (this->Apex_Window == GetForegroundWindow()) {
        return true;
    }

    if (this->Apex_Window == GetActiveWindow()) {
        return true;
    }

    if (LI_FN(GetActiveWindow).get() == LI_FN(GetForegroundWindow).get()) {
        return true;
    }

    return false;
}
auto Overlay::OverlayRender::Render() -> bool {
    MSG msg = { NULL };
    ZeroMemory(&msg, sizeof(MSG));
    RECT Windowrect;

    while (msg.message != WM_QUIT)
    {

        UpdateWindow(window_handle);
        ShowWindow(window_handle, SW_SHOW);
        

        if ((PeekMessageA)(&msg, window_handle, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        ImGuiIO& io = ImGui::GetIO();
        io.DeltaTime = 1.0f / 60.0f;


        POINT p_cursor;
        GetCursorPos(&p_cursor);
        io.MousePos.x = p_cursor.x;
        io.MousePos.y = p_cursor.y;

        if (GetAsyncKeyState(VK_LBUTTON)) {
            io.MouseDown[0] = true;
            io.MouseClicked[0] = true;
            io.MouseClickedPos[0].x = io.MousePos.x;
            io.MouseClickedPos[0].x = io.MousePos.y;
        }
        else
            io.MouseDown[0] = false;
     
        Overlay::OverlayRender::Draw();

    }
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    LI_FN(DestroyWindow)(window_handle);
    return true;
}
auto Overlay::OverlayRender::ImGui() -> bool {
    DXGI_SWAP_CHAIN_DESC swap_chain_description;
    ZeroMemory(&swap_chain_description, sizeof(swap_chain_description));
    swap_chain_description.BufferCount = 2;
    swap_chain_description.BufferDesc.Width = 0;
    swap_chain_description.BufferDesc.Height = 0;
    swap_chain_description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_description.BufferDesc.RefreshRate.Numerator = 60;
    swap_chain_description.BufferDesc.RefreshRate.Denominator = 1;
    swap_chain_description.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_description.OutputWindow = window_handle;
    swap_chain_description.SampleDesc.Count = 1;
    swap_chain_description.SampleDesc.Quality = 0;
    swap_chain_description.Windowed = 1;
    swap_chain_description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    D3D_FEATURE_LEVEL d3d_feature_lvl;

    const D3D_FEATURE_LEVEL d3d_feature_array[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

    D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, d3d_feature_array, 2, D3D11_SDK_VERSION, &swap_chain_description, &d3d_swap_chain, &d3d_device, &d3d_feature_lvl, &d3d_device_ctx);

    ID3D11Texture2D* pBackBuffer;

    d3d_swap_chain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

    d3d_device->CreateRenderTargetView(pBackBuffer, NULL, &d3d_render_target);

    pBackBuffer->Release();

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    ImVec4 clear_color = GetStyleColorVec4(ImGuiCol_WindowBg);
    io.IniFilename = NULL;
    (void)io;
    static const ImWchar ranges[] =
    {
        0x0020, 0x00FF,
        0x0400, 0x052F,
        0x2DE0, 0x2DFF,
        0xA640, 0xA69F,
        0xE000, 0xE226,
        0,
    };
    ImGuiStyle& Style = ImGui::GetStyle();
    Style.WindowRounding = 0.0f;
    Style.FrameRounding = 1.0f;
    Style.GrabRounding = 0.0f;
    Style.ScrollbarRounding = 0.0f;
    Style.ChildRounding = 1.0f;
    Style.FramePadding = ImVec2(6, 3);
    Style.ItemSpacing = ImVec2(8, 6);
    Style.ItemInnerSpacing = ImVec2(6, 6);
    Style.WindowPadding = ImVec2(12, 12);
    Style.FrameBorderSize = 0.0f;
    Style.WindowBorderSize = 0.0f;

    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    colors[ImGuiCol_Border] = ImVec4(0.25f, 0.25f, 0.28f, 0.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    colors[ImGuiCol_FrameBg] = ImVec4(0.f, 0.f, 0.f, 10.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);

    colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);

    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.12f, 0.12f, 0.12f, 0.60f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);

    colors[ImGuiCol_Separator] = ImVec4(0.25f, 0.25f, 0.28f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.35f, 0.35f, 0.38f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.45f, 0.45f, 0.48f, 1.00f);

    ImFontConfig font_config;
    font_config.PixelSnapH = false;
    font_config.OversampleH = 5;
    font_config.OversampleV = 5;
    font_config.RasterizerMultiply = 1.2f;


    //{
    //    ImGuiStyle& Style = ImGui::GetStyle();
    //    Style.WindowRounding = 0.0f; // Rounded edges for the window
    //    Style.FrameRounding = 25.0f;
    //    Style.GrabRounding = 0.0f;
    //    Style.ScrollbarRounding = 0.0f;
    //    Style.ChildRounding = 0.0f;
    //    Style.FramePadding = ImVec2(6, 3); // Compact padding for frames
    //    Style.ItemSpacing = ImVec2(8, 6); // Adjust spacing between items
    //    Style.ItemInnerSpacing = ImVec2(6, 6);
    //    Style.WindowPadding = ImVec2(12, 12); // Padding around the window content
    //    Style.FrameBorderSize = 1.0f;
    //    Style.WindowBorderSize = 1.0f;

    //    // Define the color palette
    //    ImVec4* colors = ImGui::GetStyle().Colors;
    //    colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f); // Text color
    //    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

    //    // Background colors
    //    colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f); // Solid window background
    //    colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    //    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);

    //    // Title bar colors
    //    colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f); // Opaque title bar
    //    colors[ImGuiCol_TitleBgActive] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f); // Opaque active title bar
    //    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f); // Collapsed title bar

    //    // Border colors
    //    colors[ImGuiCol_Border] = ImVec4(0.25f, 0.25f, 0.28f, 1.00f);
    //    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);

    //    // Frame background
    //    colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    //    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    //    colors[ImGuiCol_FrameBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);

    //    // Scrollbar
    //    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    //    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    //    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    //    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);

    //    // Checkmark and Slider colors
    //    colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
    //    colors[ImGuiCol_SliderGrab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    //    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);

    //    // Separators
    //    colors[ImGuiCol_Separator] = ImVec4(0.25f, 0.25f, 0.28f, 1.00f);
    //    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.35f, 0.35f, 0.38f, 1.00f);
    //    colors[ImGuiCol_SeparatorActive] = ImVec4(0.45f, 0.45f, 0.48f, 1.00f);
    //}



    FontList::Ebrima = io.Fonts->AddFontFromFileTTF(_("C:\\Windows\\Fonts\\ebrimabd.ttf"), 17.f,NULL, io.Fonts->GetGlyphRangesChineseFull());
    FontList::Pixel = io.Fonts->AddFontFromFileTTF(_("C:\\Users\\1\\Desktop\\__\\Minecraftchmc-Semibold.ttf"), 30.f);
    FontList::Arial = io.Fonts->AddFontFromFileTTF(_("C:\\Windows\\Fonts\\arialbd.ttf"), 17.f);
    FontList::Calibri = io.Fonts->AddFontFromFileTTF(_("C:\\Windows\\Fonts\\calibri.ttf"), 17.f);
    FontList::consola = io.Fonts->AddFontFromFileTTF(_("C:\\Windows\\Fonts\\consola.ttf"), 17.f);
    FontList::verdana = io.Fonts->AddFontFromFileTTF(_("C:\\Windows\\Fonts\\verdana.ttf"), 17.f);
    FontList::Franklin_Gothic = io.Fonts->AddFontFromFileTTF(_("C:\\Windows\\Fonts\\framd.ttf"), 17.f);

    D3DX11_IMAGE_LOAD_INFO info;
    ID3DX11ThreadPump* pmp{ nullptr };

    {
        
        if (!xexTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, xexBytes, sizeof(xexBytes), &info, pmp, &xexTexture, 0);

        if (!SelectedSkin::Pistol::p2020::Texture::EyeOfTheStorm)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Eye_of_the_Storm_P2020Data, sizeof(Eye_of_the_Storm_P2020Data), &info, pmp, &SelectedSkin::Pistol::p2020::Texture::EyeOfTheStorm, 0);

        if (!SelectedSkin::Pistol::p2020::Texture::TrialByFire)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Trial_by_Fire_P2020Data, sizeof(Trial_by_Fire_P2020Data), &info, pmp, &SelectedSkin::Pistol::p2020::Texture::TrialByFire, 0);

        if (!SelectedSkin::Pistol::p2020::Texture::CodeOfHonor)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Code_of_Honor_P2020Data, sizeof(Code_of_Honor_P2020Data), &info, pmp, &SelectedSkin::Pistol::p2020::Texture::CodeOfHonor, 0);

        if (!SelectedSkin::Pistol::p2020::Texture::OffTheGrid)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Off_the_Grid_P2020Data, sizeof(Off_the_Grid_P2020Data), &info, pmp, &SelectedSkin::Pistol::p2020::Texture::OffTheGrid, 0);

        if (!SelectedSkin::Pistol::p2020::Texture::BreakTheEnemy)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Break_the_Enemy_P2020Data, sizeof(Break_the_Enemy_P2020Data), &info, pmp, &SelectedSkin::Pistol::p2020::Texture::BreakTheEnemy, 0);

        if (!SelectedSkin::Pistol::p2020::Texture::ShadowWeb)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Shadow_Web_P2020Data, sizeof(Shadow_Web_P2020Data), &info, pmp, &SelectedSkin::Pistol::p2020::Texture::ShadowWeb, 0);

        if (!SelectedSkin::Pistol::p2020::Texture::HotSpot)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Hot_Spot_P2020Data, sizeof(Hot_Spot_P2020Data), &info, pmp, &SelectedSkin::Pistol::p2020::Texture::HotSpot, 0);

        if (!SelectedSkin::Pistol::p2020::Texture::HiddenHazard)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Hidden_Hazard_P2020Data, sizeof(Hidden_Hazard_P2020Data), &info, pmp, &SelectedSkin::Pistol::p2020::Texture::HiddenHazard, 0);

        if (!SelectedSkin::Pistol::alternator::Texture::Recluse)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Recluse_Alternator_SMGData, sizeof(Recluse_Alternator_SMGData), &info, pmp, &SelectedSkin::Pistol::alternator::Texture::Recluse, 0);

        if (!SelectedSkin::Pistol::alternator::Texture::EyeOfTheStorm)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Eye_of_the_Storm_Alternator_SMGData, sizeof(Eye_of_the_Storm_Alternator_SMGData), &info, pmp, &SelectedSkin::Pistol::alternator::Texture::EyeOfTheStorm, 0);

        if (!SelectedSkin::Pistol::alternator::Texture::TrialByFire)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Trial_by_Fire_Alternator_SMGData, sizeof(Trial_by_Fire_Alternator_SMGData), &info, pmp, &SelectedSkin::Pistol::alternator::Texture::TrialByFire, 0);

        if (!SelectedSkin::Pistol::alternator::Texture::CodeOfHonor)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Code_of_Honor_Alternator_SMGData, sizeof(Code_of_Honor_Alternator_SMGData), &info, pmp, &SelectedSkin::Pistol::alternator::Texture::CodeOfHonor, 0);

        if (!SelectedSkin::Pistol::alternator::Texture::OffTheGrid)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Off_the_Grid_Alternator_SMGData, sizeof(Off_the_Grid_Alternator_SMGData), &info, pmp, &SelectedSkin::Pistol::alternator::Texture::OffTheGrid, 0);

        if (!SelectedSkin::Pistol::alternator::Texture::BreakTheEnemy)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Break_the_Enemy_Alternator_SMGData, sizeof(Break_the_Enemy_Alternator_SMGData), &info, pmp, &SelectedSkin::Pistol::alternator::Texture::BreakTheEnemy, 0);

        if (!SelectedSkin::Pistol::alternator::Texture::MoltenForge)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Molten_Forge_Alternator_SMGData, sizeof(Molten_Forge_Alternator_SMGData), &info, pmp, &SelectedSkin::Pistol::alternator::Texture::MoltenForge, 0);

        if (!SelectedSkin::Pistol::alternator::Texture::Melternator)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Melternator_Alternator_SMGData, sizeof(Melternator_Alternator_SMGData), &info, pmp, &SelectedSkin::Pistol::alternator::Texture::Melternator, 0);

        if (!SelectedSkin::Pistol::alternator::Texture::StarChart)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Star_Chart_Alternator_SMGData, sizeof(Star_Chart_Alternator_SMGData), &info, pmp, &SelectedSkin::Pistol::alternator::Texture::StarChart, 0);

        if (!SelectedSkin::Pistol::alternator::Texture::TreadRunner)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Treadrunner_Alternator_SMGData, sizeof(Treadrunner_Alternator_SMGData), &info, pmp, &SelectedSkin::Pistol::alternator::Texture::TreadRunner, 0);

        if (!SelectedSkin::Pistol::alternator::Texture::CyberHide)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Cyber_Hide_Alternator_SMGData, sizeof(Cyber_Hide_Alternator_SMGData), &info, pmp, &SelectedSkin::Pistol::alternator::Texture::CyberHide, 0);


        if (!SelectedSkin::Pistol::alternator::Texture::GreatNorthernWay)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Great_Northern_Way_Alternator_SMGData, sizeof(Great_Northern_Way_Alternator_SMGData), &info, pmp, &SelectedSkin::Pistol::alternator::Texture::GreatNorthernWay, 0);

        if (!SelectedSkin::Pistol::alternator::Texture::SummoningCircle)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Summoning_Circle_Alternator_SMGData, sizeof(Summoning_Circle_Alternator_SMGData), &info, pmp, &SelectedSkin::Pistol::alternator::Texture::SummoningCircle, 0);


        if (!SelectedSkin::Pistol::re45::Texture::Recluse)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Recluse_REData, sizeof(Recluse_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::Recluse, 0);

        if (!SelectedSkin::Pistol::re45::Texture::EyeOfTheStorm)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Eye_of_the_Storm_REData, sizeof(Eye_of_the_Storm_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::EyeOfTheStorm, 0);

        if (!SelectedSkin::Pistol::re45::Texture::TrialByFire)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Trial_by_Fire_REData, sizeof(Trial_by_Fire_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::TrialByFire, 0);

        if (!SelectedSkin::Pistol::re45::Texture::CodeOfHonor)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Code_of_Honor_REData, sizeof(Code_of_Honor_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::CodeOfHonor, 0);

        if (!SelectedSkin::Pistol::re45::Texture::OffTheGrid)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Off_the_Grid_REData, sizeof(Off_the_Grid_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::OffTheGrid, 0);

        if (!SelectedSkin::Pistol::re45::Texture::BreakTheEnemy)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Break_the_Enemy_REData, sizeof(Break_the_Enemy_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::BreakTheEnemy, 0);

        if (!SelectedSkin::Pistol::re45::Texture::BlueFade)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Break_the_Enemy_REData, sizeof(Break_the_Enemy_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::BlueFade, 0);

        if (!SelectedSkin::Pistol::re45::Texture::Gnarly)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Gnarly_REData, sizeof(Gnarly_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::Gnarly, 0);

        if (!SelectedSkin::Pistol::re45::Texture::PulseCheck)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Pulse_Check_REData, sizeof(Pulse_Check_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::PulseCheck, 0);

        if (!SelectedSkin::Pistol::re45::Texture::TribalGlyph)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Tribal_Glyph_REData, sizeof(Tribal_Glyph_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::TribalGlyph, 0);

        if (!SelectedSkin::Pistol::re45::Texture::NeonCandy)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Neon_Candy_REData, sizeof(Neon_Candy_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::NeonCandy, 0);

        if (!SelectedSkin::Pistol::re45::Texture::ForceLimiter)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Force_Limiter_REData, sizeof(Force_Limiter_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::ForceLimiter, 0);

        if (!SelectedSkin::Pistol::re45::Texture::ServedFresh)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Served_Fresh_REData, sizeof(Served_Fresh_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::ServedFresh, 0);

        if (!SelectedSkin::Pistol::re45::Texture::TheMultiPass)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, The_Multipass_REData, sizeof(The_Multipass_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::TheMultiPass, 0);

        if (!SelectedSkin::Pistol::re45::Texture::SunkenTreasure)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Sunken_Treasure_REData, sizeof(Sunken_Treasure_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::SunkenTreasure, 0);

        if (!SelectedSkin::Pistol::re45::Texture::UltraViolet)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Ultraviolet_REData, sizeof(Ultraviolet_REData), &info, pmp, &SelectedSkin::Pistol::re45::Texture::UltraViolet, 0);


        if (!Kitten_Texture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, EkittenData, sizeof(EkittenData), &info, pmp, &Kitten_Texture, 0);
        if (!LootTexture::Armor::ShieldTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, CommonArmorBytes, sizeof(CommonArmorBytes), &info, pmp, &LootTexture::Armor::ShieldTexture, 0);
        if (!LootTexture::Armor::HelmetTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Helmetbytes, sizeof(Helmetbytes), &info, pmp, &LootTexture::Armor::HelmetTexture, 0);
        //ARMOR TEXTURE
        if (!AmrmorICON::CommonArmorTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, CommonArmorBytes, sizeof(CommonArmorBytes), &info, pmp, &AmrmorICON::CommonArmorTexture, 0);

        if (!AmrmorICON::UncommonArmorTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, UncommonArmorBytes, sizeof(UncommonArmorBytes), &info, pmp, &AmrmorICON::UncommonArmorTexture, 0);

        if (!AmrmorICON::RareArmorTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, RareArmorBytes, sizeof(RareArmorBytes), &info, pmp, &AmrmorICON::RareArmorTexture, 0);

        if (!AmrmorICON::LegendaryArmorTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, LegendaryArmorBytes, sizeof(LegendaryArmorBytes), &info, pmp, &AmrmorICON::LegendaryArmorTexture, 0);

        if (!AmrmorICON::MythicArmorTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, MythicArmorBytes, sizeof(MythicArmorBytes), &info, pmp, &AmrmorICON::MythicArmorTexture, 0);

        if (!LootTexture::MedTexture::EvoCacheTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, evobytes, sizeof(evobytes), &info, pmp, &LootTexture::MedTexture::EvoCacheTexture, 0);
        if (!LootTexture::MedTexture::LargeMedTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Medkitbytes, sizeof(Medkitbytes), &info, pmp, &LootTexture::MedTexture::LargeMedTexture, 0);
        if (!LootTexture::MedTexture::LargeShieldTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, ShieldLargebytes, sizeof(ShieldLargebytes), &info, pmp, &LootTexture::MedTexture::LargeShieldTexture, 0);
        if (!LootTexture::MedTexture::PhynioxTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, phynixbytes, sizeof(phynixbytes), &info, pmp, &LootTexture::MedTexture::PhynioxTexture, 0);
        if (!LootTexture::MedTexture::SmallMedTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, MedsmallBytes, sizeof(MedsmallBytes), &info, pmp, &LootTexture::MedTexture::SmallMedTexture, 0);
        if (!LootTexture::MedTexture::SmallShieldTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, ShieldSmallBytes, sizeof(ShieldSmallBytes), &info, pmp, &LootTexture::MedTexture::SmallShieldTexture, 0);


        if (!LootTexture::AmmoTexture::EnergyAmmoTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, EnergyAmmoBytes, sizeof(EnergyAmmoBytes), &info, pmp, &LootTexture::AmmoTexture::EnergyAmmoTexture, 0);
        if (!LootTexture::AmmoTexture::HeavyAmmoTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, HeavyAmmoBytes, sizeof(HeavyAmmoBytes), &info, pmp, &LootTexture::AmmoTexture::HeavyAmmoTexture, 0);
        if (!LootTexture::AmmoTexture::LightAmmoTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, LightAmmoBytes, sizeof(LightAmmoBytes), &info, pmp, &LootTexture::AmmoTexture::LightAmmoTexture, 0);
        if (!LootTexture::AmmoTexture::ShotGunAmmoTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, ShotgunAmmoBytes, sizeof(ShotgunAmmoBytes), &info, pmp, &LootTexture::AmmoTexture::ShotGunAmmoTexture, 0);
        if (!LootTexture::AmmoTexture::SniperAmmoTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, SniperAmmoBytes, sizeof(SniperAmmoBytes), &info, pmp, &LootTexture::AmmoTexture::SniperAmmoTexture, 0);

        //p202
        if (!WeaponIcon::PistolICON::P2020Texture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, p2020Bytes, sizeof(p2020Bytes), &info, pmp, &WeaponIcon::PistolICON::P2020Texture, 0);
        //re45
        if (!WeaponIcon::PistolICON::Re45Texture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, re45Bytes, sizeof(re45Bytes), &info, pmp, &WeaponIcon::PistolICON::Re45Texture, 0);
        //alternator
        if (!WeaponIcon::PistolICON::AlternatorTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, alternatorBytes, sizeof(alternatorBytes), &info, pmp, &WeaponIcon::PistolICON::AlternatorTexture, 0);
        //wingmen
        if (!WeaponIcon::PistolICON::WingmenTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, wingmenBytes, sizeof(wingmenBytes), &info, pmp, &WeaponIcon::PistolICON::WingmenTexture, 0);



        if (!WeaponIcon::ShotgunICON::EVA8Texture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, eva_8_autoBytes, sizeof(eva_8_autoBytes), &info, pmp, &WeaponIcon::ShotgunICON::EVA8Texture, 0);
        if (!WeaponIcon::ShotgunICON::MastiffTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, mastiffBytes, sizeof(mastiffBytes), &info, pmp, &WeaponIcon::ShotgunICON::MastiffTexture, 0);
        if (!WeaponIcon::ShotgunICON::MozambiqueTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, mozambiqueBytes, sizeof(mozambiqueBytes), &info, pmp, &WeaponIcon::ShotgunICON::MozambiqueTexture, 0);
        if (!WeaponIcon::ShotgunICON::peacekeeperTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, peacekeeperBytes, sizeof(peacekeeperBytes), &info, pmp, &WeaponIcon::ShotgunICON::peacekeeperTexture, 0);



        if (!WeaponIcon::Rifle::CarTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, carbytes, sizeof(carbytes), &info, pmp, &WeaponIcon::Rifle::CarTexture, 0);
        if (!WeaponIcon::Rifle::CarbineTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, CarbineBytes, sizeof(CarbineBytes), &info, pmp, &WeaponIcon::Rifle::CarbineTexture, 0);
        if (!WeaponIcon::Rifle::FlatlineTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Flatlinebytes, sizeof(Flatlinebytes), &info, pmp, &WeaponIcon::Rifle::FlatlineTexture, 0);
        if (!WeaponIcon::Rifle::HemlockTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Hemlockbytes, sizeof(Hemlockbytes), &info, pmp, &WeaponIcon::Rifle::HemlockTexture, 0);
        if (!WeaponIcon::Rifle::ProwlerTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Prowlerbytes, sizeof(Prowlerbytes), &info, pmp, &WeaponIcon::Rifle::ProwlerTexture, 0);
        if (!WeaponIcon::Rifle::RampageTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Rampagebytes, sizeof(Rampagebytes), &info, pmp, &WeaponIcon::Rifle::RampageTexture, 0);
        if (!WeaponIcon::Rifle::RepeaterTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Repeaterbytes, sizeof(Repeaterbytes), &info, pmp, &WeaponIcon::Rifle::RepeaterTexture, 0);
        if (!WeaponIcon::Rifle::ScoutTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, scoutbytes, sizeof(scoutbytes), &info, pmp, &WeaponIcon::Rifle::ScoutTexture, 0);
        if (!WeaponIcon::Rifle::SpitFireTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, SpitFirebytes, sizeof(SpitFirebytes), &info, pmp, &WeaponIcon::Rifle::SpitFireTexture, 0);

        if (!WeaponIcon::Special::BowTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, BowBytes, sizeof(BowBytes), &info, pmp, &WeaponIcon::Special::BowTexture, 0);
        if (!WeaponIcon::Special::DevotionTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Devotionbytes, sizeof(Devotionbytes), &info, pmp, &WeaponIcon::Special::DevotionTexture, 0);
        if (!WeaponIcon::Special::KnifeTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Knifebytes, sizeof(Knifebytes), &info, pmp, &WeaponIcon::Special::KnifeTexture, 0);
        if (!WeaponIcon::Special::KraberTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Kraberbytes, sizeof(Kraberbytes), &info, pmp, &WeaponIcon::Special::KraberTexture, 0);
        if (!WeaponIcon::Special::R99Texture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, R99bytes, sizeof(R99bytes), &info, pmp, &WeaponIcon::Special::R99Texture, 0);

        if (!WeaponIcon::Sniper::ChargedRifleTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, ChargedRiflebytes, sizeof(ChargedRiflebytes), &info, pmp, &WeaponIcon::Sniper::ChargedRifleTexture, 0);
        if (!WeaponIcon::Sniper::DMRTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, DMRbytes, sizeof(DMRbytes), &info, pmp, &WeaponIcon::Sniper::DMRTexture, 0);
        if (!WeaponIcon::Sniper::SentinelTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Sentinelbytes, sizeof(Sentinelbytes), &info, pmp, &WeaponIcon::Sniper::SentinelTexture, 0);

        if (!WeaponIcon::Energy::EMGTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, EMGbytes, sizeof(EMGbytes), &info, pmp, &WeaponIcon::Energy::EMGTexture, 0);
        if (!WeaponIcon::Energy::HAVOCTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Havocbytes, sizeof(Havocbytes), &info, pmp, &WeaponIcon::Energy::HAVOCTexture, 0);
        if (!WeaponIcon::Energy::NemesisTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Nemisisbytes, sizeof(Nemisisbytes), &info, pmp, &WeaponIcon::Energy::NemesisTexture, 0);
        if (!WeaponIcon::Energy::TripleTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Triplebytes, sizeof(Triplebytes), &info, pmp, &WeaponIcon::Energy::TripleTexture, 0);
        if (!WeaponIcon::Energy::VoltTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, Voltbytes, sizeof(Voltbytes), &info, pmp, &WeaponIcon::Energy::VoltTexture, 0);

        if (!DeathBoxIcon::DeathBoxTexture)
            D3DX11CreateShaderResourceViewFromMemory(d3d_device, deathboxData, sizeof(deathboxData), &info, pmp, &DeathBoxIcon::DeathBoxTexture, 0);


    }
    
    ImGui_ImplWin32_Init(window_handle);

    ImGui_ImplDX11_Init(d3d_device, d3d_device_ctx);

    d3d_device->Release();

    return true;

}
HWND Overlay::OverlayRender::find_window(const char* classname, const char* windowname, int instance) {
    HWND window_hwnd = NULL;
    int count = 0;
    HWND window = NULL;
    do {
        window = FindWindowExA(NULL, window, classname, windowname);
        if (window) {
            count++;
            if (count == instance) {
                window_hwnd = window;
                break;
            }
        }
    } while (window);

    return window_hwnd;
}


bool  Overlay::OverlayRender::DoesFileExist(const wchar_t* filePath) {
    DWORD attributes = GetFileAttributes((LPCSTR)filePath);
    return (attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY));
}
bool Overlay::OverlayRender::StartWindow()
{
    return false;
}
auto Overlay::OverlayRender::Hijack() -> bool
{
    window_handle = FindWindowA((_("MedalOverlayClass")), (_("MedalOverlay")));
    if (!window_handle) return false;
    MARGINS Margin = { -1 };
    DwmExtendFrameIntoClientArea(window_handle, &Margin);

    SetWindowPos(window_handle, 0, 0, 0, GetSystemMetrics(0), GetSystemMetrics(1), SWP_SHOWWINDOW);
    ShowWindow(window_handle, SW_SHOW);
    UpdateWindow(window_handle);
    return true;
}
auto Overlay::OverlayRender::Menu() -> void
{
}

inline int FrameRate()
{
    static int iFps, iLastFps;
    static float flLastTickCount, flTickCount;
    flTickCount = clock() * 0.001f;
    iFps++;
    if ((flTickCount - flLastTickCount) >= 1.0f) {
        flLastTickCount = flTickCount;
        iLastFps = iFps;
        iFps = 0;
    }
    return iLastFps;
}
void doCrimewareMenu()
{

    ImGui::SetNextWindowSize(ImVec2(600, 500), ImGuiCond_Once); // Adjust window size for the menu
    ImGui::Begin("Crimeware Apex", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    {
        // Set the background color to black
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
     

        ImGui::BeginTabBar("##1");
        {
            if (ImGui::BeginTabItem("Visuals"))
            {
                ImGui::BeginChild("##Vis1", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), true);
                {
                    ImGui::Text("Visuals");
                    ImGui::Separator();
                    ImGui::Checkbox(_("Full Box"), &Cheat_Private::ESP::Box);
                    ImGui::Checkbox(_("Corner Box"), &Cheat_Private::ESP::CornerBox);
                    ImGui::Checkbox(_("Filled Box"), &Cheat_Private::ESP::Filledbox);
                    ImGui::Checkbox(_("Skeleton"), &Cheat_Private::ESP::Skeleton);
                    ImGui::Checkbox(_("Head Circle"), &Cheat_Private::ESP::HeadCircle);
                    ImGui::Checkbox(_("Snap Lines"), &Cheat_Private::ESP::Snapline);
                    ImGui::Checkbox(_("Distance"), &Cheat_Private::ESP::Distance);
                    ImGui::Checkbox(_("Name"), &Cheat_Private::ESP::Weapon);
                    ImGui::Checkbox(_("Operator"), &Cheat_Private::ESP::Operator);
                    ImGui::Checkbox(_("Level"), &Cheat_Private::ESP::Level);
                    ImGui::Checkbox(_("Weapon Name"), &Cheat_Private::ESP::Name);
                    ImGui::Checkbox(_("Weapon Icon"), &Cheat_Private::ESP::WeaponICON);
                    ImGui::Checkbox(_("Health Bar"), &Cheat_Private::ESP::Health);
                    ImGui::Checkbox(_("Shield Bar"), &Cheat_Private::ESP::Shield);
                    ImGui::Checkbox(_("Seern Bar"), &Cheat_Private::ESP::SernEsp);
                    ImGui::Checkbox(_("Visibility"), &Cheat_Private::ESP::VisCheck);
                    ImGui::Checkbox(_("Glow"), &Cheat_Private::ESP::Glow);
                    ImGui::Checkbox(_("OFFArrows"), &Cheat_Private::ESP::OFFArrow);
                    ImGui::Checkbox(_("Warning"), &Cheat_Private::ESP::alert);
                    ImGui::Checkbox(_("Radar"), &Cheat_Private::ESP::Radar);
                    ImGui::Checkbox(_("Radar Name"), &Cheat_Private::ESP::RadarName);
                    ImGui::Checkbox(_("Radar TeamID"), &Cheat_Private::ESP::TeamID);
                    ImGui::Checkbox(_("Display Spectators"), &Cheat_Private::ESP::DisplaySpectators);
                }
                ImGui::EndChild();

                ImGui::SameLine();
                ImGui::BeginChild("##Vis2", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
                {
                    ImGui::Text("Settings");
                    ImGui::Separator();
                    widget->color_picker(_("Box Color"), Cheat_Private::ESP::BoxColor, true);
                    widget->color_picker(_("Filled Box Color"), Cheat_Private::ESP::FilledBoxColor, true);
                    widget->color_picker(_("Skeleton Color"), Cheat_Private::ESP::SkeletonColor, true);
                    widget->color_picker(_("Snap Line Color"), Cheat_Private::ESP::SnaplineColor, true);
                    widget->color_picker(_("Head Circle Color"), Cheat_Private::ESP::HeadCircleColor, true);
                    widget->color_picker(_("Distance Color"), Cheat_Private::ESP::DistanceColor, true);
                    widget->color_picker(_("Level Color"), Cheat_Private::ESP::LevelColor, true);
                    widget->color_picker(_("Operator Color"), Cheat_Private::ESP::OperatorColor, true);
                    widget->color_picker(_("Weapon Color"), Cheat_Private::ESP::NameColor, true);
                    widget->color_picker(_("Weapon ICON Color"), Cheat_Private::ESP::WeaponIconColor, true);
                    widget->color_picker(_("Name Color"), Cheat_Private::ESP::WeaponColor, true);
                    widget->color_picker(_("OFFArrow Color"), Cheat_Private::ESP::OFFArrowColor, true);
                    widget->color_picker(_("Vis Color"), Cheat_Private::ESP::VisColor, true);
                    widget->color_picker(_("Non-Vis Color"), Cheat_Private::ESP::NonVisColor, true);
                    widget->color_picker(_("Team Color"), Cheat_Private::ESP::TeamColor, true);
                    widget->color_picker(_("Knocked Color"), Cheat_Private::ESP::KnockedColor, true);
                    ImGui::SliderFloat(_("Radar SZ"), &Cheat_Private::ESP::RadarSize, 1.0f, 10.0f);
                    ImGui::SliderFloat(_("Alpha"), &Cheat_Private::ESP::transparency, 0.0f, 255.f);
                    ImGui::SliderFloat(_("Draw Dist"), &Cheat_Private::Settings::RenderDistance, 50.f, 1000.f);
                    ImGui::SliderFloat(_("OFF SZ"), &Cheat_Private::ESP::OFFRadius, 1.0f, 100.0f);
                    widget->multi_dropdown(_("Vis Type"), Cheat_Private::ESP::Vistype, Cheat_Private::ESP::VisTypeText, Cheat_Private::ESP::VisTypeText.size());
                    widget->dropdown(_("SnapLine Type"), &Cheat_Private::ESP::SnaplineIndex, Cheat_Private::ESP::SnaplineText, Cheat_Private::ESP::SnaplineText.size());
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Combat"))
            {
                ImGui::BeginChild("##Combat1", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), true);
                {
                    ImGui::Text("Combat");
                    ImGui::Separator();
                    ImGui::Checkbox(_("Aimbot"), &Cheat_Private::Aimbot::VABot);
                    ImGui::Checkbox(_("Hard Target Lock"), &Cheat_Private::Aimbot::HardLock);
                    ImGui::Checkbox(_("Fov Circle"), &Cheat_Private::Aimbot::FovCircle);
                    ImGui::Checkbox(_("Target Line"), &Cheat_Private::Aimbot::Snapline);
                    ImGui::Checkbox(_("Disable Tean"), &Cheat_Private::Aimbot::DisableTeam);
                    ImGui::Checkbox(_("Disable Knocked"), &Cheat_Private::Aimbot::DisableKnocked);
                    ImGui::Checkbox(_("Visibility Check"), &Cheat_Private::Aimbot::VisCheck);
                    ImGui::SliderFloat(_("Fov Size"), &Cheat_Private::Aimbot::FovCircleSize, 1.f, 500.f);
                    ImGui::SliderFloat(_("Smoothing"), &Cheat_Private::Aimbot::SmoothingAmount, 1.f, 10.f);

                }
                ImGui::EndChild();

                ImGui::SameLine();
                ImGui::BeginChild("##Combat2", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
                {
                    ImGui::Text("Settings");
                    ImGui::Separator();
                    widget->dropdown(_("Aimbot Key"), &Cheat_Private::Settings::AimbotKeyINDEX, Cheat_Private::Settings::KeyText, Cheat_Private::Settings::KeyText.size());
                    widget->dropdown(_("Bone"), &Cheat_Private::Aimbot::TargetBone, Cheat_Private::Aimbot::BoneName, Cheat_Private::Aimbot::BoneName.size());
                    widget->color_picker(_("Fov Circle Color"), Cheat_Private::Aimbot::FovCircleColor, true);
                    widget->color_picker(_("Target Line Color"), Cheat_Private::Aimbot::SnaplineColor, true);
                    ImGui::SliderFloat(_("Distance"), &Cheat_Private::Settings::AimbotDistance, 50.f, 1000.f);
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Misc"))
            {
                ImGui::BeginChild("##Set1", { ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y }, true);
                {
                    ImGui::Text("Misc");
                    ImGui::Separator();
                    {
                        ImGui::Spacing();
                        ImGui::Checkbox(_("Super-Glide"), &Cheat_Private::Misc::SuperGlide);
                        ImGui::Checkbox(_("Super-Grapple"), &Cheat_Private::Misc::AutoGrapple);
                        ImGui::Checkbox(_("Third Person"), &Cheat_Private::Misc::Thirdperson);
                        ImGui::Checkbox(_("Large Weapon"), &Cheat_Private::Misc::LargeWeapon);
                        ImGui::Checkbox(_("Bigger Hitbox (!May Crash Game!)"), &Cheat_Private::Misc::LargePlayers);
                        ImGui::Checkbox(_("No Recoil"), &Cheat_Private::Aimbot::RcsControl);
                        ImGui::Checkbox(_("Reload Bar"), &Cheat_Private::Misc::ReloadBar);
                        ImGui::Checkbox(_("Back Track (RISKY)"), &Cheat_Private::Misc::BackTrack);
                        ImGui::Checkbox(_("Ammo Counter"), &Cheat_Private::Misc::AmmoCounter);
                        ImGui::Checkbox(_("Night Mode"), &Cheat_Private::Misc::FullBright);
                        ImGui::Checkbox(_("Zoom"), &Cheat_Private::Misc::zoom);
                        ImGui::Checkbox(_("Fov Changer"), &Cheat_Private::Misc::FovChanger);
                        ImGui::SliderFloat(_("FOV"), &Cheat_Private::Misc::SetFov, 70.f, 150.f);
                    }

                }
                ImGui::EndChild();
                ImGui::SameLine();
                ImGui::BeginChild("##Vis2", { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y }, true);
                {
                    ImGui::Text("Misc 2");
                    ImGui::Separator();
                    {
                        ImGui::Spacing();
                        ImGui::Checkbox(_("Item Glow"), &Cheat_Private::Misc::ItemGlow);
                        ImGui::Checkbox(_("Free Cam"), &Cheat_Private::Misc::Freecam);
                        ImGui::Checkbox(_("Weapon Glow"), &Cheat_Private::Misc::WeaponGlow);
                        ImGui::Checkbox(_("Arm Glow"), &Cheat_Private::Misc::HandGlow);
                        ImGui::Checkbox(_("Weapon Skin-Changer"), &Cheat_Private::Misc::SkinChanger);
                        ImGui::SliderInt(_("Skin-ID"), &Cheat_Private::Misc::SkinID, 1, 25);
                        widget->dropdown(_("Super Glide Key"), &Cheat_Private::Misc::SuperGlideIndex, Cheat_Private::Settings::KeyText, Cheat_Private::Settings::KeyText.size());
                        widget->dropdown(_("Third Person Key"), &Cheat_Private::Misc::ThirdPeronIndex, Cheat_Private::Settings::KeyText, Cheat_Private::Settings::KeyText.size());
                         widget->dropdown(_("Free Cam Key"), &Cheat_Private::Misc::FreeCamKey, Cheat_Private::Settings::KeyText, Cheat_Private::Settings::KeyText.size());
                        widget->dropdown(_("Fake Duck Key"), &Cheat_Private::Misc::FakeDuckKEY, Cheat_Private::Settings::KeyText, Cheat_Private::Settings::KeyText.size());
                        widget->dropdown(_("Zoom Key"), &Cheat_Private::Misc::zoomindex, Cheat_Private::Settings::KeyText, Cheat_Private::Settings::KeyText.size());
                        widget->dropdown(_("Weapon Glow Type"), &Cheat_Private::Misc::WeaponGlowIndex, Cheat_Private::Misc::WeaponGlowText, Cheat_Private::Misc::WeaponGlowText.size());
                        widget->dropdown(_("Arm Glow Type"), &Cheat_Private::Misc::HandGlowIndex, Cheat_Private::Misc::WeaponGlowText, Cheat_Private::Misc::WeaponGlowText.size());
                    }
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
         
            
        }
        ImGui::EndTabBar();

        // Pop the background color style
        ImGui::PopStyleColor();
    }
    ImGui::End();


    switch (Cheat_Private::Misc::WeaponGlowIndex)
    {
    case 0:
        Cheat_Private::Misc::SelectedGlowIndex = 2;
        break;
    case 1:
        Cheat_Private::Misc::SelectedGlowIndex = 62;
        break;
    case 2:
        Cheat_Private::Misc::SelectedGlowIndex = 77;
        break;
    case 3:
        Cheat_Private::Misc::SelectedGlowIndex = 50;
        break;
    case 4:
        Cheat_Private::Misc::SelectedGlowIndex = 52;
        break;
    case 5:
        Cheat_Private::Misc::SelectedGlowIndex = 31;
        break;
    case 6:
        Cheat_Private::Misc::SelectedGlowIndex = 78;
        break;
    }
    switch (Cheat_Private::Misc::HandGlowIndex)
    {
    case 0:
        Cheat_Private::Misc::SelectedHandGlowIndex = 2;
        break;
    case 1:
        Cheat_Private::Misc::SelectedHandGlowIndex = 62;
        break;
    case 2:
        Cheat_Private::Misc::SelectedHandGlowIndex = 77;
        break;
    case 3:
        Cheat_Private::Misc::SelectedHandGlowIndex = 50;
        break;
    case 4:
        Cheat_Private::Misc::SelectedHandGlowIndex = 52;
        break;
    case 5:
        Cheat_Private::Misc::SelectedHandGlowIndex = 31;
        break;
    case 6:
        Cheat_Private::Misc::SelectedHandGlowIndex = 78;
        break;

    }
    switch (Cheat_Private::Misc::FakeDuckKEY)
    {
    case 0:
        Cheat_Private::Misc::KafeDuckBIND = 0x01;
        break;
    case 1:
        Cheat_Private::Misc::KafeDuckBIND = 0x02;
        break;
    case 2:
        Cheat_Private::Misc::KafeDuckBIND = 0x05;
        break;
    case 3:
        Cheat_Private::Misc::KafeDuckBIND = 0x06;
        break;
    case 4:
        Cheat_Private::Misc::KafeDuckBIND = 0xA4;
        break;
    case 5:
        Cheat_Private::Misc::KafeDuckBIND = 0xA0;
        break;
    }
    switch (Cheat_Private::Misc::FreeCamKey)
    {
    case 0:
        Cheat_Private::Misc::FreeCamBind = 0x01;
        break;
    case 1:
        Cheat_Private::Misc::FreeCamBind = 0x02;
        break;
    case 2:
        Cheat_Private::Misc::FreeCamBind = 0x05;
        break;
    case 3:
        Cheat_Private::Misc::FreeCamBind = 0x06;
        break;
    case 4:
        Cheat_Private::Misc::FreeCamBind = 0xA4;
        break;
    case 5:
        Cheat_Private::Misc::FreeCamBind = 0xA0;
        break;
    }
    switch (Cheat_Private::Misc::SuperGlideIndex)
    {
    case 0:
        Cheat_Private::Misc::SuperGliderkey = 0x01;
        break;
    case 1:
        Cheat_Private::Misc::SuperGliderkey = 0x02;
        break;
    case 2:
        Cheat_Private::Misc::SuperGliderkey = 0x05;
        break;
    case 3:
        Cheat_Private::Misc::SuperGliderkey = 0x06;
        break;
    case 4:
        Cheat_Private::Misc::SuperGliderkey = 0xA4;
        break;
    case 5:
        Cheat_Private::Misc::SuperGliderkey = 0xA0;
        break;
    }
    switch (Cheat_Private::Misc::ThirdPeronIndex)
    {
    case 0:
        Cheat_Private::Misc::ThirdPeronKey = 0x01;
        break;
    case 1:
        Cheat_Private::Misc::ThirdPeronKey = 0x02;
        break;
    case 2:
        Cheat_Private::Misc::ThirdPeronKey = 0x05;
        break;
    case 3:
        Cheat_Private::Misc::ThirdPeronKey = 0x06;
        break;
    case 4:
        Cheat_Private::Misc::ThirdPeronKey = 0xA4;
        break;
    case 5:
        Cheat_Private::Misc::ThirdPeronKey = 0xA0;
        break;
    }
    switch (Cheat_Private::Settings::PSilentKeyIndex)
    {
    case 0:
        Cheat_Private::Aimbot::PSilentKey = 0x01;
        break;
    case 1:
        Cheat_Private::Aimbot::PSilentKey = 0x02;
        break;
    case 2:
        Cheat_Private::Aimbot::PSilentKey = 0x05;
        break;
    case 3:
        Cheat_Private::Aimbot::PSilentKey = 0x06;
        break;
    case 4:
        Cheat_Private::Aimbot::PSilentKey = 0xA4;
        break;
    case 5:
        Cheat_Private::Aimbot::PSilentKey = 0xA0;
        break;
    }
    switch (Cheat_Private::Settings::AimbotKeyINDEX)
    {
    case 0:
        Cheat_Private::Aimbot::AimbotKey = 0x01;
        break;
    case 1:
        Cheat_Private::Aimbot::AimbotKey = 0x02;
        break;
    case 2:
        Cheat_Private::Aimbot::AimbotKey = 0x05;
        break;
    case 3:
        Cheat_Private::Aimbot::AimbotKey = 0x06;
        break;
    case 4:
        Cheat_Private::Aimbot::AimbotKey = 0xA4;
        break;
    case 5:
        Cheat_Private::Aimbot::AimbotKey = 0xA0;
        break;
    }
    switch (Cheat_Private::Aimbot::SkyIndex)
    {
    case 0:
        Cheat_Private::Aimbot::SkyKey = 0x01;
        break;
    case 1:
        Cheat_Private::Aimbot::SkyKey = 0x02;
        break;
    case 2:
        Cheat_Private::Aimbot::SkyKey = 0x05;
        break;
    case 3:
        Cheat_Private::Aimbot::SkyKey = 0x06;
        break;
    case 4:
        Cheat_Private::Aimbot::SkyKey = 0xA4;
        break;
    case 5:
        Cheat_Private::Aimbot::SkyKey = 0xA0;
        break;
    }
    switch (Cheat_Private::Misc::zoomindex)
    {
    case 0:
        Cheat_Private::Misc::zoomkey = 0x01;
        break;
    case 1:
        Cheat_Private::Misc::zoomkey = 0x02;
        break;
    case 2:
        Cheat_Private::Misc::zoomkey = 0x05;
        break;
    case 3:
        Cheat_Private::Misc::zoomkey = 0x06;
        break;
    case 4:
        Cheat_Private::Misc::zoomkey = 0xA4;
        break;
    case 5:
        Cheat_Private::Misc::zoomkey = 0xA0;
        break;
    }
    switch (Cheat_Private::Aimbot::TargetBone) {
    case 0: Cheat_Private::Aimbot::SelectedBone = 0; break;
    case 1: Cheat_Private::Aimbot::SelectedBone = 1; break;
    case 2: Cheat_Private::Aimbot::SelectedBone = 2; break;
    case 3: Cheat_Private::Aimbot::SelectedBone = 3; break;
    }
    switch (Cheat_Private::Loot::BattleIndex)
    {
    case 0:
        Cheat_Private::Loot::BattleKey = 0x01;
        break;
    case 1:
        Cheat_Private::Loot::BattleKey = 0x02;
        break;
    case 2:
        Cheat_Private::Loot::BattleKey = 0x05;
        break;
    case 3:
        Cheat_Private::Loot::BattleKey = 0x06;
        break;
    case 4:
        Cheat_Private::Loot::BattleKey = 0xA4;
        break;
    case 5:
        Cheat_Private::Loot::BattleKey = 0xA0;
        break;
    }

}
void doMainMenu()
{    
    ImGui::SetNextWindowSize(ImVec2(700, 700), ImGuiCond_Once);
    ImGui::Begin(_("MainWindow"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 window_size = ImGui::GetWindowSize();
        ImVec2 window_pos = ImGui::GetWindowPos();
        ImVec2 title_pos = window_pos + ImVec2((window_size.x - ImGui::CalcTextSize(_("XEX Apex Legends External")).x) / 2, 8);
        ImU32 separator_line_color = IM_COL32(0, 200, 255, 200);
        draw_list->AddText(ImVec2(title_pos.x, window_pos.y + 8), IM_COL32(255, 255, 255, 255), _("XEX Apex Legends External"));
        draw_list->AddLine(ImVec2(window_pos.x + 5, window_pos.y + 33), ImVec2(window_pos.x + window_size.x - 5, window_pos.y + 33), separator_line_color, 2.0f);
        ImGui::Dummy(ImVec2(0, 40));
        float total_tab_width = ImGui::CalcTextSize(_("Visuals")).x + ImGui::CalcTextSize(_("Aimbot")).x + ImGui::CalcTextSize(_("Misc")).x + ImGui::CalcTextSize(_("Settings")).x;
        total_tab_width += ImGui::GetStyle().ItemSpacing.x * 3;
        float available_width = ImGui::GetContentRegionAvail().x;
        float padding = (available_width - total_tab_width) / 2 - 45;
        if (padding > 0) {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + padding);
        }
        ImGui::BeginTabBar(_("##1"));
        {
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            ImVec2 window_pos = ImGui::GetWindowPos();
            if (ImGui::BeginTabItem(_("Visuals")))
            {
                ImVec2 tab_min = ImGui::GetItemRectMin();
                ImVec2 tab_max = ImGui::GetItemRectMax();
                draw_list->AddLine(ImVec2(tab_min.x, tab_max.y + 2), ImVec2(tab_max.x, tab_max.y + 2), IM_COL32(0, 155, 255, 255), 2.0f);
                ImGui::BeginChild(_("##Vis1"), ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), true);
                {
                    ImVec2 child_size = ImGui::GetContentRegionAvail();
                    ImVec2 text_size = ImGui::CalcTextSize(_("Visuals"));
                    float text_x_pos = (child_size.x - text_size.x) / 2;
                    ImGui::SetCursorPosX(text_x_pos);
                    ImGui::Text(_("Visuals"));
                    ImGui::Separator();  
                    Draw::menu->CustomCheckbox(_("Full Box"), &Cheat_Private::ESP::Box);
                    Draw::menu->CustomCheckbox(_("Corner Box"), &Cheat_Private::ESP::CornerBox);
                    Draw::menu->CustomCheckbox(_("Filled Box"), &Cheat_Private::ESP::Filledbox);
                    //Draw::menu->CustomCheckbox(_("Web Radar"), &Cheat_Private::WebRadar::Radar);
                    Draw::menu->CustomCheckbox(_("Skeleton"), &Cheat_Private::ESP::Skeleton);
#ifdef developer
        Draw::menu->CustomCheckbox(_("Gay Skeleton"), &Cheat_Private::ESP::SkeletonGay);
#endif
                    Draw::menu->CustomCheckbox(_("Head Circle"), &Cheat_Private::ESP::HeadCircle);
                    Draw::menu->CustomCheckbox(_("Snap Lines"), &Cheat_Private::ESP::Snapline);
                    Draw::menu->CustomCheckbox(_("Distance"), &Cheat_Private::ESP::Distance);
                    Draw::menu->CustomCheckbox(_("Name"), &Cheat_Private::ESP::Weapon);
                    Draw::menu->CustomCheckbox(_("Operator"), &Cheat_Private::ESP::Operator);
                    Draw::menu->CustomCheckbox(_("Level"), &Cheat_Private::ESP::Level);
                    Draw::menu->CustomCheckbox(_("Weapon Name"), &Cheat_Private::ESP::Name);
                    Draw::menu->CustomCheckbox(_("Weapon Icon"), &Cheat_Private::ESP::WeaponICON);
                    Draw::menu->CustomCheckbox(_("Health Bar"), &Cheat_Private::ESP::Health);
                    Draw::menu->CustomCheckbox(_("Shield Bar"), &Cheat_Private::ESP::Shield);
                    Draw::menu->CustomCheckbox(_("Seern Bar"), &Cheat_Private::ESP::SernEsp);
                    Draw::menu->CustomCheckbox(_("Visibility"), &Cheat_Private::ESP::VisCheck);
                    Draw::menu->CustomCheckbox(_("Glow"), &Cheat_Private::ESP::Glow);
                    Draw::menu->CustomCheckbox(_("OFFArrows"), &Cheat_Private::ESP::OFFArrow);
                    Draw::menu->CustomCheckbox(_("Warning"), &Cheat_Private::ESP::alert);
                    Draw::menu->CustomCheckbox(_("Radar"), &Cheat_Private::ESP::Radar);
                    Draw::menu->CustomCheckbox(_("Radar Name"), &Cheat_Private::ESP::RadarName);
                    Draw::menu->CustomCheckbox(_("Radar TeamID"), &Cheat_Private::ESP::TeamID);
                    Draw::menu->CustomCheckbox(_("Sexy Girl"), &Cheat_Private::ESP::EKitten);
                    Draw::menu->CustomCheckbox(_("Display Spectators"), &Cheat_Private::ESP::DisplaySpectators);
#ifdef developer
        Draw::menu->CustomCheckbox(_("Display Twitch Streamers"), &Cheat_Private::ESP::DisplayTwitchStreamer);
        Draw::menu->CustomCheckbox(_("Display Death Box"), &Cheat_Private::ESP::DisplayDeathBox);
#endif
                    Draw::menu->CustomCheckbox(_("Highlight Team"), &Cheat_Private::ESP::RemoveTeam);
                    Draw::menu->CustomCheckbox(_("Highlight Knocked"), &Cheat_Private::ESP::KnockedDraw);
                    Draw::menu->CustomCheckbox(_("Disable Team"), &Cheat_Private::ESP::Teamcheck);
                    Draw::menu->CustomCheckbox(_("Disable Knocked"), &Cheat_Private::ESP::KnockedCheck);
                }
                ImGui::EndChild();
                ImGui::SameLine();
                ImGui::BeginChild(_("##Vis2"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
                {
                    ImVec2 child_size = ImGui::GetContentRegionAvail();
                    ImVec2 text_size = ImGui::CalcTextSize(_("Settings"));
                    float text_x_pos = (child_size.x - text_size.x) / 2;
                    ImGui::SetCursorPosX(text_x_pos);
                    ImGui::Text(_("Settings"));
                    ImGui::Separator();
                    widget->color_picker(_("Box Color"), Cheat_Private::ESP::BoxColor, true);
                    widget->color_picker(_("Filled Box Color"), Cheat_Private::ESP::FilledBoxColor, true);
                    widget->color_picker(_("Skeleton Color"), Cheat_Private::ESP::SkeletonColor, true);
                    widget->color_picker(_("Snap Line Color"), Cheat_Private::ESP::SnaplineColor, true);
                    widget->color_picker(_("Head Circle Color"), Cheat_Private::ESP::HeadCircleColor, true);
                    widget->color_picker(_("Distance Color"), Cheat_Private::ESP::DistanceColor, true);
                    widget->color_picker(_("Level Color"), Cheat_Private::ESP::LevelColor, true);
                    widget->color_picker(_("Operator Color"), Cheat_Private::ESP::OperatorColor, true);
                    widget->color_picker(_("Weapon Color"), Cheat_Private::ESP::NameColor, true);
                    widget->color_picker(_("Weapon ICON Color"), Cheat_Private::ESP::WeaponIconColor, true);
                    widget->color_picker(_("Name Color"), Cheat_Private::ESP::WeaponColor, true);
                    widget->color_picker(_("OFFArrow Color"), Cheat_Private::ESP::OFFArrowColor, true);
                    widget->color_picker(_("Vis Color"), Cheat_Private::ESP::VisColor, true);
                    widget->color_picker(_("Non-Vis Color"), Cheat_Private::ESP::NonVisColor, true);
                    widget->color_picker(_("Team Color"), Cheat_Private::ESP::TeamColor, true);
                    widget->color_picker(_("Knocked Color"), Cheat_Private::ESP::KnockedColor, true);
                    ImGui::Text(_("Radar Size")); ImGui::SameLine();
                    Draw::menu->CustomSliderFloat(_("Ra"), &Cheat_Private::ESP::RadarSize, 1.0f, 10.0f);
                    ImGui::Text(_("Alpha")); ImGui::SameLine();
                    Draw::menu->CustomSliderFloat(_("Raa"), &Cheat_Private::ESP::transparency, 0.0f, 255.f);
                    ImGui::Text(_("Distance")); ImGui::SameLine();
                    Draw::menu->CustomSliderFloat(_("Draw Dist"), &Cheat_Private::Settings::RenderDistance, 50.f, 1000.f);
                    ImGui::Text(_("OFFArrow")); ImGui::SameLine();
                    Draw::menu->CustomSliderFloat(_("asd off"), &Cheat_Private::ESP::OFFRadius, 1.0f, 100.0f);
                    widget->multi_dropdown(_("Vis Type"), Cheat_Private::ESP::Vistype, Cheat_Private::ESP::VisTypeText, Cheat_Private::ESP::VisTypeText.size());
                    widget->dropdown(_("SnapLine Type"), &Cheat_Private::ESP::SnaplineIndex, Cheat_Private::ESP::SnaplineText, Cheat_Private::ESP::SnaplineText.size());

                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem(_("Aimbot")))
            {
                ImVec2 tab_min = ImGui::GetItemRectMin();
                ImVec2 tab_max = ImGui::GetItemRectMax();
                draw_list->AddLine(ImVec2(tab_min.x, tab_max.y + 2), ImVec2(tab_max.x, tab_max.y + 2), IM_COL32(0, 155, 255, 255), 2.0f);
                ImGui::BeginChild(_("##Aim1"), ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), true);
                {
                    ImVec2 child_size = ImGui::GetContentRegionAvail();
                    ImVec2 text_size = ImGui::CalcTextSize(_("Aimbot"));
                    float text_x_pos = (child_size.x - text_size.x) / 2;
                    ImGui::SetCursorPosX(text_x_pos);
                    ImGui::Text(_("Aimbot"));
                    ImGui::Separator();
                    Draw::menu->CustomCheckbox(_("Aimbot"), &Cheat_Private::Aimbot::VABot);
                    Draw::menu->CustomCheckbox(_("PSilent"), &Cheat_Private::Aimbot::PSilent);
                   //Draw::menu->CustomCheckbox(_("Predication"), &Cheat_Private::Aimbot::Predication);
                   // Draw::menu->CustomCheckbox(_("Auto Fire"), &Cheat_Private::Aimbot::AutoFire);
                    Draw::menu->CustomCheckbox(_("Hard Target Lock"), &Cheat_Private::Aimbot::HardLock);
                    Draw::menu->CustomCheckbox(_("Fov Circle"), &Cheat_Private::Aimbot::FovCircle);
                    Draw::menu->CustomCheckbox(_("Target Line"), &Cheat_Private::Aimbot::Snapline);
                    Draw::menu->CustomCheckbox(_("Disable Tean"), &Cheat_Private::Aimbot::DisableTeam);
                    Draw::menu->CustomCheckbox(_("Disable Knocked"), &Cheat_Private::Aimbot::DisableKnocked);
                    Draw::menu->CustomCheckbox(_("Visibility Check"), &Cheat_Private::Aimbot::VisCheck);
                    ImGui::Text(_("Fov Size")); ImGui::SameLine();
                    Draw::menu->CustomSliderFloat(_("Fov Size"), &Cheat_Private::Aimbot::FovCircleSize, 1.f, 500.f);
                    ImGui::Text(_("Smoothing")); ImGui::SameLine();
                    Draw::menu->CustomSliderFloat(_("Smoothing"), &Cheat_Private::Aimbot::SmoothingAmount, 1.f, 10.f);
                }
                ImGui::EndChild();
                ImGui::SameLine();
                ImGui::BeginChild(_("##Aim2"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
                {
                    ImVec2 child_size = ImGui::GetContentRegionAvail();
                    ImVec2 text_size = ImGui::CalcTextSize(_("Settings"));
                    float text_x_pos = (child_size.x - text_size.x) / 2;
                    ImGui::SetCursorPosX(text_x_pos);
                    ImGui::Text(_("Settings"));
                    ImGui::Separator();
                    widget->dropdown(_("Aimbot Key"), &Cheat_Private::Settings::AimbotKeyINDEX, Cheat_Private::Settings::KeyText, Cheat_Private::Settings::KeyText.size());
                    widget->dropdown(_("Bone"), &Cheat_Private::Aimbot::TargetBone, Cheat_Private::Aimbot::BoneName, Cheat_Private::Aimbot::BoneName.size());
                    widget->color_picker(_("Fov Circle Color"), Cheat_Private::Aimbot::FovCircleColor, true);
                    widget->color_picker(_("Target Line Color"), Cheat_Private::Aimbot::SnaplineColor, true);
                    ImGui::Text(_("Distance")); ImGui::SameLine();
                    Draw::menu->CustomSliderFloat(_("aDis"), &Cheat_Private::Settings::AimbotDistance, 50.f, 1000.f);
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem(_("Misc")))
            {
                ImVec2 tab_min = ImGui::GetItemRectMin();
                ImVec2 tab_max = ImGui::GetItemRectMax();
                draw_list->AddLine(ImVec2(tab_min.x, tab_max.y + 2), ImVec2(tab_max.x, tab_max.y + 2), IM_COL32(0, 155, 255, 255), 2.0f);
                ImGui::BeginChild(_("##Weaposn1"), ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), true);
                {
                    ImVec2 child_size = ImGui::GetContentRegionAvail();
                    ImVec2 text_size = ImGui::CalcTextSize(_("Misc"));
                    float text_x_pos = (child_size.x - text_size.x) / 2;
                    ImGui::SetCursorPosX(text_x_pos);
                    ImGui::Text(_("Misc"));
                    ImGui::Separator();

                    Draw::menu->CustomCheckbox(_("Super-Glide"), &Cheat_Private::Misc::SuperGlide);
                    Draw::menu->CustomCheckbox(_("Super-Grapple"), &Cheat_Private::Misc::AutoGrapple);
                    Draw::menu->CustomCheckbox(_("Third Person"), &Cheat_Private::Misc::Thirdperson);
                    Draw::menu->CustomCheckbox(_("Large Weapon"), &Cheat_Private::Misc::LargeWeapon);
                    Draw::menu->CustomCheckbox(_("Bigger Hitbox (!May Crash Game!)"), &Cheat_Private::Misc::LargePlayers);
                    Draw::menu->CustomCheckbox(_("No Recoil"), &Cheat_Private::Aimbot::RcsControl);
                    Draw::menu->CustomCheckbox(_("Reload Bar"), &Cheat_Private::Misc::ReloadBar);
                    Draw::menu->CustomCheckbox(_("Back Track (RISKY)"), &Cheat_Private::Misc::BackTrack);
              //      Draw::menu->CustomCheckbox(_("Full Auto"), &Cheat_Private::Misc::ForceBullets);
                    Draw::menu->CustomCheckbox(_("Ammo Counter"), &Cheat_Private::Misc::AmmoCounter);
                    Draw::menu->CustomCheckbox(_("Night Mode"), &Cheat_Private::Misc::FullBright);
                    Draw::menu->CustomCheckbox(_("Zoom"), &Cheat_Private::Misc::zoom);
                    Draw::menu->CustomCheckbox(_("Fov Changer"), &Cheat_Private::Misc::FovChanger);
                    Draw::menu->CustomSliderFloat(_("FOV"), &Cheat_Private::Misc::SetFov, 70.f, 150.f);
                    ImGui::SameLine(); ImGui::Text(_("FOV"));
                }
                ImGui::EndChild();
                ImGui::SameLine();
                ImGui::BeginChild(_("##Esxtra"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
                {
                    ImVec2 child_size = ImGui::GetContentRegionAvail();
                    ImVec2 text_size = ImGui::CalcTextSize(_("Extra"));
                    float text_x_pos = (child_size.x - text_size.x) / 2;
                    ImGui::SetCursorPosX(text_x_pos);
                    ImGui::Text(_("Extra"));
                    ImGui::Separator();
                   // CustomCheckbox(_("Player Model Spoof (!May Crash Game!)"), &Cheat_Private::Misc::PlayerModelSpoof);
                  //  CustomCheckbox(_("Cl_data"), &Cheat_Private::Misc::Clfps);
                    Draw::menu->CustomCheckbox(_("Item Glow"), &Cheat_Private::Misc::ItemGlow);
                    Draw::menu->CustomCheckbox(_("Free Cam"), &Cheat_Private::Misc::Freecam);
                   // Draw::menu->CustomCheckbox(_("Fake Duck"), &Cheat_Private::Misc::FakeDuck);
                    Draw::menu->CustomCheckbox(_("Weapon Glow"), &Cheat_Private::Misc::WeaponGlow);
                    Draw::menu->CustomCheckbox(_("Arm Glow"), &Cheat_Private::Misc::HandGlow);
                    Draw::menu->CustomCheckbox(_("Weapon Skin-Changer"), &Cheat_Private::Misc::SkinChanger);
                    Draw::menu->CustomSliderInt(_("WEAPON SKIN ID"), &Cheat_Private::Misc::SkinID, 1, 25);
                    ImGui::SameLine(); ImGui::Text(_("WEAPON"));
                  /*  Draw::menu->CustomCheckbox(_("Character Skin-Changer"), &Cheat_Private::Misc::CharacterSkinChanger);
                    Draw::menu->CustomSliderInt(_("CHARACTER SKIN ID"), &Cheat_Private::Misc::CharacterSkin, 1, 24);
                    ImGui::SameLine(); ImGui::Text(_("CHARACTER"));*/
                    widget->dropdown(_("Super Glide Key"), &Cheat_Private::Misc::SuperGlideIndex, Cheat_Private::Settings::KeyText, Cheat_Private::Settings::KeyText.size());
                    widget->dropdown(_("Third Person Key"), &Cheat_Private::Misc::ThirdPeronIndex, Cheat_Private::Settings::KeyText, Cheat_Private::Settings::KeyText.size());
                  //  widget->dropdown(_("Free Cam Key"), &Cheat_Private::Misc::FreeCamKey, Cheat_Private::Settings::KeyText, Cheat_Private::Settings::KeyText.size());
                    widget->dropdown(_("Fake Duck Key"), &Cheat_Private::Misc::FakeDuckKEY, Cheat_Private::Settings::KeyText, Cheat_Private::Settings::KeyText.size());
                    widget->dropdown(_("Zoom Key"), &Cheat_Private::Misc::zoomindex, Cheat_Private::Settings::KeyText, Cheat_Private::Settings::KeyText.size());
                    widget->dropdown(_("Weapon Glow Type"), &Cheat_Private::Misc::WeaponGlowIndex, Cheat_Private::Misc::WeaponGlowText, Cheat_Private::Misc::WeaponGlowText.size());
                    widget->dropdown(_("Arm Glow Type"), &Cheat_Private::Misc::HandGlowIndex, Cheat_Private::Misc::WeaponGlowText, Cheat_Private::Misc::WeaponGlowText.size());
                }
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
           
            if (ImGui::BeginTabItem(_("Settings")))
            {
                ImVec2 tab_min = ImGui::GetItemRectMin();
                ImVec2 tab_max = ImGui::GetItemRectMax();
                draw_list->AddLine(ImVec2(tab_min.x, tab_max.y + 2), ImVec2(tab_max.x, tab_max.y + 2), IM_COL32(0, 155, 255, 255), 2.0f);
                ImGui::BeginChild(_("##Settings1"), ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y), true);
                {
                    ImVec2 child_size = ImGui::GetContentRegionAvail();
                    ImVec2 text_size = ImGui::CalcTextSize(_("Settings"));
                    float text_x_pos = (child_size.x - text_size.x) / 2;
                    ImGui::SetCursorPosX(text_x_pos);
                    ImGui::Text(_("Settings"));
                    ImGui::Separator();
                    widget->dropdown(_("Font Selection"), &FontList::FontIndex, FontList::FontText, FontList::FontText.size());
                    Draw::menu->CustomCheckbox(_("Text Outline"), &FontList::Outline);
                    Draw::menu->CustomCheckbox(_("Text Background"), &Cheat_Private::Settings::TextBackground);
                    Draw::menu->CustomCheckbox(_("Swastika Cross Hair"), &Cheat_Private::Aimbot::SwastikaCrossHair);
                    Draw::menu->CustomCheckbox(_("WaterMark"), &Cheat_Private::Settings::Watermark);
                    Draw::menu->CustomCheckbox(_("Controller Support"), &Cheat_Private::Settings::ControllerSupport);
                    if (ImGui::Button("Unload"))
                    {
                        HANDLE processHandle = OpenProcess(PROCESS_TERMINATE, FALSE, drv::find_process((_("Medal.exe"))));
                        LI_FN(TerminateProcess)(processHandle, 0);
                        LI_FN(CloseHandle)(processHandle);
                        LI_FN(exit)(0);
                    }
                }
              /*  ImGui::EndChild();
                ImGui::SameLine();
                ImGui::BeginChild(_("##config1"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true); {
                    ImVec2 child_size = ImGui::GetContentRegionAvail();
                    ImVec2 text_size = ImGui::CalcTextSize(_("Config"));
                    float text_x_pos = (child_size.x - text_size.x) / 2;
                    ImGui::SetCursorPosX(text_x_pos);
                    ImGui::Text(_("Config"));

                    widget->dropdown("Config List", &Cheat_Private::Config::ConfigIndex, Cheat_Private::Config::ConfigName, Cheat_Private::Config::ConfigName.size());
                    gui->selection(var->c_selection.selection_icon[0].data(), "Create Config", 1, Cheat_Private::Config::LoadConfig, { GetContentRegionAvail().x, 30 });
                    gui->selection(var->c_selection.selection_icon[1].data(), "Save Config", 2, Cheat_Private::Config::SaveConfig, { GetContentRegionAvail().x, 30 });
                    gui->selection(var->c_selection.selection_icon[0].data(), "Load Config", 3, Cheat_Private::Config::RunConfig, { GetContentRegionAvail().x, 30 });

                }
                ImGui::EndChild();*/
                ImGui::EndTabItem();
            }
            ImGui::PopStyleColor();
        }
        ImGui::End();
        switch (Cheat_Private::Misc::WeaponGlowIndex)
        {
        case 0:
            Cheat_Private::Misc::SelectedGlowIndex = 2;
            break;
        case 1:
            Cheat_Private::Misc::SelectedGlowIndex = 62;
            break;
        case 2:
            Cheat_Private::Misc::SelectedGlowIndex = 77;
            break;
        case 3:
            Cheat_Private::Misc::SelectedGlowIndex = 50;
            break;
        case 4:
            Cheat_Private::Misc::SelectedGlowIndex = 52;
            break;
        case 5:
            Cheat_Private::Misc::SelectedGlowIndex = 31;
            break;
        case 6:
            Cheat_Private::Misc::SelectedGlowIndex = 78;
            break;
        }
        switch (Cheat_Private::Misc::HandGlowIndex)
        {
        case 0:
            Cheat_Private::Misc::SelectedHandGlowIndex = 2;
            break;
        case 1:
            Cheat_Private::Misc::SelectedHandGlowIndex = 62;
            break;
        case 2:
            Cheat_Private::Misc::SelectedHandGlowIndex = 77;
            break;
        case 3:
            Cheat_Private::Misc::SelectedHandGlowIndex = 50;
            break;
        case 4:
            Cheat_Private::Misc::SelectedHandGlowIndex = 52;
            break;
        case 5:
            Cheat_Private::Misc::SelectedHandGlowIndex = 31;
            break;
        case 6:
            Cheat_Private::Misc::SelectedHandGlowIndex = 78;
            break;

        }
        switch (Cheat_Private::Misc::FakeDuckKEY)
        {
        case 0:
            Cheat_Private::Misc::KafeDuckBIND = 0x01;
            break;
        case 1:
            Cheat_Private::Misc::KafeDuckBIND = 0x02;
            break;
        case 2:
            Cheat_Private::Misc::KafeDuckBIND = 0x05;
            break;
        case 3:
            Cheat_Private::Misc::KafeDuckBIND = 0x06;
            break;
        case 4:
            Cheat_Private::Misc::KafeDuckBIND = 0xA4;
            break;
        case 5:
            Cheat_Private::Misc::KafeDuckBIND = 0xA0;
            break;
        }
        switch (Cheat_Private::Misc::FreeCamKey)
        {
        case 0:
            Cheat_Private::Misc::FreeCamBind = 0x01;
            break;
        case 1:
            Cheat_Private::Misc::FreeCamBind = 0x02;
            break;
        case 2:
            Cheat_Private::Misc::FreeCamBind = 0x05;
            break;
        case 3:
            Cheat_Private::Misc::FreeCamBind = 0x06;
            break;
        case 4:
            Cheat_Private::Misc::FreeCamBind = 0xA4;
            break;
        case 5:
            Cheat_Private::Misc::FreeCamBind = 0xA0;
            break;
        }
        switch (Cheat_Private::Misc::SuperGlideIndex)
        {
        case 0:
            Cheat_Private::Misc::SuperGliderkey = 0x01;
            break;
        case 1:
            Cheat_Private::Misc::SuperGliderkey = 0x02;
            break;
        case 2:
            Cheat_Private::Misc::SuperGliderkey = 0x05;
            break;
        case 3:
            Cheat_Private::Misc::SuperGliderkey = 0x06;
            break;
        case 4:
            Cheat_Private::Misc::SuperGliderkey = 0xA4;
            break;
        case 5:
            Cheat_Private::Misc::SuperGliderkey = 0xA0;
            break;
        }
        switch (Cheat_Private::Misc::ThirdPeronIndex)
        {
        case 0:
            Cheat_Private::Misc::ThirdPeronKey = 0x01;
            break;
        case 1:
            Cheat_Private::Misc::ThirdPeronKey = 0x02;
            break;
        case 2:
            Cheat_Private::Misc::ThirdPeronKey = 0x05;
            break;
        case 3:
            Cheat_Private::Misc::ThirdPeronKey = 0x06;
            break;
        case 4:
            Cheat_Private::Misc::ThirdPeronKey = 0xA4;
            break;
        case 5:
            Cheat_Private::Misc::ThirdPeronKey = 0xA0;
            break;
        }
        switch (Cheat_Private::Settings::PSilentKeyIndex)
        {
        case 0:
            Cheat_Private::Aimbot::PSilentKey = 0x01;
            break;
        case 1:
            Cheat_Private::Aimbot::PSilentKey = 0x02;
            break;
        case 2:
            Cheat_Private::Aimbot::PSilentKey = 0x05;
            break;
        case 3:
            Cheat_Private::Aimbot::PSilentKey = 0x06;
            break;
        case 4:
            Cheat_Private::Aimbot::PSilentKey = 0xA4;
            break;
        case 5:
            Cheat_Private::Aimbot::PSilentKey = 0xA0;
            break;
        }
        switch (Cheat_Private::Settings::AimbotKeyINDEX)
        {
        case 0:
            Cheat_Private::Aimbot::AimbotKey = 0x01;
            break;
        case 1:
            Cheat_Private::Aimbot::AimbotKey = 0x02;
            break;
        case 2:
            Cheat_Private::Aimbot::AimbotKey = 0x05;
            break;
        case 3:
            Cheat_Private::Aimbot::AimbotKey = 0x06;
            break;
        case 4:
            Cheat_Private::Aimbot::AimbotKey = 0xA4;
            break;
        case 5:
            Cheat_Private::Aimbot::AimbotKey = 0xA0;
            break;
        }
        switch (Cheat_Private::Aimbot::SkyIndex)
        {
        case 0:
            Cheat_Private::Aimbot::SkyKey = 0x01;
            break;
        case 1:
            Cheat_Private::Aimbot::SkyKey = 0x02;
            break;
        case 2:
            Cheat_Private::Aimbot::SkyKey = 0x05;
            break;
        case 3:
            Cheat_Private::Aimbot::SkyKey = 0x06;
            break;
        case 4:
            Cheat_Private::Aimbot::SkyKey = 0xA4;
            break;
        case 5:
            Cheat_Private::Aimbot::SkyKey = 0xA0;
            break;
        }
        switch (Cheat_Private::Misc::zoomindex)
        {
        case 0:
            Cheat_Private::Misc::zoomkey = 0x01;
            break;
        case 1:
            Cheat_Private::Misc::zoomkey = 0x02;
            break;
        case 2:
            Cheat_Private::Misc::zoomkey = 0x05;
            break;
        case 3:
            Cheat_Private::Misc::zoomkey = 0x06;
            break;
        case 4:
            Cheat_Private::Misc::zoomkey = 0xA4;
            break;
        case 5:
            Cheat_Private::Misc::zoomkey = 0xA0;
            break;
        }
        switch (Cheat_Private::Aimbot::TargetBone) {
        case 0: Cheat_Private::Aimbot::SelectedBone = 0; break;
        case 1: Cheat_Private::Aimbot::SelectedBone = 1; break;
        case 2: Cheat_Private::Aimbot::SelectedBone = 2; break;
        case 3: Cheat_Private::Aimbot::SelectedBone = 3; break;
        }
        switch (Cheat_Private::Loot::BattleIndex)
        {
        case 0:
            Cheat_Private::Loot::BattleKey = 0x01;
            break;
        case 1:
            Cheat_Private::Loot::BattleKey = 0x02;
            break;
        case 2:
            Cheat_Private::Loot::BattleKey = 0x05;
            break;
        case 3:
            Cheat_Private::Loot::BattleKey = 0x06;
            break;
        case 4:
            Cheat_Private::Loot::BattleKey = 0xA4;
            break;
        case 5:
            Cheat_Private::Loot::BattleKey = 0xA0;
            break;
        }

#ifdef developer
   //    // Cheat_Private::ESP::Skeleton = true;
   //     //Cheat_Private::ESP::SkeletonGay = true;
   //     Cheat_Private::ESP::Weapon = true;
   //     Cheat_Private::ESP::VisCheck = true;
   //     Cheat_Private::ESP::Glow = true;
   //     //Cheat_Private::ESP::RemoveTeam = true;
   //     //Cheat_Private::ESP::KnockedDraw = true;
   //     float teamcolor[4] = { 0,0,0,0 };

   //     //Cheat_Private::ESP::TeamColor[0] = 39;
   //     //Cheat_Private::ESP::TeamColor[1] = 126;
   //     //Cheat_Private::ESP::TeamColor[2] = 128;
   //     //
   //     //Cheat_Private::ESP::KnockedColor[0] = 183;
   //     //Cheat_Private::ESP::KnockedColor[1] = 104;
   //     //Cheat_Private::ESP::KnockedColor[2] = 39;

   //     Cheat_Private::ESP::Vistype[3] = true;
   //     Cheat_Private::ESP::Vistype[4] = true;

   //    // Cheat_Private::Aimbot::VABot = true;
   //     //Cheat_Private::Aimbot::DisableTeam = true;
   //     //Cheat_Private::Aimbot::DisableKnocked = true;
   // //    Cheat_Private::Aimbot::VisCheck = true;
   ////     Cheat_Private::Aimbot::VisCheck = true;
   //     Cheat_Private::Aimbot::FovCircleSize = 300.0f;
   //     Cheat_Private::Settings::AimbotKeyINDEX = 3;
#endif

    }
}

ImVec2 RotatePoint(const ImVec2& point, const ImVec2& center, float angle) {
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);
    float dx = point.x - center.x;
    float dy = point.y - center.y;

    return ImVec2(
        cosAngle * dx - sinAngle * dy + center.x,
        sinAngle * dx + cosAngle * dy + center.y
    );
}

auto Overlay::OverlayRender::Draw() -> void {
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.f);

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
   
    if (!FindWindowA(_("Respawn001"), _("Apex Legends"))) {
        HANDLE processHandle = OpenProcess(PROCESS_TERMINATE, FALSE, drv::find_process(_("Medal.exe")));
        LI_FN(TerminateProcess)(processHandle, 0);
        LI_FN(CloseHandle)(processHandle);
        LI_FN(exit)(0);
    }

    if (GetAsyncKeyState(VK_INSERT) & 0x1)
        render_Menu = !render_Menu;

    if (render_Menu)
        doMainMenu();

  
    if (Cheat_Private::Settings::Watermark) {
        std::string displayText;

#ifdef p2c
        displayText += _("XEX | PUB BUILD  ");
#elif developer
        displayText += _("XEX | DEV BUILD  |");
#endif

        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = NULL;

        displayText += _(" FPS : ") + std::to_string((int)io.Framerate) + "  ";
        displayText += (inMatch ? _("| In Match") : _("| Not In Match")) + std::string("  ");
        displayText += _("| Player Count : ") + std::to_string(EntList.size()) + "  | ";

        std::time_t now = std::time(0);
        std::tm* ltm = std::localtime(&now);
        char timeDateStr[30];
        std::strftime(timeDateStr, sizeof(timeDateStr), _("%Y-%m-%d %H:%M:%S"), ltm);

        displayText += timeDateStr;

        Draw::esp->draw_text_outline_font(15, sdk.DisplaySize.y - 25, ImColor(255, 255, 255, 255), displayText.c_str(), .5f);

       // Draw::menu->DrawRotatedImageWithBox(xexTexture, 1, 1, 50, 50);
       
    }
    
    if (Cheat_Private::Aimbot::FovCircle) {
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(sdk.DisplaySize.x / 2, sdk.DisplaySize.y / 2), Cheat_Private::Aimbot::FovCircleSize + 1, ImColor(0, 0, 0, 255), 255.f);
        ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(sdk.DisplaySize.x / 2, sdk.DisplaySize.y / 2), Cheat_Private::Aimbot::FovCircleSize,
            ImColor(Cheat_Private::Aimbot::FovCircleColor[0], Cheat_Private::Aimbot::FovCircleColor[1], Cheat_Private::Aimbot::FovCircleColor[2], 255.f));
    }
   

    if (Cheat_Private::Config::LoadConfig && CreateConfig()) {
        MessageBox(NULL, _("Successfully Created Config"), _("RLBmods Config System"), MB_OK);
        Cheat_Private::Config::LoadConfig = 0;
    }
  

    if (Cheat_Private::ESP::DisplayTwitchStreamer)
    {
        ImGui::SetNextWindowSize(ImVec2(200, 300));
        ImGui::Begin(_("##StreamerList"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse);

        ImVec2 pos = ImGui::GetCursorPos();

        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(_("Streamer List")).x) * 0.5f);
        ImGui::Text(_("Streamer List"));

        ImGui::Spacing();

        pos = ImGui::GetCursorPos();
        ImVec2 lineStart = ImVec2(0, pos.y);
        ImVec2 lineEnd = ImVec2(ImGui::GetWindowWidth(), pos.y);

        ImVec2 windowPos = ImGui::GetWindowPos();
        lineStart += windowPos;
        lineEnd += windowPos;

        ImU32 lineColorStart = IM_COL32(0, 0, 255, 255);
        ImU32 lineColorEnd = IM_COL32(0, 0, 128, 255);

        ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, lineColorStart, 2.0f);
        ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, lineColorEnd, 1.0f);

        ImGui::Spacing();

        for (const auto& Streamer : StreamerList) {
            ImGui::Text(_("%s"), Streamer);
            ImGui::Spacing();
        }

        ImGui::End();

    }
    
    if (Cheat_Private::ESP::DisplaySpectators)
    {
        ImGui::SetNextWindowSize(ImVec2(200, 300));
        ImGui::Begin(_("##SpectatorList"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse);

        ImVec2 pos = ImGui::GetCursorPos();

        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(_("Spectator List")).x) * 0.5f);
        ImGui::Text(_("Spectator List"));

        ImGui::Spacing();

        pos = ImGui::GetCursorPos();
        ImVec2 lineStart = ImVec2(0, pos.y);
        ImVec2 lineEnd = ImVec2(ImGui::GetWindowWidth(), pos.y);

        ImVec2 windowPos = ImGui::GetWindowPos();
        lineStart += windowPos;
        lineEnd += windowPos;

        ImU32 lineColorStart = IM_COL32(0, 0, 255, 255);
        ImU32 lineColorEnd = IM_COL32(0, 0, 128, 255);

        ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, lineColorStart, 2.0f);
        ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, lineColorEnd, 1.0f);

        ImGui::Spacing();

        for (const auto& Spectator : SpectatorList) {
            ImGui::Text(_("%s"), Spectator);
            ImGui::Spacing();
        }

        ImGui::End();
    }
    if (Cheat_Private::Config::SaveConfig) {
        if (SaveConfig()) {
            MessageBox(NULL, _("Successfully Saved Config"), _("XEX Config System"), MB_OK);
        }
        else {
            MessageBox(NULL, _("Failed To Save Config"), _("XEX Config System"), MB_OK);
        }
        Cheat_Private::Config::SaveConfig = 0;
    }

    if (Cheat_Private::Config::RunConfig) {
        if (LoadConfig()) {
            MessageBox(NULL, _("Successfully Loaded Config"), _("XEX Config System"), MB_OK);
        }
        else {
            MessageBox(NULL, _("Failed To Load Config"), _("XEX Config System"), MB_OK);
        }
        Cheat_Private::Config::RunConfig = 0;
    }

    player.RunCheat();
    ImGui::Render();
    const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
    d3d_device_ctx->OMSetRenderTargets(1, &d3d_render_target, nullptr);
    d3d_device_ctx->ClearRenderTargetView(d3d_render_target, clear_color_with_alpha);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    d3d_swap_chain->Present(0, 0);
}