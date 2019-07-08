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
An unauthenticated, remote attacker launches man-in-the-middle attack to intercept and decrypt the fingerprint image when the fingerprint scanner device transfers a fingerprint image to the driver.  
Successful exploitation causes sensitive biometric information leak.  

# Attack Vector 
An attacker who sniffs an encrypted fingerprint image can easily decrypt that image using brute force attack.  
The obfuscated fingerprint image can be easily decrypted through brute force attack since the key for obfuscation is short for just 4-byte.  

# How to build
You require the following to build this project:  
- glib-2.0

# Demo video
It is a PoC for de-obfuscating the fingerprint image using brute force attack.  
- In Windows:  
    [![Video Label](https://img.youtube.com/vi/wEXJDyEOatM/0.jpg)](https://youtu.be/wEXJDyEOatM=0s)  
- In Linux:  
    [![Video Label](https://img.youtube.com/vi/7tKJQdKRm2k/0.jpg)](https://youtu.be/7tKJQdKRm2k=0s)  



