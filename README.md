# running-cat

Show a running cat on the taskbar, the faster it runs the faster your CPU is.

The cat icons are by Kyome22 under the Apache License.

I found it very difficult to implement this as there was no documentation regarding tray icons in c. This project is a simple example of such icons and can be used to learn about them.

## Compile

(If you want to rename it you will have to compile it with a different name)

```bat
windres main.rc main.o
gcc main.c main.o -o main
```

### Menu (recommended)

```bat
gcc main.c main.o -o main -D Menu
```

## Use

```bat
main.exe
```
