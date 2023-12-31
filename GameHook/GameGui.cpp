#include "GameHook.hpp"

#include "../imgui/imgui.h"
#include <array>
#include <vector>
#include <algorithm>
#include <shlobj_core.h>
#include "LicenseStrings.hpp"
#include "Mods.hpp"

float GameHook::trainerWidth = 0.0f;
float GameHook::trainerMaxHeight = 0.0f;
float GameHook::trainerHeightBorder = 0.0f;
float GameHook::trainerVariableHeight = 0.0f;
float GameHook::sameLineWidth = 0.0f;
float GameHook::inputItemWidth = 0.0f;

void HelpMarker(const char* desc) {
	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void GameHook::gameGui(void) {
	GameHook::trainerWidth = 40.0f * ImGui::GetFontSize();
	GameHook::trainerMaxHeight = ImGui::GetIO().DisplaySize.y * 0.9f;
	GameHook::trainerHeightBorder = ImGui::GetFontSize() * 6.0f;
	GameHook::sameLineWidth = GameHook::trainerWidth * 0.5f;
	GameHook::inputItemWidth = GameHook::trainerWidth * 0.3f;

	if (ImGui::Button("Save config")) {
		GameHook::onConfigSave(GameHook::cfg);
	}

	if (ImGui::BeginTabBar("Trainer", ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip)) {
		if (ImGui::BeginTabItem("General")) {
			ImGui::BeginChild("GeneralChild");

			Mods::GetInstance()->DrawUI();

			trainerVariableHeight = std::clamp(ImGui::GetCursorPosY() + trainerHeightBorder, 0.0f, trainerMaxHeight);
			ImGui::EndChild();
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Stats")) {
			ImGui::BeginChild("StatsChild");
			trainerVariableHeight = std::clamp(ImGui::GetCursorPosY() + trainerHeightBorder, 0.0f, trainerMaxHeight);
			ImGui::EndChild();
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Inventory")) {
			ImGui::BeginChild("InventoryChild");

			trainerVariableHeight = std::clamp(ImGui::GetCursorPosY() + trainerHeightBorder, 0.0f, trainerMaxHeight);
			ImGui::EndChild();
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("System")) {
			ImGui::BeginChild("SystemChild");

			trainerVariableHeight = std::clamp(ImGui::GetCursorPosY() + trainerHeightBorder, 0.0f, trainerMaxHeight);
			ImGui::EndChild();
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Credits")) {
			ImGui::BeginChild("CreditsChild");
			ImGui::TextWrapped("WARNING: PLEASE BACK UP YOUR SAVEDATA BEFORE USING THIS HOOK.");
			ImGui::TextWrapped("I haven't had any save corruption issues, but"
				"I would hate for anyone to lose their saves because of me.");
			ImGui::TextWrapped("By default your save is found here:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(0.356f, 0.764f, 0.960f, 1.0f), "My Games");
			if (ImGui::IsItemClicked()) {
				TCHAR saveGameLocation[MAX_PATH];
				TCHAR myGames[MAX_PATH] = "My Games";
				HRESULT result = SHGetFolderPathAndSubDirA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, myGames, saveGameLocation);
				ShellExecuteA(NULL, "open", saveGameLocation, NULL, NULL, SW_SHOWNORMAL);
			}

			ImGui::Separator();

			struct ImGuiURL {
				std::string text;
				std::string url;
				const ImVec4 color_hover{ 0.356f, 0.764f, 0.960f, 1.00f };
				const ImVec4 color_regular{ 0.950f, 0.960f, 0.980f, 1.00f };

				void draw() {

					ImGui::TextColored(color_regular, text.c_str());
					if (ImGui::IsItemHovered()) {
						GameHook::under_line(color_hover);
					}
					if (ImGui::IsItemClicked()) {
						ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
					}
				}
			};

			ImGui::Text("Check for updates here:");
			ImGuiURL repo{ GameHook::repoUrl, GameHook::repoUrl };
			repo.draw();

			ImGui::Separator();

			ImGui::Text("This trainer was made by:");
			static std::array<ImGuiURL, 4> links1{
				ImGuiURL { "SSSiyan", "https://twitter.com/SSSiyan" },
				ImGuiURL { "Darkness", "https://github.com/amir-120/" },
				ImGuiURL { "deepdarkkapustka", "https://www.youtube.com/@mstislavcapusta7573" },
			};
			for (auto& link : links1) {
				link.draw();
			}

			ImGui::Separator();

			ImGui::Text("This trainer was made using:");
			static std::array<ImGuiURL, 5> links2{
				ImGuiURL { "Dear ImGui", "https://github.com/ocornut/imgui" },
				ImGuiURL { "RHook", "https://github.com/amir-120/RHook" },
				ImGuiURL { "Detours", "https://github.com/microsoft/Detours" },
				ImGuiURL { "libffi", "https://github.com/libffi/libffi" },
				ImGuiURL { "spdlog", "https://github.com/gabime/spdlog" },
			};
			for (auto& link : links2) {
				link.draw();
			}

			ImGui::Separator();

			ImGui::Text("Licenses:");
			struct License {
				std::string name;
				std::string text;
			};
			static std::array<License, 4> licenses{
				License{ "imgui", license::imgui },
				License{ "detours", license::detours },
				License{ "libffi", license::libffi },
				License{ "spdlog", license::spdlog },
			};
			for (const auto& license : licenses) {
				if (ImGui::CollapsingHeader(license.name.c_str())) {
					ImGui::TextWrapped(license.text.c_str());
				}
			}

			trainerVariableHeight = std::clamp(ImGui::GetCursorPosY() + trainerHeightBorder, 0.0f, trainerMaxHeight);
			ImGui::EndChild();
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}
