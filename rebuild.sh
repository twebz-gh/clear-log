#!/bin/bash

set -e

#cgroup_line="$(cat /proc/1/cgroup | tail -n 1)"
#if [[ "$cgroup_line" == "/init.scope" ]]; then
#    echo "Run in a container that has the dependencies installed.  quitting."
#    exit 1
#fi

print_help() {
    cat <<EOM

Delete the build dir and rebuild.
Incremental builds can be done by running \`make\` in the build dir.

Options
-c     use clang instead of gcc
-h     print this help and exit
-d     set build type to debug (default release)

EOM
}

build_type=Debug  #build_type=Release
use_clang=
while getopts cdh option ; do
    case $option in
        "c")
            use_clang=yes
            ;;
        "h")
            print_help
            exit 1
            ;;
        "d")
            build_type=Debug
            ;;
        *)
            echo "Unrecognized command line arg"
            print_help
            exit 1
            ;;
    esac
done

this_files_path=$(realpath ${BASH_SOURCE[0]})
this_files_dir=$(dirname ${this_files_path})

pushd $this_files_dir
    rm -rf build
    mkdir build
    pushd build
        if [[ -n $use_clang ]]; then
            echo "export CC=/bin/clang"
            export CC=/bin/clang
        fi
        cmake -DCMAKE_BUILD_TYPE=${build_type} -S ../src -B .
        #cmake -G "Ninja Multi-Config" ..
        #ninja -f build-Release.ninja
        if [[ -n $use_clang ]]; then
            echo "run scan-build...l"
            scan-build \
            -enable-checker nullability.NullableDereferenced \
            -enable-checker nullability.NullablePassedToNonnull \
            -enable-checker nullability.NullableReturnedFromNonnull \
            -enable-checker nullability.optin.performance.Padding \
            -enable-checker nullability.optin.portability.UnixAPI \
            -enable-checker nullability.security.FloatLoopCounter \
            -enable-checker nullability.security.insecureAPI.DeprecatedOrUnsafeBufferHandling \
            -enable-checker nullability.security.insecureAPI.bcmp \
            -enable-checker nullability.security.insecureAPI.bcopy \
            -enable-checker nullability.security.insecureAPI.bzero \
            -enable-checker nullability.security.insecureAPI.rand \
            -enable-checker nullability.security.insecureAPI.strcpy \
            -enable-checker nullability.valist.CopyToSelf \
            -enable-checker nullability.valist.Uninitialized \
            -enable-checker nullability.valist.Unterminated \
            make -j4
        else
            make -j4
        fi
        # choose one of the next two:
        #cpack  # if making rpm
        make install  # if not making rpm
    popd
popd
