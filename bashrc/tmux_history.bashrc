if [[ $TMUX_PANE ]]; then
    if [ ! -d $HOME/.bash_history_tmux ]; then
        mkdir $HOME/.bash_history_tmux
    fi
    HISTFILE=$HOME/.bash_history_tmux/$(tmux display-message -p '#S')_${TMUX_PANE:1}
fi

