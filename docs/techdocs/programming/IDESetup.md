# Setting up Visual Studio Code

Visual Studio code is an IDE (interactive development environment) that provides a bunch of tools for people to make software.

Even if you are not a programmer I would recommend you install it just to have it setup just for syntax highlighting of special text files.

### Installing Visual Studio Code

Install Visual Studio code [here](https://code.visualstudio.com/Download) and follow the instructions

### Open the Project
It is recommended to open the root folder (either by right clicking in the file browser or File->Open Folder)

## User Interface



## Recommended Extensions

* [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-python.autopep8)
* [Python](https://marketplace.visualstudio.com/items?itemName=ms-python.python)
* [gettext](https://marketplace.visualstudio.com/items?itemName=mrorz.language-gettext) (features for translators)
* [glTF](https://marketplace.visualstudio.com/items?itemName=cesium.gltf-vscode) (for quickly viewing models)
* [MIPS Support](https://marketplace.visualstudio.com/items?itemName=kdarkhan.mips) (for advanced programmers)
* [Hex eEditor](https://marketplace.visualstudio.com/items?itemName=ms-vscode.hexeditor) (for viewing binary files)

## Debugger
If you are a programmer you might want to setup a debugger so you aren't flying without instruments when testing code.

### Windows Install:
1. Install [MSYS2](https://www.msys2.org/) with default settings
2. When it prompts you to run click yes or search for and open MinGW64 in your task bar
3. In the MINGW64 prompt type `pacman -S mingw-w64-x86_64-gdb-multiarch`, hit enter and install

### Linux Install

Install `gdb-multiarch` from your package manager of choice

### Using the Debugger

1. Build the project
2. Set your breakpoints (places you want to pause execution) by clicking next to the line number
After building the project open load it in the emulator and hit `F5` in VSCode
3. Load the game using `python Playtest.py -d` to run with the debugger enabled
4. Connect to the debugger using F5 inside VSCode or hitting the `Connect Debugger` option
5. When a breakpoint is hit the execution will pause and you can poke the program in VSCode's **DEBUG CONSOLE**

#### Printing Variables
Typing the name of a variable (accessible in the current context) will cause it to print.

``` C
MyVariable
```

#### Assigning Variables
You can also asign values to variables
``` C
MyVariable = 32
```

#### Executing Functions
Typing out a function with its arguments will cause it to execute and print the return value

``` C
MyFunction(32, true)
```

#### More info

Type `-exec help` for more info commands

### Troubleshooting

#### ERROR could not connect (error 138): The system tried to join a drive to a directory on a joined drive.
This happens when you try to connect to the game while it or the debugger isn't running. Try loading the game and making sure you followed the steps properly.