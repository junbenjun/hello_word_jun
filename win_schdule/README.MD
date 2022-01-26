#################################
- 本程序编译环境是win10+mingw+cmake
- 各个文件作用：
  - bat_buildrun.bat windows cmd下的编译脚本，每次执行会删除build目录下的所有文件，重新生成cmake文件和编译链接
  - bat_makerun.bat windows cmd下的编译运行脚本，每次执行不会删除build目录的cmake文件，只会重新编译和链接，并执行可执行程序
  - CMakeLists.txt cmake文件
  - sch.txt 定义计划和计划执行程序的配置文件
  - src/main.c 程序源文件
  - src/schdule.c 程序源文件
  - build/run.exe 程序可执行文件