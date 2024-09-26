Import-Module $PSScriptRoot/buildutils.psm1 -DisableNameChecking

$curdir = Get-Location
$buildloc = "$curdir/build"
mkdir -Force "$buildloc/" | out-null
cd thirdparty/PDCurses
Log-Info "Configuring PDCurses..."
cmake .
Log-Info "Building PDCurses..."
cmake --build .
Log-Info "Done. Copying Files"
cp Debug/pdcurses.* $buildloc
cd $curdir