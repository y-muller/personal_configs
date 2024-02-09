# XKB user configuration

#### Alternate symbols layout

![altgr](../.img/layout_alice69_altgr.png)

#### Installation

Copy the xkb directory to `.config`.

Set the modified keyboard option:
```
dconf write /org/gnome/desktop/input-sources/xkb-options "['lv3:ralt_switch', 'compose:rwin', 'yann_custom:intl']"
```

Get the current value:
```
dconf read /org/gnome/desktop/input-sources/xkb-options
```

