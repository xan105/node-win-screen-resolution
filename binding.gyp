{
    "targets": [
    {
        "target_name": "resolution",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "lib/src/resolution.cpp",
            "lib/src/Videomod.cpp",
            "lib/src/DpiAwareness.cpp"
        ],
        "msvs_settings": {
          "VCCLCompilerTool": {
             "ExceptionHandling": 1,
             "AdditionalOptions": []
          }
         },
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    },
    {
        "target_name": "resolution_legacy_dpi",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "lib/src/resolution.cpp",
            "lib/src/Videomod.cpp",
            "lib/src/legacy/DpiAwareness.cpp"
        ],
        "msvs_settings": {
          "VCCLCompilerTool": {
             "ExceptionHandling": 1,
             "AdditionalOptions": []
          }
         },
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}