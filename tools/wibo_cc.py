#!/usr/bin/env python3
"""Drop-in replacement for `wibo` used by the matching tools.

When invoked as  wibo_cc.py ee-gcc.exe ... -c SRC -o OBJ  it compiles SRC to assembly, runs
tools/asfix.py over it (Sly 2's short-loop padding) and assembles the result with the same driver
flags.  Every other invocation is passed straight to the real wibo."""
import os, sys, subprocess, tempfile, shutil, signal
HERE = os.path.dirname(os.path.abspath(__file__))
REAL = os.path.join(HERE, 'wibo-i686')
sys.path.insert(0, HERE)
import asfix

def run(cmd, tries=3, timeout=60):
    """wibo occasionally hangs; run in its own process group, kill and retry on timeout"""
    for _ in range(tries):
        p = subprocess.Popen(cmd, start_new_session=True)
        try:
            return p.wait(timeout=timeout)
        except subprocess.TimeoutExpired:
            os.killpg(p.pid, signal.SIGKILL); p.wait()
    return 1

def main():
    a = sys.argv[1:]
    if not (a and a[0].endswith('ee-gcc.exe') and '-c' in a and '-o' in a):
        os.execv(REAL, [REAL] + a)
    o = a.index('-o'); obj = a[o + 1]
    rest = a[1:o] + a[o + 2:]
    srcs = [x for x in rest if not x.startswith('-') and os.path.splitext(x)[1] in ('.c', '.cpp', '.cc', '.C')]
    if len(srcs) != 1:
        os.execv(REAL, [REAL] + a)
    src = srcs[0]
    t = tempfile.mkdtemp(prefix='wcc')
    try:
        s1 = os.path.join(t, 'a.s'); s2 = os.path.join(t, 'b.s')
        cmd1 = [REAL, a[0]] + ['-S' if x == '-c' else x for x in rest] + ['-o', s1]
        rc = run(cmd1)
        if rc or not os.path.exists(s1):
            return rc or 1
        txt, _ = asfix.fix(open(s1).read())
        open(s2, 'w').write(txt)
        flags = []
        skip = False
        for x in rest:
            if skip: skip = False; continue
            if x == src: continue
            if x == '-x': skip = True; continue
            if x.startswith('-x'): continue
            flags.append(x)
        # Sly 2 was assembled with SN's ps2eeas (it reproduces the original's 64-bit constant expansion
        # and FPU hazard nops); set SLY2_AS=gnu to use the GNU as that ships with the compiler instead
        asm = os.environ.get('SLY2_AS', os.path.join(HERE, 'compilers', '2.95.3-114', 'lib', 'gcc-lib', 'ee', '2.95.3', 'ps2eeas.exe'))
        if asm == 'gnu': asm = None
        if asm:
            return run([REAL, asm, '-G0', '-O2', '-mabi=eabi', '-o', obj, s2])
        return run([REAL, a[0]] + flags + ['-x', 'assembler', s2, '-o', obj])
    finally:
        shutil.rmtree(t, ignore_errors=True)

if __name__ == '__main__':
    sys.exit(main())
