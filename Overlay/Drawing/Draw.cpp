#include "Draw.hpp"
#include "../../imgui/imgui_internal.h"

void Draw::ESP::AddLine(ImVec2 pos, ImVec2 size, ImU32 color, float thickness)
{
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();

	ImU32 outlineColor = IM_COL32(0, 0, 0, 255);
	float outlineThickness = thickness + 2.0f;

	//drawList->AddLine(pos, size, outlineColor, outlineThickness);
	drawList->AddLine({ pos.x, pos.y  }, {size.x, size.y}, ImColor(0, 0, 0, 255), thickness + 0.5);
	drawList->AddLine(pos, size, color, thickness);
}



void Draw::ESP::DrawCorneredBox(int X, int Y, int W, int H, const ImU32& color, int thickness)
{
	float lineW = (W / 3);
	float lineH = (H / 3);



	// Enhanced corner lines with some extra length
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X - 1, Y), ImVec2(X - 1, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X - 1, Y), ImVec2(X + lineW, Y - 1), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y - 1), ImVec2(X + W + 1, Y - 1), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W + 1, Y), ImVec2(X + W + 1, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X - 1, Y + H - lineH), ImVec2(X - 1, Y + H + 1), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X - 1, Y + H + 1), ImVec2(X + lineW, Y + H + 1), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y + H + 1), ImVec2(X + W + 1, Y + H + 1), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W + 1, Y + H - lineH), ImVec2(X + W + 1, Y + H + 1), ImGui::GetColorU32(color), thickness);
}
void Draw::ESP::DeathBox(int X, int Y, int W, int H, const ImU32& color, int thickness)
{

	float lineW = (W / 3);
	float lineH = (H / 3);
	float radius = 5.0f;  // Radius for rounded corners

	// Outer black outline for contrast
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(X - 1, Y - 1), ImVec2(X + W + 1, Y + H + 1), ImColor(0, 0, 0, 255), radius, ImDrawFlags_RoundCornersAll, thickness + 2);

	// Rounded corners
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(X, Y), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), radius, ImDrawFlags_RoundCornersAll, thickness);

	// Slits on the edges
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + lineH), ImVec2(X, Y + H - lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y + lineH), ImVec2(X + W, Y + H - lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + lineW, Y), ImVec2(X + W - lineW, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + lineW, Y + H), ImVec2(X + W - lineW, Y + H), ImGui::GetColorU32(color), thickness);

	// Slits along the sides (horizontal)
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + lineW, Y), ImVec2(X + lineW + 2, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W - lineW - 2, Y + H), ImGui::GetColorU32(color), thickness);

	// Slits along the sides (vertical)
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + lineH), ImVec2(X + W, Y + lineH + 2), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X + W, Y + H - lineH - 2), ImGui::GetColorU32(color), thickness);
}
void Draw::ESP::DrawFilledBox(int X, int Y, int W, int H, const ImU32& color, int thickness)
{
	float lineW = (W / 3);
	float lineH = (H / 3);
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(X, Y), ImVec2(X + W, Y + H), static_cast<int>(color));
}

