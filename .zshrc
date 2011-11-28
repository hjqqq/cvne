# Lines configured by zsh-newuser-install
HISTFILE=~/.histfile
HISTSIZE=9000
SAVEHIST=9000
setopt appendhistory
unsetopt beep
bindkey -v
# End of lines configured by zsh-newuser-install
# The following lines were added by compinstall
zstyle :compinstall filename '/home/carado/.zshrc'

autoload -Uz compinit
compinit
# End of lines added by compinstall

PS1="%# %~ > "

#bindkey '^[OH' beginning-of-line
#bindkey '^[OF' end-of-line
bindkey '^[[1;5D' backward-word
bindkey '^[[1;5C' forward-word

bindkey "\e[1~" beginning-of-line # Home
bindkey "\e[4~" end-of-line # End
bindkey "\e[5~" beginning-of-history # PageUp
bindkey "\e[6~" end-of-history # PageDown
bindkey "\e[2~" quoted-insert # Ins
bindkey "\e[3~" delete-char # Del
bindkey "\e[5C" forward-word
bindkey "\eOc" emacs-forward-word
bindkey "\e[5D" backward-word
bindkey "\eOd" emacs-backward-word
bindkey "\e\e[C" forward-word
bindkey "\e\e[D" backward-word
bindkey "\e[Z" reverse-menu-complete # Shift+Tab
# for rxvt
bindkey "\e[7~" beginning-of-line # Home
bindkey "\e[8~" end-of-line # End
# for non RH/Debian xterm, can't hurt for RH/Debian xterm
bindkey "\eOH" beginning-of-line
bindkey "\eOF" end-of-line
# for freebsd console
bindkey "\e[H" beginning-of-line
bindkey "\e[F" end-of-line

autoload colors zsh/terminfo
if [[ "$terminfo[colors]" -ge 8 ]]; then
	colors
fi
for color in RED GREEN YELLOW BLUE MAGENTA CYAN WHITE
do
	eval $color='%{$terminfo[bold]$fg[${(L)color}]%}'
	eval LIGHT_$color='%{$fg[${(L)color}]%}'
	(( count = $count + 1 ))
done
NO_COLOR="%{$terminfo[sgr0]%}"

PS1="$YELLOW"'['"$GREEN%n$YELLOW@$RED%m$YELLOW:$BLUE%~$YELLOW"']'"$NO_COLOR "
PS2="$YELLOW"'['"$BLUE%_$YELLOW"']'"$NO_COLOR "

alias kat="source-highlight -t4 --out-format=esc -o STDOUT -i"
alias lock="xscreensaver-command -lock"
#alias gnome2="gsettings set org.gnome.desktop.session session-name 'gnome-fallback'"
alias steam="cd d/winestamp/drive_c/Program\ Files\ \(x86\)/Steam;WINEPREFIX=/home/carado/d/winestamp wine Steam.exe"
alias hi="cat ~/.histfile"

source /usr/share/zsh/plugins/zsh-syntax-highlight/zsh-syntax-highlighting.zsh

