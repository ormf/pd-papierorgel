#!/bin/bash
DIR=$HOME/work/programmieren/pd/papierorgel-pd

pd -rt -jack -channels 2 -send "id orgel01" $DIR/orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 2 -send "id orgel02" $DIR/orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 2 -send "id orgel03" $DIR/orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 2 -send "id orgel04" $DIR/orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 2 -send "id orgel05" $DIR/orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 2 -send "id orgel06" $DIR/orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 2 -send "id orgel07" $DIR/orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 2 -send "id orgel08" $DIR/orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 2 -send "id orgel09" $DIR/orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 2 -send "id orgel10" $DIR/orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 10 -send "id orgel01" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 10 -nogui -send "id orgel02" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 10 -nogui -send "id orgel03" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 10 -nogui -send "id orgel04" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 10 -nogui -send "id orgel05" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 10 -nogui -send "id orgel06" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 10 -nogui -send "id orgel07" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 10 -nogui -send "id orgel08" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 10 -nogui -send "id orgel09" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 10 -nogui -send "id orgel10" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 1 -send "id orgel01" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 1 -send "id orgel02" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 1 -send "id orgel03" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 1 -send "id orgel04" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 1 -send "id orgel05" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 1 -send "id orgel06" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 1 -send "id orgel07" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 1 -send "id orgel08" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 1 -send "id orgel09" orgelmodul-dsp-osc.pd &
# pd -rt -jack -channels 1 -send "id orgel10" orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 8 $DIR/papierorgel-gui.pd &