void Draw::ESP::DrawBox(int X, int Y, int W, int H, const ImU32 color, int thickness) {
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y + H), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X, Y), ImGui::GetColorU32(color), thickness);
}
void Draw::ESP::AddHexagon(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	ImGui::GetBackgroundDrawList()->PathLineTo(p1);
	ImGui::GetBackgroundDrawList()->PathLineTo(p2);
	ImGui::GetBackgroundDrawList()->PathLineTo(p3);
	ImGui::GetBackgroundDrawList()->PathLineTo(p4);
	ImGui::GetBackgroundDrawList()->PathLineTo(p5);
	ImGui::GetBackgroundDrawList()->PathLineTo(p6);

	ImGui::GetBackgroundDrawList()->PathStroke(col, true, thickness);
}
void Draw::ESP::AddHexagonFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	ImGui::GetBackgroundDrawList()->PathLineTo(p1);
	ImGui::GetBackgroundDrawList()->PathLineTo(p2);
	ImGui::GetBackgroundDrawList()->PathLineTo(p3);
	ImGui::GetBackgroundDrawList()->PathLineTo(p4);
	ImGui::GetBackgroundDrawList()->PathLineTo(p5);
	ImGui::GetBackgroundDrawList()->PathLineTo(p6);
	ImGui::GetBackgroundDrawList()->PathFillConvex(col);
}
void Draw::ESP::DrawQuadFilled(ImVec2 p1, ImVec2 p2, ImVec2 p3, ImVec2 p4, ImColor color) {
	ImGui::GetBackgroundDrawList()->AddQuadFilled(p1, p2, p3, p4, color);
}
void Draw::ESP::DrawHexagon(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col, float thickness)
{
	AddHexagon(p1, p2, p3, p4, p5, p6, col, thickness);
}
void Draw::ESP::DrawHexagonFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col)
{
	AddHexagonFilled(p1, p2, p3, p4, p5, p6, col);
}
void Draw::ESP::SeerHealth(float x, float y, int shield, int max_shield, int armorType, int health) {
	// Adjusted sizes and offsets for a smaller and more compact appearance
	int bg_offset = 1;  // Smaller offset for background hexagon
	int bar_width = 80;  // Smaller width for the health bar
	float max_health = 100.0f;
	float shield_step = 25.0f;

	int shield_25 = 15;  // Adjusted size for shield segments to fit within the background
	int steps = 5;

	// Smaller hexagon background to fit the new sizes
	ImVec2 bg1(x - bar_width / 2 - bg_offset, y);
	ImVec2 bg2(bg1.x - 4, bg1.y - 8);
	ImVec2 bg3(bg2.x + 3, bg2.y - 3);
	ImVec2 bg4(bg3.x + bar_width + bg_offset - 1, bg3.y);  // Adjusted to fit shield bars
	ImVec2 bg5(bg4.x + 6, bg4.y + 10);
	ImVec2 bg6(x + bar_width / 2 + bg_offset - 1, y);  // Adjusted to fit shield bars
	DrawHexagonFilled(bg1, bg2, bg3, bg4, bg5, bg6, ImColor(0, 0, 0, 180));  // Slightly more transparent background

	// Health bar - reduced size to fit the background
	ImVec2 h1(bg1.x + 2, bg1.y - 2);
	ImVec2 h2(h1.x - 3, h1.y - 4);
	ImVec2 h3(h2.x + (float)health / max_health * bar_width, h2.y);
	ImVec2 h4(h1.x + (float)health / max_health * bar_width, h1.y);
	ImVec2 h3m(h2.x + bar_width, h2.y);
	ImVec2 h4m(h1.x + bar_width, h1.y);
	DrawQuadFilled(h1, h2, h3m, h4m, ImColor(20, 20, 50, 100));  // Darker shadow effect
	DrawQuadFilled(h1, h2, h3, h4, ImColor(0, 255, 0, 255));  // Bright green for health

	// Shield bar colors
	ImColor shieldCracked(97, 97, 97);
	ImColor shieldCol;

	// Assign shield color based on armor type
	switch (armorType) {
	case 1:  // White
		shieldCol = ImColor(247, 247, 247);
		break;
	case 2:  // Blue
		shieldCol = ImColor(39, 178, 255);
		break;
	case 3:  // Purple
		shieldCol = ImColor(206, 59, 255);
		break;
	case 4:  // Gold
		shieldCol = ImColor(255, 255, 79);
		break;
	case 5:  // Red
		shieldCol = ImColor(219, 2, 2);
		break;
	default:  // Default to white
		shieldCol = ImColor(247, 247, 247);
	}

	// Adjust shield bar segments to match the health bar length
	int shieldRemaining = shield;
	for (int i = 0; i < 5; ++i) {
		float segmentWidth = (float)bar_width / steps;  // Divide bar width evenly for shield segments
		ImVec2 s1(h2.x + i * (segmentWidth + 1), h2.y - 2);
		ImVec2 s2(s1.x - 2, s1.y - 3);
		float shieldLength = (float)min(shieldRemaining, 25) / shield_step * segmentWidth;
		ImVec2 s3(s2.x + shieldLength, s2.y);
		ImVec2 s4(s1.x + shieldLength, s1.y);
		ImVec2 s3m(s2.x + segmentWidth, s2.y);
		ImVec2 s4m(s1.x + segmentWidth, s1.y);

		if (shieldRemaining < 25) {
			DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);  // Draw cracked if not full
		}
		if (shieldRemaining > 0) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);  // Draw filled shield
		}
		shieldRemaining -= 25;
	}
}

