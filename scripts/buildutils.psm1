function Log-Info {
    param (
        [string] $str
    )

    Write-Host -ForegroundColor "Green" $str
}

Export-ModuleMember -Function Log-Info