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