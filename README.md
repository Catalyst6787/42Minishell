FIN:

- **fix leaks**
- handle errors

**Erreurs a corriger:**

-[x] env pas free apres builtin
-[x] probleme dans expand var -> is quoted (echo '$SHELL' expand alors qu'il devrait pas et il y a des invalid reads)
-[x] cat < output.txt | cat  marche pas
-[] 'cat | cat | ls' pas comme bash mais dans bash c'est bizarre
-[x] erreurs renvoye dans $? sont pas le memes que dans bash
-[x] crash dans /bin/ls ???
 -> trouvé! double free quand le path complet est donné (c’est réglé dcp)

-[x] les commandes sans espaces (ls|cat)
-[] si commande n'existe pas (lol | cat) -> on devrait renvoyer une erreur sans faire celles d'apres
-[x] heredoc devrait pas expand quand 'DEL' mais expand a l'interieur meme si 'content' 
-[] gere les signaux dans heredoc