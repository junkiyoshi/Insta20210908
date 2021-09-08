#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(239);
	ofNoFill();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
	ofSetBackgroundAuto(false);

	this->font_size = 55;
	ofTrueTypeFontSettings font_settings("fonts/msgothic.ttc", this->font_size);
	font_settings.antialiased = true;
	font_settings.addRanges(ofAlphabet::Japanese);
	this->font.load(font_settings);

	this->words = {

		u8"‚Í‚é", u8"‚È‚Â", u8"‚ ‚«", u8"‚Ó‚ä", u8"‚»‚ç",
		u8"‚Â‚¿", u8"‚ ‚ß", u8"‚­‚à", u8"‚©‚³", u8"‚Ð‚Æ",
	};
}

//--------------------------------------------------------------
void ofApp::update() {

	ofColor color;
	vector<ofColor> color_list;
	vector<int> hex_list = { 0xef476f, 0xffd166, 0x06d6a0, 0x118ab2, 0x073b4c };
	for (auto hex : hex_list) {

		color.setHex(hex);
		color_list.push_back(color);
	}

	if (ofGetFrameNum() % 2 == 0) {

		this->mesh_list.clear();

		ofColor color_1, color_2;
		int len = 600;
		int x = ofGetWidth() * 0.5;
		int y = ofGetHeight() * 0.5;

		ofMesh mesh;
		color_1 = color_list[int(ofRandom(color_list.size()))];
		color_2 = color_list[int(ofRandom(color_list.size()))];

		int param = ofRandom(100);

		if (ofRandom(1) < 0.5) {

			mesh.addVertex(glm::vec3(x, y, 0) + glm::vec3(this->make_point(len, param), 0));
			mesh.addVertex(glm::vec3(x, y, 0) + glm::vec3(this->make_point(len, param + 2), 0));
			mesh.addColor(color_1);
			mesh.addColor(color_1);

			mesh.addVertex(glm::vec3(x, y, 0) + glm::vec3(this->make_point(len, 100 - param - 2), 0));
			mesh.addVertex(glm::vec3(x, y, 0) + glm::vec3(this->make_point(len, 100 - param), 0));
			mesh.addColor(color_2);
			mesh.addColor(color_2);
		}
		else {

			mesh.addVertex(glm::vec3(x, y, 0) + glm::vec3(this->make_point(len, param), 0));
			mesh.addVertex(glm::vec3(x, y, 0) + glm::vec3(this->make_point(len, param + 2), 0));
			mesh.addColor(color_1);
			mesh.addColor(color_1);

			mesh.addVertex(glm::vec3(x, y, 0) + glm::vec3(this->make_point(len, 75 - param + 75 - 2), 0));
			mesh.addVertex(glm::vec3(x, y, 0) + glm::vec3(this->make_point(len, 75 - param + 75), 0));
			mesh.addColor(color_2);
			mesh.addColor(color_2);
		}

		mesh.addIndex(0); mesh.addIndex(1); mesh.addIndex(3);
		mesh.addIndex(1); mesh.addIndex(2); mesh.addIndex(3);

		this->mesh_list.push_back(mesh);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	if (ofGetFrameNum() % 12 == 0) {

		int x = ofRandom(120, 600);
		int y = ofRandom(150, 570);
		int word_index = (int)ofRandom(this->words.size());

		ofFill();
		ofSetColor(239);

		ofPushMatrix();
		ofTranslate(x, y);
		ofRotateZ(ofRandom(360));

		this->font.drawString(this->words[word_index], -60, -60);

		ofPopMatrix();

	}

	ofNoFill();
	for (auto& mesh : this->mesh_list) {

		mesh.draw();

		ofSetColor(255);
		ofBeginShape();
		for (auto& vertex : mesh.getVertices()) {

			ofVertex(vertex);
		}
		ofEndShape(true);
	}

	ofSetColor(39);
	ofDrawRectangle(360, 360, 600, 600);
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}