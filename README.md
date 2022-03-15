# SpecialArcade

Effort to make a common API for the Arcade project.

> Note: This is not a game engine. It is a common interface for game engines to do basic operations.

## Generate documentation

```bash
rm -R html latex # remove existing documentation
doxygen Doxyfile
xdg-open html/index.html  # or   firefox html/index.html
```

## REQUIREMENTS of implementation

- The interfaces in the `interface/` folder MUST be left AS IS and implemented.
- The games and graphical libraries `.so` files MUST be compiled with the `-fPIC`
and `-fno-gnu-unique` flags.
- The compiled games and graphical libraries `.so` files MUST provide an
`expose` function placed inside of `extern "C" { ... }`.
- Each graphical libraries `.so` files must provide its dependencies (e.g.
`arcade-sfml.so` must be compiled with `-lsfml-graphics` and `-lsfml-window`).
- The `expose` function of games should take no arguments and MUST
return a pointer to `arc::IGame *` (no smart pointers shall be returned).
- The `expose` function of graphical libraries should take no arguments and
MUST return a pointer to `arc::IDisplayManager *` (no smart pointers shall be
returned).
- The pointers returned by the `expose` functions SHALL be managed and
deleted manually by the caller of the shared library, before calling `dlclose`.


## Keep your interfaces up to date more easily

> NOTE: NEVER run the script or `make api` if you made changes to the
> `API_DIR` folder, as it will completely erase the `API_DIR` folder
> and recreate it from this repo.

> ALSO NOTE: You're not expected to make changes in the `API_DIR` folder
> directly. Instead, you should make changes in the `interface/` folder
> of this repo, and in your project repository, create classes
> that inherit these interfaces, in another folder (NOT IN `API_DIR`).

### Makefile

Add this to your Makefile.

```makefile
API_DIR = $(PWD)/include/spc  # the API directory, ensure the folder is empty

# ...

api:
    git clone git@github.com:norech/special-arcade.git /tmp/arcade
    rm -rf $(API_DIR)
    mkdir -p $(API_DIR)
    cp -r /tmp/arcade/interface/* $(API_DIR)
    rm -rf /tmp/arcade
```

Now each time an interface is changed, your can run `make api` to keep it
up to date.

### Script

You can also create a `make-api.sh` script instead if you prefer.

```bash
#!/bin/bash
API_DIR="$PWD/include/spc"  # the API directory, ensure the folder is empty

git clone git@github.com:norech/special-arcade.git /tmp/arcade
rm -rf $API_DIR
mkdir -p $API_DIR
cp -r /tmp/arcade/interface/* $API_DIR
rm -rf /tmp/arcade
```

Now each time an interface is changed, you can run `./make-api.sh` to keep it
up to date.
