Estefani Reyes Moreno
ECE 361
Fall 2026
4 October 2026

AI usage for HW 1

How I used AI (Claude and DeepSeek):
- Setting up my C toolchain: installing WSL 2 + Ubuntu, configuring VS Code
  to connect to WSL, and getting the terminal working.
- Organizing my repository: creating the hw01/ folder structure, fixing
  files that were accidentally created in the wrong place, and verifying
  the layout.
- Getting hints and explanations for the four bit-manipulation functions
  (print_binary, get_field, set_field, sign_extend). I used it as guidance as I went through each part.

One thing I had to fix:
When I copied my code into Github, I made two types in the 'bits.c'. n `get_field` I wrote `pos + width < 32` instead of `pos + width > 32`, and in `sign_extend` I wrote `-mask` instead of `~mask`. `make test` caught both: 7 tests failed. I found the typos by comparing my file to the working
version, then fixed them and re-tested a fresh clone. I also had an empty Makefile on GitHub at first, which I found when `make` said "No targets."

What I did on my own: 
- Lines of C code in bits.c, status.c.
- All the test cases in tests/test_bits.c.
