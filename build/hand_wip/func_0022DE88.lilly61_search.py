#!/usr/bin/env python3
# usage: search.py base.cpp spec.py [nproc]   spec defines VARIANTS: list of (label, [(old,new),...])  -> prints sorted scores
import sys, os, tempfile, multiprocessing as mp
sys.path.insert(0,'/tmp/w22')
import score as S
def run(a):
    label,text=a
    d=tempfile.mkdtemp(prefix='sv',dir='/tmp/w22')
    p=os.path.join(d,'v.cpp'); open(p,'w').write(text)
    r=S.score(p)
    os.remove(p); os.rmdir(d)
    return label,r,text
def main():
    base=open(sys.argv[1]).read()
    ns={'BASE':base}
    exec(open(sys.argv[2]).read(),ns)
    items=[]
    for label,edits in ns['VARIANTS']:
        t=base; ok=True
        for old,new in edits:
            if old not in t: ok=False;break
            t=t.replace(old,new,1)
        if ok: items.append((label,t))
        else: print('skip',label)
    n=int(sys.argv[3]) if len(sys.argv)>3 else 12
    with mp.Pool(n) as pool:
        res=pool.map(run,items)
    res=[r for r in res if r[1]]
    res.sort(key=lambda r:r[1][0])
    for l,r,_ in res[:int(os.environ.get('TOP','15'))]: print(r,l)
    print('base',S.score(sys.argv[1]))
    if os.environ.get('SAVE'):
        open(os.environ['SAVE'],'w').write(res[0][2])
main()
