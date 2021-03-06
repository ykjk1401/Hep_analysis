#!/bin/sh

MODULE=qualitycheck
HBKFILE=test.hbk
# OUTFILE=test.dat
INFILE= ./../test.mdst
# INFILE=bfsa07:/bdata/dstprod/dat/e000031/HadronBJ/0429/on_resonance/01/HadronBJ-e000031r000152-b20040429_2253.mdst
# INFILE=bfsa02:/bdata/dstprod/dat/e000051/HadronBJ/0307/on_resonance/01/HadronBJ-e000051r000199-b20070307_1108.mdst

NEVENT=12

basf <<EOF
path create main
path create analysis
path add_module main fix_mdst
path add_condition main >:0:analysis
path add_condition main <=:0:KILL
path add_module analysis ${MODULE}
initialize
histogram define ${HBKFILE}
process_event ${INFILE} ${NEVENT}
output close
terminate
EOF
