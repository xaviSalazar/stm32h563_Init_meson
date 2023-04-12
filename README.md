# Compile stm32 source files with MESON BUILD 

### Project inspired from @jhamberg repository name: stm32-meson

1. I modified certain lines to accept new features libraries that 
   are generated from CubeIDE. (ext and ll located in drivers).

2. Meson is a requirement to compile this example project.

3. Also you need to download the firmware header and source files
   for the board in this case STM32H563ZI.

```
meson build --cross-file stm32-meson/stm32h5.build -Dstm32_chip=STM32H563ZI -Dstm32_cube_dir=$HOME/STM32CubeH5-main
```

then go to build/

```
ninja
```
