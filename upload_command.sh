# Write binary to stm32 target
STM32_Programmer_CLI -c port=SWD freq=8000 ap=1 -w ./build/Core/stm32_cross.bin 0x08000000 -v
