@echo off

REM Remove all build artifacts
rmdir /S /Q ".\bin"
rmdir /S /Q ".\obj"

REM Remove all platform specific configuration files
del Makefile
del *.make
del /S /Q *.xcodeproj
del /S /Q *.xcworkspace
del *.vcxproj.user
del *.vcxproj
del *.sln
del *.vcxproj.filters