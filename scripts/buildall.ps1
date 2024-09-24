Import-Module $PSScriptRoot/buildutils.psm1 -DisableNameChecking


$game_name = "Station Game"
Log-Info "Building $game_name...."
Log-Info "Running prebuild script...."
& 'scripts/prebuild.ps1'
