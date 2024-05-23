#include <iostream>
#include "AudioFile.h"
#include <fstream>
#include "../audiofunc.h"


void lowAndHighPassFilter(const std::string &path, float coef, const bool type){
    
    AudioFile<double> audioFile;
    AudioFile<float> a;
    bool loadedOK = a.load(path);
    
    /** If you hit this assert then the file path above
     probably doesn't refer to a valid audio file */
    assert (loadedOK);
    assert (coef >= 0 && coef <= 0.5);

    int flip = 1;
    std::string outputFilePath = "../audio-clips/audio-lowpass-filter-basic.wav"; // change this to somewhere useful for you
    // IF type is true, this becomes a high pass filter
    if(type){
        flip*=-1;
        outputFilePath = "../audio-clips/audio-highpass-filter-basic.wav";
    }

    int samplePerChannel = a.getNumSamplesPerChannel();
    int numChannels = a.getNumChannels();
    int bitDepth = a.getBitDepth();

    // Output audio file
    AudioFile<float> outSong;
    outSong.setAudioBufferSize( numChannels, samplePerChannel);
    outSong.setBitDepth(bitDepth);
    outSong.setSampleRate(a.getSampleRate());

    

    for (int i = 1; i < a.getNumSamplesPerChannel(); i++){
        for (int channel = 0; channel < a.getNumChannels(); channel++){
        
            //Simple Basic Low & High Pass filter
            outSong.samples[channel][i] =  (coef * a.samples[channel][i]) + (((1-coef) * a.samples[channel][i-1])* flip);

    
        }
    }


    outSong.save (outputFilePath, AudioFileFormat::Wave);

    
}