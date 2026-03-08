# XKB user configuration

This user-space XKB configuration defines a layout with 8 levels. The base levels are
unchanged from the default US layout. The other levels are entirely custom.

#### Alternate symbols layout

![altgr](../img/layout_corne42_altgr.png)

The AltGr symbols (levels 3 and 4), in black in the diagram above, are mostly accented
characters for French and Spanish. The French accented vowels are grouped around their
primary characters. The Spanish ones are added where space was available. The layout is
designed to make sense on a Colemak DH keyboard. When using QWERTY, the groups are broken up.

The levels 5 and 6, in red in the diagram, are extra characters and a few common emojis.
The Level 5 key is set to `Right Control`.

The levels 7 and 8 are for Greek characters. These levels are accessed by pressing both the 
keys for Level 3 and Level 5.

#### Installation

### Wayland & Gnome

Copy the xkb directory to `.config`.

Set the modified keyboard option:
```
dconf write /org/gnome/desktop/input-sources/xkb-options "['lv3:ralt_switch', 'lv5:rctrl', 'compose:rwin', 'yann_custom:colemak']"
```

To reload after a change:
```
dconf write /org/gnome/desktop/input-sources/xkb-options "['lv3:ralt_switch', 'compose:rwin']" && dconf write /org/gnome/desktop/input-sources/xkb-options "['lv3:ralt_switch', 'lv5:rctrl', 'compose:rwin', 'yann_custom:colemak']"
```

Get the current value:
```
dconf read /org/gnome/desktop/input-sources/xkb-options
```

Use `/usr/share/X11/xkb/symbols/us` as a source for the key names.
`/usr/include/X11/keysymdef.h` for the full list.

### X11

I have found the user config to not work very well with X11!

Edit the system file directly: `/usr/share/X11/xkb/symbols/us`.

