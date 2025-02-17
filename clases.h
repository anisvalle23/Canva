#ifndef CLASES_H
#define CLASES_H

#include "estructuras.h"
#include <QList>

class Clases {
public:
    Clases();  // Constructor
    void saveClases();    // Guardar en archivo
    void loadClases();    // Cargar desde archivo
    void addClase(const Clase &nuevaClase);  // Agregar nueva clase
    void eliminarClase(const QString &id);   // Eliminar clase

    QList<Clase> getClases() const { return listaClases; }  // Obtener lista de clases

private:
    QList<Clase> listaClases;  // Lista de clases
    QString archivoClases = "/Users/anavalle/Desktop/Estru Datos I/MiniCanva/registro.txt";
};

#endif // CLASES_H
