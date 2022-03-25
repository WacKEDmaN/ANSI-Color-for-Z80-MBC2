
install cpcfont.fon into windows

load TERATERM.INI into teraterm to setup size and colors

upload the .BAS file via xmodem: 
```
xmodem cpc.bas /r 
xmodem Z80MBC2.BAS /r
```

upload profile.sub viz xmodem then copy over original: 
```
xmodem profile.su /r
pip profile.sub=profile.su
erase profile.su
```


