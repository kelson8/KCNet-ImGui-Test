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

bool neverWanted = false;
// Vehicle
bool infiniteHealth = false;
bool highVehicleMass = false;
bool vehicleInvincible = false;

int vehicleMin = 130;

// Test for code in here.
int wantedLevel = 0;

enum Vehicles {
	Rhino = 0,
	Cheetah = 1,
	Infernus = 2
};

/// <summary>
/// Toggle infinite health, moved out of main menu 
/// and refactored the checkbox to be under an if statement.
/// </summary>
void
toggleInfiniteHealth()
{
	if (infiniteHealth) {
		std::cout << "Infinite health enabled" << std::endl;
	}
	else {
		std::cout << "Infinite health disabled" << std::endl;
	}
}

void
toggleVehicleInvincible()
{
	//CPlayerPed* pPed = FindPlayerPed();
	//VehicleFunctions vehicleFunctions = VehicleFunctions();

	//if (vehicleFunctions.IsPlayerInVehicle()) {
		//CVehicle* currentVeh = pPed->m_pMyVehicle;

		if (vehicleInvincible) {
			std::cout << "Vehicle invincibility enabled" << std::endl;
			//VehicleCheats::EnableVehicleInvincibility(currentVeh);
		}
		else {
			std::cout << "Vehicle invincibility disabled" << std::endl;
			//VehicleCheats::DisableVehicleInvincibility(currentVeh);
		}

	//}

}

/// <summary>
/// Well, I created a bug with the high mass. I made a fun effect
/// TODO Figure out how to reset this back to default
/// TODO Figure out how to get these values from lua... Use my lua_test.cpp
/// This is fun, although it does crash after a minute since I can't turn it off.
/// </summary>
void
toggleHighVehicleMass()
{
	// This makes the vehicle super strong
	float vehicleMass = 30000.0f;

	// Well I created the spinny effect but sadly it crashes after a minute.
	// This creates the spinny effect like from the reddit post I saw.
	float vehicleTurnMass = 4.0f;

	//VehicleFunctions vehicleFunctions = VehicleFunctions();

	//if (vehicleFunctions.IsPlayerInVehicle()) {
		//CVehicle* currentVeh = pPed->m_pMyVehicle;

		if (highVehicleMass)
		{
			std::cout << "Vehicle mass set to " << vehicleMass << std::endl;
			std::cout << "Vehicle turn mass set to " << vehicleTurnMass << std::endl;

			//currentVeh->m_fMass = 10000000.0f;
			//currentVeh->m_fMass = 10000.0f;


			// This makes the vehicle super strong
			//currentVeh->m_fMass = vehicleMass;

			// Spinny effect
			//currentVeh->m_fTurnMass = vehicleTurnMass;
		}

	//}

}

void toggleNeverWanted()
{
	//neverWanted = !neverWanted;
	if (neverWanted) {
		std::cout << "Never wanted enabled" << std::endl;
	}
	else {
		std::cout << "Never wanted disabled" << std::endl;
	}
}


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

				if (ImGui::Checkbox("Infinite health", &infiniteHealth)) {
					toggleInfiniteHealth();
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

				// ReVC specific functions that I have created.
				if (ImGui::Button("Spawn Vehicle")) {
					if (spawnInCar) {
						std::cout << "Cheetah spawned, removed old vehicle and warped player into it." << std::endl;
						//VehicleFunctions::SpawnVehicle(VehicleModels::CHEETAH, true, true);

					}
					else {
						std::cout << "Cheetah spawned." << std::endl;
						//VehicleFunctions::SpawnVehicle(VehicleModels::CHEETAH, false, false);
					}
				}

				if (ImGui::Checkbox("Toggle high mass", &highVehicleMass)) {
					toggleHighVehicleMass();
				}

				if (ImGui::Checkbox("Toggle invincibility", &vehicleInvincible)) {
					toggleVehicleInvincible();
				}

				
				//


				// Moved to above, this is the original function
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

				
				// Police cheats
				ImGui::Text("Police");

				if (ImGui::Button("Raise Wanted Level")) {
					//PlayerCheats::RaiseWantedLevel();
					if (wantedLevel < 1 || wantedLevel > 6) {
						std::cout << "Error, wanted level cannot be less then 1 or more then 6" << std::endl;
					}
					else {
						wantedLevel++;
						std::cout << "Wanted level raised by 1, new wanted level: " << wantedLevel << std::endl;
					}

					std::cout << "Wanted level raised by 1, new wanted level: " << wantedLevel << std::endl;
				}

				if (ImGui::Button("Lower Wanted Level")) {
					//PlayerCheats::LowerWantedLevel();
					if (wantedLevel < 1 || wantedLevel > 6) {
						std::cout << "Error, wanted level cannot be less then 1 or more then 6" << std::endl;
					}
					else {
						wantedLevel--;
						std::cout << "Wanted level lowered by 1, new wanted level: " << wantedLevel << std::endl;
					}
					
					
				}

				//ImGui::Checkbox("Never wanted", &neverWanted);
				if (ImGui::Checkbox("Never wanted", &neverWanted)) {
					toggleNeverWanted();
				}


				// 
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