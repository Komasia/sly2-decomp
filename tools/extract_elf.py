#!/usr/bin/env python3
"""Extract SCUS_973.16 from your own Sly 2 (USA) disc image into disc/ and verify it.
usage: python3 tools/extract_elf.py "path/to/Sly 2 - Band of Thieves (USA).iso" """
import struct, sys, os, hashlib
SHA1 = 'de2af92a54de71e33edc8a160c31c0337a95e6f5'
iso = open(sys.argv[1], 'rb')
def sec(n, c=1): iso.seek(n * 2048); return iso.read(2048 * c)
pvd = sec(16); assert pvd[1:6] == b'CD001', 'not an ISO9660 image'
root = pvd[156:190]
lba, size = struct.unpack('<I', root[2:6])[0], struct.unpack('<I', root[10:14])[0]
d = sec(lba, (size + 2047) // 2048); i = 0
while i < len(d):
    l = d[i]
    if l == 0: i = (i // 2048 + 1) * 2048; continue
    e = d[i:i + l]; name = e[33:33 + e[32]].decode('latin1').split(';')[0]
    if name == 'SCUS_973.16':
        elba, esz = struct.unpack('<I', e[2:6])[0], struct.unpack('<I', e[10:14])[0]
        iso.seek(elba * 2048); data = iso.read(esz)
        h = hashlib.sha1(data).hexdigest()
        os.makedirs('disc', exist_ok=True); open('disc/SCUS_973.16', 'wb').write(data)
        print('wrote disc/SCUS_973.16', 'SHA1 OK' if h == SHA1 else f'SHA1 MISMATCH {h} (wrong region/version?)')
        sys.exit(0 if h == SHA1 else 1)
    i += l
sys.exit('SCUS_973.16 not found on this disc')
