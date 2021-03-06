MIDIClient.init;
MIDIIn.connectAll;
NetAddr("127.0.0.1", 57120);
s.options.memSize = 80000;
FreqScope.new;

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
			t1,t2,t3,t4,lev2,lev3,lev4,lev5,                         // envelopes vars
			cur1,cur2,cur3,cur4,gate = 1,envPitDepth,
			amp=0,lev1 = 0,freq,phase,pan = 0,                       // oscillators vars
			lfrate,lfoAmpDepth=0,lfoPitDepth=0,lfoFade=0,lfophase,   // lfo vars
			in,out=0,s1,m1,m2,m3,m4,m5,m6,m7,m8,inbus=8,             // fm vars and buses
			lpCutoff, lpRes, lpGain,                                 // filters vars
			hpCutoff , hpRes, hpGain,
			strtv = 0, atkv, decv, susv, relv,                       // master Env vars
			tm1,tm2,tm3,tm4, masterEnv,
			masterGain,masterCut, mix, room                          // others
			|

			var env,osc,input,lfo,lfofade;

			input = In.ar(inbus,1);

			env = EnvGen.kr(Env.new([lev1,lev2,lev3,lev4,lev5],[t1,t2,t3,t4],[cur1,cur2,cur3,cur4],3,4),gate,doneAction:2);
            masterEnv = EnvGen.kr(Env.new([strtv, atkv, decv, susv, relv],[tm1,tm2,tm3,tm4],[cur1,cur2,cur3,cur4],3,4),gate,doneAction:2);
			lfofade = Line.kr(0.0001,1,lfoFade);
			lfo = SinOsc.ar(lfrate,lfophase,lfofade);

			// oscillator declaration + chain of effects
			osc = SinOsc.ar(freq+ (input)+(lfo*lfoPitDepth)+(env*envPitDepth),phase,1+(lfo*lfoAmpDepth),0)*env * masterEnv;
			osc = RLPF.ar(osc,lpCutoff,lpRes,1);
			osc = RHPF.ar(osc,hpCutoff,hpRes,1);
			osc = LPF.ar(osc, masterCut, 1);
			osc = FreeVerb.ar(osc, mix,room, 0.2);

			// first Out is a feedback, the signal returns inside as input, the second is the actual output
			Out.ar(s1,[osc*m1,osc*m2,osc*m3,osc*m4,osc*m5,osc*m6,osc*m7,osc*m8]);
			Out.ar(out,Pan2.ar(osc,pan,amp*masterGain));
		}

	).send(s);

// connect the group chain of global object, on which we will attach the two synthdefs
	s.sync;
	~feedback = Group.new;
	s.sync;
	~synth =  Group.new(~feedback,\addAfter);
	s.sync;

	// first synthdef attachment (~feedback, polyphony setting)
	polyphon = 6;
	polyphon.do{|o|
		8.do{
			|i|
			Synth(\feedback,[\in,((8+i)+(16*o)),\out,((16+i)+(16*o))],target:~feedback);
		};
	};

// control and grouping variables
	noSynths = 0;
	synTest = 0;
	synTestArray = polyphon.collect{0};
	synthArray = Array.newClear(128);
	nodecoll = 128.collect{List[]};

// global variables database representing the state of the synth
	~envtimes    = 9.collect{[0.1,0.5,0.7,0.2]};
	~envlevs     = 9.collect{[1.0,0.5,0.5,0.0]};
	~envPitDepth = 8.collect{0};
	~envcurves   = 8.collect{[0,0,0,0]};

	~masterKnobs = [1,0,0, 20000];

	~lfoAmpDepth = 8.collect{0.5};
	~lfoPitDepth = 8.collect{1};
	~lfoRate     = 8.collect{3};
	~lfoFadeTime = 8.collect{4};
	~lfoPhase    = 8.collect{0};

	~modlevs     = 8.collect{8.collect{0}};
	~amplevs     = 8.collect{1};
	~fratio      = 8.collect{|i| 8-i};
	~oscphase    = 8.collect{0};
	~lpFilter    = 8.collect{[7000, 1,1]};
    ~hpFilter    = 8.collect{[40, 1,1]};

