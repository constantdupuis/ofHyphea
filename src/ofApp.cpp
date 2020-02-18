#include "ofApp.h"
#include "Point.h"
#include "QuadTree.h"


//--------------------------------------------------------------
void ofApp::setup(){

	qtree = make_unique<QuadTree<Point>>(
		make_unique<ofRectangle>(10, 10, ofGetWidth()-20, ofGetHeight()-20),
		8);

	shared_ptr<Point> np;
	for (int i = 0; i < 2000; i++)
	{
		np = make_shared<Point>(10 + ofRandom(ofGetWidth() - 20), 10 + ofRandom(ofGetHeight() - 20));
		qtree->insert(np);
	}
	queryArea = ofRectangle(100, 156, 234, 182);
	foundPoints = qtree->query(queryArea);
}

//--------------------------------------------------------------
void ofApp::update(){
	// add point when left button mouse is pressed
	if (ofGetMousePressed(0)) // left button
	{
	/*	auto bound = ofRectangle(10, 10, ofGetWidth() - 20, ofGetHeight() - 20);
		if (bound.inside(ofGetMouseX(), ofGetMouseY()))
		{
			shared_ptr<Point> np = make_shared<Point>(ofGetMouseX(), ofGetMouseY());
			qtree->insert(np);
		}*/
	}
	else if (ofGetMousePressed(2))
	{

	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(55);

	//draw boundary and points
	qtree->forEach([](QuadTree<Point>& qtree) {
		auto r = qtree.boundary();

		ofSetColor(ofColor::greenYellow);
		ofNoFill();
		ofDrawRectangle(qtree.boundary());

		for (auto p : *(qtree.points()))
		{
			ofFill();
			ofSetColor(ofColor::pink);
			ofDrawCircle(p->_pos, 5.0);
		}
	});

	ofSetColor(ofColor::white);
	ofNoFill();
	ofDrawRectangle(queryArea);

	for (auto p : *(foundPoints))
	{
		ofFill();
		ofSetColor(ofColor::yellow);
		ofDrawCircle(p->_pos, 5.0);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
