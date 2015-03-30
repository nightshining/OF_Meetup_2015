# OF_Meetup_2015
Example of how to setup a mixer, instrument, file player and effects with ofxAudioUnit.

   1. You'll need to download Automat Synth
     
     http://www.alphakanal.de/automat.html
     
     and michael norris software package containing 'spectral chorus' effect
     
     http://www.michaelnorris.info/software/soundmagic-spectral
     
     
     2. Make sure you go to Build Phases > Link Binaries > add CoreMidi.framework, CoreAudioKit.framework, and AudioUnit.framework
     
     3. Open terminal and use command 'auval -a' to list au components
     
     4. to Utilize the method showUI() you need to checkout carbon tag of ofxAudioUnit repo. Terminal into repo and 'git checkout tags/carbon'
