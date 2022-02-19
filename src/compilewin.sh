x86_64-w64-mingw32-gcc -c xac_win.c -o xac_win.o
x86_64-w64-mingw32-gcc -c xac_common.c -o xac_common.o 
x86_64-w64-mingw32-gcc xac.c xac_win.o xac_common.o -o xacw
