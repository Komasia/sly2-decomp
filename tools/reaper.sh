#!/bin/bash
# kill wibo/compiler processes running longer than 180 s (wibo occasionally hangs)
while true; do
  ps -eo pid,etimes,args | awk '$2>180 && /wibo/ && !/awk/ {print $1}' | xargs -r kill -9 2>/dev/null
  sleep 30
done
