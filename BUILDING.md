# Building Simula-24

## Windows

You will need to run the appropriate scripts before you do anything.

```powershell
C:\Users\Hugh Mann\Simula-24> ./scripts/prebuild.ps1
```

## Linux

You will need to install your compiler and SDL and for now, ncurses. NCUrses will be stripped out soon.

```bash
hugh-mann@coputer:/path/to/simula24$ sudo apt install build-essential libsdl2-dev libncursesw5 libsdl2-image-dev`
hugh-mann@coputer:/path/to/simula24$ cmake .
hugh-mann@coputer:/path/to/simula24$ cmake --build .
```

