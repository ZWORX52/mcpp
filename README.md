# mcpp
minecraft.cpp, server for now

## usage
pretty simple! just make sure you clone with --recurse-submodules and you'll be set; just run `make` and then you have the executable (`./mc`)

currently I only have the server implemented; naturally a client may be coming in the future.

the {fmt} requirement will be dropped when gcc 13 is released, as std::format will become available. around that time I might just drop tomlplusplus so I can be requirement-free.

a decently recent version of gcc is required as I use some most-likely-recent features of c++ (at least c++11 I think, but when gcc 13 is released, then c++23)

requirements: [{fmt}](https://fmt.dev) [tomlplusplus](https://github.com/marzer/tomlplusplus) (packed through submodules)
