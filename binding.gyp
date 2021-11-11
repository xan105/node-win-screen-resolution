{
    "targets": [
    {
        "target_name": "resolution",
        "sources": [
          "lib/src/resolution.cpp",
          "lib/src/videomod.cpp",
          "lib/src/dpiAwareness.cpp"
        ],
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "msvs_settings": {
          "VCCLCompilerTool": {
            "ExceptionHandling": 1,
            "AdditionalOptions": []
          },
          "VCLinkerTool": {
            "AdditionalDependencies": ["nafxcw.lib;libcmt.lib"],
            "IgnoreDefaultLibraryNames": "nafxcw.lib;libcmt.lib",
            "AdditionalOptions": []
          },
         },
        "include_dirs": ["<!(node -p \"require('node-addon-api').include_dir\")"],
        "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS", "NODE_ADDON_API_ENABLE_MAYBE" ]
    },
    {
        "target_name": "resolution_legacy_dpi",
        "sources": [
          "lib/src/resolution.cpp",
          "lib/src/videomod.cpp",
          "lib/src/legacy/dpiAwareness.cpp"
        ],
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "msvs_settings": {
          "VCCLCompilerTool": {
            "ExceptionHandling": 1,
            "AdditionalOptions": []
          },
          "VCLinkerTool": {
            "AdditionalDependencies": ["nafxcw.lib;libcmt.lib"],
            "IgnoreDefaultLibraryNames": "nafxcw.lib;libcmt.lib",
            "AdditionalOptions": []
          },
         },
        "include_dirs": ["<!(node -p \"require('node-addon-api').include_dir\")"],
        "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS", "NODE_ADDON_API_ENABLE_MAYBE" ]
    }]
}