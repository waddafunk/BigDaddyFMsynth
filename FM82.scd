MIDIClient.init;
MIDIIn.connectAll;
NetAddr("127.0.0.1", 57120);

(

Task({s.waitForBoot{
	var
	noSynths,synthArray,synTest,synTestArray,polyphon,reltime,debug,nodecoll;

	SynthDef(\feedback, {
		|in,out|

		var input;

		input = InFeedback.ar(in);

		Out.ar(out,input);
	}
	).send(s);

	SynthDef(\fmTex,
		{
			|
			t1,t2,t3,t4,in,out=0,amp=0,lev1,lev2,lev3,lev4,lev5,
			lfrate,lfoAmpDepth=0,freq,phase=0,pan=0,fmout=8,
			s1,m1,m2,m3,m4,m5,m6,m7,m8,fmouts,inbus=8,
			cur1,cur2,cur3,cur4,gate = 1,
			lfoPitDepth=0,lfoFade=0,envPitDepth,
			lpCutoff = 7000, lpRes = 1, hpCutoff = 30, hpRes = 1
			|

			var env,osc,input,lfo,lfofade;

			input = In.ar(inbus,1);

			env = EnvGen.kr(Env.new([lev1,lev2,lev3,lev4,lev5],[t1,t2,t3,t4],[cur1,cur2,cur3,cur4],3,4),gate,doneAction:2);

			lfofade = Line.kr(0.0001,1,lfoFade);

			lfo = SinOsc.ar(lfrate,0,lfofade);

			osc = SinOsc.ar(freq+(input)+(lfo*lfoPitDepth)+(env*envPitDepth),phase,1+(lfo*lfoAmpDepth),0)*env;

			osc = RLPF.ar(osc,lpCutoff,lpRes,1);
			osc = RHPF.ar(osc,hpCutoff,hpRes,1);

			Out.ar(s1,[osc*m1,osc*m2,osc*m3,osc*m4,osc*m5,osc*m6,osc*m7,osc*m8]);

			Out.ar(out,Pan2.ar(osc,pan,amp));
		}

	).send(s);


	s.sync;

	~feedback = Group.new;

	s.sync;

	~synth =  Group.new(~feedback,\addAfter).postln;

	s.sync;

	polyphon = 12;
	polyphon.do{|o|
		8.do{
			|i|
			Synth(\feedback,[\in,((8+i)+(16*o)),\out,((16+i)+(16*o))],target:~feedback)
		}
	};

	noSynths = 0;

	synTest = 0;

	synTestArray = polyphon.collect{0};

	synthArray = Array.newClear(128);
	nodecoll = 128.collect{List[]};


	~envtimes = 8.collect{[0.0,0.1,0.5,0.7,1.0]}.postln;

	~envlevs = 8.collect{[0.0,1.0,0.5,0.5,0.0]}.postln;

	~envPitDepth = 8.collect{0}.postln;

	~lfoAmpDepth = 8.collect{0.5}.postln;

	~lfoPitDepth = 8.collect{1}.postln;

	~lfoRate = 8.collect{3};

	~lfoFadeTime = 8.collect{4};

	~envcurves = 8.collect{[0,0,0,0]};

	~modlevs = 8.collect{8.collect{0}};

	~times = 8.collect{1};

	~fratio = 8.collect{|i| 8-i};

	~amplevs = 8.collect{0.1};

	~lpFilter = [1400, 1];

	~hpFilter = [40, 1];



	MIDIIn.noteOn_({ |src, chan, num, vel|
		case{noSynths < polyphon }
		{ synTest=0;

			if(synTestArray.includesEqual(num))
			{
				"wank".postln;
			}
			{
				"yay".postln;
			};

			synTest = synTestArray.detectIndex { |item| item == 0 };
			if(synTest.notNil) { synTestArray.put(synTest,num) } { /* else fail, maybe throw an error? */ };

			synthArray.put(num,
				8.collect{|i| var syn;

				syn =
					Synth(\fmTex,
						[
							\lev1,~envlevs[i][0],
							\lev2,~envlevs[i][1],
							\lev3,~envlevs[i][2],
							\lev4,~envlevs[i][3],
							\lev5,~envlevs[i][4],
							\t1,(~envtimes[i][1]-~envtimes[i][0])*~times[i],
							\t2,(~envtimes[i][2]-~envtimes[i][1])*~times[i],
							\t3,(~envtimes[i][3]-~envtimes[i][2])*~times[i],
							\t4,(~envtimes[i][3]-~envtimes[i][2])*~times[i],
							\cur1,~envcurves[i][0],
							\cur2,~envcurves[i][1],
							\cur3,~envcurves[i][2],
							\cur4,~envcurves[i][3],
							\freq,num.midicps*~fratio[i],
							\inbus,(16+i)+(synTest*16),
							\lfoPitDepth,~lfoPitDepth[i],
							\lfoAmpDepth,~lfoAmpDepth[i],
							\lfoFade,~lfoFadeTime[i],
							\lfrate,~lfoRate[i],
							\envPitDepth,~envPitDepth[i],
							\s1,8+(synTest*16),
							\m1,(num.midicps/10)*~modlevs[i][0],
							\m2,(num.midicps/10)*~modlevs[i][1],
							\m3,(num.midicps/10)*~modlevs[i][2],
							\m4,(num.midicps/10)*~modlevs[i][3],
							\m5,(num.midicps/10)*~modlevs[i][4],
							\m6,(num.midicps/10)*~modlevs[i][5],
							\m7,(num.midicps/10)*~modlevs[i][6],
							\m8,(num.midicps/10)*~modlevs[i][7],
							\amp,~amplevs[i]/8,

							\lpCutoff, ~lpFilter[0],
							\lpRes , ~lpFilter[1],
							\hpCutoff ,~hpFilter[0],
							\hpRes , ~hpFilter[1]

						],target:~synth
					);


				}
			);

			//z = Synth.after(s, \flanger, [\inBus,[0,1],\outBus,[0,1]]);

			reltime = 8.collect{|i|(~envtimes[i][3]-~envtimes[i][2])*~times[i]};
			reltime = reltime.maxItem;
			noSynths = noSynths +1;
		}
	});

	MIDIIn.noteOff_(

		{|src, chan, num, vel|

			synthArray[num].do{|syn| syn.set(\gate,0)};

			Routine({1.do{ var spot;
				spot = synTestArray.indicesOfEqual(num);
				synTestArray.put(spot,129);
				reltime.wait; noSynths = noSynths-1;
				synTestArray.put(spot,0);
					synTestArray.postln;
			}}).play;

		}

	);

}},AppClock).play);

