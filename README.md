# BigDaddy FM synthesizer

FM synthesizer with **juce-powered c++** graphic interface connected to a **supercollider** server. 
**All is needed to run the application is the two files found in the following link** 
[BigDaddyV1.1.zip](https://drive.google.com/file/d/1G9ZSSqRgZz3AXU1HTHx8N8j_sianmmLi/view?usp=sharing).

## Setup

<img src = "/images/Scd_interface.PNG" width = "1000" >

Unzip **"BigDaddyV1.1.zip"** and place it where you want to store it. Open first **"FM_receiver.scd"** with your [SuperCollider IDE](https://supercollider.github.io/download), connect your midi input, run the first five lines of the code and the subsequent task (pressing **ctrl+enter** one time when inside the task is sufficient to run all of it). After having booted the server open **"BigDaddy.exe"**: when the interface is loaded it will initialise all SuperCollider global variables and all their values will be printed on the SuperCollider post window. All it remains to do is setup and play.
 
*It is not essential to run first supercollider and then the .exe file but is recommended. Doing otherwise will not initialise Supercollider variables, which will be initialised only when changing their parameters and could result in abrupt variations*. 

We advice to set the oscs fRatio into integer numbers if you want to keep the sense of pitch intact. Otherwise you can just experiment.

## Interface

Switch between the two views by clicking on **"Oscillators"** or **"Matrix"** in the upper bar. All knobs can be set either by mouse wheel, mouse drag or keyboard input (click on the knob value and insert the desired value) Envelopes are set by mouse drag and filters by mouse drag, wheel and sweep.

### Oscillator view controls

<img src = "/images/Oscillator_Interface.PNG" width = "700" >

- Amp controls the amplitude of the wave;
- Fratio controls the ratio between the midi note input and the actual frequency of the oscillator. For example setting it to 1 will set the oscillator to the same frequency of the note corresponding to the midi input, to 3 frequency of the oscillator will be three times this value and so on;
- Phase controls the phase of the wave;
- Trigger freezes wave movement (optimal for example for relative phase adjustments);
- LfoA controls the amount of Lfo modulating the amplitude of the oscillator of the corresponding row;
- LfoFr controls the frequency of the Lfo modulating the frequency of the oscillator of the corresponding row;
- LfoRate is the rate of the Lfo;
- LfoPhase is the phase of the Lfo.
- Highpass and lowpass filters cutoff and gain are set by dragging, resonance by mouse wheel/vertical sweep and cutoff slope by horizontal sweep. The On/Off botton to the left of them routes the oscillator corresponding to their row to them.

### Matrix view controls

<img src = "/images/Matrix_Interface.PNG" width = "700" >

- 64 knobs corresponding to the modulation indexes of the various oscillators. Diagonal knobs correspond to feedback;
- 1 index envelope for each row, note that these envelopes can have negative release; 
- 1 Volume envelope;
- 1 Master Volume slider;
- 3 knobs controlling one the cutoff frequency of a lowpass filter filtering the output signal and the other two room and dry/wet mix of a reverb.