void Draw::ESP::draw_text_outline_font(float x, float y, ImColor color, const char* string, float size) {
	char buf[512];
	ImVec2 len = ImGui::CalcTextSize(string);
	

	ImFont* Font = NULL;
	switch (FontList::FontIndex)
	{
	//{ "Arial", "Calibri", "Ebrima", "Franklin Gothic", "Pixel" };

	case 0: // arial
		Font = FontList::Arial;
		FontList::FontSize = 17.0f;
		break;
	case 1: // Calibri
		Font = FontList::Calibri;
		FontList::FontSize = 17.0f;
		break;
	case 2: // Ebrima
		Font = FontList::Ebrima;
		FontList::FontSize = 17.0f;
		break;
	case 3: // Franklin
		Font = FontList::Franklin_Gothic;
		FontList::FontSize = 17.0f;
		break;
	case 4: // Pixel
		Font = FontList::Pixel;
		FontList::FontSize = 20.0f;
		break;
	case 5: // Consola
		Font = FontList::consola;
		FontList::FontSize = 17.0f;
		break;
	case 6: // verdana
		Font = FontList::verdana;
		FontList::FontSize = 17.0f;
		break;
	}
	size = 1.f;
	ImVec2 text_size = ImGui::CalcTextSize(string);
	if (Cheat_Private::Settings::TextBackground)
	{
		ImVec2 rect_min(x - size, y - size);
		ImVec2 rect_max(x + text_size.x + size, y + text_size.y + size);

		ImGui::GetBackgroundDrawList()->AddRectFilled(rect_min, rect_max, ImColor(0.1f, 0.1f, 0.1f, 0.8f)); // Adjust alpha for transparency
	}
	if (FontList::Outline)
	{
		ImGui::GetBackgroundDrawList()->AddText(Font, FontList::FontSize , ImVec2(x - size, y), ImColor(0.0f, 0.0f, 0.0f, 255.f), string);
		ImGui::GetBackgroundDrawList()->AddText(Font, FontList::FontSize , ImVec2(x + size, y), ImColor(0.0f, 0.0f, 0.0f, 255.f), string);
		ImGui::GetBackgroundDrawList()->AddText(Font, FontList::FontSize , ImVec2(x, y - size ), ImColor(0.0f, 0.0f, 0.0f, 255.f), string);
		ImGui::GetBackgroundDrawList()->AddText(Font, FontList::FontSize, ImVec2(x, y + size), ImColor(0.0f, 0.0f, 0.0f, 255.f), string);

	}
	
	ImGui::GetBackgroundDrawList()->AddText(Font, FontList::FontSize, ImVec2(x, y), color, string);

}
void Draw::ESP::draw_text_outline_wFont(ImFont* font, float size, float x, float y, ImColor color, const char* string) {
	char buf[512];
	ImVec2 len = ImGui::CalcTextSize(string);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(x - 1, y), ImColor(0.0f, 0.0f, 0.0f, 255.f), string);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1, y), ImColor(0.0f, 0.0f, 0.0f, 255.f), string);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y - 1), ImColor(0.0f, 0.0f, 0.0f, 255.f), string);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y + 1), ImColor(0.0f, 0.0f, 0.0f, 255.f), string);

	ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y), color, string);

}
void Draw::ESP::DrawRoundBox(int x, int y, int w, int z, const ImU32 color, int Roundess) {
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(w, z), color, Roundess);
}
void Draw::ESP::HealthBar(ImVec2 Botton, float height, float health)
{
	float width = (float(height) / 2) * (float(health) / 100);
	ImColor HealthCol;

	if (health > 75)
	{
		HealthCol = { 0,255,0,255 };
	}
	else if (health > 45)
	{
		HealthCol = { 255, 99,0,255 };
	}
	else {
		HealthCol = { 255,0,0,255 };

	}
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(Botton.x - height / 4 - 2, Botton.y + 3 - 2), ImVec2(Botton.x + height / 4 + 2, Botton.y + 9 + 2), ImColor(0, 0, 0)); // black outline
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(Botton.x - height / 4, Botton.y + 3), ImVec2(Botton.x + height / 4, Botton.y + 9), ImColor(28, 28, 28)); // grey background
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(Botton.x - height / 4 , Botton.y + 3), ImVec2((Botton.x - height / 4 ) + width, Botton.y + 9), HealthCol); // green health bar
	
}
void Draw::ESP::ShieldBar(ImVec2 Botton, float height, int Shield, int type, bool EnableHealth)
{
		
	int shield = Shield;
	float width = (float(height) / 2) * (float(shield) / 125);
	bool draw = true;
	int shieldType = type;
	ImColor color;
	if (shieldType == 5)
	{
		color = ImColor(200, 15, 50);
	}
	else if (shieldType == 4)
	{
		color = ImColor(205, 195, 50);
	}
	else if (shieldType == 3)
	{
		color = ImColor(150, 65, 245);
	}
	else if (shieldType == 2)
	{
		color = ImColor(25, 115, 175);
	}
	else if (shieldType == 1)
	{
		color = ImColor(215, 215, 215);
	}
	else
	{
		draw = false;
	}

	if (draw)
	{
		if (EnableHealth)
		{
			ImGui::GetBackgroundDrawList()->AddRect(ImVec2(Botton.x - height / 4 - 1, Botton.y + 12 - 1), ImVec2(Botton.x + height / 4 + 1, Botton.y + 18 + 1), ImColor(0, 0, 0)); // black outline
			ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(Botton.x - height / 4, Botton.y + 12), ImVec2(Botton.x + height / 4, Botton.y + 18), ImColor(10, 10, 10)); // grey background
			ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(Botton.x - height / 4, Botton.y + 12), ImVec2((Botton.x - height / 4) + width, Botton.y + 18), color); // shield bar
		}
		else
		{
			ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(Botton.x - height / 4 - 2, Botton.y + 3 - 2), ImVec2(Botton.x + height / 4 + 2, Botton.y + 9 + 2), ImColor(0, 0, 0)); // black outline
			ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(Botton.x - height / 4, Botton.y + 3), ImVec2(Botton.x + height / 4, Botton.y + 9), ImColor(28, 28, 28)); // grey background
			ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(Botton.x - height / 4, Botton.y + 3), ImVec2((Botton.x - height / 4) + width, Botton.y + 9), color); // green health bar
		}
	}
}
void Draw::ESP::HealthBarOutline (ImVec2 Head, ImVec2 Org, int height, int width, float health)
{
	int healthBarYOffset = ((int)(height * health * 0.01f));

	float red = (255.f - (health * 2.55f)) - 100.f;
	float green = (health * 2.55f) / 100.f;

	ImGui::GetBackgroundDrawList()->AddRectFilled({ Head.x - (width + 2.f) - 5, Org.y - height  }, { Head.x - (width) - 10, Org.y }, ImColor(0.f, 0.f, 0.f, 1.f));
	ImGui::GetBackgroundDrawList()->AddRectFilled({ Head.x - (width + 2.f) - 5, Org.y - healthBarYOffset }, { Head.x - (width) - 10 , Org.y  }, ImColor(red, green, 0.f, 1.f));
}
void Draw::ESP::HealthBarRound(ImVec2 Head, ImVec2 Org, int height, int width, float health)
{
	int healthBarYOffset = ((int)(height * health * 0.01f));

	float red = (255.f - (health * 2.55f)) - 100.f;
	float green = (health * 2.55f) / 100.f;

	DrawRoundBox( Head.x - (width + 2.f), Org.y - height ,  Head.x - (width + 4.5f), Org.y , ImColor(0.f, 0.f, 0.f, 0.3f),5);
	DrawRoundBox( Head.x - (width + 2.f), Org.y - healthBarYOffset ,  Head.x - (width + 4.5f), Org.y , ImColor(red, green, 0.f, 1.f),5);
}
void Draw::ESP::arc(float x, float y, float radius, float min_angle, float max_angle, ImColor col, float thickness) {

	//author : https://www.unknowncheats.me/forum/counterstrike-global-offensive/408826-cool-looking-oof-arrows.html

	ImGui::GetBackgroundDrawList()->PathArcTo(ImVec2(x, y), radius, DEG2RAD(min_angle), DEG2RAD(max_angle), 32);
	ImGui::GetBackgroundDrawList()->PathStroke(ImU32(col), false, thickness);
}

