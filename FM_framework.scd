// OUR SYNTH
MIDIClient.init;
MIDIIn.connectAll;

(
SynthDef.new(\fmSynth, {
	arg  freq = 200, mRatio = 1, cRatio = 1,
	index =1, iScale = 5,
	atk = 0.01, rel = 3, cAtk = 4, cRel = (-4),
	outBus = 0,direct = 0.33,
	amp = 0.2, pan = 0, a = 1,
	effectBus,
	lpCutoff = 300, hpCutoff= 30;

	var car, mod, env, iEnv, out;
	// iENV for synthesisation of acoustic like instruments
	iEnv = EnvGen.kr(
		Env.new(
			[index, index * iScale, index], // start at a index basic value , move to the scale and then fall back.
			[atk, rel], //  it has same attack and release time of the time envelope
			[cAtk, cRel] //the length of
		)
	);

	env = EnvGen.kr(
		Env.perc(atk, rel, curve: [cAtk, cRel]), doneAction: 2);

	mod = SinOsc.ar(freq * mRatio, mul:freq * mRatio * iEnv);   // modAmp * index
	car = SinOsc.ar(freq * cRatio + mod) * env * amp;
	car = Pan2.ar(car,pan);

	// THERE ARE TWO FILTERS ALWAYS ACTING; AN HIGHPASS AND A LOWPASS
	out = LPF.ar(car,lpCutoff,1,0);
	out = HPF.ar(out,hpCutoff,1,0);

	Out.ar(effectBus,out * (1 - direct));
	Out.ar(out,(out * direct).dup);
}).add;
)

// SYNTHDEF REVERB, DELAY, PHASER, FLANGER, COMPRESSOR, LIMITER

(
SynthDef(\reverb,
{
arg inBus, outBus;
var dry, wet;
dry = In.ar (inBus);
wet = Mix.arFill(7,{
CombL.ar(wet,0.1,LFNoise1.kr(Rand(0,0.1),0.04,0.05),1 )});
4.do({wet = AllpassC.ar(wet,0.05,
[Rand(0,0.05),Rand(0,0.05)],15) });
Out.ar(outBus, wet);
}
).add;
)

(
SynthDef(\delay, {arg delaytime=0.4;
var input, effect;
input=In.ar(0,2); //get two channels of input starting (and ending) on bus 0
effect= DelayN.ar(input, 1,delaytime); //max delay of one second
Out.ar(0,effect); //adds to bus 0
}).add;
)


(
SynthDef(\phaser, {arg freq=0.2;
var input, effect;
input=In.ar(0,2); //get two channels of input starting (and ending) on bus 0
effect= AllpassN.ar(input,0.02,SinOsc.kr(freq,0,0.01,0.01)); //max delay of 20msec
Out.ar(0,effect); //adds to bus 0 where original signal is already playing
}).add;
)


(
SynthDef(\flanger, {arg flangefreq=0.1, fdback=0.3;
var input, effect;
input=In.ar(0,2); //get two channels of input starting (and ending) on bus 0
input= input+ LocalIn.ar(2); //add some feedback
effect= DelayN.ar(input,0.02,SinOsc.kr(flangefreq,0,0.005,0.005)); //max delay of 20msec
LocalOut.ar(fdback*effect);
Out.ar(0,effect); //adds to bus 0 where original signal is already playing
}).add;
)

(
SynthDef(\limiter, {arg gain=1;
var input, effect;
input=In.ar(0,2); //get two channels of input starting (and ending) on bus 0
effect= Limiter.ar(gain*input,0.99, 0.01);
ReplaceOut.ar(0,effect); //replaces bus 0 where original signal is already playing
}).add;
)






// SYNTH INSTANTATION 1 : only OSC STUFF
(
var bus = Bus.audio(s);
x =
Synth(\fmSynth,[\freq,300,\index,2,\modratiol,2.4,\outBus,0,\level,0.1, \effectBus, bus,\lpCutoff,600, \hpCutoff, 350 ]);

//y =
//Synth.after(x,\reverb,[\inBus,bus,\outBus,0]);

a = Synth.tail(s, \delay);
c = Synth.tail(s, \flanger);
d = Synth.tail(s, \limiter);

OSCdef('OSCreceiver', {
	arg msg;
	x.set(\freq, msg[1]);

},
"FMsynth/NoteOn")
)



// SYNTH INSTANTATION 2 : only MIDI STUFF
(
var keys;
var bus = Bus.audio(s);
keys = Array.newClear(128);

~noteOnFunc = {
	arg src, chan, num, vel;
	var node;
	node = keys.at(num);

	// to deal with notes playing in the same moment
	if (node.notNil, {
		node.release;
		keys.put(num,nil);
	});

	node = Synth.tail(nil, \fmSynth, [\freq, num.midicps, \amp, vel/127
		,\outBus,0,\level,0.1, \effectBus, bus,\lpCutoff,600, \hpCutoff, 350]);

	y = Synth.tail(node,\reverb,[\inBus,bus,\outBus,0]);
	z = Synth.tail(y, \delay, [\inBus,bus,\outBus,0]);
	keys.put(num, node);
	[chan,num,vel/127].postln;
};

MIDIIn.addFuncTo(\noteOn, ~noteOnFunc);

~noteOffFunc = {
	arg src, chan, num , vel;
	var node;
	node = keys.at(num);
	if(node.notNil, {
		node.set(\gate,0);
		node.release;
		keys.put(num,nil);}
	);
};

MIDIIn.addFuncTo(\noteOff, ~noteOffFunc);
)

MIDIIn.removeFuncFrom(\noteOn, ~noteOnFunc);
MIDIIn.removeFuncFrom(\noteOff, ~noteOffFunc);


(
SynthDef('delay',
	{ arg  inBus = 0, outBus,
	       delTime= 0.4, feedback = 0.6;
	var dry, wet, input;

	dry = In.ar(inBus);
	wet = DelayL.ar(dry,0.2,0.2);
		Out.ar(outBus, wet);
}).add;
)