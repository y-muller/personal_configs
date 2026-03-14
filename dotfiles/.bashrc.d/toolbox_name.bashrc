# If running in a toolbx container
#   - set the BOXNAME variable to the container name
#   - set the prompt to show the box name

if [ -f /run/.containerenv ]; then
    export BOXNAME=$(cat /run/.containerenv | grep -oP "(?<=name=\")[^\";]+")
    #echo $BOXNAME
    export PS1="\[\033[35m\]⬢ \[\033[0m\][\u@$BOXNAME \W]\\$ "
    #PS1=$(printf "\[\033[35m\]⬢ \[\033[0m\]%s" "[\u@$BOXNAME \W]\\$ ")
fi

