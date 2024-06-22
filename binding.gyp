{
  "targets": 
    [
      {
        "target_name": "video",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "conditions": [
          ["OS=='win'", {
            "sources": [
              "lib/src/win32/video.cpp"
            ],
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
             }
          }],
        ],
        "include_dirs": [
            "<!(node -p \"require('node-addon-api').include_dir\")"
        ],
        "dependencies": [
            "<!(node -p \"require('node-addon-api').targets\"):node_addon_api_maybe"
        ],
        "defines": [ "NODE_ADDON_API_DISABLE_DEPRECATED" ]
      }
  ]
}