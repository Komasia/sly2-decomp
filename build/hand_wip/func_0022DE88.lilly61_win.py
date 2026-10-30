import sys, os
sys.path.insert(0, os.path.expanduser('~/sly2-decomp/tools'))
import matchtool as M
src=os.path.abspath(sys.argv[1]); lo=int(sys.argv[2],0); hi=int(sys.argv[3],0)
of=M.compile_src(src); fns=M.obj_functions(of)
words,rel=fns['func_0022DE88']; addr,size=M.load_functions()['func_0022DE88']
tgt=M.target_words(addr,size)
for i in range(lo,hi):
    t=M.disasm(tgt[i],addr+4*i) if i<len(tgt) else ''
    o=M.disasm(words[i],0) if i<len(words) else ''
    print(f'{i:5d} {t:44s}| {o}')
