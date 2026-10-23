# NaGa worklist (2026-10-23)

Everything still unmatched in NaGa's ranges, from `tools/worklist.py`. **Size** is the number of target instructions.
**Closeness** is the aligned diff count from `build/hand_wip/RANKING.csv` (last refreshed 10-17, so it may be stale; re-run
`python3 tools/rank_drafts.py` for current numbers). **Drafts** are the draft files in `build/hand_wip/`, and the highest version is usually the newest.
Check `notes/<range>.md` before starting a function: it records what has already been tried.

## 0x160000–0x190000 (engine) — 35 functions

| Function | Address | Size | Closeness | Drafts |
|---|---|---|---|---|
| func_0016E438 | 0x16E438 | 377 | 0 | func_0016E438.codex18v1.cpp, func_0016E438.cpp |
| func_00173D18 | 0x173D18 | 88 | 1 | func_00173D18.c |
| func_001638F8 | 0x1638F8 | 148 | 2 | func_001638F8.c, func_001638F8.codex18v1.c |
| func_0017DE50 | 0x17DE50 | 164 | 3 | func_0017DE50.c |
| func_00188960 | 0x188960 | 218 | 8 | func_00188960.cpp |
| func_0018F2B0 | 0x18F2B0 | 171 | 12 | func_0018F2B0.cpp, func_0018F2B0.v2.cpp, func_0018F2B0.v3.cpp |
| func_0017D608 | 0x17D608 | 48 | 13 | func_0017D608.codex18v1.cpp, func_0017D608.cpp, func_0017D608_v2.cpp |
| func_001681F8 | 0x1681F8 | 182 | 21 | func_001681F8.codex18fresh1.cpp, func_001681F8.v2.c, func_001681F8.v3.c |
| func_00167320 | 0x167320 | 340 | 22 | func_00167320.codex18v1.cpp, func_00167320.cpp |
| func_00179898 | 0x179898 | 97 | 22 | func_00179898.codex18v1.c, func_00179898.v2.c, func_00179898.v3.c |
| func_00165E38 | 0x165E38 | 116 | 23 | func_00165E38.c, func_00165E38.codex18v1.c, func_00165E38.v2.c |
| func_00185D18 | 0x185D18 | 69 | 33 | func_00185D18.c, func_00185D18.codex18fresh1.c, func_00185D18.codex18fresh2.c |
| func_001823C8 | 0x1823C8 | 205 | 34 | func_001823C8.c |
| func_0018D760 | 0x18D760 | 185 | 36 | func_0018D760.v2.c, func_0018D760.v3.c, func_0018D760.v4.c |
| func_001821C0 | 0x1821C0 | 129 | 40 | func_001821C0.codex18v1.cpp, func_001821C0.cpp |
| func_001728B0 | 0x1728B0 | 407 | 42 | func_001728B0.c, func_001728B0.codex18v2.c |
| func_00178EE0 | 0x178EE0 | 186 | 43 | func_00178EE0.c, func_00178EE0.codex18v1.c, func_00178EE0.codex18v2.c |
| func_00189C40 | 0x189C40 | 161 | 49 | func_00189C40.c, func_00189C40.codex18v1.c |
| func_00185A80 | 0x185A80 | 94 | 53 | func_00185A80.c, func_00185A80.clean.c, func_00185A80.codex18v1.c |
| func_001758A0 | 0x1758A0 | 279 | 63 | func_001758A0.codex18v1.cpp, func_001758A0.codex18v2.cpp, func_001758A0.cpp |
| func_0016CF78 | 0x16CF78 | 456 | 75 | func_0016CF78.codex18fresh1.cpp, func_0016CF78.codex18v1.cpp, func_0016CF78.cpp |
| func_0017BFF8 | 0x17BFF8 | 252 | 81 | func_0017BFF8.c |
| func_0018F958 | 0x18F958 | 194 | 102 | func_0018F958.codex18fresh1.cpp, func_0018F958.cpp |
| func_001856C0 | 0x1856C0 | 240 | 106 | func_001856C0.c, func_001856C0.codex18v1.c |
| func_00189618 | 0x189618 | 394 | 113 | func_00189618.c, func_00189618.codex18v1.c |
| func_0018A8C8 | 0x18A8C8 | 638 | 114 | func_0018A8C8.v3.cpp, func_0018A8C8.v4.cpp, func_0018A8C8.v5.cpp |
| func_00173F18 | 0x173F18 | 350 | 120 | func_00173F18.codex18fresh1.cpp, func_00173F18.codex18fresh2.cpp, func_00173F18.cpp |
| func_00185E40 | 0x185E40 | 413 | 155 | func_00185E40.codex18v1.cpp, func_00185E40.codex18v2.cpp, func_00185E40.cpp |
| func_0018FC60 | 0x18FC60 | 469 | 162 | func_0018FC60.codex18v1.cpp, func_0018FC60.codex18v2.cpp, func_0018FC60.cpp |
| func_00180668 | 0x180668 | 544 | 172 | func_00180668.c, func_00180668.codex18v1.cpp, func_00180668.codex18v2.cpp |
| func_00169198 | 0x169198 | 508 | 185 | func_00169198.codex18fresh1.cpp, func_00169198.codex18fresh2.cpp, func_00169198.codex18fresh4.cpp |
| func_00168638 | 0x168638 | 728 | 316 | func_00168638.codex18fresh3.cpp, func_00168638.codex18fresh4.cpp, func_00168638.cpp |
| func_0018C250 | 0x18C250 | 1195 | 342 | func_0018C250.codex18fresh2.cpp, func_0018C250.cpp, func_0018C250.v2.cpp |
| func_00177F78 | 0x177F78 | 672 | 368 | func_00177F78.codex18fresh9.cpp, func_00177F78.cpp, func_00177F78.v2.cpp |
| func_0016A000 | 0x16A000 | 2616 | 1321 | func_0016A000.codex18fresh5.cpp, func_0016A000.cpp, func_0016A000_v2.cpp |