bool Draw::Menu::Didclick()
{
	if (GetAsyncKeyState(VK_RIGHT)&0x1)
		return true;
	else
		return false;
}
void Draw::Menu::GetIndex()
{
	if (GetAsyncKeyState(VK_DOWN)&0x1) // +1
		CurrentIndex += 1;
	else if (GetAsyncKeyState(VK_UP)&0x1) // -1
		CurrentIndex -= 1;
}
void Draw::Menu::Title(int index, const char* str, ImColor Color) {
	if (index == CurrentIndex)
		CurrentIndex += 1;
	draw_text_outline_font(Position.x + 125, Position.y + 75, Color, str,2);
}
void Draw::Menu::CreateMenu()
{
	ImVec2 P1, P2;
	ImDrawList* pDrawList;
	const auto& CurrentWindowPos = ImGui::GetWindowPos();
	const auto& pWindowDrawList = ImGui::GetBackgroundDrawList();
	const auto& pBackgroundDrawList = ImGui::GetBackgroundDrawList();
	const auto& pForegroundDrawList = ImGui::GetBackgroundDrawList();

	P1 = ImVec2(10.000f, 25.000f);
	P1.x += CurrentWindowPos.x;
	P1.y += CurrentWindowPos.y;
	P2 = ImVec2(250.000f, 275.000f);
	P2.x += CurrentWindowPos.x;
	P2.y += CurrentWindowPos.y;
	pDrawList = pWindowDrawList;
	pDrawList->AddRectFilledMultiColor(P1, P2,
		ImColor(0.000f, 1.000f, 0.859f, 1.000f),
		ImColor(0.000f, 1.000f, 0.857f, 1.000f),
		ImColor(1.000f, 0.000f, 0.675f, 1.000f),
		ImColor(1.000f, 0.000f, 0.675f, 1.000f));

	P1 = ImVec2(11.000f, 26.000f);
	P1.x += CurrentWindowPos.x;
	P1.y += CurrentWindowPos.y;
	P2 = ImVec2(249.000f, 274.000f);
	P2.x += CurrentWindowPos.x;
	P2.y += CurrentWindowPos.y;
	pDrawList = pWindowDrawList;
	pDrawList->AddRectFilled(P1, P2, ImColor(0.100f, 0.100f, 0.100f, 1.000f), 0.000f);
}
void Draw::Menu::CreateExtendedMenu() {
	ImVec2 P1, P2;
	ImDrawList* pDrawList;
	const auto& CurrentWindowPos = ImGui::GetWindowPos();
	const auto& pWindowDrawList = ImGui::GetBackgroundDrawList();
	const auto& pBackgroundDrawList = ImGui::GetBackgroundDrawList();
	const auto& pForegroundDrawList = ImGui::GetBackgroundDrawList();

	P1 = ImVec2(10.000f, 25.000f);
	P1.x += CurrentWindowPos.x;
	P1.y += CurrentWindowPos.y;
	P2 = ImVec2(250.000f, 651.000f);
	P2.x += CurrentWindowPos.x;
	P2.y += CurrentWindowPos.y;
	pDrawList = pWindowDrawList;
	pDrawList->AddRectFilledMultiColor(P1, P2,
		ImColor(0.000f, 1.000f, 0.859f, 1.000f),
		ImColor(0.000f, 1.000f, 0.857f, 1.000f),
		ImColor(1.000f, 0.000f, 0.675f, 1.000f),
		ImColor(1.000f, 0.000f, 0.675f, 1.000f));

	P1 = ImVec2(11.000f, 26.000f);
	P1.x += CurrentWindowPos.x;
	P1.y += CurrentWindowPos.y;
	P2 = ImVec2(249.000f, 650.000f);
	P2.x += CurrentWindowPos.x;
	P2.y += CurrentWindowPos.y;
	pDrawList = pWindowDrawList;
	pDrawList->AddRectFilled(P1, P2, ImColor(0.100f, 0.100f, 0.100f, 1.000f), 0.000f);
}
void Draw::Menu::CreateTab(int Index, bool& Clicked, const char* str) {
	if (Index == CurrentIndex)
	{
		draw_text_outline_font(Position.x + 75, Position.y + (Index * 25) + 100, ImColor(0, 255, 25, 255), str,2);

		if (Didclick())
			Clicked = !Clicked;
	}
	else
		draw_text_outline_font(Position.x + 75, Position.y + (Index * 25) + 100, ImColor(255, 255, 255, 255), str,2);
}
void Draw::Menu::Checkbox(int Index, bool& value, const char* str) {
	std::string Text = str;
	if (Index == CurrentIndex)
	{
		if (Didclick())
			value = !value;

		if (value)
			Text = "-> " + std::string(str) + " [+]";
		else
			Text = "-> " + std::string(str) + " [-]";
		
		draw_text_outline_font(Position.x + 75, Position.y + (Index * 25) + 100, ImColor(255, 255, 255, 255), Text.c_str(),2);
	}
	else
	{
		if (value)
			Text =  std::string(str) + " [+]";
		else
			Text =  std::string(str) + " [-]";
		draw_text_outline_font(Position.x + 75, Position.y + (Index * 25) + 100, ImColor(255, 255, 255, 255), Text.c_str(),2);
	}
}
void Draw::Menu::Text(int Index, const char* str) {
	std::string Text = str;	
	draw_text_outline_font(Position.x + 75, Position.y + (Index * 25) + 100, ImColor(255, 255, 255, 255), Text.c_str(),2);
}
bool Draw::Menu::CheckIndex(int MaxIndex) {
	if (CurrentIndex > MaxIndex || CurrentIndex < 1)
		return true;
	else
		return false;
}

