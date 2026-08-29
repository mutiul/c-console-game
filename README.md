# Number Rush — A Beginner C Project

Number Rush is a colorful number-guessing game that runs in a terminal. It is
a small project for anyone beginning to learn the C programming language.

The computer chooses a secret number. You choose a difficulty and try to find
the number before you run out of lives. The game gives higher/lower,
warmer/colder, and proximity clues.

## What you can learn

This project demonstrates several important C concepts:

- Variables and data types
- Functions
- `if`, `else`, and loops
- Arrays and structures (`struct`)
- Reading user input safely
- Random numbers
- Constants and terminal colors
- Compiling a program with warnings enabled

The complete program is in [`src/main.c`](src/main.c).

## Game features

- Chill, Classic, and Insane difficulty modes
- Different number ranges, lives, and score multipliers
- Colorful life and heat meters
- Warmer/colder and higher/lower hints
- Score bonuses and winning streaks
- Input validation, surrender, and replay options

## Project files

```text
c-console-game/
├── src/
│   └── main.c       # The C source code
├── .gitignore       # Files Git should not track
├── Makefile         # Convenient build commands
└── README.md        # This guide
```

## Before you begin

You need:

1. A terminal (also called a command line or shell).
2. A C compiler such as GCC or Clang.
3. Optionally, `make` to use the included Makefile.

To check whether the tools are already installed, open a terminal and run:

```sh
cc --version
make --version
```

If both commands display version information, skip to **Build and play**.

## macOS setup

macOS can install the Clang compiler and `make` through Apple's Command Line
Tools.

1. Open **Terminal**. You can find it with Spotlight Search.
2. Install the tools:

   ```sh
   xcode-select --install
   ```

3. Complete the installation window, then verify it:

   ```sh
   cc --version
   make --version
   ```

## Linux setup

Open a terminal and use the command for your distribution.

### Ubuntu, Debian, or Linux Mint

```sh
sudo apt update
sudo apt install build-essential
```

### Fedora

```sh
sudo dnf install gcc make
```

### Arch Linux or Manjaro

```sh
sudo pacman -S base-devel
```

Verify the installation:

```sh
cc --version
make --version
```

## Windows setup

### Recommended: MSYS2 and GCC

MSYS2 provides a Unix-like terminal, GCC, and `make`, so the commands match the
macOS and Linux instructions.

1. Download and install MSYS2 from [msys2.org](https://www.msys2.org/).
2. Open the **MSYS2 UCRT64** terminal from the Start menu.
3. Update its packages:

   ```sh
   pacman -Syu
   ```

   If the terminal asks you to close it, reopen **MSYS2 UCRT64** and run the
   same command again.

4. Install GCC and Make:

   ```sh
   pacman -S --needed mingw-w64-ucrt-x86_64-gcc make
   ```

5. Verify the installation:

   ```sh
   gcc --version
   make --version
   ```

Always use the **MSYS2 UCRT64** terminal when following the `make` commands in
this guide.

### Windows alternative: compile without Make

If GCC is already available in PowerShell or Command Prompt, go to the project
folder and run:

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic src/main.c -o guessing-game.exe
./guessing-game.exe
```

Windows Terminal, modern PowerShell, and the MSYS2 terminal support the colors
used by the game. An older Command Prompt may not display them correctly.

## Build and play

First, open a terminal inside the project folder. For example, on macOS or
Linux:

```sh
cd /path/to/c-console-game
```

On Windows with MSYS2, a folder such as `C:\Users\Sam\Projects` is written as
`/c/Users/Sam/Projects`:

```sh
cd /c/Users/Sam/Projects/c-console-game
```

Compile the game:

```sh
make
```

Run it on macOS, Linux, or MSYS2:

```sh
./guessing-game
```

You can also compile and run it with one command:

```sh
make run
```

Choose a difficulty by typing `1`, `2`, or `3` and pressing Enter. During a
round, enter `0` to surrender.

## Compile manually

The Makefile is only a shortcut. Seeing the full compiler command is useful
when learning C.

On macOS or Linux:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic src/main.c -o guessing-game
./guessing-game
```

On Windows with GCC:

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic src/main.c -o guessing-game.exe
./guessing-game.exe
```

Here is what each part means:

- `cc` or `gcc` starts the C compiler.
- `-std=c11` asks the compiler to use the C11 language standard.
- `-Wall -Wextra -Wpedantic` enables helpful warnings.
- `src/main.c` is the source file to compile.
- `-o guessing-game` names the finished program.

Warnings are valuable learning tools. Read and fix them instead of hiding
them.

## Rebuild after changing the code

Edit `src/main.c`, save it, and run:

```sh
make
./guessing-game
```

`make` checks whether the source changed and rebuilds the program when needed.
To remove the generated program and start with a clean build, run:

```sh
make clean
make
```

In native Windows PowerShell, remove the executable with:

```powershell
Remove-Item guessing-game.exe
```

## Using Visual Studio Code (optional)

VS Code is an editor, not a C compiler. Install a compiler using the setup
instructions above first.

1. Open VS Code.
2. Select **File > Open Folder** and choose `c-console-game`.
3. Install Microsoft's **C/C++** extension when prompted.
4. Open **Terminal > New Terminal**.
5. Run `make`, followed by `./guessing-game`.

On Windows, start VS Code from the MSYS2 UCRT64 terminal with `code .` if you
want its integrated terminal to inherit your MSYS2 environment.

## Common problems

### `cc`, `gcc`, or `make` is “not found”

The development tools are missing or are not on your system's `PATH`. Follow
the setup section for your operating system, close the terminal, and open a
new one.

### `No rule to make target` or `No targets specified`

The terminal is probably in the wrong folder. Run `pwd` on macOS/Linux/MSYS2,
or `Get-Location` in PowerShell. The folder should contain `Makefile`.

### `Permission denied` when running the game

On macOS or Linux, restore executable permission and try again:

```sh
chmod +x guessing-game
./guessing-game
```

### The screen shows characters such as `[31m`

Your terminal does not support ANSI colors. Use Windows Terminal, PowerShell,
MSYS2 UCRT64, the macOS Terminal app, or a modern Linux terminal.

### The game does not rebuild

Make sure `src/main.c` was saved, then perform a clean build:

```sh
make clean
make
```

## Ideas for your next changes

After you understand the current game, try one change at a time:

- Add a new difficulty level.
- Change how many lives each mode provides.
- Add a player name.
- Save the high score to a file.
- Add a time limit.
- Split the program into multiple `.c` and `.h` files.

Compile and test after every small change. That makes errors much easier to
find and understand.
