#pragma once

#include "imgui.h"

// This file will add shortcuts for certain ImGui actions with a preprocessor
// The idea for this came from Google Gemini, I've never really messed with these too much.

// Set the style color with 'r, g, b, a' values 
#define PUSH_TEXT_COLOR(r, g, b, a) ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(r, g, b, a))

// Remove the style color
#define POP_TEXT_COLOR ImGui::PopStyleColor

// This works for shortening the ImGui text.
// Add it to files that use ImGui text.
#define IMGUITEXT ImGui::Text