param([bool]$clean=$false) 
Import-Module $PSScriptRoot/buildutils.psm1 -DisableNameChecking

$curdir = Get-Location
$buildloc = "$curdir/build"
mkdir -Force "$buildloc/" | out-null
cd thirdparty/PDCurses

if($clean -eq $true) {
    Log-Info "Cleaning..."
    rm -Force pdcurses.dir,x64,Debug,CMakeFiles
}

Log-Info "Configuring PDCurses..."
cmake .
Log-Info "Building PDCurses..."
cmake --build .
Log-Info "Done. Copying Files"
cp Debug/pdcurses.* $buildloc
cd $curdir
cp thirdparty/SDL2/lib/x64/*.lib $buildloc
cp thirdparty/SDL2/lib/x64/*.dll $buildloc
cp thirdparty/SDL2_ttf/lib/x64/*.lib $buildloc
cp thirdparty/SDL2_ttf/lib/x64/*.dll $buildloc