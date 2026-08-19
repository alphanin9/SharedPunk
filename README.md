### Shared library for Cyberpunk 2077 mods

A library with some core utilities for making Cyberpunk 2077 mods using [RED4ext](https://github.com/WopsS/RED4ext.SDK), along with various reverse engineered data. Mostly put together for my personal use.

Credits to [psiberx](https://github.com/psiberx), a lot of this library is ripped off from him.

### Integration into your mod

SharedPunk is packaged in [cp2077-xmake-repo](https://github.com/alphanin9/cp2077-xmake-repo):

```lua
add_repositories("cp2077-repo https://gitlab.com/alphanin9/cp2077-xmake-repo.git")
add_requires("sharedpunk")

target("your-cool-mod")
    ...
    add_packages("sharedpunk")
```

Or as a submodule, to build it from source alongside your mod:

`git submodule add https://github.com/alphanin9/SharedPunk.git deps/sharedpunk`

```lua
includes("deps/sharedpunk/xmake.lua")
...
target("your-cool-mod")
    ...
    add_deps("cp2077-shared-data", ...)
```

Either way RED4ext.SDK, RedLib and SafetyHook come from xmake packages, so there is
nothing to clone recursively.

### How to use

**Note: the \<Impl/> directory contains various implementation data 
(hooking detail, address hashes for defined reversed functions, etc), 
it should not be necessary to include anything from there directly**

```cpp
#include <Shared/Util/Core.hpp>

constexpr auto fn = shared::util::RawFunc<...>();
```
