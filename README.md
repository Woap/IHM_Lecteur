# Lecteur audio - Interface Homme Machine

Nous avons choisi de faire un lecteur assez minimaliste avec les boutons basiques d’un lecteur, l’affichage du titre, de l’artiste et de la cover art. Le bouton à droite du son permet de passer vers le mode étendu.
On pourra également avancer/reculer la chanson à l’aide de la barre de progression.
Le temps en gras indique le temps en cours et le temps au dessus la durée de la chanson. Si la cover art n’est pas disponible ( par exemple dans un flux radio ), il y aura une image générique.

Descriptif des flux de données et des échanges asynchrones avec le serveur.


Flux de données :

Client -> Serveur :
Le client envoie une requête vers le serveur lorsqu’il éffectue une action ( changement de volume, de musique ... ).
{ "command": ["command_name", "param1", "param2", ...] }
exemple : play : { "command": ["set_property", "play", true] } -> demande au serveur de démarrer la musique
Le serveur renvoie un JSON indiquant le succès ou non de la requête

Serveur -> Client :
Utilisation d’événements pour observer les changements sur le serveur
Une observation des propriétés est effectuée par chaque client sur le serveur
Lorsqu’une propriété est modifiée, le serveur informe tous les clients via un JSON indiquant la valeur modifiée
{ "command": ["observe_property", id, "propriété"] }



