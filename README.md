# Station Game thingy

Station Game Thingy is a space-station management game. It was inspired by
- Dwarf Fortress
- Alien[s,2,isolation]
- Cataclysm: DDA

## Development Decisions
Station Game Thingy is heavily inspired by the whole 1970s themes of green cursors, 
malevolent clicking, and ~~shi~~ bad programming.

That being said, I would like to develop this game *almost* completely from scratch.
Here is what I will __not__ be developing:
- Graphics API - I will be using SDL
- My own language - C++20 and possibly Lua instead

Here is what I *will* be developing:
- Template Library
- Sound API (prob. WASAPI/ALSA)
- Network Code if I add multiplayer
- Renderer - SDL is the backend


Q: Why C++? Why not use C99 or even ADA or FORTRAN? 

A: I am not *that* much of a masochist. C++ is a good language choice. It provides a nice way to create
<u>clean</u> abstractions. 

