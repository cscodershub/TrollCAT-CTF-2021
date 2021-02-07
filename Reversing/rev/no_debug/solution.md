# Solution

1. Bypass ptrace check, by either patching the binary or by making the condition true while running in gdb, to execute the real main function
2. run the binary in gdb till the password is decrypted
3. extract password from the memory
