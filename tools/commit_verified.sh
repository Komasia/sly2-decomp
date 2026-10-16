#!/bin/bash
# Commit changed/new files under src/ only if every function in them is an exact MATCH; also commit notes and
# build/hand_wip drafts. Pushes to main without the graph hook (the graph is refreshed at the end of each round).
cd "$(dirname "$0")/.." || exit 1
ok=(); bad=()
for f in $(git status --porcelain src | awk '{print $NF}'); do
  [ -f "$f" ] || continue
  out=$(timeout 300 python3 tools/matchtool.py check "$f" 2>&1)
  n=$(echo "$out" | grep -c '@0x'); m=$(echo "$out" | grep -c ': MATCH')
  if [ "$n" -gt 0 ] && [ "$n" = "$m" ]; then ok+=("$f"); else bad+=("$f"); fi
done
git add "${ok[@]}" notes build/hand_wip 2>/dev/null
git diff --cached --quiet && { echo "nothing verified to commit; unverified: ${bad[*]}"; exit 0; }
names=$(for f in "${ok[@]}"; do basename "${f%.*}"; done | tr '\n' ' ')
git commit -q -m "${#ok[@]} verified matches${names:+: $names}

Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>
Claude-Session: https://claude.ai/code/session_01MyNuwXDFhBWVGHJy1N4W4y"
git push -q --no-verify origin main && echo "pushed ${#ok[@]}: $names"; [ ${#bad[@]} -gt 0 ] && echo "left uncommitted (not matching yet): ${bad[*]}"
exit 0
