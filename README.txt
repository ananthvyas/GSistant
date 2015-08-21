README for the GSistant project.

To compile the project, use this command :

g++ -std=c++11 GSistant.cpp -o GSistant `pkg-config --cflags --libs gtk+-3.0`
GTK+ is installed by default in GNOME systems.
Basic information about the GTK+ library can be seen here :
https://developer.gnome.org/gtk3/stable/gtk-getting-started.html

This should be enough to get you started.
Although GTK+ is supported in Windows, it'll be good to code this in a linux environment to maintain consistency.

Currently supports :

search <phrase>
open <url/path>
