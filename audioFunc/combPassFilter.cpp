#include <iostream>
#include <string>
#include "AudioFile.h"
#include <fstream>
#include "../audiofunc.h"

void combPassFilter(const std::string &path, float delayMs, float gain) {
    AudioFile<float> audioFile;
    bool loadedOK = audioFile.load(path);

    // Check if the file was loaded successfully
    assert(loadedOK);
    assert(gain >= -1.0f && gain <= 1.0f);

    int sampleRate = audioFile.getSampleRate();
    int delaySamples = static_cast<int>(delayMs * sampleRate / 1000.0f);

    int numSamplesPerChannel = audioFile.getNumSamplesPerChannel();
    int numChannels = audioFile.getNumChannels();
    int bitDepth = audioFile.getBitDepth();

    // Output audio file
    AudioFile<float> outSong;
    outSong.setAudioBufferSize(numChannels, numSamplesPerChannel);
    outSong.setBitDepth(bitDepth);
    outSong.setSampleRate(sampleRate);

    // Apply the comb filter
    for (int i = 0; i < numSamplesPerChannel; i++) {
        for (int channel = 0; channel < numChannels; channel++) {
            float delayedSample = (i >= delaySamples) ? outSong.samples[channel][i - delaySamples] : 0.0f; //Use of Ternary Operator
            outSong.samples[channel][i] = audioFile.samples[channel][i] + gain * delayedSample;
        }
    }

    std::string outputFilePath = "../audio-clips/audio-comb-filtered.wav"; // change this to somewhere useful for you
    outSong.save(outputFilePath, AudioFileFormat::Wave);
}