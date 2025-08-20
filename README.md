# learn-opengl

## msys2 setup

- install [msys2](https://www.msys2.org/) and then run `msys2Dependencies.sh` in MSYS2 CLANG64 shell
  this will install all the neccessary packages like `cmake`, `clang`, `ninja`, `gdb`. once this is
  done, add `C:\msys64\clang64\bin` to the path and restart vscode.

## git submodules

- by default git submodules are not cloned with the repository so please don't forget to run `git submodule init`
  and `git submodule update` to fetch all the modules, which in this case are libraries like `glfw`, `glad` which
  a typical opengl project needs.
