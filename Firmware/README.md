# Project 1

Putting dev notes and things in here! This is a SCHOOL PROJECT
so not really meant to be a complete system!
For complet system (in the future) see the whole fennec modem
repo! https://github.com/Kitsune-Robotics/FENNEC-Modem


## To build on your own

You'll need the pico SDK somewhere, avail as an aur package or just via cmake init

```
mkdir build && cd build
cmake ..
make
```

Then if you have `picotool`

```
picotool load -f pico_project.uf2
```

Otherwise load the uf2 via flash mode.