void Draw::Menu::DrawRotatedImageWithBoxColor(ImTextureID textureID, float x, float y, float width, float height, ImColor tintColor)
{
	// Calculate the center point of the rectangle
	ImVec2 center = ImVec2(x + width * 0.5f, y + height * 0.5f);

	// Calculate the rotation angle (180 degrees)
	float angle = 3.14159265359f; // 180 degrees in radians

	// Calculate the transformation matrix for rotation
	ImVec2 rotationMatrix[2] = {
		ImVec2(cos(angle), -sin(angle)), // Adjusted to avoid flipping
		ImVec2(sin(angle), cos(angle))   // Adjusted to avoid flipping
	};

	// Function to calculate rotated coordinates
	auto calculateRotatedCoordinates = [&](ImVec2 point) -> ImVec2 {
		return ImVec2(
			center.x + rotationMatrix[0].x * (point.x - center.x) + rotationMatrix[0].y * (point.y - center.y),
			center.y + rotationMatrix[1].x * (point.x - center.x) + rotationMatrix[1].y * (point.y - center.y)
		);
		};

	// Original top-left and bottom-right coordinates
	ImVec2 topLeft = ImVec2(x, y);
	ImVec2 bottomRight = ImVec2(x + width, y + height);

	// Calculate rotated coordinates for the main image
	ImVec2 rotatedTopLeft = calculateRotatedCoordinates(topLeft);
	ImVec2 rotatedBottomRight = calculateRotatedCoordinates(bottomRight);

	// Outline offsets
	ImVec2 offset[8] = {
	ImVec2(-1, -1), ImVec2(1, -1), ImVec2(-1, 1), ImVec2(1, 1), // Diagonals
	ImVec2(-1, 0), ImVec2(1, 0), ImVec2(0, -1), ImVec2(0, 1)   // Sides
	};

	// Draw outline by rendering the image 8 times with a small offset in black
	for (int i = 0; i < 8; i++) {
		ImVec2 outlineTopLeft = ImVec2(rotatedTopLeft.x + offset[i].x, rotatedTopLeft.y + offset[i].y);
		ImVec2 outlineBottomRight = ImVec2(rotatedBottomRight.x + offset[i].x, rotatedBottomRight.y + offset[i].y);
		ImGui::GetBackgroundDrawList()->AddImage(textureID, outlineTopLeft, outlineBottomRight, ImVec2(0, 0), ImVec2(1, 1), IM_COL32(0, 0, 0, 255));
	}

	// Draw the actual rotated image
	ImGui::GetBackgroundDrawList()->AddImage(textureID, rotatedTopLeft, rotatedBottomRight, ImVec2(0, 0), ImVec2(1, 1), ImGui::ColorConvertFloat4ToU32(tintColor));

}

