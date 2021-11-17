# running-cat

Show a running cat on the taskbar, the faster it runs the faster your CPU is.

The cat icons are by Kyome22 under the Apache License.

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
