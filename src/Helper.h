#pragma once
#include "imgui.h"
#include "imconfig.h"
#include "imgui_internal.h"

#include "ofParameter.h"
#include "ofFbo.h"
#include "ofTexture.h"

namespace ofxImGui
{
bool isUsing();
const char* GetUniqueName(ofAbstractParameter& parameter);
const char* GetUniqueName(const std::string& candidate);

struct WindowOpen
{
	std::stack<std::vector<std::string>> usedNames;
	std::shared_ptr<ofParameter<bool>> parameter;
	bool value;
};
static WindowOpen windowOpen;

void AddGroup(const ofParameterGroup& group);

bool AddParameter(ofParameter<float>& parameter);
bool AddParameter(ofParameter<int>& parameter);
bool AddParameter(ofParameter<bool>& parameter);

bool AddParameter(ofParameter<glm::tvec2<int>>& parameter);
bool AddParameter(ofParameter<glm::tvec3<int>>& parameter);
bool AddParameter(ofParameter<glm::tvec4<int>>& parameter);
bool AddParameter(ofParameter<glm::vec2>& parameter);
bool AddParameter(ofParameter<glm::vec3>& parameter);
bool AddParameter(ofParameter<glm::vec4>& parameter);
bool AddParameter(ofParameter<ofVec2f>& parameter);
bool AddParameter(ofParameter<ofVec3f>& parameter);
bool AddParameter(ofParameter<ofVec4f>& parameter);
bool AddParameter(ofParameter<ofFloatColor>& parameter, bool alpha = true);
bool AddParameter(ofParameter<std::string>& parameter, size_t maxChars, bool multiline);
bool AddParameter(ofParameter<void>& parameter);

bool ImageButton(const ofFbo& src, float scale);
bool ImageButton(const ofTexture& src, float scale);

void Begin(const std::string& name);
void End();
}