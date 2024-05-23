#include <iostream>
#include "AudioFile.h"
#include <fstream>
#include "../audiofunc.h"


void highPassFilter(const std::string &path, float coef = 0.5f){
    
    AudioFile<double> audioFile;
    AudioFile<float> a;
    bool loadedOK = a.load(path);
    
    /** If you hit this assert then the file path above
     probably doesn't refer to a valid audio file */
    assert (loadedOK);
    assert (coef >= 0 && coef <= 0.5);

    int samplePerChannel = a.getNumSamplesPerChannel();
    int numChannels = a.getNumChannels();
    int bitDepth = a.getBitDepth();

    // Output audio file
    AudioFile<float> outSong;
    outSong.setAudioBufferSize( numChannels, samplePerChannel);
    outSong.setBitDepth(bitDepth);
    outSong.setSampleRate(a.getSampleRate());

    float coef = 0.5f;
    int order = 1001;
    float gain = 10.0f;

    assert(order != 0);

    //Simple Moving average
    float accumalator = 0;

    //Initialize accumalator
    for (int i = 0; i < (order*2 -1); i+=((order*2 -1)-1)){
        for (int channel = 0; channel < a.getNumChannels(); channel++){
            accumalator+=a.samples[channel][i];
        }
    }
    

    for (int i = (order*2 -1); i < a.getNumSamplesPerChannel(); i++){
        for (int channel = 0; channel < a.getNumChannels(); channel++){
        
            //Low Pass Filter First Order
            outSong.samples[channel][i] = (a.samples[channel][i-1] + a.samples[channel][i])/2;
            
        }
    }


    std::string outputFilePath = "audio-clips/audio-lowpass-"+std::to_string(order)+"-order.wav"; // change this to somewhere useful for you
    outSong.save (outputFilePath, AudioFileFormat::Wave);

    //Audio Recognition
    //Other Stuff

    
    
}