#pragma once

#include "ofMain.h"
#include "ofxAudioUnit.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    //// ofxAudioUnit ////
    
    ofxAudioUnitMixer mixer;
    ofxAudioUnitSampler synth; // AU Instrument
    ofxAudioUnitFilePlayer audioFile; // AU Audiofile
    ofxAudioUnit effect; // AU Effect
    ofxAudioUnitTap tapSynth, tapEffect; // Get Waveform
    ofxAudioUnitOutput output;
    
    vector <int> tones;
    int playNote;
    float parameter1, parameter2;
    
    vector <int> buttonAlpha;
    ofPolyline synthWaveform, effectWaveform;
    
    /* HOW TO run this example:
     
     1. You'll need to download Automat Synth
     
     http://www.alphakanal.de/automat.html
     
     and michael norris software package containing 'spectral chorus' effect
     
     http://www.michaelnorris.info/software/soundmagic-spectral
     
     
     2. Make sure you go to Build Phases > Link Binaries > add CoreMidi.framework, CoreAudioKit.framework, and AudioUnit.framework
     
     3. Open terminal and use command 'auval -a' to list au components
     
     4. to Utilize the method showUI() you need to checkout carbon tag of ofxAudioUnit repo. Terminal into repo and 'git checkout tags/carbon'
     
     */
    
    
};
