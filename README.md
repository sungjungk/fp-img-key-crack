# PoC: encryption key cracking for U.are.U 4500 Fingerprint Reader
It is a PoC to crack encrypted fingerprint image generated in U.are.U 4500 Fingerprint Reader.  

# Overview
Digital Persona U.are.U 4500 is a fingerprint reader for authentication and identification solutions.  
The manufacturer describes the product as follows (see [1]):  

* To use, simply place a finger on the reader window and the reader quickly and automatically captures and ***encrypts the fingerprint image*** before sending it to the DigitalPersona® FingerJet™ biometric engine for verification. For superior user feedback, a red “flash” indicates that a fingerprint image has been captured.

link: https://www.hidglobal.com/sites/default/files/resource_files/eat-digitalpersona-4500-reader-ds-en.pdf  

Due to weak encryption, the U.are.U 4500 Fingerprint Reader is vulnerable to decryption of the encrypted fingerprint image. 
This could allows an attacker to make a natural-looking fingerprint image and impersonate a legitimate fingerprint authentication.

# Vulnerabilities Details:
[CVE-2019-13604] An issue was discovered in U.are.U 4500 Fingerprint Reader v24. 
A key for encrypting fingerprint image is vulnerable to brute-force attacks. 
It allows an attacker to extract a natural-looking fingerprint image from encrypted fingerprint image. 
Successful exploitation causes sensitive biometric information leak. 
- CWE-310: Cryptographic Issues

# Proof of Concept (PoC):
We launch man-in-the-middle attack to intercept a fingerprint image and perform brute-force attack to decrypt that image against U.are.U 4500 Fingerprint Reader.

# How to build
You require the following to build this project:  
- glib-2.0

# Disclosure Timeline:
2019-03-23: Vulnerability reported to manufacturer.    
2019-07-09: Public release of security advisory.  
2019-07-15: CVE-2019-13604 has been assigned.
