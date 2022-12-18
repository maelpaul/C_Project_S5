Passer du jeu de la vie au sable et inversement:

Remarque : Pensez à faire "make clean" avant de refaire "make" pour être sûr que les changements soient pris en compte.

1- Dans le fichier worldalgo.h à la ligne 6, définir la valeur de ACHIEV à:
   pour le jeu de la vie noir et blanc (base version):
   	0
   pour le jeu de la vie multicolore (multicoloritude):
   	1
   pour le sable (déplacements multiples):
   	2

2- Dans le fichier rule.c à la ligne 6, définir la valeur de NB_RULE à:
   pour le jeu de la vie noir et blanc ou multicolore (achiev 0 et 1):
   	512
   pour le sable (achiev 2):
   	6
