$curdir = Get-Location
$buildloc = "$curdir/build"
mkdir -Force "$buildloc/"
cd thirdparty/PDCurses
cmake .
cmake --build .
cp Debug/* $buildloc
cd $curdir