<CsoundSynthesizer> 

<CsOptions> 
</CsOptions> 

<CsInstruments> 
sr      =      	44100 
ksmps  	=     	10
nchnls	=	2


	instr 1

kcps = cpsmidinn(p4) ;convert from midi note number to cycles per second
kenv adsr .1, .1, .7, .2
aout oscil kenv*p5, kcps, 1
outs aout, aout

	endin


</CsInstruments> 
<CsScore>

f 1 0 65536 10 1 ;sine osc table

i1 0 3600 60  0

e

</CsScore> 
</CsoundSynthesizer>
