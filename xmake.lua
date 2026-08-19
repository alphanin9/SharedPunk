set_languages("c++latest")

-- RED4ext.SDK and RedLib are not in the official xmake-repo.
-- add_repositories takes a single url with no fallback; the GitHub mirror is at
-- https://github.com/alphanin9/cp2077-xmake-repo
add_repositories("cp2077-repo https://gitlab.com/alphanin9/cp2077-xmake-repo.git")

add_requires("red4ext-sdk", "red-lib", "safetyhook")

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
    -- All public: the SDK and RedLib appear in the public headers, and
    -- Shared/Hooks/HookManager.hpp reaches safetyhook.hpp via HookingDriver.hpp.
    add_packages("red4ext-sdk", "red-lib", "safetyhook", { public = true })

add_rules("plugin.vsxmake.autoupdate")
