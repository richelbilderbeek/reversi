# Building

Requires Qt and Boost.

The code the game uses from Richèl Bilderbeek's other repositories
is copied into this one:

- [DotMatrix](https://github.com/richelbilderbeek/DotMatrix), in the `dot_matrix` folder
- [RibiClasses](https://github.com/richelbilderbeek/RibiClasses), in the `ribi_classes` folder

Build the desktop version:

```bash
qmake ReversiDesktop.pro
make
```

Or build the console version:

```bash
qmake ReversiConsole.pro
make
```

## Online version

The online version only needs Qt 6 and the Boost headers,
and not the other repositories.
Use the `qmake` from a single-threaded Qt for WebAssembly installation,
with the matching
[Emscripten](https://doc.qt.io/qt-6/wasm.html) version:

```bash
qmake ReversiWebAssembly.pro BOOST_INCLUDE_DIR=/path/to/boost_headers
make
```

[GitHub Actions](https://github.com/richelbilderbeek/reversi/blob/main/.github/workflows/create_zensical_website.yaml)
builds the online version and puts it on this website.
