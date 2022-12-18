# Auteurs

        Maël PAUL
        Maxime SALAND

# Dépôt pour les projets S5 (PR103)

- Lien vers le sujet du projet :

        <https://www.labri.fr/perso/renault/working/teaching/projets/2021-22-S5-Sandwich.php>

- Lien vers la documentation sur l'utilisation de git :

        <https://thor.enseirb-matmeca.fr/ruby/docs/repository/git>

# Compiler et exécuter

- Compiler le projet:  
        make

- Exécuter le projet sans visualisation de l'image:  
        ./project

- Options:  
        -m suivi du nombre d'images (exemple: ./project -m 100 pour 100 images)  
        -s suivi de la seed (exemple: ./project -s 100)

- Exécuter le projet avec visualisation de l'image:        
        ./project | ./sdl

- Options de l'exécutable sdl:  
        -m permet d'avoir l'affichage image par image après l'exécution complète (exemple: ./project | ./sdl -m)  
        -M permet d'avoir l'affichage image par image (exemple: ./project | ./sdl -M)

- Compiler les tests:  
        make test

- Exécuter les tests:  
        ./test_project

- Clean:  
        make clean
