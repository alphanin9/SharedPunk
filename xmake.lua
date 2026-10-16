set_languages("c++latest")

-- RED4ext.SDK and RedLib are not in the official xmake-repo.
-- add_repositories takes a single url with no fallback; the GitHub mirror is at
-- https://github.com/alphanin9/cp2077-xmake-repo
add_repositories("cp2077-repo https://gitlab.com/alphanin9/cp2077-xmake-repo.git")

add_requires("red4ext-sdk", "red-lib")
if is_plat("windows") then
    -- x86 only; the macOS hook driver (src/code/Hooks/HookingDriver.cpp) goes through the RED4ext loader API.
    add_requires("safetyhook")
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
    if is_plat("windows") then
        add_syslinks("Version", "User32")
        add_defines("WINVER=0x0601", "WIN32_LEAN_AND_MEAN", "NOMINMAX")
    end
    -- All public: the SDK and RedLib appear in the public headers, and
    -- Shared/Hooks/HookManager.hpp reaches safetyhook.hpp via HookingDriver.hpp.
    add_packages("red4ext-sdk", "red-lib", { public = true })
    if is_plat("windows") then
        add_packages("safetyhook", { public = true })
    end

add_rules("plugin.vsxmake.autoupdate")
