# Nom de l'exécutable final
TARGET = jeu.exe

# Liste des fichiers source
SRCS = main.c plateau.c menu.c logique.c score.c

# Compilateur
CC = gcc

# Règle par défaut : compile tout
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET)

# Règle pour nettoyer les fichiers inutiles
clean:
	del /f $(TARGET)