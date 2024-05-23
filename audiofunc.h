#ifndef audiofunc_h_
#define audiofunc_h_

#include <iostream>
#include "AudioFile.h"
#include <fstream>

/*
    Applies a Low or High Pass Filter on an audio file

    @param path the path to the audio file
    @param coef the coeficient of the filter
    @param type filter choise, FALSE for low  
*/
void lowAndHighPassFilter(const std::string &path, float coef = 0.5f, const bool type = false);

/*
    Applies a Comb Pass Filter on an audio file

    @param path the path to the audio file
    @param delayMS the milisecond delay of the signal
    @param gain the gain of the audio signal
*/
void combPassFilter(const std::string &path, float delayMs, float gain);

/*

    Apples a Dune Audio Effect on to audio files.

    @param path the path to the audio file

*/
void duneFilter(const std::string &path);
#endif