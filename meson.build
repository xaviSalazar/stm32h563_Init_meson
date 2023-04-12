### PROJECT DECLARATION ###
###

project(
  'stm32-app',
  'c',
  default_options : ['warning_level=3'],
 )
 
 ## module imports 
 fs = import('fs')
 
### EDIT THESE PARAMETERS FOR YOUR BOARD.
#=============================================
# Include the required modules to compile the projects!!!
stm32_hal_components = ['cortex','usb', 'adc', 'dma', 'eth', 'exti', 'flash', 'gpio',
	 'icache', 'pcd', 'pwr', 'rcc', 'uart', 'upcd']
	 
stm32_chip_family = 'STM32H5'
stm32_chip_series = 'STM32H563'
stm32_chip_type = 'xx'
stm32_cube_dir = 'STM32CubeH5'
#===============================================
### end of editable parameters
 
 ## STM32 LINKER FILE
 #
 stm32_linker_script = join_paths(meson.current_source_dir(),
 				  'STM32H563ZITX_FLASH.ld')
 
 # Add linker script to all executable linking 
 stm32_link_args = [ '-T', stm32_linker_script]
 
 add_project_link_arguments(stm32_link_args, language : ['c', 'cpp'] )
 
 
 # Create list of include directories required for 
stm32_cube_inc = include_directories(
  [
    stm32_cube_dir + '/Drivers/CMSIS/Include',
    stm32_cube_dir + '/Drivers/' + stm32_chip_family + 'xx_HAL_Driver/Inc/',
    stm32_cube_dir + '/Drivers/CMSIS/Device/ST/' + stm32_chip_family + 'xx/Include/',
  ])
  
 
 # Store a list of all the board src files.
stm32_cube_src = []
stm32_cmsis_src = []

  # Create prefix for all the Driver source files.
stm32_driver_src_prefix = stm32_cube_dir + '/Drivers/' + stm32_chip_family + 'xx_HAL_Driver/Src/' + stm32_chip_family.to_lower() + 'xx_hal'
  
 stm32_driver_src_ll_prefix = stm32_cube_dir + '/Drivers/' + stm32_chip_family + 'xx_HAL_Driver/Src/' + stm32_chip_family.to_lower() + 'xx_ll'
                               
# Add the HAL component
stm32_cube_src += stm32_driver_src_prefix + '.c'


# Add all the requested components.
foreach component : stm32_hal_components
    if fs.exists(stm32_driver_src_prefix + '_' + component + '.c')
      stm32_cube_src += stm32_driver_src_prefix + '_' + component + '.c'
    endif
    if fs.exists(stm32_driver_src_prefix + '_' + component + '_ex.c') 
      stm32_cube_src += stm32_driver_src_prefix + '_' + component + '_ex.c'
    endif
    if fs.exists(stm32_driver_src_ll_prefix + '_' + component + '.c')
      stm32_cube_src += stm32_driver_src_ll_prefix + '_' + component + '.c'
    endif   
endforeach

# template directory
stm32_template_dir = stm32_cube_dir + '/Drivers/CMSIS/Device/ST/' + stm32_chip_family + 'xx/Source/Templates'
# CMSIS directory
stm32_cmsis_system = stm32_template_dir + '/system_' + stm32_chip_family.to_lower() + 'xx.c'
# CMSIS startup
stm32_cmsis_startup = stm32_template_dir + '/gcc/startup_' + stm32_chip_series.to_lower() + stm32_chip_type.to_lower() + '.s'

stm32_cmsis_src += stm32_cmsis_system
stm32_cmsis_src += stm32_cmsis_startup

# cube args
stm32_cube_args = ['-D' + stm32_chip_family, '-D' + stm32_chip_series + stm32_chip_type, '-DUSE_FULL_LL_DRIVER']

stm32_cube_dep = declare_dependency(
  sources : [stm32_cube_src],
  compile_args : stm32_cube_args,
  include_directories : [stm32_cube_inc],
  )

stm32_cmsis_dep = declare_dependency(
  sources : [stm32_cmsis_src],
  compile_args : stm32_cube_args,
  include_directories : [stm32_cube_inc],
  )
 
 #========================================================================
 #========================================================================
 #### SOURCE FILES TO COMPILE #####
 
headers_inc = include_directories( 'Core/Inc' )

stm32_app = executable('stm32_app.elf',
  'Core/Src/main.c',
  'Core/Src/stm32h5xx_hal_msp.c',
  'Core/Src/stm32h5xx_it.c',
  'Core/Src/syscalls.c',
  'Core/Src/sysmem.c',
  
  include_directories : [
    headers_inc,
  ],
  
  dependencies : [
  	stm32_cube_dep, 
  	stm32_cmsis_dep
  ]
 ) # end executable
 
 
objcopy = find_program('arm-none-eabi-objcopy')
 
custom_target(
    'stm32_app.bin',
    input	     : [stm32_app],
    output           : ['stm32_app.bin'],
    build_by_default : true,
    command          : [objcopy, '-O', 'binary', '@INPUT@', '@OUTPUT@'],
    depends          : [stm32_app]
)
 

	
