{
    "targets": [{
        "target_name": "resolution",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "src/resolution.cpp",
            "src/Videomod.cpp"
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