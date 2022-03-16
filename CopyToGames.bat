@echo off

SET script_path=%~dp0
if exist %script_path%\CopyToGamesLocal.bat (
	CALL %script_path%\CopyToGamesLocal.bat %1 %2
	exit
)

if "%username%" NEQ "bo3b" exit
REM The below is Bo3b's setup, but can serve as a template for CopyToGamesLocal.bat

if %2=="amd64" GOTO Copyx64

:Copyx86
@echo on

REM xcopy /C "%1*.*" "W:\SteamLibrary\SteamApps\common\Assassin's Creed 3\"  /F /Y /S
REM xcopy /C "%1*.*" "W:\SteamLibrary\SteamApps\common\Saints Row IV\" /F /Y /S
REM xcopy /C "%1*.*" "W:\SteamLibrary\SteamApps\common\Saints Row the Third\" /F /Y /S
REM xcopy /C "%1*.*" "W:\SteamLibrary\SteamApps\common\F.E.A.R. 3\" /F /Y /S
REM xcopy /C "%1*.*" "W:\SteamLibrary\SteamApps\common\DefenseGrid2\" /F /Y /S
xcopy /C "%1*.*" "W:\SteamLibrary\SteamApps\common\DiRT Rally\" /F /Y /S

REM Works with hooking
xcopy /C "%1*.*" "W:\SteamLibrary\SteamApps\common\Alien Isolation\" /F /Y /S

exit


:Copyx64
@echo on
echo 
REM xcopy /C "%1*.*" "W:\Games\Far Cry 4\bin\" /F /Y /S
REM xcopy /C "%1*.*" "W:\Games\The Crew (Worldwide)\" /F /Y /S
REM xcopy /C "%1*.*" "W:\SteamLibrary\SteamApps\common\Call of Duty Ghosts\"  /F /Y /S
REM xcopy /C "%1*.*" "W:\SteamLibrary\SteamApps\common\Project CARS\" /F /Y /S
 xcopy /C "%1*.*" "W:\Games\Watch_Dogs\bin"  /F /Y /S

REM Works with hooking
REM xcopy /C "%1*.*" "G:\Games\INSIDE\" /F /Y /S
REM xcopy /C "%1*.*" "G:\Games\The Witcher 3 Wild Hunt\bin\x64\" /F /Y /S

REM xcopy /C "%1*.*" "G:\uPlay\Tom Clancy's The Division\" /F /Y /S

xcopy /C "%1*.*" "W:\SteamLibrary\SteamApps\common\HeadLander\" /F /Y /S
xcopy /C "%1*.*" "W:\SteamLibrary\SteamApps\common\NieRAutomata\" /F /Y /S
xcopy /C "%1*.*" "W:\SteamLibrary\steamapps\common\Dishonored2\" /F /Y /S
