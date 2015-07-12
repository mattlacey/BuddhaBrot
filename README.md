# BuddhaBrot
A BuddhaBrot Engine. Hacky as all hell.

Right now this is just the core source files and they need to be linked against SDL2 for building.

It's got the world's hackiest threading job added (literally crammed it in just to get quick performance boost) and simply dumps a raw image data file in RGB888, this can easily be opened in something like GIMP.

The images with the current settings don't come close to using the full 8 bit range of each channel, so typically you have to modify the levels (again, GIMP Is handy here) after the fact.
