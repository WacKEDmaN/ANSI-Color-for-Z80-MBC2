
install cpcfont.fon into windows

load TERATERM.INI into teraterm to setup size and colors

upload the .BAS files via xmodem: 
```
xmodem cpc.bas /r 
xmodem Z80MBC2.BAS /r
```

upload profile.sub via xmodem then copy over original: 
```
xmodem profile.su /r
pip profile.sub=profile.su
erase profile.su
```

matrix1.c Sarah Libman's matrix code with some mods for larger terminal (80x43), using all lines, and clear screen when USER button is pressed, also uses extended font (chr$ 33 to 255)

compiles with z88dk (on PC)
```
zcc +cpm -v -o matrix1.com matrix1.c
```
![Matrix](https://github.com/WacKEDmaN/ANSI-Color-for-Z80-MBC2/blob/main/extras/matrix.png "matrix")

