@echo OFF
echo.

if not exist bin mkdir bin
cd bin

WHERE cmake
if %ERRORLEVEL% NEQ 0 (
	echo "x - cmake wasn't found"
	echo "You have to: "
	echo "1. Google download cmake"
	echo "2. Install cmake"
	echo "3. find cmake.exe"
	echo "4. Set it to system path: _PATH_=%PATH%;C:\path\to\cmake (remove underlines)"
	exit /b %errorlevel%
) else (
	echo "v - cmake found"
)

:: Build

:: cmake --help for diff. versions of VS or platform
cmake -G "Visual Studio 14 2015 Win64" "..\"

:: Path to msbuild
echo "If you haven't yet, Add the msbuild path to _PATH_(remove underlines) environment."
reg.exe query "HKLM\SOFTWARE\Microsoft\MSBuild\ToolsVersions\4.0" /v MSBuildToolsPath

set msbuild.exe=
for /D %%D in (%SYSTEMROOT%\Microsoft.NET\Framework\v4*) do set msbuild.exe=%%D\MSBuild.exe

msbuild.exe "..\bin\ALL_BUILD.vcxproj" /t:Build

echo.
echo "If your build succeeded, binaries are in:"
echo "%cd%\bin\Debug"
echo.

:: Add to the path
:: set PATH=%PATH%;C:\some\path