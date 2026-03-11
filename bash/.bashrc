# If not running interactively, don't do anything
[[ $- != *i* ]] && return

if [ -f ~/.alias ]; then
    . ~/.alias
fi

export PATH="/usr/lib/llvm20/bin:$PATH"
export XDG_CONFIG_HOME="$HOME/.config"

# History control
shopt -s histappend

HISTCONTROL=ignoreboth
HISTSIZE=32768
HISTFILESIZE="${HISTSIZE}"

# Autocompletion
if [[ ! -v BASH_COMPLETION_VERSINFO && -f /usr/share/bash-completion/bash_completion ]]; then
  source /usr/share/bash-completion/bash_completion
fi

# Ensure command hashing is off for mise
set +h
