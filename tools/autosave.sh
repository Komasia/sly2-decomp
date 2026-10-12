#!/bin/bash
# Background safety net: every INTERVAL seconds, commit the whole working tree (respecting .gitignore)
# to the `autosave` branch on GitHub and refresh the local snapshot tarball.
# It never touches `main`, the checked-out branch, or the normal git index, so `main` stays
# "verified matches only" and in-progress agent work is still backed up.
# usage: nohup tools/autosave.sh [INTERVAL] > build/autosave.log 2>&1 &
cd "$(dirname "$0")/.." || exit 1
INTERVAL=${1:-900}
IDX=/tmp/sly2_autosave.idx
while true; do
  (
    export GIT_INDEX_FILE=$IDX
    git read-tree HEAD
    git add -A . 2>/dev/null
    tree=$(git write-tree)
    parent=$(git rev-parse -q --verify refs/heads/autosave || git rev-parse HEAD)
    if [ "$(git rev-parse "$parent^{tree}")" != "$tree" ]; then
      c=$(git commit-tree "$tree" -p "$parent" -p HEAD -m "autosave $(date -u +%Y-%m-%dT%H:%MZ)")
      git update-ref refs/heads/autosave "$c"
      git push -q -f origin autosave && echo "$(date -u +%H:%M) pushed $c" || echo "$(date -u +%H:%M) push failed"
    else
      echo "$(date -u +%H:%M) no changes"
    fi
  )
  bash tools/snapshot.sh >/dev/null 2>&1
  sleep "$INTERVAL"
done
