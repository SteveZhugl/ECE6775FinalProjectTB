#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/mts247/ece6775/FinalProject/ECE6775FinalProjectTB/softmax/softmax_proj.prj/solution1/.autopilot/db/a.g.bc ${1+"$@"}
