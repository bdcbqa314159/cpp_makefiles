# Lesson 24 -- `install` Target

## What you'll learn

How to write `install` and `uninstall` targets that copy built artifacts to standard system directories, using the conventions that package builders expect.

## The `install` command

You might wonder why install rules use the `install` command instead of `cp`. Three reasons:

1. **Permissions in one step** -- `install -m 755 greeter /usr/local/bin/` copies the file and sets it executable atomically.
2. **Directory creation** -- `install -d /usr/local/bin` creates the directory (and parents) if it doesn't exist, like `mkdir -p`.
3. **Convention** -- every Unix Makefile uses `install`. Package build systems (`dpkg-buildpackage`, `rpmbuild`, `brew`) expect it.

```makefile
install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)   # executable: rwxr-xr-x
install -m 644 $(LIB) $(DESTDIR)$(LIBDIR)      # library:    rw-r--r--
install -m 644 include/greet.hpp $(DESTDIR)$(INCDIR)  # header: rw-r--r--
```

## Directory conventions

| Variable | Default | Contents |
|----------|---------|----------|
| `PREFIX` | `/usr/local` | Base directory for all installed files |
| `BINDIR` | `$(PREFIX)/bin` | Executables |
| `LIBDIR` | `$(PREFIX)/lib` | Static and shared libraries |
| `INCDIR` | `$(PREFIX)/include` | Public headers (often in a subdirectory like `include/greetlib/`) |

`PREFIX` is declared with `?=` so users can override it:

```bash
make install PREFIX=/opt/myapp
```

This installs to `/opt/myapp/bin/`, `/opt/myapp/lib/`, etc.

## `DESTDIR` -- staged installs

`DESTDIR` is **not** the same as `PREFIX`. It is a staging root prepended to every path, used by package builders to install into a temporary directory tree without touching the real filesystem.

```bash
make install DESTDIR=/tmp/staging
```

This creates:

```
/tmp/staging/usr/local/bin/greeter
/tmp/staging/usr/local/lib/libgreet.a
/tmp/staging/usr/local/include/greetlib/greet.hpp
```

The package builder then wraps that tree into a `.deb`, `.rpm`, or similar. The final user installs the package, which unpacks into the real `/usr/local/`.

The key difference: `PREFIX` affects the runtime paths baked into the software. `DESTDIR` only affects where files land during `make install` -- the software still thinks it lives at `PREFIX`.

## `uninstall` target

The `uninstall` target removes exactly what `install` put in place:

```makefile
uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(notdir $(TARGET))
	rm -f $(DESTDIR)$(LIBDIR)/$(notdir $(LIB))
	rm -f $(DESTDIR)$(INCDIR)/greet.hpp
	-rmdir $(DESTDIR)$(INCDIR) 2>/dev/null || true
```

The `-rmdir` at the end removes the `greetlib/` subdirectory, but only if it's empty. The leading `-` tells Make to ignore the error if the directory isn't empty (other software may have installed headers there too). The `|| true` ensures the shell exit code is zero regardless.

## File manipulation functions

The `uninstall` target uses `$(notdir)` to strip the directory prefix from a path. Make provides four path-dissection functions:

| Function | Input | Output | Use case |
|----------|-------|--------|----------|
| `$(notdir path)` | `build/greeter` | `greeter` | Get the filename for install/uninstall |
| `$(dir path)` | `build/greeter` | `build/` | Get the directory part (includes trailing `/`) |
| `$(basename path)` | `build/greeter` | `build/greeter` | Strip the suffix (no `.ext` here, so unchanged) |
| `$(suffix path)` | `build/libgreet.a` | `.a` | Get the file extension |

Run `make debug` to see these in action with the actual values from this Makefile.

## How CMake replaces this

CMake has built-in install support that handles PREFIX, DESTDIR, permissions, and platform differences automatically:

```cmake
install(TARGETS greeter DESTINATION bin)
install(TARGETS greet ARCHIVE DESTINATION lib)
install(FILES include/greet.hpp DESTINATION include/greetlib)
```

Running `cmake --install build --prefix /opt/myapp` does the equivalent of `make install PREFIX=/opt/myapp`. CMake also generates an `uninstall` target and handles RPATH fixup for shared libraries.

## Try it

```bash
cd 24_install_target
make                                        # build the executable and library
./build/greeter World                       # test it locally
make debug                                  # see path functions and install paths

make install PREFIX=/tmp/test_install       # install to a safe location
ls /tmp/test_install/bin/                   # greeter is there
ls /tmp/test_install/lib/                   # libgreet.a is there
ls /tmp/test_install/include/greetlib/      # greet.hpp is there
/tmp/test_install/bin/greeter Make          # run from installed location

make uninstall PREFIX=/tmp/test_install     # clean up
rm -rf /tmp/test_install                    # remove the test directory
make clean
```

## Files

| File | Purpose |
|------|---------|
| `include/greet.hpp` | Declares `greet()` -- the public header installed to `INCDIR` |
| `src/greet.cpp` | Implements `greet()` -- compiled into `libgreet.a` |
| `src/main.cpp` | CLI entry point -- compiled into the `greeter` executable |
| `Makefile` | Demonstrates `install`, `uninstall`, `DESTDIR`, `PREFIX`, and path functions |
