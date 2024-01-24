# Config files

## QMK keyboards
- Keychron V3
- Keychron V8
- Keychron K1 Pro  (bluetooth)
- Keychron K11 Pro (bluetooth)

for Bluetooth keyboards use Keychron's fork of QMK


#### How to use
Create a new keymap with `qmk new-keymap`, move the new directory to this repo and create a link.

For shared files across keyboards, create a link in `users` with the github user name to the `userspace` directory of this repo.

## XKB user extensions
Copy the `xkb` directory to `.config`.

Set the modified keyboard option;
dconf write /org/gnome/desktop/input-sources/xkb-options "['lv3:ralt_switch', 'compose:rwin', 'yann_custom:intl']"

Get the current value:
dconf read /org/gnome/desktop/input-sources/xkb-options

