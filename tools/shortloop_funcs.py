#!/usr/bin/env python3
"""List functions whose target code contains a short backward loop (<= 6 instructions incl. delay slot)."""
import sys, os
sys.path.insert(0, os.path.dirname(__file__)); import matchtool as M, rabbitizer
def has_short_loop(a, s):
    w = M.target_words(a, s)
    for i, x in enumerate(w):
        ins = rabbitizer.Instruction(x, vram=a + 4 * i, category=rabbitizer.InstrCategory.R5900)
        if not ins.isBranch() or ins.isUnconditionalBranch(): continue
        t = (ins.getBranchVramGeneric() - a) // 4
        if 0 <= t <= i and i - t + 2 <= 6: return True
    return False
if __name__ == '__main__':
    f = M.load_functions()
    out = [n for n, (a, s) in f.items() if M.TEXT_VA <= a < M.TEXT_VA + M.TEXT_SIZE and has_short_loop(a, s)]
    open(os.path.join(M.ROOT, 'build', 'shortloop_funcs.txt'), 'w').write('\n'.join(out) + '\n')
    print(len(out))
