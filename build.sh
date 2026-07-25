#!/bin/sh

EXAMPLE_ARG=""

while [ "$#" -gt 0 ]; do
    case "$1" in
        --example)
            if [ -n "$2" ] && [ "${2#"-"}" = "$2" ]; then
                EXAMPLE_ARG="-DBUILD_EXAMPLE=$2"
                shift 2
            else
                echo "error: --example requries an example folder name"
                exit 1
            fi
            ;;
        *)
            echo "unknown parameter: $1"
            exit 1
            ;;
    esac
done

cmake -B build -S . $EXAMPLE_ARG && cmake --build build
