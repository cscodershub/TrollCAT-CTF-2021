#!/usr/bin/env python3
from z3 import *

key = [BitVec(f'key_{i}', 8) for i in range(0x16)]

solver = Solver()

for i in range(0x16):
    solver.add(And(key[i] >= ord('0'),key[i] <= ord('z')))

solver.add(key[3] + key[0] == 0x64)
solver.add(key[0x12] + key[1] == 0xd6)
solver.add(key[4] + key[2] == 0xb2)
solver.add(key[6] ^ key[5] == 0x4c)
solver.add(key[8] - key[7] == 0x11)
solver.add(key[10] - key[9] == 0x3b)
solver.add(key[0xb] + key[0xc] - key[0xd] == 0x45)
solver.add(key[0xe] + key[0xf] - key[0x10] == 0x1f)
solver.add(key[0x11] + key[0x10] - key[0x12] == 0x58)
solver.add(key[0x15] ^ key[0x13] ^ key[0x14] == 0x45)

if solver.check() == sat:
    m = solver.model()
    flag = ''.join([chr(m.evaluate(key[i]).as_long()) for i in range(0x16)])
    print(flag)
