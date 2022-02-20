#!/bin/sh

file=$(pwd)
valshell="valgrind --suppressions=$file/valgrind_readline_leaks_ignore.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --verbose minishell"
megashell="cd $file"
export PATH=$file:$PATH
alias megashell=$megashell
alias valshell=$valshell

touch ~/bin/megashell.sh ~/bin/valshell.sh
chmod 777 ~/bin/megashell.sh ~/bin/valshell.sh
echo "#!/bin/sh" > ~/bin/megashell.sh
echo $megashell >> ~/bin/megashell.sh
echo "#!/bin/sh" > ~/bin/valshell.sh
echo $valshell >> ~/bin/valshell.sh

#lunch with : source ./home.sh
