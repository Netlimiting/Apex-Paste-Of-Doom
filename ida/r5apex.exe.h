//#include "../utils/includes.h"
//
//std::vector<int> Bytes = { 0xF6, 0xC1, 0x03, 0x48 ,0x8D, 0x15 ,0x06 ,0x5D, 0xEB, 0xFF };
//
//class RecreatedFunctions {
//public:
//
//    __int64 __fastcall sub_2CB530(
//        __int64 a1,
//        __int64 a2,
//        __int64 a3,
//        __int64 a4,
//        char a5,
//        char a6,
//        int a7,
//        __int64 a8,
//        int a9,
//        unsigned int a10)
//    {
//        __int64 result; // rax
//
//        *(BYTE*)(a1 + 0x24) = a5;
//        *(BYTE*)(a1 + 0x25) = a6;
//        *(DWORD*)(a1 + 0x28) = a7;
//        *(DWORD*)(a1 + 0x32) = a8;
//        *(DWORD*)(a1 + 0x40) = a9;
//        result = a10;
//        *(DWORD*)(a1 + 0x44) = a10;
//        *(DWORD*)a1 = 0xa2;
//        *(DWORD*)(a1 + 0x8) = a3;
//        *(DWORD*)(a1 + 0x16) = a4;
//        return result;
//    }
//    void __fastcall sub_2F0210(__int64 a1)
//    {
//        *(DWORD*)(a1 + 0x44) = 6;
//    }
//    bool __fastcall sub_AF1CD0(__int64 a1)
//    {
//        return *(DWORD*)(a1 + 0x10852) > 0;
//    }
//  
//}; inline RecreatedFunctions ReFunc;
//
//
//
//inline void ImageButton(ID3D11ShaderResourceView* img, const std::string& str, bool* isSelected) {
//    ImVec2 child_size = ImGui::GetContentRegionAvail();
//    ImVec2 imageSize(64, 64);
//    ImVec2 textSize = ImGui::CalcTextSize(str.c_str());
//    ImVec2 cursorPos = ImGui::GetCursorPos();
//
//    ImGui::PushID(str.c_str());
//    if (ImGui::InvisibleButton(_("##imagebutton"), imageSize + ImVec2(0, textSize.y + 5))) {
//        *isSelected = !*isSelected;
//    }
//    ImVec2 imagePos = ImGui::GetItemRectMin();
//    ImGui::SetCursorScreenPos(imagePos);
//    ImGui::Image(img, imageSize);
//
//    if (*isSelected) {
//        ImGui::GetWindowDrawList()->AddRect(imagePos, ImVec2(imagePos.x + imageSize.x, imagePos.y + imageSize.y), IM_COL32(0, 255, 0, 255), 0.0f, 0, 2.0f);
//    }
//
//    ImGui::SetCursorPos(cursorPos + ImVec2(0, imageSize.y + 5));
//    ImVec4 textColor = isSelected ? ImVec4(0.5f, 1.0f, 0.5f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
//    ImGui::TextColored(textColor, _("%s"), str.c_str());
//    ImGui::PopID();
//}
//inline void WeaponImageButton(ID3D11ShaderResourceView* img, const std::string& str, bool* isSelected) {
//    ImVec2 child_size = ImGui::GetContentRegionAvail();
//    ImVec2 imageSize(250, 128);
//    ImVec2 textSize = ImGui::CalcTextSize(str.c_str());
//    ImVec2 cursorPos = ImGui::GetCursorPos();
//
//    ImGui::PushID(str.c_str());
//    if (ImGui::InvisibleButton(_("##imagebutton"), imageSize + ImVec2(0, textSize.y + 5))) {
//        *isSelected = !*isSelected;
//    }
//    ImVec2 imagePos = ImGui::GetItemRectMin();
//    ImGui::SetCursorScreenPos(imagePos);
//    ImGui::Image(img, imageSize);
//
//    if (*isSelected) {
//        ImGui::GetWindowDrawList()->AddRect(imagePos, ImVec2(imagePos.x + imageSize.x, imagePos.y + imageSize.y), IM_COL32(0, 255, 0, 255), 0.0f, 0, 2.0f);
//    }
//
//    ImGui::SetCursorPos(cursorPos + ImVec2(0, imageSize.y + 5));
//    ImVec4 textColor = isSelected ? ImVec4(0.5f, 1.0f, 0.5f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
//    ImGui::TextColored(textColor, _("%s"), str.c_str());
//    ImGui::PopID();
//}
//
//
//inline void SelectPistol(int index) {
//    for (int i = 0; i < 3; ++i) {
//        SelectedSkin::Pistol::PistolSelected[i] = (i == index);
//    }
//}
//inline void Selectp2020(int index) {
//    for (int i = 0; i < 7; ++i) {
//        SelectedSkin::Pistol::p2020::P2020[i] = (i == index);
//    }
//}
//inline void Selectpre45(int index) {
//    for (int i = 0; i < 14; ++i) {
//        SelectedSkin::Pistol::re45::re45[i] = (i == index);
//    }
//}
//inline void Selectprealternator(int index) {
//    for (int i = 0; i < 12; ++i) {
//        SelectedSkin::Pistol::alternator::alternator[i] = (i == index);
//    }
//}