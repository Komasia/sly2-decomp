#!/bin/sh
# usage: pool.sh draft.cpp  -> spill-reg first-seen order + matchtool score
cd ~/sly2-decomp
W=/tmp/w22/p$$
bash tools/dump.sh $W "$1" -da -dg >/dev/null 2>&1
awk '/^Spilling for insn/{ins=$4} /^Spilling reg/{ if(!($3 in s)){s[$3]=1; printf "%s@%s ", $3, ins}} END{print ""}' $W/d.cc.greg
python3 tools/matchtool.py check "$1" func_0022DE88 2>/dev/null | head -1
rm -rf $W
