#! bin/sh

# Remove all files created by the build process.
rm -rf bin/
rm -rf obj/

# Remove all platform specific configuration files
rm Makefile
rm *.make
rm -r *.xcodeproj
rm -r *.xcworkspace
rm *.vcxproj.user
rm *.vcxproj
rm *.sln
rm *.vcxproj.filters
