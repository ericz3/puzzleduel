#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {
  ofSetupOpenGL(1024, 1536 , OF_WINDOW);  // <-------- setup the GL context

  // this kicks off the running of my app
  // can be OF_WINDOW or OF_FULLSCREEN
  // pass in width and height too:
  ofRunApp(new ofApp());
}
