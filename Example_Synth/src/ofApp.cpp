#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    ofSetCircleResolution(100);
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    
    //// ofxAudioUnit ////
    
    // Load up a new audio unit instrument, print it's parameters and load a custom preset
    // To find list of audio units:
    // 1. Open Terminal
    // 2. auval -a
    // 3. find 'someName' 'someName' 'someName'
    
    synth = ofxAudioUnitSampler ('aumu', 'aut1', 'Alfa'); //load 3rdparty synth
    synth.printParameterList();
    synth.loadCustomPreset("User_Preset");
    
    effect = ofxAudioUnit ('aufx', 'Chor', 'MNor');
    effect.printParameterList();
    
    audioFile.setFile(ofFilePath::getAbsolutePath("DrumLoop.aif"));
    audioFile.play();
    audioFile.loop();
    
    // Set up signal chain, start output
    mixer.setInputBusCount(2);
    synth.connectTo(tapSynth).connectTo(mixer, 0);
    audioFile.connectTo(effect).connectTo(tapEffect).connectTo(mixer, 1); // Only effect Audio Loop
    mixer.connectTo(output);
    output.start();
    
    
    // Create Cminor scale from midi note graph in data bin
    tones.push_back(60);
    tones.push_back(62);
    tones.push_back(63);
    tones.push_back(65);
    tones.push_back(67);
    tones.push_back(68);
    tones.push_back(70);
    tones.push_back(72);
    
    playNote = 0;
    parameter1 = 0.0;
    parameter2 = 0.0;
    
    buttonAlpha.resize(tones.size());
    
}

//--------------------------------------------------------------
void ofApp::update(){

    for (int i = 0; i < buttonAlpha.size(); i++) {
        buttonAlpha[i] -= 5;
        
        if (buttonAlpha[i] <= 0.0) {
            buttonAlpha[i] = 0.0;
        }
    }
    
    tapEffect.getLeftWaveform(synthWaveform, 150, 100);
    tapSynth.getLeftWaveform(effectWaveform, 150, 100);
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackgroundGradient(ofColor::gray, ofColor::white);
    
    // Onscreen button graphics //
    
    int buttonRadius = 30;
    
    for ( int i = 0; i < tones.size(); i++ ) {
    
    float spacingX = ofGetWidth() * .15 + i * 100;
    ofColor c = ofColor::lightYellow;
    c.a = buttonAlpha[i];
        
    ofPushMatrix();
    ofSetColor(c);
    ofFill();
    ofCircle( spacingX, ofGetHeight() * .5, buttonRadius);
    ofSetColor(ofColor::black);
    ofNoFill();
    ofRect( spacingX, ofGetHeight() * .5, buttonRadius * 3, buttonRadius * 3);
    ofPopMatrix();
        
    }
    
    // Draw Waveform //
    ofPushMatrix();
    ofTranslate(ofGetWidth() * .50, ofGetHeight() * .75);
    synthWaveform.draw();
    ofPopMatrix();
    ofPushMatrix();
    ofTranslate(ofGetWidth() * .75, ofGetHeight() * .75);
    effectWaveform.draw();
    ofPopMatrix();
    
    // Onscreen Text //
    
    ofVec2f textPos = ofVec2f(ofGetWidth() * .10, ofGetHeight() * .10);
    ofSetColor(0);
    
    ofDrawBitmapString("ofxAudioUnit Example", textPos);
    ofDrawBitmapString("Keys 'a' 's' 'd' 'f' 'g' 'h' 'j' to play tones", textPos.x, textPos.y + 50);
    ofDrawBitmapString("Mouse X / Y to control drum loop effect", textPos.x, textPos.y + 75);
    ofDrawBitmapString("'Space' to ShowUI '1' to Save synth preset '2' to Load Preset ", textPos.x, textPos.y + 100);
    ofDrawBitmapString("Parameter X: " + ofToString(parameter1) + " Parameter Y: " + ofToString(parameter2), textPos.x, textPos.y + 500);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
   
    // Show Synth with Spacebar
    
    if ( key == ' ' ) {
    
        synth.showUI();
        effect.showUI();
    
    }
    
    // Save Synth with
    
    if ( key == '1' ) {
        
        synth.saveCustomPreset("User_Preset");
        
    }
    
    // Load Synth with
    
    if ( key == '2' ) {
        
        synth.loadCustomPreset("User_Preset");
        
    }
    
    
    //synth.saveCustomPreset("User_Preset");
    
    //send noteOn with different tones at full velocity
    
    switch (key) {
        case 'a':
            playNote = 0;
            break;
        case 's':
            playNote = 1;
            break;
        case 'd':
            playNote = 2;
            break;
        case 'f':
            playNote = 3;
            break;
        case 'g':
            playNote = 4;
            break;
        case 'h':
            playNote = 5;
            break;
        case 'j':
            playNote = 6;
            break;
        case 'k':
            playNote = 7;
            break;
        default:
            playNote = 0;
            break;
    }
    
    buttonAlpha[playNote] = 255;
    synth.midiNoteOn(tones[playNote], 127);


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    //send noteOff with different tones at no velocity
    
    switch (key) {
        case 'a':
            playNote = 0;
            break;
        case 's':
            playNote = 1;
            break;
        case 'd':
            playNote = 2;
            break;
        case 'f':
            playNote = 3;
            break;
        case 'g':
            playNote = 4;
            break;
        case 'h':
            playNote = 5;
            break;
        case 'j':
            playNote = 6;
            break;
        case 'k':
            playNote = 7;
            break;
        default:
            playNote = 0;
            break;
    }
    
    synth.midiNoteOff(tones[playNote], 0);
    
    
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
    /////////////////
    // WARNING: ALWAYS SET OFMAP 'TRUE' TO CLAMP VALUE OTHERWISE VOLUME CAN GET EXTREMELYLOUD!//
    
    // Setting Parameters: Set Parameter Index (Found in print parameter list), Set it's Scope, Set Value //
    
    parameter1 = ofMap(x, 0, ofGetWidth(), 0.0, 100.0, true);
    parameter2 = ofMap(y, 0, ofGetHeight(), 0.0, 100.0, true);
    
    effect.setParameter(0, kAudioUnitScope_Global, parameter1);
    effect.setParameter(5, kAudioUnitScope_Global, parameter2);
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
