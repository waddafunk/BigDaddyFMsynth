// OUR SYNTH
(
SynthDef.new(\fmSynth, {
	arg  freq, mRatio = 1, cRatio = 1,
	index =1, iScale = 5,
	atk = 0.01, rel = 3, cAtk = 4, cRel = (-4),
	outBus = 0,direct = 0.33,
	amp = 0.2, pan = 0, a = 1,
	effectBus,
	lpCutoff, hpCutoff;

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

// SYNTHDEF REVERB

(
SynthDef(\reverb,
{
arg inBus, outBus;
var dry, wet;
dry = In.ar (inBus);
wet = DelayN.ar(dry,0.048,0.048);
wet = Mix.arFill(7,{
CombL.ar(wet,0.1,LFNoise1.kr(Rand(0,0.1),0.04,0.05),1 )});
4.do({wet = AllpassC.ar(wet,0.05,
[Rand(0,0.05),Rand(0,0.05)],15) });
Out.ar(outBus, wet);
}
).add;
)


// SYNTH INSTANTATION
(
var bus = Bus.audio(s);
x =
Synth(\fmSynth,[\freq,300,\index,2,\modratiol,2.4,\outBus,0,\level,0.1, \effectBus, bus,\lpCutoff,600, \hpCutoff, 350 ]);

y =
Synth.after(x,\reverb,[\inBus,bus,\outBus,0]);

OSCdef('OSCreceiver', {
	arg msg;
	x.set(\freq, msg[1]);

},
"FMsynth/NoteOn")
)
