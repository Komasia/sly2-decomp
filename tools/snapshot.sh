#!/bin/bash
# Pack everything that isn't regenerable into /mnt/user-data/outputs/sly2_decomp_latest.tgz
cd /home/claude/decomp
tar czf /mnt/user-data/outputs/sly2_decomp_latest.tgz --exclude='*.o' --exclude='__pycache__' \
  README.md docs notes src include config build/hand_wip build/context.h build/signatures.csv \
  $(ls tools/*.py tools/*.sh 2>/dev/null) 2>/dev/null
ls -la /mnt/user-data/outputs/sly2_decomp_latest.tgz
