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

Something the model what wrong: 
At one point I accidentally created the hw01 through hw09 folders as files instead of directories, and my bits.c, bits.h, status.c, status.h, and tests/ ended up in the wrong location. I noticed when `cd hw01` failed with "Not a directory." I deleted the mistaken files, recreated the folders
with mkdir, and moved the files into hw01/ with mv.

What I did on my own: 
- Every line of C code in bits.c, status.c.
- All the test cases in tests/test_bits.c.
