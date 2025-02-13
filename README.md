FIN:

- **fix leaks**
- handle errors

**Erreurs a corriger:**

-[x] env pas free apres builtin
-[x] probleme dans expand var -> is quoted (echo '$SHELL' expand alors qu'il devrait pas et il y a des invalid reads)
-[x] cat < output.txt | cat  marche pas
-[x] 'cat | cat | ls' pas comme bash mais dans bash c'est bizarre
-[x] erreurs renvoye dans $? sont pas le memes que dans bash
-[x] crash dans /bin/ls ???
 -> trouvé! double free quand le path complet est donné (c’est réglé dcp)

-[x] les commandes sans espaces (ls|cat)
-[x] heredoc devrait pas expand quand 'DEL' mais expand a l'interieur meme si 'content' 
-[x] gere les signaux dans heredoc

cat <"./test_files/infile" | grep hello

echo hello'world' 
mini output = (hello'world')
bash output = (helloworld)

echo "$" 
mini output = ()
bash output = ($)

echo $?HELLO 
mini output = ()
bash output = (0HELLO)

exit hello 
mini exit code = 0
bash exit code = 2

exit 42 world 
mini output = (minishell: exit: too many arguments)
bash output = ()
mini exit code = 0
bash exit code = 1

echo > file hello
cat < file1 file2