# QMK config
## Corne 42 keys split keyboard

This layout is an evolution of my [ortholinear](ORTHO47.md) layout and is still a work in progress.

To get help, the combo `D` + `H` shows the layout for the current layer on screen until the key is released.
For the AltGr symbols tap the Symbols key before the help combo.

#### Main layer

![main](../img/layout_corne42_main.png)

Tap the symbols `SYMB` key once for a One-Shot of the `AltGr` symbols with a custom [XKB](../xkb/README.md) configuration.
Holding the key accesses the Symbols layer described below. The normal Linux Compose key is available on the symbols layer.

Tapping the Tmux key sends `Ctrl-A` and holding it sends `Ctrl-A` before each key press until released.

A [leader key](LeaderKey.md) sequence is started with the combo `H` + `,`.

TODO: document the other combos: save, copy, paste,...

#### Symbols layer

![nav](../img/layout_corne42_symbols.png)

A long press on `(`, `[` or `{` open and close the parenthesis or bracket and move the cursor in the middle. A long press 
on `!`, `&` or `=` outputs the symbol twice and surrounded by spaces.

#### Numbers layer

![nav](../img/layout_corne42_numpad.png)

Currently trying numpad on the left.

#### Extend layer
Accessible with the `EXT` keys. Press Layer lock key `LLOCK` to lock to this layer and again to exit it.

![extend](../img/layout_corne42_extend.png)

#### Nav layer
Accessible with the `NAV` key. 

![nav](../img/layout_corne42_nav.png)

Find next and previous work in several editors (F3 and Shift-F3). With Shift, switches to "Find in files" mode (F8 and Control-F8).   
Tab switching is with Control-Alt-PgUp/Dn and works is several editors and can be configured in gnome-terminal and others.  
The Dynamic Macro is recorded in the System layer.  

Application shortcuts work with the [run-or-raise](../run-or-raise/README.md) Gnome extension.  

#### Media and browsing layer
![media](../img/layout_corne42_media.png)
This layer is dedicated to browsing and other non-typing activities. It is accessed by holding the `ESC` key or activated by the
combo `ESC` + `Q`.

#### System layer
Accessible by activating both the `Extend` and `Symbols` layers at the same time.

![system](../img/layout_corne42_system.png)

The default layer changes are persistent between reboots. The cursor layer at the bottom right is not persistent.

RGB defaults returns to the rainbow effect and 100% brightness.

### Layout images
The layouts were created with [keyboard-layout-editor.com](http://www.keyboard-layout-editor.com).

[blank](http://www.keyboard-layout-editor.com/#/gists/3bfed02864e018f692c1bb9a38c1b25) -
[main](http://www.keyboard-layout-editor.com/#/gists/b42f83b159878ef53c8cfe383613fbdb) -
[extend](http://www.keyboard-layout-editor.com/#/gists/5c048b99cea0962223a2aa11d8d6f741) -
[nav](http://www.keyboard-layout-editor.com/#/gists/b65235844553a408eae33be10ab5b621) -
[system](http://www.keyboard-layout-editor.com/#/gists/7d0409ff0df964887f6e4fe35cc3be79)
