#ifndef ALUMNOS_H
#define ALUMNOS_H

#include "estructuras.h"
#include <QMainWindow>
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Alumnos;
}

class Alumnos : public QMainWindow {
    Q_OBJECT

public:
    explicit Alumnos(QWidget *parent = nullptr);
    ~Alumnos();

    void saveAlumnosUser();  // ✅ Guardar alumnos en archivo de texto
    void loadAlumnosUser();  // ✅ Cargar alumnos desde archivo de texto
    void addAlumno(const Usuario &nuevoAlumno);  // ✅ Agregar alumno a la lista
    QList<Usuario> getAlumnosUsers() const; // ✅ Debe estar declarado aquí
    void eliminarAlumno(const QString &username); // ✅ Eliminar alumno de la lista
    void modificarAlumno(const QString &usuario, const Usuario &nuevoDatos);


private:
    Ui::Alumnos *ui;
    QList<Usuario> AlumnosUsers; // Lista de alumnos

    void addDefaultAlumnos(); // Agregar usuario predeterminado
};

#endif // ALUMNOS_H
