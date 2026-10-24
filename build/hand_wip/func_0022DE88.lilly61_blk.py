import sys,re
f=sys.argv[1]; pat=sys.argv[2]; which=int(sys.argv[3]) if len(sys.argv)>3 else 0
txt=open(f).read()
# split into visualization blocks
parts=re.split(r'(?=;;   ==================== scheduling visualization for block)',txt)
n=0
for p in parts:
    if pat in p.split(';;   total time')[0] and 'scheduling visualization' in p[:100]:
        if n==which:
            print('\n'.join(l[:200] for l in p.split('\n')[:40])); break
        n+=1
