#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include "AudioFile.h"
#include "../audiofunc.h"

// Generated using chatGPT-4o using this prompt: Using the code here. How would you create an audio filter that mimics "The Voice" from the Movie Dune? The Voice is what the Bene Gesserit uses. It looks to be accomplished through overlaying anther actor's audio and then adding bass thump. 
// Fine Tuned and commented by Denzell

// Function to generate a sine wave at a given frequency and duration
std::vector<float> generateSineWave(float frequency, float duration, int sampleRate) {
    int numSamples = static_cast<int>(duration * sampleRate);
    std::vector<float> sineWave(numSamples);
    for (int i = 0; i < numSamples; ++i) {
        sineWave[i] =  sin(2.0f * M_PI * frequency * i / sampleRate);
    }
    return sineWave;
}

void addBassThump(AudioFile<float>& audioFile, float frequency, float duration, float threshold) {
    int sampleRate = audioFile.getSampleRate();
    auto sineWave = generateSineWave(frequency, duration, sampleRate);
    int numSamplesPerChannel = audioFile.getNumSamplesPerChannel();
    int numChannels = audioFile.getNumChannels();
    int thumpSize = static_cast<int>(duration * sampleRate);

    for (int i = 0; i < numSamplesPerChannel; ++i) {
        for (int channel = 0; channel < numChannels; ++channel) {
            float sampleValue = std::abs(audioFile.samples[channel][i]);

            if (sampleValue > threshold) {
                // Add bass thump
                for (int j = 0; j < thumpSize && (i + j) < numSamplesPerChannel; ++j) {
                    for (int ch = 0; ch < numChannels; ++ch) {
                        audioFile.samples[ch][i + j] += sineWave[j];
                        audioFile.samples[ch][i + j] = std::clamp(audioFile.samples[ch][i + j], -1.0f, 1.0f);
                    }
                }

                // Skip ahead to avoid overlapping thumps
                i += thumpSize;
                break;
            }
        }
    }
}

//Function to combine two audio files
void combineVoices(const std::string &originalPath, const std::string &overlayPath, const std::string &outputPath, float overlayGain) {
    AudioFile<float> originalFile;
    AudioFile<float> overlayFile;

    bool originalLoaded = originalFile.load(originalPath);
    bool overlayLoaded = overlayFile.load(overlayPath);

    assert(originalLoaded && overlayLoaded);
    assert(originalFile.getSampleRate() == overlayFile.getSampleRate());

    int numSamplesPerChannel = std::min(originalFile.getNumSamplesPerChannel(), overlayFile.getNumSamplesPerChannel());
    int numChannels = originalFile.getNumChannels();
    int sampleRate = originalFile.getSampleRate();
    int bitDepth = originalFile.getBitDepth();

    // Output audio file
    AudioFile<float> outFile;
    outFile.setAudioBufferSize(numChannels, numSamplesPerChannel);
    outFile.setBitDepth(bitDepth);
    outFile.setSampleRate(sampleRate);

    // Combine original and overlay voices
    for (int i = 0; i < numSamplesPerChannel; ++i) {
        for (int channel = 0; channel < numChannels; ++channel) {
            float combinedSample = originalFile.samples[channel][i] + overlayGain * overlayFile.samples[channel][i];
            outFile.samples[channel][i] = std::clamp(combinedSample, -1.0f, 1.0f);
        }
    }

    outFile.save(outputPath, AudioFileFormat::Wave);
}


void duneFilter(const std::string &path){

    float delayMs = 75.0f; // Delay in milliseconds
    float gain = 0.2f; // Gain factor for the delayed signal
    
    combPassFilter(path, delayMs, gain);

    float bassFrequency = 30.0f; // Frequency of the bass thump
    float thumpDuration = 0.3f; // Duration of each bass thump in seconds
    float threshold = 0.2f; // Amplitude threshold to trigger bass thump

    //Fine Tune values to fit your signal

    AudioFile<float> combFile;
    combFile.load("../audio-clips/audio-comb-filtered.wav");

    addBassThump(combFile, bassFrequency, thumpDuration, threshold);

    combFile.save("../audio-clips/dune-filter.wav", AudioFileFormat::Wave);
}


