# Interleaved-String
Algorithm(s) for dealing with interleaved strings

__Check for Interleave__

This implementation uses dynamic programming with memoization table to determine if a string is interleaved between two other strings.

* Use g++ to compile: e.g. "g++ check_for_interleave.cc -o \<executable_name>"
* To use, invoke the executable and pass in 3 strings via command prompt. The first and second string can be any string. The third string is the one to check if it is interleaved of the other two strings.
* e.g. "check_for_interleave hello world worldhello"

__Limitations__

This algorithm only consider the string in question to be a combination of the two other strings and nothing more. Therefore, for cases such as the following:
* string a = "hello", string b = "world", string c = "worldhello" would return true
* string a = "hello", string b = "world", string c = "worldbyehello" would return false
