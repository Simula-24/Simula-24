param([bool]$clean=$false) 
Import-Module $PSScriptRoot/buildutils.psm1 -DisableNameChecking

$curdir = Get-Location
$buildloc = "$curdir/build"
mkdir -Force "$buildloc/" | out-null
Log-Info "Copying Files..."
cp thirdparty/SDL2/lib/x64/*.lib $buildloc
cp thirdparty/SDL2/lib/x64/*.dll $buildloc
cp thirdparty/SDL2_ttf/lib/x64/*.lib $buildloc
cp thirdparty/SDL2_ttf/lib/x64/*.dll $buildloc

cp thirdparty/SDL2_image/lib/x64/*.lib $buildloc
cp thirdparty/SDL2_image/lib/x64/*.dll $buildloc