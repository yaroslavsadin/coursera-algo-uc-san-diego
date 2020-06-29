#!/bin/sh

pushd $1
g++ -std=c++17 -I$WORKSPACE_ROOT $WORKSPACE_ROOT/profile_advanced.cpp -DDEBUG -O0 -g *.cpp
for test in $(find ./tests \( ! -iname '*.a' -a ! -iname 'tests' \))
do
    result=$(./a.exe < $test)
    if [ "$result" != $(cat "${test}.a") ]; then
        echo "${test} FAIL: $result"
        exit 1
    else
        echo "${test} OK: $result"
    fi
done
popd