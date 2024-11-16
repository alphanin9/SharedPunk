### Shared library for Cyberpunk 2077 mods

A library with some core utilities for making Cyberpunk 2077 mods using [RED4ext](https://github.com/WopsS/RED4ext.SDK), along with various reverse engineered data. Mostly put together for my personal use.

Credits to [psiberx](https://github.com/psiberx), a lot of this library is ripped off from him.

### Integration into your mod

`git submodule add https://github.com/alphanin9/SharedPunk.git deps/sharedpunk`

Add this to your `xmake.lua` file:

```lua
includes("deps/sharedpunk/xmake.lua")
...
target("your-cool-mod")
    ...
    add_deps("cp2077-shared-data", ...)
```