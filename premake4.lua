
solution "UnityAssetTool"
  location "build/"
  debugdir "bin/"
  configurations {"Debug", "Release"}
  language "C++"

  configuration "Debug"
    defines { "DEBUG" }
    flags { "Symbols"}
    targetsuffix "_d"

  configuration "Release"
    defines { "NDEBUG" }
    flags { "Optimize"}

  project "lzma"
    kind "StaticLib"
    language "C"
    targetdir "lib/"
    
    files {
      "src/lzma/**.h",
      "src/lzma/**.c",
    }
    includedirs { "src/lzma/" }
    libdirs {"lib/"}

  local lib_proj_dir = ""
  project "unity_asset"
    kind "StaticLib"
    language "C++"
    targetdir "lib/"
    
    files {
      "src/unity_asset/**.h",
      "src/unity_asset/**.cpp",
    }
    includedirs { "src", "src/unity_asset/" }
    libdirs {"lib/"}
    links { "lzma" }

    configuration "windows"
      defines { "_CRT_SECURE_NO_WARNINGS" }

    configuration "macosx"
      buildoptions { "-std=c++11", "-Wno-deprecated-declarations" }

  project "unity_asset_extractor"
    kind "ConsoleApp"
    targetdir "bin/"
    
    files {
      "src/unity_asset_extractor/**.h",
      "src/unity_asset_extractor/**.cpp",
    }
    
    includedirs { "src/unity_asset/", "src/unity_asset_extractor/" }
    libdirs {"lib/"}
    links { "lzma", "unity_asset" }

    configuration "windows"
      defines { "_CRT_SECURE_NO_WARNINGS" }

    configuration "macosx"
      buildoptions { "-std=c++11", "-Wno-deprecated-declarations" }
