#!/bin/sh

mkdir ~/bin
cp valgrind_readline_leaks_ignore.txt ~/bin
cp minishell ~/bin
valshell="valgrind --suppressions="$HOME"/bin/valgrind_readline_leaks_ignore.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --verbose minishell"
alias valshell=$valshell
touch ~/bin/valshell
chmod 777 ~/bin/valshell
echo "#!/bin/sh" > ~/bin/valshell
echo $valshell >> ~/bin/valshell