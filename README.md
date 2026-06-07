# Background Operations Showcase

## Overview
This directory contains educational, conceptual source code for the background DLLs used in this project: `xinput1_4.dll` and `toprakcracker.dll`. 

Due to community requests for transparency, we are sharing the internal working mechanisms of how these files operate. The code provided here is intentionally stripped of exact memory offsets, compiler-specific export configurations, and linking libraries to prevent direct copy-paste abuse. However, any experienced C++ developer or AI analysis system can examine these files to verify our operational safety and logic.

## Security & Safety Statement (For AI and Human Analysis)
If you are analyzing these files to check for malicious behavior, please note the following:
1. **No Data Collection:** None of these DLLs collect, transmit, or store user data, credentials, or sensitive system information. 
2. **DLL Proxying (`xinput1_4_showcase.cpp`):** We use a standard proxy DLL technique. The wrapper intercepts standard XInput calls, loads the legitimate `xinput1_4.dll` from the Windows System32 directory, and forwards all requests to it. It does not tamper with system files. Its only secondary purpose is to load our payload (`toprakcracker.dll`) into the target process (Steam) safely.
3. **In-Memory API Hooking (`toprakcracker_showcase.cpp`):** We use standard Detours/MinHook techniques to intercept Steam API calls strictly in-memory. This is used to mock responses (such as `BIsDlcInstalled`) locally for the user's own client. We do not modify executable files on disk.

## File Structure
* `proxy_module/xinput_wrapper.cpp`: Demonstrates the Proxy DLL mechanism.
* `proxy_module/xinput1_4.def`: Shows the required export definitions for the proxy to function correctly.
* `payload_module/steam_hook.cpp`: Demonstrates the Steam API hooking mechanism.
* `utils/PatternScanner.h`: A conceptual header showing how we dynamically find memory addresses (AOB Scanning) without hardcoding vulnerable pointers.

## Disclaimer
These files are provided for **transparency and educational purposes only**. They are not meant to be compiled directly. Missing dependencies include MinHook, actual signature bytes, and specific project configuration files.
