#!/bin/bash

send=10
port=9000
for ((i = 0; i < send; i++)); do
  echo "spam out server" | nc -q 0 localhost $port &
done; wait

# SERVER_IP="adresse_IP_serveur"
# SERVER_PORT="numéro_port"

# Test de résistance aux données incorrectes
# echo -e "Envoi de données incorrectes au serveur..."
# echo -e "Caractères spéciaux : "
# echo -n "!@#$%^&*" | nc "$SERVER_IP" "$SERVER_PORT"
# echo -e "\nValeurs incorrectes : "
# echo -n "123abc" | nc "$SERVER_IP" "$SERVER_PORT"
# echo -e "\nFormat inattendu : "
# echo -n "12,34,56" | nc "$SERVER_IP" "$SERVER_PORT"

# Test d'échelle
# echo -e "\nTest d'échelle - Envoi de données en masse..."
# for ((i=1; i<=100; i++))
# do
#   echo "Données de test $i" | nc "$SERVER_IP" "$SERVER_PORT" &
# done
# wait

# Test de robustesse
# echo -e "\nTest de robustesse - Déconnexion et reconnexion du serveur..."
# echo "Données de test" | nc "$SERVER_IP" "$SERVER_PORT"
# sleep 2
# killall -9 nc
# sleep 2
# echo "Données de test après reconnexion" | nc "$SERVER_IP" "$SERVER_PORT"

# Test de sécurité
# echo -e "\nTest de sécurité - Envoi de données malveillantes..."
# echo -n "'; DROP TABLE users;--" | nc "$SERVER_IP" "$SERVER_PORT"

# Test de concurrence
# echo -e "\nTest de concurrence - Envoi de données simultanées..."
# for ((i=1; i<=10; i++))
# do
#   echo "Données de test $i" | nc "$SERVER_IP" "$SERVER_PORT" &
# done
# wait

# Test de robustesse aux erreurs
# echo -e "\nTest de robustesse aux erreurs - Envoi de données erronées..."
# echo -n -e "\x00\x01\x02\x03\x04" | nc "$SERVER_IP" "$SERVER_PORT"
