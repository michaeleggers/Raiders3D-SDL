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
* The update functions get called with a delta time, that is the time being past since the last render. One could also limit the framerate  so the CPU and GPU don't go crazy. Do it if you feel more comfortable that way.

## How to build and run
Go into repo's root dir and do:
```bash
mkdir build && cd build
cmake -DSDL2IMAGE_INSTALL=OFF -DSDL2_DISABLE_INSTALL=OFF ..
cmake --build .
```
On Windows, double-click the build EXE.
On MacOS/Linux start the game by typing:
```bash
./Raiders3D
```
## TODOs
* Add sound (maybe via SDL_mixer)

## Questions / Criticism / Thoughts
Please feel free to contact me if you have questions about the code or how to build it. Also, if you have any suggestions on how to improve the SDL part I coded, just tell me or contribute. The SDL "backend" was written some time ago and I thought it was cool to have virtual functions... just because I can. However, the code is functional and the purpose was to get it running on newer platforms.