## 0x190000–0x230000 (engine) — 119 functions

| Function | Address | Size | Closeness | Drafts |
|---|---|---|---|---|
| func_001F4558 | 0x1F4558 | 95 | 0 | func_001F4558.codex18v1.cpp, func_001F4558.cpp |
| func_001ACFE0 | 0x1ACFE0 | 97 | 1 | func_001ACFE0.cpp |
| func_0019AC88 | 0x19AC88 | 93 | 2 | func_0019AC88.c, func_0019AC88.codex18v1.c |
| func_001DDB08 | 0x1DDB08 | 50 | 2 | func_001DDB08.c |
| func_0020B868 | 0x20B868 | 155 | 2 | func_0020B868.cpp, func_0020B868.v2.cpp, func_0020B868.v3.cpp |
| func_0020D9D0 | 0x20D9D0 | 363 | 2 | func_0020D9D0.cpp |
| func_001DF0A0 | 0x1DF0A0 | 111 | 3 | func_001DF0A0.c |
| func_00204DA8 | 0x204DA8 | 35 | 3 | func_00204DA8.codex18fresh1.cpp, func_00204DA8.codex18v1.cpp, func_00204DA8.v2.c |
| func_00196928 | 0x196928 | 95 | 4 | func_00196928.c, func_00196928.codex18v1.cpp |
| func_001B20B8 | 0x1B20B8 | 78 | 4 | func_001B20B8.c, func_001B20B8.codex18v1.cpp, func_001B20B8.cpp |
| func_001CDF88 | 0x1CDF88 | 121 | 4 | func_001CDF88.codex18v1.c, func_001CDF88.codex18v2.c, func_001CDF88.codex18v3.c |
| func_001E9C88 | 0x1E9C88 | 178 | 4 | func_001E9C88.c |
| func_0020F318 | 0x20F318 | 173 | 4 | func_0020F318.codex18v1.cpp, func_0020F318.codex18v2.cpp, func_0020F318.cpp |
| func_00199D48 | 0x199D48 | 211 | 5 | func_00199D48.c, func_00199D48.v2.c |
| func_001C1A38 | 0x1C1A38 | 89 | 6 | func_001C1A38.c |
| func_001F70C0 | 0x1F70C0 | 142 | 6 | func_001F70C0.cpp, func_001F70C0.v2.cpp |
| func_001C5148 | 0x1C5148 | 265 | 7 | func_001C5148.cpp, func_001C5148.v2.cpp, func_001C5148.v3.cpp |
| func_001CA118 | 0x1CA118 | 123 | 11 | func_001CA118.cpp |
| func_001E1E30 | 0x1E1E30 | 1687 | 12 | func_001E1E30.codex18fresh1.cpp, func_001E1E30.codex18fresh2.cpp, func_001E1E30.cpp |
| func_001CFE88 | 0x1CFE88 | 108 | 13 | func_001CFE88.cpp |
| func_001E95B0 | 0x1E95B0 | 157 | 13 | func_001E95B0.codex18v1.cpp, func_001E95B0.cpp |
| func_00204250 | 0x204250 | 152 | 13 | func_00204250.codex18v1.c, func_00204250.codex18v2.c, func_00204250.codex18v3.c |
| func_001C9B08 | 0x1C9B08 | 387 | 15 | func_001C9B08.cpp, func_001C9B08.v2.cpp, func_001C9B08.v3.cpp |
| func_001EA000 | 0x1EA000 | 235 | 15 | func_001EA000.c, func_001EA000.v2.c |
| func_002044B0 | 0x2044B0 | 107 | 16 | func_002044B0.codex18v1.c, func_002044B0.codex18v2.c, func_002044B0.v2.c |
| func_001A3F78 | 0x1A3F78 | 183 | 17 | func_001A3F78.cpp |
| func_001A4AD8 | 0x1A4AD8 | 117 | 17 | func_001A4AD8.cpp, func_001A4AD8.v2.cpp, func_001A4AD8.v3.cpp |
| func_001F59A0 | 0x1F59A0 | 164 | 17 | func_001F59A0.codex18fresh1.cpp, func_001F59A0.cpp, func_001F59A0.v2.cpp |
| func_00202378 | 0x202378 | 114 | 17 | func_00202378.codex18fresh1.cpp, func_00202378.cpp |
| func_001C9190 | 0x1C9190 | 147 | 19 | func_001C9190.cpp |
| func_00225300 | 0x225300 | 177 | 19 | func_00225300.codex18v1.cpp, func_00225300.cpp |
| func_00194A40 | 0x194A40 | 321 | 20 | func_00194A40.cpp |
| func_001BFDB0 | 0x1BFDB0 | 93 | 20 | func_001BFDB0.c, func_001BFDB0.codex18v1.c |
| func_002188B0 | 0x2188B0 | 530 | 22 | func_002188B0.codex18fresh1.cpp, func_002188B0.cpp |
| func_001DB0C8 | 0x1DB0C8 | 177 | 24 | func_001DB0C8.cpp |
| func_001F1A40 | 0x1F1A40 | 173 | 24 | func_001F1A40.codex18v1.cpp, func_001F1A40.cpp, func_001F1A40.v2.cpp |
| func_001B6078 | 0x1B6078 | 428 | 25 | func_001B6078.codex18fresh1.cpp, func_001B6078.cpp |
| func_00219FE0 | 0x219FE0 | 621 | 25 | func_00219FE0.codex18v1.cpp, func_00219FE0.codex18v2.cpp, func_00219FE0.cpp |
| func_001A3D00 | 0x1A3D00 | 98 | 27 | func_001A3D00.c |
| func_001C3500 | 0x1C3500 | 278 | 27 | func_001C3500.codex18v2.cpp, func_001C3500.codex18v3.cpp, func_001C3500.cpp |
| func_001FD0E8 | 0x1FD0E8 | 320 | 28 | func_001FD0E8.codex18fresh1.cpp, func_001FD0E8.codex18v1.cpp, func_001FD0E8.cpp |
| func_002236E8 | 0x2236E8 | 202 | 28 | func_002236E8.codex18v3.cpp, func_002236E8.codex18v4.cpp, func_002236E8.cpp |
| func_002057E8 | 0x2057E8 | 73 | 30 | func_002057E8.codex18v2.cpp, func_002057E8.codex18v3.cpp, func_002057E8.cpp |
| func_001E5FC8 | 0x1E5FC8 | 110 | 32 | func_001E5FC8.c, func_001E5FC8.codex18fresh1.c |
| func_001997D8 | 0x1997D8 | 126 | 34 | func_001997D8.cpp, func_001997D8.v2.cpp, func_001997D8.v3.cpp |
| func_001CC5E8 | 0x1CC5E8 | 239 | 35 | func_001CC5E8.cpp |
| FUN_0018b988 | 0x1AABC0 | 197 | 36 | FUN_0018b988.codex18v2.c, FUN_0018b988.v2.c, FUN_0018b988.v3.c |
| func_001BDE80 | 0x1BDE80 | 217 | 36 | func_001BDE80.codex18v1.cpp, func_001BDE80.cpp |
| func_001999D0 | 0x1999D0 | 221 | 37 | func_001999D0.codex18fresh1.cpp, func_001999D0.cpp |
| func_001C6DE8 | 0x1C6DE8 | 124 | 37 | func_001C6DE8.codex18fresh1.cpp, func_001C6DE8.cpp |
| func_001B1328 | 0x1B1328 | 291 | 39 | func_001B1328.codex18fresh1.cpp, func_001B1328.codex18fresh2.cpp, func_001B1328.cpp |
| func_00195368 | 0x195368 | 168 | 40 | func_00195368.c |
| func_0019A750 | 0x19A750 | 194 | 44 | func_0019A750.c, func_0019A750.codex18v1.c, func_0019A750.v2.c |
| func_00206900 | 0x206900 | 273 | 44 | func_00206900.codex18v2.cpp, func_00206900.cpp |
| func_0020E3C0 | 0x20E3C0 | 224 | 44 | func_0020E3C0.codex18v1.cpp, func_0020E3C0.cpp, func_0020E3C0.v2.c |
| func_001CE2E8 | 0x1CE2E8 | 199 | 49 | func_001CE2E8.v2.cpp, func_001CE2E8.v3.cpp, func_001CE2E8.v4.cpp |
| func_00194F70 | 0x194F70 | 253 | 51 | func_00194F70.codex18v1.cpp, func_00194F70.cpp, func_00194F70.v2.cpp |
| func_001DF5B0 | 0x1DF5B0 | 213 | 51 | func_001DF5B0.codex18v1.cpp, func_001DF5B0.codex18v2.cpp, func_001DF5B0.cpp |
| func_001C2EF0 | 0x1C2EF0 | 210 | 52 | func_001C2EF0.codex18fresh2.cpp, func_001C2EF0.codex18v1.cpp, func_001C2EF0.cpp |
| func_001E6F60 | 0x1E6F60 | 264 | 52 | func_001E6F60.codex18fresh1.cpp, func_001E6F60.cpp |
| func_00205008 | 0x205008 | 182 | 52 | func_00205008.cpp, func_00205008.v2.cpp, func_00205008.v3.cpp |
| func_001F50E0 | 0x1F50E0 | 232 | 59 | func_001F50E0.codex18fresh2.cpp, func_001F50E0.codex18v1.cpp, func_001F50E0.cpp |
| func_001F6C08 | 0x1F6C08 | 187 | 59 | func_001F6C08.cpp, func_001F6C08.v2.cpp |
| func_001E9858 | 0x1E9858 | 153 | 60 | func_001E9858.codex18v1.cpp, func_001E9858.codex18v2.cpp, func_001E9858.cpp |
| func_001BFF28 | 0x1BFF28 | 233 | 67 | func_001BFF28.codex18fresh1.cpp, func_001BFF28.cpp |
| func_001CAA60 | 0x1CAA60 | 223 | 68 | func_001CAA60.v2.cpp, func_001CAA60.v3.cpp, func_001CAA60.v4.cpp |
| func_001C55E0 | 0x1C55E0 | 336 | 69 | func_001C55E0.codex18v2.cpp, func_001C55E0.codex18v3.cpp, func_001C55E0.cpp |
| func_00224820 | 0x224820 | 245 | 70 | func_00224820.codex18fresh2.cpp, func_00224820.codex18fresh3.cpp, func_00224820.cpp |
| func_001D4568 | 0x1D4568 | 245 | 72 | func_001D4568.codex18v1.cpp, func_001D4568.cpp |
| func_00195A00 | 0x195A00 | 365 | 76 | func_00195A00.codex18v2.cpp, func_00195A00.cpp |
| func_001A87F0 | 0x1A87F0 | 215 | 77 | func_001A87F0.codex18fresh1.cpp, func_001A87F0.cpp |
| func_001D09A0 | 0x1D09A0 | 150 | 79 | func_001D09A0.codex18v2.cpp, func_001D09A0.codex18v3.cpp, func_001D09A0.cpp |
| func_001E9090 | 0x1E9090 | 215 | 80 | func_001E9090.codex18fresh1.cpp, func_001E9090.codex18v1.cpp, func_001E9090.cpp |
| func_001A4258 | 0x1A4258 | 135 | 81 | func_001A4258.c, func_001A4258.codex18fresh1.c |
| func_002297F8 | 0x2297F8 | 346 | 83 | func_002297F8.codex18v1.cpp, func_002297F8.codex18v2.cpp, func_002297F8.cpp |
| func_001E6A30 | 0x1E6A30 | 226 | 88 | func_001E6A30.codex18fresh2.cpp, func_001E6A30.codex18fresh3.cpp, func_001E6A30.cpp |
| func_001BC688 | 0x1BC688 | 217 | 89 | func_001BC688.codex18v1.cpp, func_001BC688.cpp |
| func_001AA1D8 | 0x1AA1D8 | 402 | 91 | func_001AA1D8.codex18fresh1.cpp, func_001AA1D8.codex18fresh2.cpp, func_001AA1D8.cpp |
| func_0022A908 | 0x22A908 | 376 | 91 | func_0022A908.codex18fresh1.cpp, func_0022A908.codex18fresh2.cpp, func_0022A908.cpp |
| func_00205910 | 0x205910 | 254 | 95 | func_00205910.codex18fresh1.cpp, func_00205910.codex18fresh2.cpp, func_00205910.cpp |
| func_001D0190 | 0x1D0190 | 213 | 96 | func_001D0190.codex18fresh2.cpp, func_001D0190.codex18v1.cpp, func_001D0190.cpp |
| func_00211528 | 0x211528 | 341 | 98 | func_00211528.codex18fresh1.cpp, func_00211528.codex18fresh2.cpp, func_00211528.cpp |
| func_001C6FD8 | 0x1C6FD8 | 411 | 101 | func_001C6FD8.codex18v1.cpp, func_001C6FD8.cpp |
| func_00194688 | 0x194688 | 238 | 102 | func_00194688.c, func_00194688.codex18v1.c |
| func_001D6B00 | 0x1D6B00 | 375 | 104 | func_001D6B00.codex18v1.cpp, func_001D6B00.codex18v2.cpp, func_001D6B00.cpp |
| func_0019CD38 | 0x19CD38 | 382 | 105 | func_0019CD38.codex18v1.cpp, func_0019CD38.cpp |
| func_001F6068 | 0x1F6068 | 417 | 110 | func_001F6068.codex18fresh2.cpp, func_001F6068.codex18v1.cpp, func_001F6068.cpp |
| func_00192BD8 | 0x192BD8 | 825 | 112 | func_00192BD8.codex18v1.cpp, func_00192BD8.cpp |
| func_001C21D8 | 0x1C21D8 | 321 | 112 | func_001C21D8.cpp |
| func_001D2610 | 0x1D2610 | 496 | 114 | func_001D2610.codex18v2.cpp, func_001D2610.codex18v3.cpp, func_001D2610.cpp |
| func_00197500 | 0x197500 | 677 | 119 | func_00197500.codex18fresh1.cpp, func_00197500.cpp |
| func_00202D38 | 0x202D38 | 524 | 123 | func_00202D38.codex18v8.cpp, func_00202D38.cpp, func_00202D38_v2.cpp |
| func_001911A8 | 0x1911A8 | 538 | 133 | func_001911A8.codex18v1.cpp, func_001911A8.cpp |
| func_001FFD98 | 0x1FFD98 | 512 | 143 | func_001FFD98.codex18fresh1.cpp, func_001FFD98.codex18fresh2.cpp, func_001FFD98.cpp |
| func_001B72B0 | 0x1B72B0 | 276 | 151 | func_001B72B0.codex18fresh1.cpp, func_001B72B0.cpp |
| func_001D2E18 | 0x1D2E18 | 397 | 151 | func_001D2E18.codex18v1.cpp, func_001D2E18.codex18v2.cpp, func_001D2E18.cpp |
| func_0019B110 | 0x19B110 | 1147 | 155 | func_0019B110.codex18v1.cpp, func_0019B110.cpp |
| func_002149D8 | 0x2149D8 | 761 | 157 | func_002149D8.codex18fresh1.cpp, func_002149D8.codex18v2.cpp, func_002149D8.cpp |
| func_0022B7D8 | 0x22B7D8 | 393 | 160 | func_0022B7D8.codex18fresh1.cpp, func_0022B7D8.cpp |
| func_001EFAC0 | 0x1EFAC0 | 386 | 163 | func_001EFAC0.codex18fresh1.cpp, func_001EFAC0.codex18fresh2.cpp, func_001EFAC0.cpp |
| func_001F9410 | 0x1F9410 | 451 | 168 | func_001F9410_v5.cpp, func_001F9410_v6.cpp, func_001F9410_v7.cpp |
| func_001A4478 | 0x1A4478 | 407 | 184 | func_001A4478.codex18fresh1.cpp, func_001A4478.cpp |
| func_00191A10 | 0x191A10 | 953 | 188 | func_00191A10.codex18fresh1.cpp, func_00191A10.codex18fresh2.cpp, func_00191A10.cpp |
| func_00200598 | 0x200598 | 386 | 192 | func_00200598.codex18v3.cpp, func_00200598.codex18v4.cpp, func_00200598.cpp |
| func_001A8B50 | 0x1A8B50 | 365 | 196 | func_001A8B50.v2.cpp, func_001A8B50.v3.cpp, func_001A8B50.v4.cpp |
| func_00219400 | 0x219400 | 759 | 206 | func_00219400.codex18fresh2.cpp, func_00219400.cpp, func_00219400.v2.cpp |
| func_0021FB70 | 0x21FB70 | 517 | 207 | func_0021FB70.v3.cpp, func_0021FB70.v4.cpp, func_0021FB70.v5.cpp |
| func_001BF3D8 | 0x1BF3D8 | 329 | 210 | func_001BF3D8.codex18fresh1.c, func_001BF3D8.codex18fresh2.c, func_001BF3D8_v2.c |
| func_0022A220 | 0x22A220 | 441 | 230 | func_0022A220.fresh6.cpp, func_0022A220.v2.cpp, func_0022A220.v3.cpp |
| func_001E3890 | 0x1E3890 | 807 | 237 | func_001E3890.codex18fresh3.c, func_001E3890.codex18fresh4.c, func_001E3890.v2.c |
| func_0021CB18 | 0x21CB18 | 386 | 240 | func_0021CB18.codex18fresh3.cpp, func_0021CB18.codex18fresh4.cpp, func_0021CB18.cpp |
| func_001DE5D8 | 0x1DE5D8 | 501 | 259 | func_001DE5D8.codex18fresh1.cpp, func_001DE5D8.codex18v1.cpp, func_001DE5D8.cpp |
| func_001A93C8 | 0x1A93C8 | 472 | 299 | func_001A93C8.codex18fresh2.cpp, func_001A93C8.codex18fresh3.cpp, func_001A93C8.cpp |
| func_001D5808 | 0x1D5808 | 705 | 394 | func_001D5808.codex18fresh1.cpp, func_001D5808.codex18fresh2.cpp, func_001D5808.cpp |
| func_001D3450 | 0x1D3450 | 637 | 406 | func_001D3450.cpp |
| func_00197F98 | 0x197F98 | 1154 | 418 | func_00197F98.codex18fresh2.cpp, func_00197F98.codex18fresh3.cpp, func_00197F98.cpp |
| func_00221DD8 | 0x221DD8 | 1604 | 462 | func_00221DD8.codex18fresh2.cpp, func_00221DD8.codex18fresh3.cpp, func_00221DD8.cpp |
| func_001E8378 | 0x1E8378 | 838 | 652 | func_001E8378.codex18fresh3.cpp, func_001E8378.codex18fresh4.cpp, func_001E8378.codex18v1.c |
| func_0022DE88 | 0x22DE88 | 1766 | 954 | func_0022DE88.codex18fresh5.cpp, func_0022DE88.cpp, func_0022DE88_v2.cpp |

