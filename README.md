**plan:**

main
	boucle
		readline -> parsing -> execution
		free(readline)
		retour a la ligne

parsing
	tab = split()
	while(tab)
		if (tab[i])

test.txt < wc > res.txt

input -> ls -la

export A="fileout.txt"

< filein.txt echo "test | wc " | wc > $A

should become:

node 1:
	0: <
	1: filein.txt
node 2:
	0: echo
	1: "test | wc "
node 3:
	0: wc
node 4:
	0: >
	1: fileout.txt

TODO: pour se faciliter la vie on peut remplacer tout les < file.txt, >> file.txt, pipe par un node avec les deux fd et le mode append: oui/non

LULU:

ameliorer parsing pour quotes "" ''
suprrimer characters speciaux comme \ et ;
$var
clean (optionel)


KIMESTRE
ameliorer export
etudier les signaux

FIN:
- delimiteur
- redirectiosn dans les deux sens
- trouver l'exit status de la derniere fonction et le mettre dans envp $?
  l'afficher si cmd = $?
- fix leaks