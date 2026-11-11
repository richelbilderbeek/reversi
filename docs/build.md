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
