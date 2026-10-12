# usage: python3 build/hand_wip/hyb_asm_experiment.py FILE.c NAME [extra cflags] [-v]
# experiment: 2.95.3 with reorg, then un-fill backward-branch delay slots, assemble with GNU as (gnu_reorder.assemble)
import sys, os, re, subprocess
sys.path.insert(0, '/home/claude/decomp/tools')
os.chdir('/home/claude/decomp')
import matchtool, gnu_reorder
src, name = sys.argv[1], sys.argv[2]
extra = [a for a in sys.argv[3:] if a != '-v']
import tempfile
S = tempfile.mkdtemp(prefix='hyb')
d = 'tools/compilers/bundle/ee-gcc2.95.3-136'
cc = os.path.join(d, 'bin', 'ee-gcc.exe')
lib = os.path.join(d, 'lib/gcc-lib/ee/2.95.3') + '/'
s = S + '/h.s'
p = subprocess.run(['tools/wibo-i686', cc, '-S', '-x', 'c', '-O2', '-G0', '-B' + lib] + matchtool.INCLUDES + extra + [src, '-o', s], capture_output=True, text=True)
if p.returncode: print(p.stderr); sys.exit(1)
L = open(s).read().split('\n')
labels = {}
for i, l in enumerate(L):
    m = re.match(r'^(\$L\d+):', l)
    if m: labels[m.group(1)] = i
out = []; i = 0
while i < len(L):
    l = L[i]
    if l.strip() == '.set\tnoreorder' and i + 5 < len(L) and L[i+1].strip() == '.set\tnomacro':
        br = L[i+2]; slot = L[i+3]
        m = re.match(r'^\s+(b\w*)\s+(.*)$', br)
        if m and not m.group(1).endswith('l') and L[i+4].strip() == '.set\tmacro' and L[i+5].strip() == '.set\treorder':
            tgt = m.group(2).split(',')[-1].strip()
            def isloop(a, b):
                for q in range(a, b):
                    mm = re.match(r'^\s+(j\w*|b\w*)\s', L[q]) and not re.match(r'^\s+(jal|break)\s', L[q])
                    if mm: return False
                n = sum(1 for q in range(a, b) if re.match(r'^\s+[a-z]', L[q]) and not L[q].strip().startswith('.'))
                return n <= int(os.environ.get('LOOPMAX', '5'))
            sm = re.match(r'^\s+\w+\s+(\$\w+)', slot)
            wr_br = sm and sm.group(1) in set(re.findall(r'\$\w+', m.group(2)))
            if tgt in labels and labels[tgt] < i and isloop(labels[tgt], i) and not wr_br:
                if slot.strip() != 'nop':
                    regs = set(re.findall(r'\$\w+', m.group(2)))
                    k = len(out) - 1
                    while k >= 0 and (out[k].strip() == '' or out[k].strip().startswith('#')): k -= 1
                    pm = re.match(r'^\s+\w+\s+(\$\w+)', out[k]) if k >= 0 else None
                    if pm and pm.group(1) in regs: out.insert(k, slot)
                    else: out.append(slot)
                out.append(br)
                i += 6; continue
    out.append(l); i += 1
open(S + '/h2.s', 'w').write('\n'.join(out))
obj = S + '/h.o'
if gnu_reorder.assemble(S + '/h2.s', obj, '/home/claude/decomp'): sys.exit(1)
fns = matchtool.obj_functions(obj)
score, res = matchtool.compare(name, *fns[name])
print(res[0]); [print(l) for l in res[1] if '!!' in l or '-v' in sys.argv]
