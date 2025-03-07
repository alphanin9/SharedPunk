set_languages("c++latest")
add_requires("zydis")

target("cp2077-shared-data")
    set_kind("static")
    if is_mode("ci") then
        set_warnings("all", "error")
    else
        set_warnings("more")
    end
    set_optimize("fastest")
    add_files("src/code/**.cpp")
    add_includedirs("src/include/", { public = true })
    add_includedirs("src/include/Public", { public = true })
    add_headerfiles("src/include/**.hpp")
    add_syslinks("Version", "User32")
    add_defines("WINVER=0x0601", "WIN32_LEAN_AND_MEAN", "NOMINMAX")
    add_deps("red4ext.sdk", "redlib", "safetyhook")

target("red4ext.sdk")
    set_default(false)
    set_kind("headeronly")
    set_warnings("none")
    set_group("deps")
    add_headerfiles("deps/red4ext.sdk/vendor/**.h")
    add_headerfiles("deps/red4ext.sdk/include/**.hpp")
    add_includedirs("deps/red4ext.sdk/vendor/")
    add_includedirs("deps/red4ext.sdk/include/", { public = true })

target("redlib")
    set_default(false)
    set_kind("headeronly")
    set_warnings("none")
    set_group("deps")
    add_defines("NOMINMAX")
    add_headerfiles("deps/redlib/vendor/**.hpp")
    add_headerfiles("deps/redlib/include/**.hpp")
    add_includedirs("deps/redlib/vendor/", { public = true })
    add_includedirs("deps/redlib/include/", { public = true })

target("safetyhook")
    set_default(false)
    set_warnings("none")
    set_kind("static")
    set_group("deps")
    -- NOTE: The .asm files are there to paste the machine code of into src/mid_hook.cpp
    add_files("deps/safetyhook/src/**.cpp")
    add_headerfiles("deps/safetyhook/include/**.hpp")
    add_includedirs("deps/safetyhook/include/", { public = true })
    add_cxflags("/GR-")
    add_packages("zydis")

add_rules("plugin.vsxmake.autoupdate")

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

