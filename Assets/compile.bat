@echo off
setlocal enabledelayedexpansion

echo Compiling Shaders

for /r %%f in (*.vert) do (
    set "folder=%%~dpf"
    if "!folder:~-1!"=="\" set "folder=!folder:~0,-1!"

    if not exist "!folder!\Bin" (
        mkdir "!folder!\Bin"
    )

    C:/VulkanSDK/1.4.313.2/Bin/glslc.exe "%%f" -o "!folder!\Bin\%%~nf-vert.spv"
)

for /r %%f in (*.frag) do (
    set "folder=%%~dpf"
    if "!folder:~-1!"=="\" set "folder=!folder:~0,-1!"

    if not exist "!folder!\Bin" (
        mkdir "!folder!\Bin"
    )

    C:/VulkanSDK/1.4.313.2/Bin/glslc.exe "%%f" -o "!folder!\Bin\%%~nf-frag.spv"
)

for /r %%f in (*.comp) do (
    set "folder=%%~dpf"
    if "!folder:~-1!"=="\" set "folder=!folder:~0,-1!"

    if not exist "!folder!\Bin" (
        mkdir "!folder!\Bin"
    )

    C:/VulkanSDK/1.4.313.2/Bin/glslc.exe "%%f" -o "!folder!\Bin\%%~nf-comp.spv"
)