# Development

### msys2 setup

- install [msys2](https://www.msys2.org/) and then run `msys2Dependencies.sh` in MSYS2 CLANG64 shell
  this will install all the neccessary packages like `cmake`, `clang`, `ninja`, `gdb`. once this is
  done, add `C:\msys64\clang64\bin` to the path and restart vscode.

### git submodules

- by default git submodules are not cloned with the repository so please don't forget to run `git submodule init`
  and `git submodule update` to fetch all the modules, which in this case are libraries like `glfw`, `glad` which
  a typical opengl project needs.

### git markers in vscode

- `git` is the first msys2 package that i install as then i can use it to clone my projects and run the
  dependencies install script inside them. vscode doesn't have access to this yet, so we need to add
  `C:\msys64\usr\bin` to the windows `PATH` variable. this shouldn't be an issue if you are not mixing 
  compiler toolchains, i am using everything clang64.

### where to place git and ssh configs

- if you are using msys2's git then you should place it in `C:\msys64\home\username\{.ssh,.gitconfig}`, if
  you are using `git for windows`, the configs should be placed in `C:\Users\username\{.ssh,.gitconfig}`.

### clangd issues

- the clangd vscode extension asks you to download clangd when it doesn't find it in the path, please don't 
  do that as that would install clangd in the windows environment and it won't find the headers there (as they
  are in /clang64 environment). `msys2Dependencies.sh` downloads clang-tools-extra package which downloads 
  `clangd.exe` in the /clang64 env, and `.vscode/settings.json` points to that, so things should work just fine.