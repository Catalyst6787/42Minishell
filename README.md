FIN:

- **fix leaks**
- handle errors

**Erreurs a corriger:**

-[] env pas free apres builtin
-[] probleme dans expand var -> is quoted (echo '$SHELL' expand alors qu'il devrait pas et il y a des invalid reads)
-[] commandes marchent toujours quand on unset le path
-[] cat < output.txt | cat >> output.txt marche pas
-[] 'cat | cat | ls' pas comme bash mais dans bash c'est bizarre
-[] erreurs renvoye dans $? sont pas le memes que dans bash
-[x] crash dans /bin/ls ???
 -> trouvé! double free quand le path complet est donné (c’est réglé dcp)