void Draw::Menu::DrawRotatedImageWithBox(ImTextureID textureID, float x, float y, float width, float height)
{
	// Calculate the center point of the rectangle
	ImVec2 center = ImVec2(x + width * 0.5f, y + height * 0.5f);

	// Calculate the rotation angle (180 degrees)
	float angle = 3.14159265359f; // 180 degrees in radians

	// Calculate the transformation matrix for rotation
	ImVec2 rotationMatrix[2] = {
		ImVec2(cos(angle), -sin(angle)), // Adjusted to avoid flipping
		ImVec2(sin(angle), cos(angle))   // Adjusted to avoid flipping
	};

	// Rotate the texture
	ImVec2 rotatedTopLeft = ImVec2(
		center.x + rotationMatrix[0].x * (x - center.x) + rotationMatrix[0].y * (y - center.y),
		center.y + rotationMatrix[1].x * (x - center.x) + rotationMatrix[1].y * (y - center.y)
	);

	ImVec2 rotatedBottomRight = ImVec2(
		center.x + rotationMatrix[0].x * ((x + width) - center.x) + rotationMatrix[0].y * ((y + height) - center.y),
		center.y + rotationMatrix[1].x * ((x + width) - center.x) + rotationMatrix[1].y * ((y + height) - center.y)
	);

	// Outline offsets
	ImVec2 offset[8] = {
	ImVec2(-1, -1), ImVec2(1, -1), ImVec2(-1, 1), ImVec2(1, 1), // Diagonals
	ImVec2(-1, 0), ImVec2(1, 0), ImVec2(0, -1), ImVec2(0, 1)   // Sides
	};

	// Draw outline by rendering the image 8 times with a small offset in black
	for (int i = 0; i < 8; i++) {
		ImVec2 outlineTopLeft = ImVec2(rotatedTopLeft.x + offset[i].x, rotatedTopLeft.y + offset[i].y);
		ImVec2 outlineBottomRight = ImVec2(rotatedBottomRight.x + offset[i].x, rotatedBottomRight.y + offset[i].y);
		ImGui::GetBackgroundDrawList()->AddImage(textureID, outlineTopLeft, outlineBottomRight, ImVec2(0, 0), ImVec2(1, 1), IM_COL32(0, 0, 0, 255));
	}
	// Draw the rotated image
	ImGui::GetBackgroundDrawList()->AddImage(textureID, rotatedTopLeft, rotatedBottomRight);
}
void Draw::Menu::CustomSliderFloat(const char* label, float* v, float v_min, float v_max, const char* format)
{
	ImGui::PushID(label);

	ImGui::SliderFloat(_(""), v, v_min, v_max, format);

	ImVec2 sliderPos = ImGui::GetItemRectMin();
	ImVec2 sliderSize = ImGui::GetItemRectSize();

	float fillWidth = (sliderSize.x - 2) * ((*v - v_min) / (v_max - v_min));

	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	draw_list->AddRectFilled(
		ImVec2(sliderPos.x + 1, sliderPos.y + 1),
		ImVec2(sliderPos.x + 1 + fillWidth, sliderPos.y + sliderSize.y - 1),
		IM_COL32(0, 155, 255, 255) // Purple color
	);

	draw_list->AddRect(
		ImVec2(sliderPos.x, sliderPos.y),
		ImVec2(sliderPos.x + sliderSize.x, sliderPos.y + sliderSize.y),
		IM_COL32(255, 255, 255, 255) // White color
	);

	char numberText[64];
	snprintf(numberText, sizeof(numberText), format, *v);
	ImVec2 textSize = ImGui::CalcTextSize(numberText);
	ImVec2 numberPos = ImVec2(sliderPos.x + sliderSize.x / 2 - textSize.x / 2, sliderPos.y + sliderSize.y / 2 - textSize.y / 2);
	draw_list->AddText(numberPos, IM_COL32(255, 255, 255, 255), numberText);

	ImGui::PopID();
}
void Draw::Menu::CustomSliderInt(const char* label, int* v, int v_min, int v_max, const char* format)
{
	ImGui::PushID(label);

	ImGui::SliderInt("", v, v_min, v_max, format);

	ImVec2 sliderPos = ImGui::GetItemRectMin();
	ImVec2 sliderSize = ImGui::GetItemRectSize();

	float fillWidth = (sliderSize.x - 2) * ((float)(*v - v_min) / (float)(v_max - v_min));

	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	draw_list->AddRectFilled(
		ImVec2(sliderPos.x + 1, sliderPos.y + 1),
		ImVec2(sliderPos.x + 1 + fillWidth, sliderPos.y + sliderSize.y - 1),
		IM_COL32(0, 155, 255, 255)
	);

	draw_list->AddRect(
		ImVec2(sliderPos.x, sliderPos.y),
		ImVec2(sliderPos.x + sliderSize.x, sliderPos.y + sliderSize.y),
		IM_COL32(255, 255, 255, 255)
	);

	char numberText[64];
	snprintf(numberText, sizeof(numberText), format, *v);
	ImVec2 textSize = ImGui::CalcTextSize(numberText);
	ImVec2 numberPos = ImVec2(sliderPos.x + sliderSize.x / 2 - textSize.x / 2, sliderPos.y + sliderSize.y / 2 - textSize.y / 2);
	draw_list->AddText(numberPos, IM_COL32(255, 255, 255, 255), numberText);

	ImGui::PopID();

}
bool Draw::Menu::CustomCheckbox(const char* label, bool* v)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	const float square_sz = ImGui::GetFrameHeight();
	const ImVec2 pos = window->DC.CursorPos;
	const float total_bb_width = square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f);
	const float total_bb_height = label_size.y + style.FramePadding.y * 2.0f;
	const ImRect total_bb(pos, ImVec2(pos.x + total_bb_width, pos.y + total_bb_height));
	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
	{
		IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
		return false;
	}

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
	if (pressed)
	{
		*v = !(*v);
		ImGui::MarkItemEdited(id);
	}
	const ImVec2 check_bb_max(pos.x + square_sz, pos.y + square_sz);
	const ImRect check_bb(pos, check_bb_max);

	ImGui::RenderNavHighlight(total_bb, id);
	ImGui::RenderFrame(check_bb.Min, check_bb.Max, ImGui::GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), true, style.FrameRounding);
	if (*v)
	{
		const float pad = ImMax(1.0f, (float)(int)(square_sz / 9.1f));
		ImVec2 padded_min(check_bb.Min.x + pad, check_bb.Min.y + pad);
		ImVec2 padded_max(check_bb.Max.x - pad, check_bb.Max.y - pad);
		window->DrawList->AddRectFilled(padded_min, padded_max, IM_COL32(0, 155, 255, 255), style.FrameRounding);
	}


	ImVec2 label_pos = ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y);
	if (g.LogEnabled)
		ImGui::LogRenderedText(&label_pos, *v ? _("[x]") : _("[ ]"));
	if (label_size.x > 0.0f)
		ImGui::RenderText(label_pos, label);

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags | ImGuiItemStatusFlags_Checkable | (*v ? ImGuiItemStatusFlags_Checked : 0));
	return pressed;

}
void Draw::Menu::DrawMenu()
{
	Draw::Menu::GetIndex();
	if (!esp && !aimbot && !misc) // Home Menu
	{
		Draw::Menu::CreateMenu();
		Draw::Menu::Title(0, _("Benzo.wtf"), ImColor(255, 0, 155, 255));
		Draw::Menu::CreateTab(1, esp, _("Player Visuals"));
		Draw::Menu::CreateTab(2, aimbot, _("Player Combat"));
		Draw::Menu::CreateTab(3, misc, _("Player Modifications"));
		Draw::Menu::CreateTab(4, settings, _("Settings"));
		Draw::Menu::CreateTab(5, help, _("Help"));
		Draw::Menu::Checkbox(6, Draw::toggled, _("Toggle Cheat"));

		if (Draw::Menu::CheckIndex(6))
			CurrentIndex = 1;
	}
	if (esp) // Esp Tab
	{
		Draw::Menu::CreateExtendedMenu();
		Draw::Menu::Title(0, _("Player Visuals"), ImColor(255, 0, 155, 255));
		Draw::Menu::Checkbox(1, Cheat_Private::ESP::Box, _("Box"));
	
	

		Draw::Menu::Checkbox(18, esp, _("Go Back"));

		if (Draw::Menu::CheckIndex(18))
			CurrentIndex = 1;
	}
	else if (aimbot) // Aimbot Tab
	{
		Draw::Menu::CreateExtendedMenu();
		Draw::Menu::Title(0, _("Player Combat"), ImColor(255, 0, 155, 255));
		Draw::Menu::Checkbox(1, Cheat::Aimbot::Aimbot, _("Aimbot"));
		Draw::Menu::Checkbox(2, Cheat::ESP::HealthBased, _("pSilent"));
		Draw::Menu::Checkbox(3, Cheat::ESP::Rainbow, _("TriggerBot"));
		Draw::Menu::Checkbox(4, Cheat::ESP::SkipTeam, _("Auto Shoot"));
		Draw::Menu::Checkbox(5, Cheat::ESP::SkipTeam, _("Fov Circle"));
		Draw::Menu::Checkbox(6, Cheat::ESP::SkipTeam, _("RCS Control"));
		Draw::Menu::Checkbox(7, Cheat::ESP::SkipTeam, _("Legit Overall"));

		Draw::Menu::Checkbox(8, aimbot, _("Go Back"));

		if (Draw::Menu::CheckIndex(8))
			CurrentIndex = 1;
	}
	else if (misc) // Misc Tab
	{
		Draw::Menu::CreateExtendedMenu();
		Draw::Menu::Title(0, _("Player Modifications"), ImColor(255, 0, 155, 255));
		Draw::Menu::Checkbox(1, Cheat::Aimbot::Aimbot, _("Free Cam"));
		Draw::Menu::Checkbox(2, Cheat::ESP::HealthBased, _("Super Glide"));
		Draw::Menu::Checkbox(3, Cheat::ESP::Rainbow, _("Super Grapple"));
		Draw::Menu::Checkbox(4, Cheat::ESP::SkipTeam, _("Third Person"));
		Draw::Menu::Checkbox(5, Cheat::ESP::SkipTeam, _("Fake Fire"));
		Draw::Menu::Checkbox(6, Cheat::ESP::SkipTeam, _("Rainbow Hands"));
		Draw::Menu::Checkbox(7, Cheat::ESP::SkipTeam, _("Rainbow Weapon"));
		Draw::Menu::Checkbox(8, misc, _("Go Back"));

		if (Draw::Menu::CheckIndex(8))
			CurrentIndex = 1;
	}
	else if (help) // Help Tab
	{
		Draw::Menu::CreateExtendedMenu();
		Draw::Menu::Title(0, _("Help"), ImColor(255, 0, 155, 255));
		Draw::Menu::Text(1, _("UP Arrow - Moves up"));
		Draw::Menu::Text(2, _("DOWN Arrow - Down up"));
		Draw::Menu::Text(3, _("LEFT Arrow - Decrease / off"));
		Draw::Menu::Text(4, _("RIGHT Arrow - Increase / on"));
		Draw::Menu::Text(5, _("INSERT - Toggle Menu"));
		Draw::Menu::Text(6, _("[END] Close Cheat"));

		Draw::Menu::Checkbox(7, help, _("Go Back"));

		if (Draw::Menu::CheckIndex(7))
			CurrentIndex = 1;
	}
	else if (settings) {

		Draw::Menu::CreateExtendedMenu();
		Draw::Menu::Title(0, _("Settings"), ImColor(255, 0, 155, 255));
		Draw::Menu::Text(1, _("Resolution"));
		Draw::Menu::Checkbox(2, Cheat_Private::Settings::ControllerSupport, _("Controller Support"));

		Draw::Menu::Checkbox(3, settings, _("Go Back"));

		if (Draw::Menu::CheckIndex(3))
			CurrentIndex = 1;
	}
}