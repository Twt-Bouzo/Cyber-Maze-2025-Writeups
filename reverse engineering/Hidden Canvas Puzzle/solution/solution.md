<img width="903" height="605" alt="11" src="https://github.com/user-attachments/assets/9a37c6a3-96c5-409a-acab-40a99c42f9da" />


The challenge involves extracting hidden data from the image's hexadecimal representation

```bash
strings fanta.jpg
```
Extracted data reveals Base64 encoding, necessitating decoding to recover the original content.

<img width="1536" height="712" alt="13" src="https://github.com/user-attachments/assets/76a80420-2d12-423c-9c37-1103b2f75639" />

<img width="1535" height="547" alt="14" src="https://github.com/user-attachments/assets/503a9772-f211-44a0-bdf8-6e1c209ba92b" />

The decoded plaintext reveals a URL containing the second stage of the challenge.

<img width="712" height="134" alt="15" src="https://github.com/user-attachments/assets/6c5fd196-e387-431a-b160-f8a72c0c8977" />

let's try to run the loader.exe

<img width="565" height="268" alt="capture_251125_184656" src="https://github.com/user-attachments/assets/82cddb85-b6b9-4076-8e1c-fbcf60be43bc" />

The loader application displays a usage prompt when executed without arguments

<img width="657" height="229" alt="capture_251125_184721" src="https://github.com/user-attachments/assets/de0ee785-d2eb-4357-afee-9c8f1cab80b8" />

The error originates from brokenAuth.dll during the key extraction phase

After decompiling the Windows file, it reads a key from the MT7A9C21 section of the borkenAuth.dll file. If the key is not equal to 0xFFFFFFFF, the program prints the flag.

<img width="832" height="249" alt="16" src="https://github.com/user-attachments/assets/bec50e88-7d87-476f-b3e1-5ddd2145464e" />

So the best way is to patch the if instruction and rerun the program.

<img width="502" height="615" alt="capture_251126_112106" src="https://github.com/user-attachments/assets/e7530615-1dbc-455c-973d-d7793aa049bd" />

test eax , eax (Bytes : 85 D2) ----> xor eax ,eax (Bytes : 31 D2)
change bytes ---> apply patches to input file

<img width="790" height="648" alt="capture_251126_112450" src="https://github.com/user-attachments/assets/2e07f682-b2fd-46b0-83f6-9691dc3e0a31" />

MT7A9C21 after patching : 

<img width="575" height="160" alt="17" src="https://github.com/user-attachments/assets/3bc27d67-598f-4b5c-a1a1-aa5725bb9d6e" />

Now, rerun the program to get the flag.

<img width="643" height="397" alt="capture_251126_112734" src="https://github.com/user-attachments/assets/92577c5e-b94c-4297-b991-f7777e9ec4d9" />

FLAG : CM{TH_CMPHON_WH0_BR0K3_TH3_PH4NT0M_A3G1S_DLL}
