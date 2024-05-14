# Config files

## QMK keyboards
- Keychron V8
- Keychron K11 Pro (bluetooth)
- KPrepublic CSTC40
- ~~Keychron V3~~
- ~~Keychron K1 Pro  (bluetooth)~~

for Bluetooth keyboards use Keychron's fork of QMK and the `wireless_playground` branch.

My layouts are described in the QMK section, for [Alice 69 keys](qmk_keyboards/README.md) layouts and [Ortholinear 47 keys](qmk_keyboards/ORTHO47.md).

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

