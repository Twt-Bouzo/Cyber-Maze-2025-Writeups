```bash
$ file fast                          
fast: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked,
 interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=4311f6ae74892919cf16556cf6bb2e3b09f86870, for GNU/Linux 3.2.0, stripped
```
The file  is a stripped executable - a binary that has had its debugging information, symbols, and metadata removed to reduce size and hinder analysis. This is common in production software and malware.

Let's decompile it using any decompiler .For me i used IDA 

<img width="1366" height="674" alt="1" src="https://github.com/user-attachments/assets/84c2e1a5-49c3-4919-9a4f-16f9e42a5f09" />

Analysis reveals that the main function invokes a cryptographic routine which XORs a static character array (representing the secret data) with a dynamically generated key ( on sub_1795() ) .

<img width="997" height="291" alt="2" src="https://github.com/user-attachments/assets/4becdc3b-35f5-42d6-a9ba-91b75afd18af" />

<img width="915" height="271" alt="3" src="https://github.com/user-attachments/assets/07c19dcb-2378-4c13-b262-b8ede1d8487b" />

The next phase involves analyzing the key generation method.

```Pyhton
#!/usr/bin/env python3
#!/usr/bin/env python3
from typing import List, Optional
encoded_str = ']>>>@?MQ=D=d:Q?99977'
sec = [ord(c) for c in encoded_str]

def rotl8(v: int, n: int) -> int:
    return ((v << n) & 0xFF) | (v >> (8 - n))

class KNode:
    def __init__(self, v: int):
        self.v = v & 0xFF
        self.l = None
        self.r = None

def build_key_tree() -> KNode:
    A = KNode(0x51)   
    B = KNode(0xA3)   
    C = KNode(0x6F)   
    D = KNode(0x12)   
    E = KNode(0xD4)   
    F = KNode(0x3B)   
    
    A.l = B; A.r = C
    B.l = D; B.r = E
    C.r = F
    
    return A

def walk_tree(n: Optional[KNode], out: List[int]) -> None:
    if n is None:
        return
    
    n.v = n.v ^ ((8 * n.v) & 0xFF) ^ (n.v >> 2)
    out.append(n.v & 0xFF)
    
    walk_tree(n.l, out)
    walk_tree(n.r, out)

def generate_key() -> int:
    root = build_key_tree()
    seq: List[int] = []
    walk_tree(root, seq)
    
    k = 66
    
    for v in seq:
        k = (7 * (v ^ k)) ^ (v >> 1)
        k = k & 0xFF
    
    return k

def decode(key: int, data: List[int]) -> str:
    return ''.join(chr(b ^ key) for b in data)

def main():
    key = generate_key()
    print(f"Key: {key} (0x{key:02X})")
    print(f"sec array: {sec}")
    print("Decoded secret:", decode(key, sec))

if __name__ == "__main__":
    main()

```
```bash
$ ./fast           
💠 Enter Neon Grid Access Code: S000N1C_3J3j4_177799

✨ Grid Stabilized — Access Granted!
🔓 Secret: S000N1C_3J3j4_177799

```
FLAG : CM{S000N1C_3J3j4_177799}
