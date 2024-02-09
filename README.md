# Config files

## QMK keyboards
- Keychron V3
- Keychron V8
- Keychron K1 Pro  (bluetooth)
- Keychron K11 Pro (bluetooth)

for Bluetooth keyboards use Keychron's fork of QMK

My layouts are described on the [QMK page](qmk_keyboards/README.md).

#### How to use
Create a new keymap with `qmk new-keymap`, move the new directory to this repo and create a link.

For shared files across keyboards, create a link in `users` with the github user name to the `userspace` directory of this repo.

## XKB user extensions

XKB layouts can be modified by user configuration without modifying system files. See the [XKB page](xkb/README.md).

## Compose
https://help.ubuntu.com/community/GtkComposeTable

`.XCompose` for custom compose sequences.

## run-or-raise Gnome extension

Used to launch applications, display the keyboard layout help...

