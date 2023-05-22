# [Fast as Fox] Cahier des charges

## Description du jeu
---

Le jeu est basé sur le concept des Runners, il s'inspire du jeu Sonic : [Vidéo de démonstration du Sonic d'inspiration](https://www.youtube.com/watch?v=x1XEd5Q7E7Y&t=1s).

Le concept d'un Runner est de terminer l'exploration du niveau le plus rapidement possible. Le joueur est ensuite classé en fonction de son temps puis de son nombre de pièces accumulées lors de l'exploration du niveau.

## Version 1 [Alpha]
---

- Le jeu dispose d'un seul niveau, le niveau est basé sur une tilemap
- La map est stockée dans un fichier à part. Le niveau est fixe.
- Le joueur est représenté par un renard : https://star-dragon.itch.io/fox-sprites
<br><center><img src="https://img.itch.zone/aW1nLzY0MzM3MzMucG5n/315x250%23c/LQBQNb.png"></center>

- Le niveau est basé sur des textures en 32x32 : [Tileset niveau](https://cainos.itch.io/pixel-art-platformer-village-props)
  
<br>
<center>
<img src="https://img.itch.zone/aW1hZ2UvMTAzNDU1MS83MTU0ODQyLnBuZw==/original/zNokSD.png" width="30%">
<img src="https://img.itch.zone/aW1hZ2UvMTAzNDU1MS83MTU0ODQzLnBuZw==/347x500/AKeRih.png" width="30%">
<img src="https://img.itch.zone/aW1hZ2UvMTAzNDU1MS81OTA1MzY0LnBuZw==/347x500/njUOOZ.png" width="30%">
<img src="https://img.itch.zone/aW1hZ2UvMTAzNDU1MS81OTA1MzYzLnBuZw==/347x500/AgICjI.png" width="30%">
<img src="https://img.itch.zone/aW1hZ2UvMTAzNDU1MS81OTA1MzYyLnBuZw==/347x500/eDPceO.png" width="30%">
<img src="https://img.itch.zone/aW1hZ2UvMTAzNDU1MS81OTA1MzQxLnBuZw==/347x500/DAbpeb.png" width="30%">
<img src="https://img.itch.zone/aW1hZ2UvMTAzNDU1MS81OTA1MzQwLnBuZw==/347x500/1Hm1KO.png" width="30%">
</center>

- Le temps de complétion du niveau est chronométré en secondes + centièmes, et correspond au score du joueur
- Le joueur ne peut qu’avancer et accélérer et ralentir (induit par l’accélération)
- La réussite du niveau est déterminée par le fait que le joueur atteint une zone du niveau
- Les touches de déplacements sont affichées en bas de l'interface du joueur :
  
  - [Interface joueur](https://crusenho.itch.io/complete-gui-essential-pack)
  - [Affichage contrôles](https://crusenho.itch.io/ps4-xbox-controller-buttons)
  - [Police d'écriture](https://masubiwa.itch.io/irisdot-h21-oblique)

- Les touches de base sont :
  - Sauter : <kbd>Space</kbd>/<kbd>↑</kbd>
  - Bas : <kbd>S</kbd>/<kbd>↓</kbd>
  - Droite : <kbd>D</kbd>/<kbd>→</kbd>

## Version 2 [Beta]
---

- Le joueur peut atteindre des power ups qui apparaissent à des endroits prédéfinis mais le type de baie qui apparaît est aléatoire. (Ils sont représentés par des baies de différentes couleurs [Sprites de baies](https://ninjikin.itch.io/fruit), une couleur est associée à un effet) :

  - Dash : Elance le joueur en avant 1 sec d'animation (+100% de vitesse)
  - Double sauts : Permet d'effectuer deuxième saut pendant le temps de vol d'un premier saut.
  - Dash vers le bas : Permet de s'élancer vers le bas pour attérir immédiattement au sol 
  - Speed : Augmente la vitesse de déplacement du joueur : +145% pendant 5 secondes
  - Revive : Permet d'annuler la prochaine mort du joueur.

<br><center>
<img src="https://img.itch.zone/aW1nLzY4MTY4NTgucG5n/original/yt%2FJgc.png" width="20%">
<img src="https://img.itch.zone/aW1nLzY4MTY4NzAucG5n/original/q1o2dc.png" width="20%">
<img src="https://img.itch.zone/aW1nLzY4MTY4ODIucG5n/original/3LKpQp.png" width="20%">
<img src="https://img.itch.zone/aW1nLzY4MTY4ODMucG5n/original/ZGfvYt.png" width="20%">
</center><br>

- Les power ups se stockent dans un slot du joueur (affiché à côté de son icône par la baie du powerup récupéré (en haut a droite)). Il peut choisir de les activer lorsqu'il le souhaite (<kbd>E</kbd>). Le joueur ne peut concerver qu'un seul powerup à la fois.

- Le jeu comporte un compteur de pièces qui fait office de score secondaire, il est affiché en haut à droite sous le compteur de temps.
- Le niveau comporte des pièces qui augmentent le score (augmente le compteur de pièces) du joueur

- Le niveau comporte es obstacles qui peuvent tuer le joueur :

  - Des Hérissons qui se déplacent de gauche à droite jusqu'au bord de leur "étage"
  - Des Pics situés au sols, qui infligent des dégats lorsqu'on leur marche/tombe dessus et qui repoussent légèrement le joueur en arrière
  
- Le joueur dispose de 3 vies représentées par des coeurs (situés en haut à gauche de l'interface)

- La caméra suit le joueur durant ses déplacements

## Version 3 [Release]
---

- Version infinie avec génération procédurale de la map :
  - La map est un assemblage de sections de terrain qui se fait durant la progression du joueur
  - Les sections disposent de tags indicant leur hauteur de début et de fin
  - Un algorithme de recherche de compatiblité est utilisé pour déterminer si des sections de terrain sont compatibles
    - L'algorithme se base sur la recherche du nombre chromatique pour concaténer les sections de terrain.
    - Une section est voisine avec une autre si la différence de hauteur est supérieure à la hauteur de saut du joueur.
- Ajout de power down qui peuvent apparaître aux mêmes emplacements que les power up : 
  - Slow : Ralentit le joueur pendant 5 secondes à 80% de sa vitesse de déplacement
  - Trop rapide : Augmente la vitesse de base de déplacement de joueur à 180% de sa vitesse de base
  - Bump en arrière : Repousse le joueur en l'air à un angle de -30° par rapport à la verticale et une vitesse initiale de 60% de la vitesse de déplacement du joueur
  - Joueur invisible : Fait disparaitre le joueur pendant 5 secondes de l'écran  (sa texture disparait) mais le joueur peut toujours intéragir avec la map, les obstacles et le reste du jeu.
  - Baie explosive : Fait exploser le joueur, il meurt instantanément lorsqu'il touche la baie.
  
- Le renard peut changer d’apparence, il peut changer de couleur :
  
  - Polaire
  - Roux
  - Crimson
  - Albinos

- Sauvegarde des scores locaux dans un classement :
  - Classement global de chaque niveau par pièces
  - Classement global de chaque niveau par temps
  - Classement par pièces pour le mode infini

<center><img src="https://assetstorev1-prd-cdn.unity3d.com/package-screenshot/c6e86b96-9d07-4e07-8ad4-ad2935deba62.webp"></center>

## Version 4 [MaJ]
---

- Deux joueurs peuvent jouer en 1v1, avec l’écran scindé en deux parties (horizontalement)

