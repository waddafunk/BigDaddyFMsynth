# FMsynth

FM synthesizer with **juce-powered c++** graphic interface connected to a **supercollider** server. 
All is needed to run the application is the two files found in **"BigDaddyV1.1.zip"**.

## Setup

Unzip **"BigDaddyV1.1.zip"** and place it where you want to store it. Open first **"FM_receiver.scd"** with your [SuperCollider IDE](https://supercollider.github.io/download),connect your midi input, run the first five lines of the code and the subsequent task (pressing **ctrl+enter** one time when inside the task is sufficient to run all of it). After having booted the server open **"BigDaddy.exe"**: when the interface is loaded it will initialise all SuperCollider global variables and all their values will be printed on the SuperCollider post window. All it remains to do is setup and play.

<img src = "/images/Scd_interface.PNG" width = "1000" >
 
*It is not essential to run first supercollider and then the .exe file but is recommended. Doing otherwise will not initialise Supercollider variables, which will be initialised only when changing their parameters and could result in abrupt variations*. 
