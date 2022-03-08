# SpecialArcade

Effort to make a common API for the Arcade project.

## Generate documentation

```bash
doxygen Doxyfile
```

## REQUIREMENTS of implementation

- The interfaces in the `interface/` folder MUST be left AS IS and implemented.
- The games and display managers `.so` files MUST be compiled with the `-fPIC`
and `-fno-gnu-unique` flags.
- The compiled games and display managers `.so` files MUST provide an
`expose` function placed inside of `extern "C" { ... }`.
- The `expose` function of games should take no arguments and MUST
return a pointer to `arc::IGame *` (no smart pointers shall be returned).
- The `expose` function of display managers should take no arguments and
MUST return a pointer to `arc::IDisplayManager *` (no smart pointers shall be
returned).
- The pointers returned by the `expose` functions SHALL be managed and
deleted manually by the caller of the shared library, before calling `dlclose`.
