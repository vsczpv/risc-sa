project(
    'risc-sa',
    'cpp',
    version : '1.0.0',
    default_options : [
        'buildtype=debug',
        'optimization=0',
        'cpp_std=c++20'
    ],
    meson_version: '>= 0.60.0',
)


executable('risc-sa',
           'main.cpp',
           'filemgt/bitsfile.cpp',
           'rv/instruction.cpp',
           'rv/program.cpp',
           'rv/benchdata.cpp',
           'rv/opcode.cpp',
           'app.cpp'
)

