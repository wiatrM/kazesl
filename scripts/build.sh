#!/bin/bash

err()
{
  echo -e "error: $1"
  exit 1
}
msg()
{
    echo "$1"
}
msg_line()
{
    echo -n "$1..."
}
msg_done()
{
    if [[ -n "$1" ]]; then
        echo "$1"
    else
        echo "done"
    fi
}

# Check source directory
is_src_dir()
{
    [[ -f "$1/CMakeLists.txt" ]]
}

SRC_DIR="$PWD"
BUILD_DIR="$PWD/build"
fdebug=yes
fUT=no

for option
do
    case $option in

    -debug | --debug | -d)
      fdebug=yes
      ;;
    -release | --release | -r)
      fdebug=no
      ;;
    -ut | --unittest | --ut)
      fUT=yes
      ;;
    -*)
      err "unrecognized option: $option"
      ;;
    esac
done
msg_line "Building kaze-sl project..."

pushd /app/

if [ "x$fdebug" = "xyes" ]; then
    cmake -Bbuild -H. -DCMAKE_BUILD_TYPE=Debug
else
    cmake -Bbuild -H. -DCMAKE_BUILD_TYPE=Release
fi
msg_line "Cmake generated building files"

pushd build

cmake --build .
msg_done "kaze-sl builded."

if [ "x$fUT" = "xyes" ]; then
    cd /app/build/bin/
    ls
    ./runUT
    ./kazesl-lib-Common-ut
fi

popd
popd
