#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  
  fbo.allocate(ofGetWidth(), ofGetHeight());
  fboGlitch.allocate(ofGetWidth(), ofGetHeight());
  
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  
  speed = 50;
  
  bShowHelp = true;
  bDoGlitch = false;
  
  std::string url = "http://toneelhuis.be/en/rest/views/getprofiles?limit=0&offset=0";
  
  // Now parse the JSON
  bool parsingSuccessful = result.open(url);
  if (parsingSuccessful) {
    
    ofLogNotice("ofApp::setup") << result.getRawString();
    if(result.isArray()) {
      for(unsigned int i = 0; i < result.size(); i++) {
        
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
  
  // draw here
  ofBackground(0);
  
  // the image to draw
  float clampedSpeed = ofClamp(speed, 1, 1000);
  int index = bDoGlitch ? (int)(ofGetElapsedTimeMillis() / clampedSpeed) % images.size() : 0;
  ofImage image = images[index];
  
  // calculate width & height of image to fill the whole screen but keep the image's original ratio
  float ratio = image.getWidth() / image.getHeight();
  float newWidth = ofGetWidth();
  float newHeight = newWidth / ratio;
  if(newHeight < ofGetHeight()) {
    newHeight = ofGetHeight();
    newWidth = newHeight * ratio;
  }
  
  // draw the image
  image.setAnchorPercent(0.5, 0.5);
  image.draw(ofGetWidth() / 2, ofGetHeight() / 2, newWidth, newHeight);
  
  
  fbo.end();
  
  // draw with or without glitch effect
  if(!bDoGlitch) {
    fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
  } else {
    fboGlitch.draw(fbo, 0, 0, ofGetWidth(), ofGetHeight());
  }
  
  
  /* show information */
  string info = "";
  info += "0,1,2,3 keys : Change glitch factor (low = higher glitch.\n";
  info += "G key : Toggle glitch.\n";
  info += "+,- keys : Faster, slower - current: " + ofToString(clampedSpeed) + "\n";
  info += "H key : Hide or show this information.";
  
  if (bShowHelp){
    ofSetColor(0, 200);
    ofRect(25, 17, 465, 60);
    ofSetColor(255);
    ofDrawBitmapString(info, 30,30);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == '0') fboGlitch.setGlichResetProbability(0.75);
  if (key == '1') fboGlitch.setGlichResetProbability(0.50);
  if (key == '2') fboGlitch.setGlichResetProbability(0.25);
  if (key == '3') fboGlitch.setGlichResetProbability(0.10);
  
  if (key == '+') speed += 25;
  if (key == '-') speed -= 25;

  if (key == 'g') bDoGlitch ^= true;
  if (key == 'h') bShowHelp ^= true;
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
