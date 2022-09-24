This is my own simplified version of libc.

It only has some functions cuz I'm not *that* skilled at coding and problem solving :3

Also this is only available in Linux, Sorry.

Compile the library with this:
```console
gcc -shared -nostdlib -fno-builtin -fno-math-errno -fno-stack-protector -fPIC -O3 -o libnoc.so.1 *.c
ar -crs libnoc.a libnoc.so.1
```