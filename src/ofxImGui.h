#pragma once

#include "ofMain.h"
#include "imgui.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "opengl/imgui_impl_glfw.h"
#include "opengl/imgui_impl_opengl3.h"

namespace ofxImGui {
class Gui {
public:

	void setup() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

			// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		const char* glsl_version = "#version 130";

		ofAppGLFWWindow* window = (ofAppGLFWWindow*)ofGetWindowPtr();
		ImGui_ImplGlfw_InitForOpenGL(window->getGLFWWindow(), true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		ofAddListener(ofEvents().exit, this, &Gui::exit);
	}

	void exit(ofEventArgs& args) {
		ImGui::DestroyContext();
		ofRemoveListener(ofEvents().exit, this, &Gui::exit);
	}

	void begin() {
		ImGuiIO& io = ImGui::GetIO();

		float currentTime = ofGetElapsedTimef();
		if (lastTime > 0.f)
		{
			io.DeltaTime = currentTime - lastTime;
		}
		else
		{
			io.DeltaTime = 1.0f / 60.f;
		}
		lastTime = currentTime;

		// Update settings
		io.MousePos = ImVec2((float)ofGetMouseX(), (float)ofGetMouseY());
		for (int i = 0; i < 5; i++) {
			//io.MouseDown[i] = engine.mousePressed[i];
		}


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void end() {
		ofAppGLFWWindow* window = (ofAppGLFWWindow*)ofGetWindowPtr();
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window->getGLFWWindow(), &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
private:

	float lastTime;
};
}
