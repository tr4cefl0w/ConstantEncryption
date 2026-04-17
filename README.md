## Denuvo inspired constant encryption 

Whats Denuvo's constant encryption?<br>

Denuvo “removes” constants from functions by storing them remotely and encrypting them using user-specific hardware information.

For this PoC, I chose NTBuildNumber located in KUserSharedData, but you can basically use any value you want.

## Function prolog of __scrt_initialize_crt
```asm
sub rsp, 0x28
```
## Encrypted version
```asm
sub rsp, 0x10
mov qword ptr [rsp], r11
mov r11d, 0x53472785
not r11d
mov dword ptr [rsp + 8], 0x4758e2b3
ror dword ptr [rsp + 8], 8
xor r11d, dword ptr [rsp + 8]
lea r11, [r11*4]
movzx r11, word ptr [r11]
push r9
mov r9, 0x4a4d
xor r9, r11
neg r9
mov r11, qword ptr [rsp + 8]
lea rsp, [rsp + r9]
mov r9, qword ptr [rsp + r9]
add rsp, 0x18
```
## Features
current features:
- encrypts function prolog (stack allocation)
- some very light anti-disassembly tricks (rewrite call to jump, jump +1, xor reg, reg -> sub reg, reg)
- places obfuscated/encrypted function in a new section

planned features
- add more instructions
- more encryption/obfuscation passes 
- small vm to achieve more obfuscation

  
