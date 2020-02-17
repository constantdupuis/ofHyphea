#include "ofApp.h"
#include "Point.h"
#include "QuadTree.h"


//--------------------------------------------------------------
void ofApp::setup(){

	qtree.setup( ofRectangle(10, 10, ofGetWidth()-20, ofGetHeight()-20), 4);

	//shared_ptr<Point> np;
	for (int i = 0; i < 20; i++)
	{
		//np = make_shared<Point>(10+ofRandom(ofGetWidth() - 20), 10+ofRandom(ofGetHeight()-20));
		qtree.insert(make_shared<Point>(10 + ofRandom(ofGetWidth() - 20), 10 + ofRandom(ofGetHeight() - 20)));
	}

	qtree.forEach([](QuadTree<Point>& qtree) {
		cout << "Quatree\n";
		cout << " contains " << qtree.nbPoints() << " points\n";
		/*for(int i = 0; i < qtree.nbPoints(); i++)
		{	
			Point p = qtree._points[i];
			cout << " point (" << p._pos.x << "x" << p._pos.y << ")\n";
		}*/
		for (auto p : qtree.points())
		{
			cout << " point ("<< p->pos().x << "x" << p->pos().y << ")\n";
		}
	});
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(55);

	qtree.forEach([](QuadTree<Point>& qtree) {
		auto r = qtree.boundary();

		ofSetColor(ofColor::greenYellow);
		ofNoFill();
		ofDrawRectangle(qtree.boundary());

		for (auto p : qtree.points())
		{
			ofFill();
			ofSetColor(ofColor::pink);
			ofDrawCircle(p->pos(), 5.0);
		}
	});
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
