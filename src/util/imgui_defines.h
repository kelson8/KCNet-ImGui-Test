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

// Make a button
#define IMGUIBUTTON ImGui::Button

// Make a input int value
#define IMGUI_INPUT_INT(LABEL, VALUE) ImGui::InputInt(LABEL, VALUE)

// Make a input int with flags
#define IMGUI_INPUT_INT_FLAGS(LABEL, VALUE, FLAGS) ImGui::InputInt(LABEL, VALUE, FLAGS)

// Make an ImGui separator
#define IMGUI_SEPERATOR ImGui::Separator