# tmux

## Plugins

#### [tpm]() : plugin manager
Used to install the other plugins

#### [continuum](https://github.com/tmux-plugins/tmux-continuum)
Start tmux server after boot. Saves the sessions every 15 minutes.

#### [resurrect](https://github.com/tmux-plugins/tmux-resurrect)
Needed by continuum.

#### [better-mouse-mode](https://github.com/NHDaly/tmux-better-mouse-mode) : mouse improvements

#### [tmux-yank](https://github.com/tmux-plugins/tmux-yank) : manage clipboard
Configured for X11 with `xsel`. If switching back to wayland, change the
command to `wl-copy` (wl-clipboard)

## Themes

neokyoto

## .bashrc changes

Separate history per pane:
```
if [[ $TMUX_PANE ]]; then
  HISTFILE=$HOME/.tmux_history/pane_${TMUX_PANE:1}
fi
```

Window title for Buildterm, etc...
```
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${TERMTITLE:+[$TERMTITLE]  }${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
```

