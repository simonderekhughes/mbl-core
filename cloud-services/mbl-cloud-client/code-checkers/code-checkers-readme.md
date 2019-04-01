# Tools used
## clang-tidy
clang-tidy is a clang-based C/C++ static analysis tool. Its purpose is to provide an extensible framework for diagnosing and fixing typical programming errors, like style violations, interface misuse, or bugs that can be deduced via static analysis. This tool does not enforce C/C++ style. Read more about the [clang-tidy tool][clang-tidy]. 
## clang-format
clang-format enforces a set of rools on the C/C++ code style. It can help in finding and fixing of code style compliance failures. Read more about the [clang-format tool][clang-format].
- By default, we use clang-format in a code formatter mode, not as only a checker. The tool will change the files according to the provided configuration file(.clang-dormat). The proposed change is always correct.
### clang-format configuration file
- We use clang-format with a configuration file that defines our C/C++ style. See the file `mbl-core/cloud-services/mbl-cloud-client/.clang-format`. We can change the clang-format configuration file in order to support additional style rules. A comprehensive explanation about clang-format style configuration file read here https://www.clangformat.com/ and https://clang.llvm.org/docs/ClangFormatStyleOptions.html.


# Prerequisites
## Toolchains installations
`sudo apt-get install -y clang clang-tidy clang-format`

## Libraries for mbl-cloud-client on PC compilation installations
Install all required libraries in order to compile mbl-cloud-client code (among which systemd development library).

`sudo apt-get install -y libsystemd-dev libjsoncpp-dev`

libjsoncpp-dev installs the header to /usr/include/jsoncpp/json/ while bitbake expects it to be under /usr/include/json directory. In order to enable both - make a soft link:
`sudo ln -s /usr/include/jsoncpp/json/ /usr/include/json`

Install all required libraries. 


# Build
## Aggregate mbl-cloud-client code on your PC
- Download mbl-core repository to the folder `mbl-core` on your PC. 
- Download mbed-cloud-client repository to the `mbl-core/cloud-services/mbl-cloud-client/`. Pay attention, `mbed-cloud-client` release version should be the same as specified in this [README.md][mbl-cloud-client-README.md].
- Copy `mbed_cloud_dev_credentials.c` and `update_default_resources.c` into the `mbl-core/cloud-services/mbl-cloud-client/` folder.

## Configure PAL
- `cd cloud-services/mbl-cloud-client/`
- `python pal-platform/pal-platform.py deploy --target=x86_x64_NativeLinux_mbedtls generate`

##  Generate makefiles
- `cd __x86_x64_NativeLinux_mbedtls`
- `cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=./../pal-platform/Toolchain/GCC/GCC.cmake -DEXTARNAL_DEFINE_FILE=./../define.txt -DCODE_CHECK_MODE=ON`

The following command generates makefiles with the corresponding rules for clang-tidy and clang-format running.


# Run
Run the following commands from the `__x86_x64_NativeLinux_mbedtls` folder.

## Running tools on mbl-cloud-client
### Run clang-format in a code formatter mode
`make clang-format`
- The tool will change the content of the files. Changes can be reviewed by running `git diff`.
### Run clang-tidy
`make clang-tidy`
- The tool will print warnings and recomendations on the code quality to the stdout. Suggested changes can be viewed in `mbl-core/cloud-services/mbl-cloud-client/code-checkers/clang-tidy-suggested-fixes.txt` file.

## Running tools on the specific source file(s)
### Run clang-format in a code checker mode
`clang-format -style=file /absolute_or_relative/path/to/sigle_c_cpp_file_or_file_list`
- The tool will print file(s) content after the suggested changes being applied to the stdout.
### Run clang-format in a code formatter mode
`clang-format -i -style=file /absolute_or_relative/path/to/sigle_c_cpp_file_or_file_list`
- The tool will change the content of the file(s). Changes can be reviewed by running `git diff`.
### Run clang-tidy
`clang-tidy -p=. -export-fixes=./clang-tidy-suggested-fixes.txt -checks=-*,bugprone-*,cert-*,cppcoreguidelines-*,clang-analyzer-*,modernize-*,performance-*,readability-*,-cppcoreguidelines-pro-type-vararg,-cppcoreguidelines-pro-bounds-array-to-pointer-decay /absolute_or_relative/path/to/sigle_c_cpp_file_or_file_list`
- The tool will print warnings and recomendations on the code quality to the stdout. Suggested changes can be viewed in `mbl-core/cloud-services/mbl-cloud-client/code-checkers/clang-tidy-suggested-fixes.txt` file.


[mbl-cloud-client-README.md]: https://github.com/ARMmbed/mbl-core/blob/mbl-core-preq331/cloud-services/mbl-cloud-client/README.md
[clang-tidy]: http://releases.llvm.org/7.0.0/tools/clang/tools/extra/docs/clang-tidy/index.html
[clang-format]: https://clang.llvm.org/docs/ClangFormat.html
