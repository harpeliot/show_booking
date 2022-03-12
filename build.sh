#!/bin/bash
clear
gcc  -Wall serveur.c -o serveur.out -lpthread 
gcc  -Wall client.c -o client.out -lpthread