## 0x234F48–0x2550A0 (Sony SDK; see the status table in notes/23C000.md) — 11 functions

| Function | Address | Size | Closeness | Drafts |
|---|---|---|---|---|
| sceRead | 0x2382B8 | 155 | 2 | sceRead.codex18v1.c, sceRead.v2.c, sceRead.v3.c |
| sceWrite | 0x238528 | 176 | 2 | sceWrite.codex18v1.c, sceWrite.v2.c, sceWrite.v3.c |
| sceFsInit | 0x237BD8 | 130 | 3 | sceFsInit.v2.c, sceFsInit.v3.c, sceFsInit.v4.c |
| sceSifInitRpc | 0x236A60 | 103 | 4 | sceSifInitRpc.c, sceSifInitRpc.v2.c |
| sceCdInit | 0x2420F0 | 186 | 5 | sceCdInit.v2.c, sceCdInit.v3.c, sceCdInit.v4.c |
| scePadPortOpen | 0x243088 | 121 | 16 | scePadPortOpen.codex18v2.c, scePadPortOpen.codex18v3.c, scePadPortOpen.v2.c |
| _sceSnprintf | 0x235B08 | 837 | 57 | _sceSnprintf.v2.c, _sceSnprintf.v3.c, _sceSnprintf_pf.c |
| func_002401D8 | 0x2401D8 | 83 | 62 | func_002401D8.codex18v3.c, func_002401D8.codex18v4.c, func_002401D8.v2.c |
| sceGsSetDefDispEnv | 0x240C38 | 221 | 99 | sceGsSetDefDispEnv.codex18v5.c, sceGsSetDefDispEnv.codex18v6.c, sceGsSetDefDispEnv.v2.c |
| sceMpegDemuxPssRing | 0x24F390 | 248 | 173 | sceMpegDemuxPssRing.v7.c, sceMpegDemuxPssRing.v8.c, sceMpegDemuxPssRing.v9.c |
| _getRef0 | 0x2505B0 | 290 | 205 | _getRef0.v5.c, _getRef0.v6.c, _getRef0.v7.c |
