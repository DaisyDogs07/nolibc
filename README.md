This is my own simplified version of libc.

It only has some functions cuz I'm not *that* skilled at coding and problem solving :3

And obvously this is only available in Linux, Sorry.

Compile the library with this:
```console
gcc -shared -nostdlib -fno-builtin -fno-math-errno -fno-stack-protector -fPIC -O3 -o /path/to/libs/libnoc.so.1 *.c
```

Also since ld can only link shared libraries using a `.a` file (Don't know why) run this after compiling:
```console
ar -crs /path/to/libs/libnoc.a /path/to/libs/libnoc.so.1
```