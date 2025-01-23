**plan:**

LULU:

- [x]  ameliorer parsing pour quotes "" ''
- suprimer characters speciaux comme \ et ;
- [x]  $var
- clean (optionel)


KIMESTRE
ameliorer export
etudier les signaux

FIN:
- delimiteur
- redirectiosn dans les deux sens
- trouver l'exit status de la derniere fonction et le mettre dans envp $?
  l'afficher si cmd = $?
- fix leaks
- handle errors

**Erreurs a corriger:**
- segfault quand on ajoute une variable vide { export A="" }
