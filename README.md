# Shadow Caster
Shadwo Caster is a project created for Objective Programming curse.
The main idea is to cast shadowd on area, that is out of player's vision.

## instalation
use vcpkg to download SFML x64 in latest version

`vcpkg install sfml:x64-windows`

download SFML x64 in latest version from official website

`https://www.sfml-dev.org/download/sfml/2.5.1/`

Then change <sfml path> in makefile to path of your sfml files (f.e C:/libs/SFML-2.5.1 )

To compile project you need to install an g++ compiler ( MinGW-W64 7.3.0 )
that you can download from `https://bit.ly/3ni0ZeB`

Remember to add nesessery paths to windows path section.

If you set up everything correctly, compile project typing "make" in commandline while you are in project's folder

File ShadowCaster.exe should be created in bin folder.
