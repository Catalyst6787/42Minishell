FIN:

- **fix leaks**
- handle errors

**Erreurs a corriger:**

-[] env pas free apres builtin
-[x] probleme dans expand var -> is quoted (echo '$SHELL' expand alors qu'il devrait pas et il y a des invalid reads)
-[] cat < output.txt | cat  marche pas
-[] 'cat | cat | ls' pas comme bash mais dans bash c'est bizarre
-[x] erreurs renvoye dans $? sont pas le memes que dans bash
-[x] crash dans /bin/ls ???
 -> trouvé! double free quand le path complet est donné (c’est réglé dcp)

