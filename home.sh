#!/bin/sh

file=$(pwd)
export PATH=$file:$PATH
alias megashell='cd $file'
alias valshell='valgrind --suppressions=$file/valgrind_readline_leaks_ignore.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --verbose minishell'

#lunch with : source ./home.sh
