# Building

Requires Qt, Boost and some of Richèl Bilderbeek's other repositories.

Get these other repositories by running, from the project root:

```bash
./download_other_githubs
```

This clones DotMatrix, plane, RibiClasses and RibiLibraries
next to this repository.

Then build the desktop version:

```bash
qmake ReversiDesktop.pro
make
```

Or build the console version:

```bash
qmake ReversiConsole.pro
make
```
