param (
    [string]$sourceFolder
)

# Check source folder argument
if (-Not $sourceFolder) {
    Write-Host "ERROR: Source folder argument is required." -ForegroundColor Red
    exit 1
}

# Check if the source folder exists
if (-Not (Test-Path $sourceFolder)) {
    Write-Host "ERROR: Source folder '$sourceFolder' does not exist." -ForegroundColor Red
    exit 1
}

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
$destinationFolder = Join-Path -Path $scriptDir -ChildPath "build/install"
$fileListPath = Join-Path -Path $scriptDir -ChildPath "required_libs_for_windows.txt"
$windeployqtPath = Join-Path -Path $sourceFolder -ChildPath "windeployqt.exe"

# Check if windeployqt.exe exists
if (-Not (Test-Path $windeployqtPath)) {
    Write-Host "ERROR: windeployqt.exe not found in $sourceFolder" -ForegroundColor Red
    exit 1
}

if (!(Test-Path $destinationFolder)) {
    New-Item -ItemType Directory -Force -Path $destinationFolder | Out-Null
}

$fileList = Get-Content -Path $fileListPath

foreach ($pattern in $fileList) {
    $matchedFiles = Get-ChildItem -Path $sourceFolder -Filter $pattern -File

    if ($matchedFiles.Count -eq 0) {
        Write-Warning "No match found for pattern '$pattern'"
        continue
    }

    foreach ($file in $matchedFiles) {
        $destinationFile = Join-Path -Path $destinationFolder -ChildPath $file.Name
        Copy-Item -Path $file.FullName -Destination $destinationFile -Force
    }
}

$exePath = Join-Path -Path $destinationFolder -ChildPath "XFakeContrib.exe"
& "$sourceFolder\windeployqt.exe" --no-compiler-runtime -network -concurrent $exePath

if ($LASTEXITCODE -ne 0) {
    Write-Error "Failed operation with windeployqt.exe"
    exit $LASTEXITCODE
}

Write-Host "DLL files successfully moved and application deployed."