#!/bin/bash

set -e

BUILD_TYPE=${BUILD_TYPE:-Debug}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/../bin
cd $DIR/../bin

if [ -z "$2" ]
  then
    cmake . -DCMAKE_BUILD_TYPE=${BUILD_TYPE}  ../
else
    echo ">> I'm here..."
    cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_CXX_COMPILER=$2 . ../
fi

make --no-print-directory
make $*
