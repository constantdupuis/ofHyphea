#include "ofApp.h"
#include "Point.h"
#include "QuadTree.h"
#include "test.h"

//--------------------------------------------------------------
void ofApp::setup(){
	test<int> t;

	t.toto();

	qtree = make_unique<QuadTree<Point>>(make_unique<ofRectangle>(10, 10, ofGetWidth(), ofGetHeight()), 8);
	/*shared_ptr<Point> np = make_shared<Point>(ofRandomWidth(), ofRandomHeight());
	qtree->insert(np);*/

	/*np = make_shared<Point>(ofRandomWidth(), ofRandomHeight());
	qtree->insert(np);

	np = make_shared<Point>(ofRandomWidth(), ofRandomHeight());
	qtree->insert(np);

	np = make_shared<Point>(ofRandomWidth(), ofRandomHeight());
	qtree->insert(np);

	np = make_shared<Point>(ofRandomWidth(), ofRandomHeight());
	qtree->insert(np);*/

	/*qtree->forEach([](const QuadTree<Point>&) {
		cout << "Quatree\n";
	});*/
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

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
