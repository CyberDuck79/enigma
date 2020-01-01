# Enigma Machine
## Personnal project
Implementation of a enigma machine in C.  
### USAGE :
compilation : launch make command
first arg : configuration  
seconde arg : message  
### configration :
3 rotors among 8 to put in the machine, order matters and rotors cannot be used twice.  
1 reflector : B or C.  
3 starting postions set by letter (A-Z).  
0 to 13 wires that connect 2 letters, a letter can only be connected twice.
### configuration syntax :
rotor1-rotor2-rotor3-reflector-position1-position2-position3-wire1_letter1/wire1_letter2-wire2_letter1/wire2_letter2...  
exemple :  
./enigma_machine "4-2-7-C-Z-R-W-A/Z-B/R-S/W" "TEST DE CHIFFREMENT" -> NHROUCQFEYKQLNZXS  
./enigma_machine "4-2-7-C-Z-R-W-A/Z-B/R-S/W" "NHROUCQFEYKQLNZXS" -> TESTDECHIFFREMENT  
