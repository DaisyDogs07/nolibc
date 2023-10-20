This is my own simplified version of libc. Made to be readable as well.

It only has some functions cuz I'm not *that* skilled at coding and problem solving :3

Also this is only available in Linux, Sorry.

If you want to add something just submit a pull request with your added code

Compile the library with this:
```console
gcc -shared -ffreestanding -nostdlib -fno-builtin -fno-math-errno -fno-stack-protector -fno-plt -fPIC -O2 -o libnoc.so.1 *.c
ar -crs libnoc.a libnoc.so.1
```