## Various Audio Signal Filters


### Application of different filters on audio files:

1. **Low Pass Filter FIR (Finite Impulse Response)**
    1. Filters out high frequencies and ***allows low*** frequencies to pass.
    2. Basic:       y = (x1 + x2)/2 (1st order)
    3. Advanced:    y= (x1 + x2 + x3 +x4)/4 (2nd Order)
    4. Multi Order:
        Recognize that this problem is merely the Moving average problem.

        > "Mathematically, a moving average is a type of convolution. Thus in signal processing it is viewed as a low-pass finite impulse response filter. Because the boxcar function outlines its filter coefficients, it is called a boxcar filter. It is sometimes followed by downsampling."- [Wikipedia](https://en.wikipedia.org/wiki/Moving_average)
        
2. **High Pass Filter (Finite Impulse Response)**
    1. Filters out low frequencies and ***allows high*** frequencies to pass.
    2. Basic:   y= ax1 + (a-1)x2 where 0<=a<=1 
3. **Comb Pass Filter**
    1. Once you hear the audio, we know this as the robot voice filter. It delays the audio and filters out bands of frequencies resulting in a comb shape when on a frequency domain graph
4. **Dune Audio Filter**
    1. Recreate the voice from Dune. Example:[Video](https://www.youtube.com/watch?v=uJvv3Ee-k1M)
    2. Execution
        - Take original Audio,
        - Pass audio file through a comb pass filter
        - Add a thump/bass signal on top of audio file

___
## Take Aways
I do not have a good voice for Dune. This was a great exploration of C++ and audio signal design and processing. More Fine tuning can be done for each audio signal.

### Future Features/ Topics
* Discrete Fourier Transform (Discrete Time Fourier Transform)
    * Our sound files are not continuous.
    * Fast Fourier Transform
* Add more filter functions.
* Make it a live filer
* Add Gui element

### Use of AI Statement:
ChatGPT-4o was used in the creation of some functions.

### Resources:
1. [Youtube Series](https://www.youtube.com/watch?v=ffVcEvYvtcQ) 
2. [Low Pass Filter](https://dobrian.github.io/cmp/topics/filters/lowpassfilter.html)
3. [Github Page](https://dobrian.github.io/cmp/)
4. [Moving Averge Problem](https://pages.mtu.edu/~shene/COURSES/cs201/NOTES/chap08/mov-avg.html#:~:text=Given%20a%20sequence%20of%20n,1%20elements%20as%20shown%20above.&text=Thus%2C%20the%20moving%20average%20sequence,4%2B1%3D7%20values)
