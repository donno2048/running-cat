# running-cat

Show a running cat on the taskbar, the faster it runs the faster your CPU is.

The cat icons are by Kyome22 under the Apache License.

I found it very difficult to implement this as there was no documentation regarding tray icons in c. This project is a simple example of such icons and can be used to learn about them.

## Compile

```bat
windres main.rc main.o
gcc main.c main.o -omain
```

### Options

- Invisible: make the command line invisible (will make it impossible to kill the cat until the menu will be implemented)

```bat
gcc main.c -o main -D Invisible
```

- Menu: use experimental menu (not recommended)

```bat
gcc main.c -o main -D Menu
```

## Use

```bat
main.exe
```
