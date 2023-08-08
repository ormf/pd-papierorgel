#!/bin/bash
pd -rt -jack -channels 1 -send "id orgel01" orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 1 -nogui -send "id orgel02" orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 1 -nogui -send "id orgel03" orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 1 -nogui -send "id orgel04" orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 1 -nogui -send "id orgel05" orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 1 -nogui -send "id orgel06" orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 1 -nogui -send "id orgel07" orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 1 -nogui -send "id orgel08" orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 1 -nogui -send "id orgel09" orgelmodul-dsp-osc.pd &
pd -rt -jack -channels 1 -nogui -send "id orgel10" orgelmodul-dsp-osc.pd &
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
pd -rt -jack -channels 8 papierorgel-gui.pd &
