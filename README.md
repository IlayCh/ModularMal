# ModularMal

A modular malware
● The program have 2 threads running:
● Scan for every new “notepad.exe” and inject the given DLL (from the disk) into every new “notepad.exe”, and write into the file “C:\Temp\just_another_innocent_file.txt” the ID of the process into which you injected.
● Kill every “calc.exe” process that is created on the system.
