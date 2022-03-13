$ErrorActionPreference = "Stop"

If (-NOT ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator))
{
  # Relaunch as an elevated process:
  Start-Process powershell.exe "-File",('"{0}"' -f $MyInvocation.MyCommand.Path) -Verb RunAs
  exit
}

Write-Host "Installing BCC102 in C:\"
Write-Host "Please wait..."
$TmpFile = Join-Path -Path $Env:Temp -ChildPath BCC102.zip

# From https://www.embarcadero.com/es/free-tools/ccompiler
Invoke-WebRequest https://altd.embarcadero.com/download/bcppbuilder/BCC102.zip -OutFile $TmpFile
Expand-Archive $TmpFile -DestinationPath C:\
Remove-Item $TmpFile

[System.Environment]::SetEnvironmentVariable("PATH", $Env:Path + ";C:\BCC102\bin", "Machine")

Read-Host -Prompt "Done. Press Enter to exit"