// Each time a note is played we set the synth accordingly to the database
	MIDIIn.noteOn_({ |src, chan, num, vel|
		case{noSynths < polyphon }
		{ synTest=0;
			"BDHN".postln;
			[num, vel].postln;

			synTest = synTestArray.detectIndex { |item| item == 0 };
			if(synTest.notNil) { synTestArray.put(synTest,num) } { "what?".postln; };

			synthArray.put(num,
				8.collect{|i| var syn;

				// second Synthdef attachment (called eight times, grouped into ~synth)
				syn =
					Synth(\fmTex,
						[
							\masterGain,~masterlev,
							\lev2,~envlevs[i][0],
							\lev3,~envlevs[i][1],
							\lev4,~envlevs[i][2],
							\lev5,~envlevs[i][3],
							\t1,(~envtimes[i][0]),
							\t2,(~envtimes[i][1]),
							\t3,(~envtimes[i][2]),
							\t4,(~envtimes[i][3]),
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
							\lfophase, ~lfoPhase[i],

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
							\amp,~amplevs[i]/8*vel/128,
							\phase, ~oscphase[i],

							\lpCutoff, ~lpFilter[i][0],
							\lpRes , ~lpFilter[i][1],
							\lpGain, ~lpFilter[i][2],
							\hpCutoff ,~hpFilter[i][0],
							\hpRes , ~hpFilter[i][1],
							\hpGain, ~hpFilter[i][2],

							\atkv,~envlevs[8][1],
						    \decv,~envlevs[8][2],
						    \susv,~envlevs[8][3],
						    \relv,~envlevs[8][4],
						    \tm1,(~envtimes[8][0]),
						    \tm2,(~envtimes[8][1]),
						    \tm3,(~envtimes[8][2]),
						    \tm4,(~envtimes[8][3]),
							\masterGain, ~masterKnobs[0],
							\masterCut,~masterKnobs[3],
							\mix,~masterKnobs[1],
							\room,~masterKnobs[2]
						],target:~synth
					);
				}
			);
			reltime = 8.collect{|i|(~envtimes[i][3]-~envtimes[i][2])};
			reltime = reltime.maxItem;
			noSynths = noSynths +1;
		}
	});

// Then we release it
	MIDIIn.noteOff_(

		{|src, chan, num, vel|

			synthArray[num].do{|syn| syn.set(\gate,0)};

			Routine({1.do{ var spot;
				spot = synTestArray.indicesOfEqual(num);
				synTestArray.put(spot,129);
				reltime.wait; noSynths = noSynths-1;
				synTestArray.put(spot,0);
			}}).play;
		}
	);

//________________________________________________________________________________________
// =============================== OSC MESSAGES SECTION ==================================
// =======================================================================================

// msg[1] tells me the column  // msg[2] tells me the row // msg[3] tells me the value
OSCdef('OSCmatrix', {
		arg msg;
	msg.postln;

	~modlevs[msg[1]][msg[2]] = msg[3];
	~modlevs.postln;
},
"FmSynth/Matrix");

// ======================================================================================

// discriminator tells me the variable to update// index the relative oscillator // the third the value
OSCdef('OSCoscillator', {
	arg msg;
	var discriminator = msg[2], index = msg[1], value = msg[3];
		msg.postln;
	if(discriminator == 0, {~amplevs[index] = value});
	if(discriminator == 1, {~fratio[index] = value});
	if(discriminator == 2, {~oscphase[index] = value});
},
"FmSynth/Oscillator");

// ======================================================================================

// discriminator tells me the variable to update// index the relative oscillator // the third the value
OSCdef('OSCLfo', {
	arg msg;
	var discriminator = msg[2], index = msg[1], value = msg[3];
	if(discriminator == 0, {~lfoAmpDepth[index] = value;
			                ~synth.set(\lfoAmpDepth, value);});
	if(discriminator == 1, {~lfoPitDepth[index] = value;
			                ~synth.set(\lfoPitDepth, value);});
	if(discriminator == 2, {~lfoRate[index] = value;
			                ~synth.set(\lfrate, value);});
	if(discriminator == 3, {~lfoPhase[index] = value;
			                ~synth.set(\lfophase, value);});
},
"FmSynth/Lfo");

