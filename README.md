**plan:**

LULU:

- [x]  ameliorer parsing pour quotes "" ''
- [x]  suprimer characters speciaux comme \ et ;
- [x]  $var
- clean (optionel)


KIMESTRE
- [x] ameliorer export
- [x] etudier les signaux

FIN:
- delimiteur
- redirectiosn dans les deux sens
- trouver l'exit status de la derniere fonction et le mettre dans envp $?
  l'afficher si cmd = $?
- fix leaks
- handle errors

**Erreurs a corriger:**
- [x] segfault quand on ajoute une variable vide { export A="" }
- [x] double prompt apres avoir quitte une commande avec CTRL + C { yes CTRL + C}
