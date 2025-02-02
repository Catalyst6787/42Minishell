**plan:**

LULU:

- clean (optionel)


KIMESTRE
- [x] ameliorer export
- [x] etudier les signaux

FIN:
- [x] delimiteur
- [x] redirections dans les deux sens
- [x] verifier si les fichier d’input existent avant de les ouvrirs
- [x] trouver l'exit status de la derniere fonction et le mettre dans envp $?
- [x] l'afficher si cmd = $?
- fix leaks
- handle errors

**Erreurs a corriger:**
- [x] segfault quand on ajoute une variable vide { export A="" }
- [x] double prompt apres avoir quitte une commande avec CTRL + C { yes CTRL + C}
