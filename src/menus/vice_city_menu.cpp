#include "vice_city_menu.h"
#include "imgui.h"

#include <iostream>

// ReVC Stuff
// I'm basically making a test menu for ReVC in my own ImGui test.

bool spawnInCar = false;


bool showVehicleListBox = false;
const char* vehicles[] = { "Rhino", "Cheetah", "Infernus" };
int currentItem = 150;
//int currentItem = 150;
//int *currentItemPtr = &currentItem;

// Test
int selectedIndex = 0;
bool showMainMenuBar = false;

bool pedsEnabled = true;
bool vehiclesEnabled = true;

int vehicleMin = 130;


enum Vehicles {
	Rhino = 0,
	Cheetah = 1,
	Infernus = 2
};


void VC::Menus::MainMenu()
{
	bool item_highlight = false;

	if (ImGui::CollapsingHeader("ReVC")) 
	{

	
		if (ImGui::BeginTabBar("ReVC"))
		{
			//-------------- Player -----------//
			if (ImGui::BeginTabItem("Player")) {

				if (ImGui::Button("Heal")) {
					std::cout << "Player healed" << std::endl;
					//PlayerCheats::HealPlayer();
				}

				ImGui::SameLine();
				if (ImGui::Button("Suicide")) {
					std::cout << "Player killed" << std::endl;
					//PlayerCheats::SuicideCheat();
				}

				// TODO Come up with a solution for this.
				// Possibly use ImGui::ListBox, need to test it some more and mess around with it.
				//ImGui::Text("Warps");
				//if (ImGui::Button("Airport")) {

				//}

				ImGui::EndTabItem();
			}

			//-------------- Vehicles -----------//
			if (ImGui::BeginTabItem("Vehicle"))
			{
				//
				ImGui::Text("ReVC Vehicle test");


				if (ImGui::Button("Toggle vehicle list"))
				{
					showVehicleListBox = !showVehicleListBox;
				}

				// Add a test for spawning in the car
				// TODO Add a list of vehicles to spawn into
				ImGui::Checkbox("Spawn in vehicle", &spawnInCar);


				//
				
				ImGui::SliderInt("Vehicles", &vehicleMin, 130, 236);

				if (showVehicleListBox)
				{
					// TODO Figure out how to make this start from 130 instead of 0.
					// TODO Setup submit button for this.
					if (ImGui::BeginListBox("Vehicles"))
					{
						for (int n = 0; n < IM_ARRAYSIZE(vehicles); n++)
						{
							const bool is_selected = (currentItem == n);
							if (ImGui::Selectable(vehicles[n], is_selected)) {
								currentItem = n;
								std::cout << n << std::endl;
								
								// TODO Come up with a better solution for this...
								switch (n) {
									case Rhino:
										// Spawn the vehicle in here..
										// VehicleFunctions::SpawnVehicle(VehicleModels::TAXI, false, false);
										std::cout << "Rhino spawned" << std::endl;
								}
							}


							if (item_highlight && ImGui::IsItemHovered())
								currentItem = n;

							// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
							if (is_selected)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndListBox();
					}
				}
				//


				// Moved to above
				//if (showVehicleListBox)
				//{
				//	ImGui::ListBox("Vehicles", &currentItem, vehicles, 3);
				//}

				ImGui::EndTabItem();
			}

			//-------------- Cheats -----------//
			if (ImGui::BeginTabItem("Cheats"))
			{

				if (ImGui::Button("Weapon1"))
				{
					std::cout << "Weapon set 1 given" << std::endl;
				}

				if (ImGui::Button("Weapon2"))
				{
					std::cout << "Weapon set 2 given" << std::endl;
				}

				if (ImGui::Button("Weapon3"))
				{
					std::cout << "Weapon set 3 given" << std::endl;
				}

				// These two below mimic the change that happens in ReVC with my ImGui menu.
				if (ImGui::Button("Toggle peds")) {
					pedsEnabled = !pedsEnabled;
					if (pedsEnabled) {
						std::cout << "Peds enabled" << std::endl;
					}
					else {
						std::cout << "Peds disabled" << std::endl;
					}
				}

				if (ImGui::Button("Toggle vehicles")) {
					vehiclesEnabled = !vehiclesEnabled;
					if (vehiclesEnabled) {
						std::cout << "Vehicles enabled" << std::endl;
					}
					else {
						std::cout << "Vehicles disabled" << std::endl;
					}
				}
				//

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();

		}

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Separator();
	}


}