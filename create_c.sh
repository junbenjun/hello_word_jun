#! /bin/bash
echo 'making c project files ...'
echo 'modify from win10'
project=default
if [ ! $1 ]; then
    echo '============input a project name first !!!!!=============='
    exit
else
    echo '============inpputed project is:' $1 '==================='
    project=$1
fi
rm -rf ./$project

mkdir ./$project
mkdir ./$project/src
mkdir ./$project/src/include
mkdir ./$project/build

echo 'making CMakeLists.txt'
echo 'set(PROJECT CProject_main)' >> ./$project/CMakeLists.txt
echo 'message("Making ${PROJECT} ...")' >> ./$project/CMakeLists.txt
echo 'cmake_minimum_required(VERSION 3.16)' >> ./$project/CMakeLists.txt
echo 'project(${PROJECT})' >> ./$project/CMakeLists.txt
echo 'aux_source_directory(./src SRC_FILE)' >> ./$project/CMakeLists.txt
echo 'add_executable(run ${SRC_FILE})' >> ./$project/CMakeLists.txt
echo 'message("Make ${PROJECT} ok, please execute run")' >> ./$project/CMakeLists.txt

echo 'making main.c'
echo '#include <stdio.h>' >> ./$project/src/main.c
echo '#include <stdlib.h>' >> ./$project/src/main.c
echo '' >> ./$project/src/main.c
echo 'int main()' >> ./$project/src/main.c
echo '{' >> ./$project/src/main.c
echo '    printf("Hello world\\n");' >> ./$project/src/main.c
echo '    return 0;' >> ./$project/src/main.c
echo '}' >> ./$project/src/main.c

echo 'making rebuild_run.sh'
echo 'rm -rf ./build/*' >> ./$project/rebuild_run.sh
echo 'cd ./build' >> ./$project/rebuild_run.sh
echo 'cmake ../' >> ./$project/rebuild_run.sh
echo 'make' >> ./$project/rebuild_run.sh
echo './run' >> ./$project/rebuild_run.sh

echo 'making buildrun.sh'
echo 'cd ./build' >> ./$project/buildrun.sh
echo 'make' >> ./$project/buildrun.sh
echo './run' >> ./$project/buildrun.sh
