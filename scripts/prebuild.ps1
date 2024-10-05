param([bool]$clean=$false) 
Import-Module $PSScriptRoot/buildutils.psm1 -DisableNameChecking

$curdir = Get-Location
$buildloc = "$curdir/build"
mkdir -Force "$buildloc/" | out-null
Log-Info "Copying Files..."

$sdl_lib_locs = @('SDL2', 'SDL2_ttf', 'SDL2_image')

foreach($lib in $sdl_lib_locs)
{
    Log-Info "Copying $lib binaries..."
    cp thirdparty/$lib/lib/x64/*.lib $buildloc
    cp thirdparty/$lib/lib/x64/*.dll $buildloc
}