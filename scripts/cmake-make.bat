@echo OFF
echo.

if not exist mkdir "bin"
cd "bin"

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

echo "Bulding stars now..."
timeout 5

:: cmake --help for diff. versions of VS or platform
cmake -G "Visual Studio 14 2015 Win64" "../"

:: Add to the path
:: set PATH=%PATH%;C:\some\path