// =======================================================================================

// msg[1] tells me the column  // msg[2] tells me the row // msg[3] tells me the value
OSCdef('OSCmodlev', {
	arg msg;
	msg.postln;
	~modlevels[msg[1]][msg[2]] = msg[3];
},
"FmSynth/modLev");

// ========================================================================================

// msg[1] says me the row   // msg[2] tells me the row // msg[3] the new level // msg[4] the new time

OSCdef('OSCmodenv', {
	arg msg;
	~envlevs[msg[1]][msg[2]] = msg[3]
	~envtimes[msg[1]][msg[2]] = msg[4]
},
"FmSynth/modEnv");

// ========================================================================================

// msg[1] tells me the input, // msg[2] tells me the amp

OSCdef('OSCLFOamp', {
	arg msg;
	var index = msg[1];
	~lfoAmpDepth[index] = msg[2];
},
"FmSynth/lfoAmp");

// ========================================================================================

// msg[1] tells me the input, // msg[2] tells me the amp

OSCdef('OSCLFOpit', {
	arg msg;
	var index = msg[1];
	~lfoPitDepth[index] = msg[2];
},
"FmSynth/lfoPitch");

// ========================================================================================

// msg[1] tells me the input, // msg[2] tells me the rate

OSCdef('OSCLFOrate', {
	arg msg;
	var index = msg[1];
	~lfoRate[index] = msg[2];
},
"FmSynth/lfoRate");

// ========================================================================================

// msg[1] tells me the input, // msg[2] tells me the value

OSCdef('OSCfRatio', {
	arg msg;
	var index = msg[1];
	~fRatio[index] = msg[2];
},
"FmSynth/fRatio");

// ========================================================================================

// msg[1] tells me the input, // msg[2] tells me the amplitude

OSCdef('OSCamps', {
	arg msg;
	var index = msg[1];
	~amplevs[index] = msg[2];
},
"FmSynth/amps");

// ========================================================================================

// msg[1] tells me the filter moved, // msg[2] tells me cutoff // msg[3] the resonance (height)
OSCdef('OSCfilter', {
	arg msg;
	var index = msg[1];
	if( index == 1,{~lpFilter = [msg[2], msg[3]];} )
	if( index == 0,{~hpFilter = [msg[2], msg[3]];} )

	~hpFilter = [40, 1];;
},
"FmSynth/filter");

// =======================================================================================

~lpFilter = [1200,1];


// =======================================================================================

(
SynthDef(\delay, {arg delaytime=0.4;
var input, effect;
input=In.ar(0,2); //get two channels of input starting (and ending) on bus 0
effect= DelayN.ar(input, 1,delaytime, mul: 0.2); //max delay of one second
Out.ar(0,effect); //adds to bus 0
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