// ======================================================================================

// discriminator tells me the variable to update// msg[2] tells me the value
OSCdef('OSCmaster', {
	arg msg;
	var discriminator = msg[1], value = msg[2];
		if(discriminator == 0, {~masterKnobs[3] = value;
			                    ~synth.set(\masterCut, value);});
		if(discriminator == 1, {~masterKnobs[2] = value;
			                    ~synth.set(\room, value);});
		if(discriminator == 2, {~masterKnobs[1] = value;
			                    ~synth.set(\mix, value);});
		if(discriminator == 3, {~masterKnobs[0] = value  });
		//msg.postln;
},
"FmSynth/Master");

// ======================================================================================

// the index tells me the relative oscillator // then we have the level and adjacent times
OSCdef('OSCenvAtk', {
	arg msg;
	var index = msg[1], atklev = msg[2], atktime = msg[3], dectime = msg[4];
		~envlevs[index][0] = atklev;
		~envtimes[index][0] = atktime;
		~envtimes[index][1] = dectime;
	msg.postln;
},
"FmSynth/Envelope/Attack");

// the index tells me the relative oscillator // then we have the level and adjacent times
OSCdef('OSCenvDec', {
	arg msg;
	var index = msg[1], declev = msg[2], dectime = msg[3], sustime = msg[4];
		~envlevs[index][1] = declev;
		~envtimes[index][1] = dectime;
		~envtimes[index][2] = sustime;
	msg.postln;
},
"FmSynth/Envelope/Decay");

// the index tells me the relative oscillator // then we have the level and adjacent times
OSCdef('OSCenvSus', {
	arg msg;
	var index = msg[1], suslev = msg[2], sustime = msg[3], reltime = msg[4];
		~envlevs[index][2] = suslev;
		~envtimes[index][2] = sustime;
		~envtimes[index][3] = reltime;
		msg.postln;
},
"FmSynth/Envelope/Sustain");


// the index tells me the relative oscillator // then we have the level and adjacent times
OSCdef('OSCenvRel', {
	arg msg;
	var index = msg[1], rellev = msg[2], reltime = msg[3];
		~envlevs[index][3] = rellev;
		~envtimes[index][3] = reltime;
		msg.postln;
},
"FmSynth/Envelope/Release");

// =====================================================================================

// type tells me the filter type// index the relative oscillator // the others are values
OSCdef('OSCfilters', {
	arg msg;
		var type = msg[1], index = msg[2], cutoff = msg[3], res = msg[4], gain = msg[5];
		if( type == 1,
		   {~synth.set(\lpCutoff, cutoff);
		    ~synth.set(\lpRes, res);
		    ~synth.set(\lpGain, gain);
			~lpFilter[index][0] = cutoff;
		    ~lpFilter[index][1] = res;
		    ~lpFilter[index][2] = gain;
			});

		if (type == 0,
		   {~synth.set(\hpCutoff, cutoff);
		    ~synth.set(\hpRes, res);
		    ~synth.set(\hpGain, gain);
			~hpFilter[index][0] = cutoff;
		    ~hpFilter[index][1] = res;
		    ~hpFilter[index][2] = gain;});
		//msg.postln;
	},
"FmSynth/Filter");

// type tells me the filter type// index the relative oscillator // the state disables the filter
// whenever the state it's 1, JUCE will send a FmSynth/Filter message to revert to previous conditions

OSCdef('OSCfilterState', {
	arg msg;
		var type = msg[1], index = msg[2], state = msg[3];
		if(type == 0,
			{if(state == 0, { ~hpFilter[index] = [20,1,1] });
		});
		if (type == 1, {
			if(state == 0, { ~lpFilter[index] = [20000,1,1];});
		});
		msg.postln;
},
"FmSynth/Filter/State");

// ========================== END OSC MESSAGES SECTION ==================================
// ======================================================================================
	"Let's Go".postln;
}},AppClock).play);

(1.asString ++ "sss").postln;