# DSAP2 PROJECT: WORD LOOKUP WITH TRIE VS HASH

This project compares lookup in a list of words for a trie and a hash. `assets` folder contains a file with the list of words; these words were sourced from the directory `/usr/share/dict/words` found on Unix systems by default. The program relies on the exact file name being `dictionary.txt`. If you wish to change the list of words, please ensure the file is named appropriately. This project uses Catch2 and expects a system package; if Catch2 is not installed on your system, please install it. 

## USAGE:

0. From project root directory (`~/DSAP2`), run `make do` in terminal to build the project. Once built, run `make run` to run the application in terminal and `make test` to run tests. To build and run application in terminal, run `make do run` in terminal. 
1. While the application is running in terminal, there will be 3 options. Input one of the 3 numbers to select the option.
	1. Exact word lookup. Returns "found" if the exact word was found for either the trie or the hash. 
	2. Prefix lookup. Accepts partial word lookup. Input the first several letters of a word; mispellings will give false results. Will return number of possible matches found and the first 5 matches found for both trie and hash. 
	3. Exit. Quits the program. 

