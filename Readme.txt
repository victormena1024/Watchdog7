

%(AdditionalDependencies);
SDL2.lib;SDL2main.lib;SDL2_Net.lib;
Ws2_32.lib;
Spelmotorlib.lib;
SDL_draw_static.lib





A Simple C++/SDL_net Chat Server and Client Rewritten | Nov 2011 | r3dux

Instructions & Caveats:
-----------------------

The two projects in this solution will work with Visual Studio 2008 on 32-Bit Windows XP using
Visual Studio 2008. If they work on other set-ups then great, if not then sorry, but I don't have
the time to fix it for you.

I've placed SDL.dll (from SDL 1.2.14) and SDL_net.dll (from SDL_net 1.2.7) files in the Debug folder,
which is where the executables from building the project will turn up. If you want to move your exe
files elsewhere, take a copy of the two DLL files as well or it won't work.

The project will build successfully only in Debug mode (and NOT Release mode). Why? Who knows. I
avoid Windows like the plague whenever possible, and would strongly encourage you to do the same.

The project will moan if you don't explicitely avoid the msvcrt.lib library, as I've done in the
project configurations.

SDL and SDL_net are provided under the Lesser GPL, a copy of which is included in the Licenses folder.

This simple Chat Server and Client code is released under the the Creative Commons Attribution 3.0
Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/
or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.

-----------------------



LNK2019: unresolved external 
symbol _GetAdaptersInfo@8 referenced in function 
_SDLNet_GetLocalAddresses	
E:\cpp\Watchdog.2017.10.27\SocketServer-Rewritten\SDL_Net_Debug.lib(SDLnet.obj)
	SocketServer-Rewritten


