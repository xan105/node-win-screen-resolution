{
  "targets": 
    [
      {
        "target_name": "video",
        "sources": [
          "lib/src/video.cpp"
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
      }
  ]
}