<Qucs Schematic 25.2.0>
<Properties>
  <View=93,116,1343,858,1.2904,45,90>
  <Grid=10,10,1>
  <DataSet=Audio Simulation.dat>
  <DataDisplay=Audio Simulation.dpl>
  <OpenDisplay=0>
  <Script=Audio Simulation.m>
  <RunScript=0>
  <showFrame=0>
  <FrameText0=Title>
  <FrameText1=Drawn By:>
  <FrameText2=Date:>
  <FrameText3=Revision:>
</Properties>
<Symbol>
</Symbol>
<Components>
  <OpAmp OP1 1 670 390 -26 42 0 0 "1e6" 1 "15 V" 0>
  <GND * 1 600 380 0 0 0 0>
  <C C1 1 420 410 -26 17 0 0 "1uF" 1 "" 0 "neutral" 0>
  <R R1 1 520 410 -26 15 0 0 "120k" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "US" 0>
  <R R2 1 670 530 -26 15 0 0 "2k" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "US" 0>
  <C C2 1 670 620 -26 17 0 0 "265nf" 1 "" 0 "neutral" 0>
  <GND * 1 250 500 0 0 0 0>
  <Vrect V1 1 250 440 18 -26 0 1 "3.3 V" 1 "454us" 1 "454us" 1 "1 ns" 0 "1 ns" 0 "0 ns" 0 "1.2 V" 1>
  <.TR TR1 1 250 580 0 56 0 0 "lin" 1 "0" 1 "1 ms" 1 "200" 0 "Trapezoidal" 0 "2" 0 "1 ns" 0 "1e-16" 0 "150" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "26.85" 0 "1e-3" 0 "1e-6" 0 "1" 0 "CroutLU" 0 "no" 0 "yes" 0 "0" 0>
</Components>
<Wires>
  <250 410 390 410 "" 0 0 0 "">
  <450 410 490 410 "" 0 0 0 "">
  <550 410 620 410 "" 0 0 0 "">
  <600 370 600 380 "" 0 0 0 "">
  <600 370 640 370 "" 0 0 0 "">
  <620 410 620 530 "" 0 0 0 "">
  <620 530 620 620 "" 0 0 0 "">
  <700 620 720 620 "" 0 0 0 "">
  <720 530 720 620 "" 0 0 0 "">
  <700 530 720 530 "" 0 0 0 "">
  <720 390 720 530 "" 0 0 0 "">
  <710 390 720 390 "" 0 0 0 "">
  <720 390 840 390 "" 0 0 0 "">
  <620 530 640 530 "" 0 0 0 "">
  <620 620 640 620 "" 0 0 0 "">
  <620 410 640 410 "" 0 0 0 "">
  <250 470 250 500 "" 0 0 0 "">
  <840 390 840 390 "AudioOut" 870 360 0 "">
  <250 410 250 410 "PicoPWM" 280 380 0 "">
</Wires>
<Diagrams>
  <Rect 790 680 376 248 3 #c0c0c0 1 00 0 0 20 100 1 -1 0.5 1 1 -1 0.5 1 315 0 225 1 0 0 "" "" "">
	<"Pico PWM" #0000ff 0 3 0 0 0>
  </Rect>
</Diagrams>
<Paintings>
</Paintings>
