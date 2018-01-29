# Raiders3D SDL2 port
This code is a port of the Raiders3D example from the book [Tricks of the 3D Game Programming Gurus](https://www.amazon.com/Tricks-Programming-Gurus-Advanced-Graphics-Rasterization/dp/0672318350/ref=cm_cr_arp_d_product_top?ie=UTF8) by [Andre LaMothe](https://en.wikipedia.org/wiki/Andr%C3%A9_LaMothe).

The main purpose, still, is to show some basic 3D to 2D screen projection, so the project is kept simple. You can, without
looking at the SDL-code read the chapter from the book and follow along the code. The logical steps are the same.

SDL2 is used for Keyboard-Input and Graphics (rendering lines and dots). Everything else was mostly left as it appears in the book.
Font-Rendering however is done with a bitmap fontsheet. Audio is not yet implemented.

The plan was to port further code-examples to newer platforms as - at least for me - it was not trivial to get the
legacy DirectX libraries to link. I just learnt about this project: https://github.com/ans-hub/game_console that ports the Wireframe Raiders3D example from the mentioned book to Linux. Maybe I'll just participate there ;-)

## A few changes to the original were made
* The lasers beams fired by the player are red instead of blue, because Rebels... you know...
* The trajectory of the pieces of a Tie fighter contain their velocity when they explode.
* The draw functions get called with a delta time, that is the time being past since the last render. One could also limit the framerate  so the CPU and GPU don't go crazy. Do it if you feel more comfortable that way.

## How to build
* CMake is used. To generate a Visual Studio Solution follow these steps:
1. via cmd go into the repo and type: `mkdir build && cd build`
2. `cmake -G "Visual Studio 15 2017 Win64" ..` (For other Visual Studio versions check the cmake documentation, please)
3. the generated solution should be in the build folder you just created.
4. Copy the DLLs from SDL_Image and SDL2 to the Release/Debug/RelWithDebInfo folders in the build folder. (They will be there after you have built the project for these target once in VS).

## TODOs
* Add cmake command so that DLLs get copied automatically
* Add sound (maybe via SDL_mixer)

## Questions / Criticism / Thoughts
Please feel free to contact me if you have questions about the code or how to build it. Also, I would like to hear from you if you hate the port. I'll try my best to improve the code. The SDL "backend" was written some time ago and I thought it was cool to have virtual functions... just because I can. However, the code is functional and the purpose was to get it running on newer platforms.

