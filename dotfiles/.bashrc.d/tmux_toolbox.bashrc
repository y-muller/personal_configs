# If running in toolbx start a different tmux server for each container

function bmux() {
    if [[ $BOXNAME != "" ]]; then
        TMUXARGS="-L $BOXNAME new-session -A -s $BOXNAME"
    fi

    tmux $TMUXARGS
}
