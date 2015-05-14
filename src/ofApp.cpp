#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
      fbo.allocate(ofGetWidth(),ofGetHeight());
      fboGlitch.allocate(320, 240);
  
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  
  
//  bool succ = testImage.loadImage("http://toneelhuis.be/sites/default/files/profile_images/main/foto_3_1.jpg");
//  if (!succ) {
//    cout << "loading image failed ...\n";
//  }
  
  std::string url = "http://toneelhuis.be/en/rest/views/getprofiles?limit=0&offset=0";
  
  // Now parse the JSON
  bool parsingSuccessful = result.open(url);
  if (parsingSuccessful) {
    
    ofLogNotice("ofApp::setup") << result.getRawString();
    if(result.isArray()) {
      for(unsigned int i = 0; i < 2; i++) {
        
        // names
        std::string firstname = result[i]["field_field_profile_firstname"][0].asString();
        std::string lastname = result[i]["field_field_profile_name"][0].asString();
        std::string fullname = firstname + ' ' + lastname;
        
        // url to image
        std::string uri = result[i]["field_field_profile_image_main"][0]["uri"].asString();
        uri.replace(0,
                    string("public://").size(),
                    string("http://toneelhuis.be/sites/default/files/styles/1200_x_auto/public/"));
        
        // log stuff
        ofLogNotice("ofApp::setup") << fullname;
        ofLogNotice("ofApp::setup") << uri;
        
        // load image
        ofImage image;
        bool success = image.loadImage(uri);
        if (!success) {
          cout << "loading image failed ...\n";
        }
        images.push_back(image);
      }
    }
  }
  else
  {
    ofLogNotice("ofApp::setup")  << "Failed to parse JSON" << endl;
  }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

  
      fbo.begin();
    ofBackground(0);
  images[1].draw(0, 0);
      fbo.end();
  
      fbo.draw(0, 0,ofGetWidth()/2,ofGetHeight()/2);
      fboGlitch.draw(fbo, ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight()/2);
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
