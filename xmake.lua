set_languages("c++latest")

-- RED4ext.SDK and RedLib are vendored as git submodules for the `git submodule add`
-- integration documented in the README. When they are not checked out -- which is the case
-- when SharedPunk is consumed as an xmake package -- take them from the package repo
-- (https://github.com/alphanin9/cp2077-xmake-repo) instead.
local deps_dir = path.join(os.scriptdir(), "deps")
local has_vendored_deps = os.isdir(path.join(deps_dir, "red4ext.sdk", "include"))
                      and os.isdir(path.join(deps_dir, "redlib", "include"))

add_requires("safetyhook")
if not has_vendored_deps then
    add_requires("red4ext-sdk", "red-lib")
end

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
    -- The parenthesised part is the path kept on install, so headers land under
    -- <prefix>/include/Impl/... and <prefix>/include/Shared/..., matching the two
    -- include dirs above. Without it xmake flattens everything into <prefix>/include/.
    add_headerfiles("src/include/(Impl/**.hpp)")
    add_headerfiles("src/include/Public/(Shared/**.hpp)")
    add_syslinks("Version", "User32")
    add_defines("WINVER=0x0601", "WIN32_LEAN_AND_MEAN", "NOMINMAX")
    -- Public: Shared/Hooks/HookManager.hpp reaches safetyhook.hpp through HookingDriver.hpp.
    add_packages("safetyhook", { public = true })
    if has_vendored_deps then
        add_deps("cp2077-shared-data-red::red4ext.sdk", "cp2077-shared-data-red::redlib")
    else
        add_packages("red4ext-sdk", "red-lib", { public = true })
    end

if has_vendored_deps then
    namespace("cp2077-shared-data-red", function()
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
    end)
end

add_rules("plugin.vsxmake.autoupdate")
