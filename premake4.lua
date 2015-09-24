
function add_proj (name, with_boost)
    project (name)
      kind "ConsoleApp"
      targetdir "bin/"
      
      files {
        path.join("src", name, "**.h"),
        path.join("src", name, "**.hpp"),
        path.join("src", name, "**.cpp")
      }
      
      includedirs {
        "src/thirdpart/",
        "src/thirdpart/lzma/",
        "src/unity_asset/",
        path.join("src", name)
      }
      libdirs { "lib/" }
      if with_boost then libdirs{ "lib/boost/" } end
      links { "lzma", "unity_asset" }
  
      configuration "windows"
        defines { "_CRT_SECURE_NO_WARNINGS" }
  
      configuration "macosx"
        buildoptions { "-std=c++11", "-Wno-deprecated-declarations" }
end

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
    language "C++"
    targetdir "lib/"
    
    files {
      "src/thirdpart/lzma/**.h",
      "src/thirdpart/lzma/**.c",
    }
    includedirs { "src/thirdpart/lzma/" }
    libdirs {"lib/"}
    defines {"_7ZIP_ST"}

  project "unity_asset"
    kind "StaticLib"
    language "C++"
    targetdir "lib/"
    
    files {
      "src/unity_asset/**.h",
      "src/unity_asset/**.cpp",
    }
    includedirs {
      "src/thirdpart/",
      "src/thirdpart/lzma/",
      "src/unity_asset/"
    }
    libdirs {"lib/"}
    links { "lzma" }

    configuration "windows"
      defines { "_CRT_SECURE_NO_WARNINGS" }

    configuration "macosx"
      buildoptions { "-std=c++11", "-Wno-deprecated-declarations" }

    add_proj("unity_asset_extractor", true)
    add_proj("unity_assetbundle_extractor", false)
    add_proj("test", false)
