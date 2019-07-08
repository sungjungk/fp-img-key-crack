# PoC: obfuscated fingerprint image cracking in U.are.U 4500 fingerprint reader
It is a PoC for cracking obfuscated fingerprint image generated in U.are.U 4500 fingerprint reader.  

# Background: basic operation
When a user try to use fingerprint authentication, a user might touch a finger on the fingerprint reader device.
Just after the capturing fingerprint, the driver generates an initialization vector, and sends it to the reader device.
The device makes a key for image obfuscation and do obfuscate the fingerprint image using provided initialization vector and the key.
After then, the obfuscated fingerprint image and the key are transferred to the driver.
Finally, the driver can de-obfuscate the image using provided key from the device and initialization vector that was held before.  

# Vulnerability
There is a short key vulnerability in U.are.U 4500 Fingerprint Reader v24.
The key for obfuscating the fingerprint image is vulnerable to brute-force attacks.
It allows an attacker to recover the key and decrypt that image using the key.
Successful exploitation causes sensitive biometric information leak.  

# Attack Vector 
An unauthenticated, attacker launches man-in-the-middle attack to intercept a fingerprint image and performs brute-force attack to decrypt that image.
The obfuscated fingerprint image can be easily decrypted through brute-force attack since the key for obfuscation is short for just 4-byte.  

# How to build
You require the following to build this project:  
- glib-2.0

# Demo video
A brute force attack is performed for de-obfuscating the fingerprint image after MITMing.
It is a PoC for de-obfuscating the fingerprint image using brute force attack.  
- In Windows:  
    [![Video Label](https://img.youtube.com/vi/BwYK_xZlKi4/0.jpg)](https://youtu.be/BwYK_xZlKi4=0s)  
- In Linux:  
    [![Video Label](https://img.youtube.com/vi/7tKJQdKRm2k/0.jpg)](https://youtu.be/7tKJQdKRm2k=0s)  

