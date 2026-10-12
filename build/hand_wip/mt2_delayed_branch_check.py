# scratch: matchtool with delayed-branch kept (env DB=1) and optional no loop pinning (NOPIN=1)
import sys, os, subprocess
sys.path.insert(0, os.path.join(os.getcwd(), 'tools'))
import matchtool, gnu_reorder
_run = subprocess.run
def run(cmd, *a, **k):
    if os.environ.get('DB') and isinstance(cmd, list):
        cmd = [x for x in cmd if x != '-fno-delayed-branch']
    return _run(cmd, *a, **k)
matchtool.subprocess.run = run
if os.environ.get('NOPIN'):
    gnu_reorder.pin_loop_branches = lambda t: t
_ra = run
def run2(cmd, *a, **k):
    if os.environ.get('ASF') and isinstance(cmd, list) and cmd and cmd[0].endswith('/as'):
        cmd = cmd[:1] + os.environ['ASF'].split() + cmd[1:]
    return _ra(cmd, *a, **k)
gnu_reorder.subprocess.run = run2
matchtool.subprocess.run = run2
_as = gnu_reorder.assemble
def as2(s_path, obj, root):
    import shutil
    if os.environ.get('KEEP'): shutil.copy(s_path, os.environ['KEEP'])
    return _as(s_path, obj, root)
gnu_reorder.assemble = as2
sys.argv = ['matchtool.py', 'check'] + sys.argv[1:]
matchtool.main()
