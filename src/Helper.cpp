#include "Helper.h"

namespace ofxImGui {
bool isUsing() { return ImGui::GetIO().WantCaptureMouse; }

//--------------------------------------------------------------
const char* GetUniqueName(ofAbstractParameter& parameter)
{
	return GetUniqueName(parameter.getName());
}

//--------------------------------------------------------------
const char* GetUniqueName(const std::string& candidate)
{
	std::string result = candidate;
	while (std::find(windowOpen.usedNames.top().begin(), windowOpen.usedNames.top().end(), result) != windowOpen.usedNames.top().end())
	{
		result += " ";
	}
	windowOpen.usedNames.top().push_back(result);
	return windowOpen.usedNames.top().back().c_str();
}

void AddGroup(const ofParameterGroup& group) {
	// Push a new list of names onto the stack.
	windowOpen.usedNames.push(std::vector<std::string>());

	for (auto parameter : group)
	{
		// Group.
		auto parameterGroup = std::dynamic_pointer_cast<ofParameterGroup>(parameter);
		if (parameterGroup)
		{
			// Recurse through contents.
			ofxImGui::AddGroup(*parameterGroup);
			continue;
		}

		// Parameter, try everything we know how to handle.
#if OF_VERSION_MINOR >= 10
		auto parameterVec2f = std::dynamic_pointer_cast<ofParameter<glm::vec2>>(parameter);
		if (parameterVec2f)
		{
			ofxImGui::AddParameter(*parameterVec2f);
			continue;
		}
		auto parameterVec3f = std::dynamic_pointer_cast<ofParameter<glm::vec3>>(parameter);
		if (parameterVec3f)
		{
			ofxImGui::AddParameter(*parameterVec3f);
			continue;
		}
		auto parameterVec4f = std::dynamic_pointer_cast<ofParameter<glm::vec4>>(parameter);
		if (parameterVec4f)
		{
			ofxImGui::AddParameter(*parameterVec4f);
			continue;
		}
#endif
		auto parameterOfVec2f = std::dynamic_pointer_cast<ofParameter<ofVec2f>>(parameter);
		if (parameterOfVec2f)
		{
			ofxImGui::AddParameter(*parameterOfVec2f);
			continue;
		}
		auto parameterOfVec3f = std::dynamic_pointer_cast<ofParameter<ofVec3f>>(parameter);
		if (parameterOfVec3f)
		{
			ofxImGui::AddParameter(*parameterOfVec3f);
			continue;
		}
		auto parameterOfVec4f = std::dynamic_pointer_cast<ofParameter<ofVec4f>>(parameter);
		if (parameterOfVec4f)
		{
			ofxImGui::AddParameter(*parameterOfVec4f);
			continue;
		}
		auto parameterFloatColor = std::dynamic_pointer_cast<ofParameter<ofFloatColor>>(parameter);
		if (parameterFloatColor)
		{
			ofxImGui::AddParameter(*parameterFloatColor);
			continue;
		}
		auto parameterFloat = std::dynamic_pointer_cast<ofParameter<float>>(parameter);
		if (parameterFloat)
		{
			ofxImGui::AddParameter(*parameterFloat);
			continue;
		}
		auto parameterInt = std::dynamic_pointer_cast<ofParameter<int>>(parameter);
		if (parameterInt)
		{
			ofxImGui::AddParameter(*parameterInt);
			continue;
		}
		auto parameterBool = std::dynamic_pointer_cast<ofParameter<bool>>(parameter);
		if (parameterBool)
		{
			ofxImGui::AddParameter(*parameterBool);
			continue;
		}

		ofLogWarning(__FUNCTION__) << "Could not create GUI element for parameter " << parameter->getName();
	}
	// Unlink the referenced ofParameter.
	windowOpen.parameter.reset();

	// Clear the list of names from the stack.
	windowOpen.usedNames.pop();
}

bool AddParameter(ofParameter<float>& parameter) {
	auto tmpRef = parameter.get();
	if (ImGui::SliderFloat(GetUniqueName(parameter), (float*)& tmpRef, parameter.getMin(), parameter.getMax()))
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

bool AddParameter(ofParameter<int>& parameter) {
	auto tmpRef = parameter.get();
	if (ImGui::SliderInt(GetUniqueName(parameter), (int*)& tmpRef, parameter.getMin(), parameter.getMax()))
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

bool AddParameter(ofParameter<bool>& parameter) {
	auto tmpRef = parameter.get();
	if (ImGui::Checkbox(GetUniqueName(parameter), (bool*)& tmpRef))
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
bool AddParameter(ofParameter<glm::tvec2<int>>& parameter)
{
	auto tmpRef = parameter.get();
	if (ImGui::SliderInt2(GetUniqueName(parameter), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
bool AddParameter(ofParameter<glm::tvec3<int>>& parameter)
{
	auto tmpRef = parameter.get();
	if (ImGui::SliderInt3(GetUniqueName(parameter), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
bool AddParameter(ofParameter<glm::tvec4<int>>& parameter)
{
	auto tmpRef = parameter.get();
	if (ImGui::SliderInt4(GetUniqueName(parameter), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
bool AddParameter(ofParameter<glm::vec2>& parameter)
{
	auto tmpRef = parameter.get();
	if (ImGui::SliderFloat2(GetUniqueName(parameter), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
bool AddParameter(ofParameter<glm::vec3>& parameter)
{
	auto tmpRef = parameter.get();
	if (ImGui::SliderFloat3(GetUniqueName(parameter), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
bool AddParameter(ofParameter<glm::vec4>& parameter)
{
	auto tmpRef = parameter.get();
	if (ImGui::SliderFloat4(GetUniqueName(parameter), glm::value_ptr(tmpRef), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
bool AddParameter(ofParameter<ofVec2f>& parameter)
{
	auto tmpRef = parameter.get();
	if (ImGui::SliderFloat2(GetUniqueName(parameter), tmpRef.getPtr(), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
bool AddParameter(ofParameter<ofVec3f>& parameter)
{
	auto tmpRef = parameter.get();
	if (ImGui::SliderFloat3(GetUniqueName(parameter), tmpRef.getPtr(), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
bool AddParameter(ofParameter<ofVec4f>& parameter)
{
	auto tmpRef = parameter.get();
	if (ImGui::SliderFloat4(GetUniqueName(parameter), tmpRef.getPtr(), parameter.getMin().x, parameter.getMax().x))
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}

//--------------------------------------------------------------
bool AddParameter(ofParameter<ofFloatColor>& parameter, bool alpha)
{
	auto tmpRef = parameter.get();
	if (alpha)
	{
		if (ImGui::ColorEdit4(GetUniqueName(parameter), &tmpRef.r))
		{
			parameter.set(tmpRef);
			return true;
		}
	}
	else if (ImGui::ColorEdit3(GetUniqueName(parameter), &tmpRef.r))
	{
		parameter.set(tmpRef);
		return true;
	}
	return false;
}


//--------------------------------------------------------------
bool AddParameter(ofParameter<std::string>& parameter, size_t maxChars, bool multiline)
{
	auto tmpRef = parameter.get();
	char* cString = new char[maxChars];
	strcpy(cString, tmpRef.c_str());
	auto result = false;
	if (multiline)
	{
		if (ImGui::InputTextMultiline(GetUniqueName(parameter), cString, maxChars))
		{
			parameter.set(cString);
			result = true;
		}
	}
	else if (ImGui::InputText(GetUniqueName(parameter), cString, maxChars))
	{
		parameter.set(cString);
		result = true;
	}
	delete[] cString;
	return result;
}

//--------------------------------------------------------------
bool AddParameter(ofParameter<void>& parameter)
{
	if (ImGui::Button(GetUniqueName(parameter)))
	{
		parameter.trigger();
		return true;
	}
	return false;
}


bool ImageButton(const ofFbo& src, float scale) {
	return ImGui::ImageButton((ImTextureID)(uintptr_t)src.getTexture().getTextureData().textureID, ImVec2(src.getWidth()*scale, src.getHeight() * scale), ImVec2(0, 0), ImVec2(1, 1), 0);
}


bool ImageButton(const ofTexture& src, float scale) {
	return ImGui::ImageButton((ImTextureID)(uintptr_t)src.getTextureData().textureID, ImVec2(src.getWidth() * scale, src.getHeight() * scale), ImVec2(0, 0), ImVec2(1, 1), 0);
}

void Begin(const std::string& name) {
	auto snap = [=](float value, float snap_threshold) -> float {
		float modulo = std::fmodf(value, snap_threshold);
		float moduloRatio = std::fabsf(modulo) / snap_threshold;
		if (moduloRatio < 0.5f)
			value -= modulo;
		else if (moduloRatio > (1.f - 0.5f))
			value = value - modulo + snap_threshold * ((value < 0.f) ? -1.f : 1.f);
		return value;
	};

	ImGui::Begin(name.data());
	if (ImGui::IsItemActive()) {
		auto p = ImGui::GetWindowPos();
		auto size = ImGui::GetWindowSize();

		float x = snap(p.x, 16.f);
		float y = snap(p.y, 16.f);
		float sizex = snap(size.x, 16.f);
		float sizey = snap(size.y, 16.f);
		ImGui::SetWindowSize(ImFloor(ImVec2(sizex, sizey)));
		ImGui::SetWindowPos(ImFloor(ImVec2(x, y)));
	}
}

void End() {
	ImGui::End();
}


void DrawParamSaveWindow(const ofParameterGroup& parameter, const std::string& base_save_dir) {
	std::string name = parameter.getName();
	ofxImGui::Begin(name);
	ofxImGui::AddGroup(parameter);
	if (ImGui::Button("Save")) {
		ofJson json;
		ofSerialize(json, parameter);
		ofSaveJson(base_save_dir + "/" + name + "_settings.json", json);
	}
	ofxImGui::End();
}
}