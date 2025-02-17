#include "alumnos.h"
#include "ui_alumnos.h"
#include "QMessageBox"

Alumnos::Alumnos(QWidget *parent) : QMainWindow(parent), ui(new Ui::Alumnos) {
    ui->setupUi(this);

    loadAlumnosUser();

    if (AlumnosUsers.isEmpty()) {
        addDefaultAlumnos();
        saveAlumnosUser();
    }
}

Alumnos::~Alumnos() {
    delete ui;
}

void Alumnos::addDefaultAlumnos() {
    Usuario defaultUser = {"0001", "alumno", "1234", "Estudiante Predeterminado", "Alumno", "", 0.0, "Ingeniería", "Matemáticas,Física"};
    AlumnosUsers.append(defaultUser);
}

void Alumnos::saveAlumnosUser() {
    QString rutaAlumnos = "/Users/anavalle/Desktop/Estru Datos I/MiniCanva/alumnos.txt";
    QFile file(rutaAlumnos);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const Usuario &user : AlumnosUsers) {
            out << user.toText() << "\n";  // ✅ Guardamos en formato correcto
        }
        file.close();
        qDebug() << "✅ Archivo 'alumnos.txt' actualizado correctamente.";
    } else {
        qWarning() << "❌ No se pudo abrir el archivo en " << rutaAlumnos << " para escritura.";
    }
}

void Alumnos::loadAlumnosUser() {
    QString rutaAlumnos = "/Users/anavalle/Desktop/Estru Datos I/MiniCanva/alumnos.txt";
    QFile file(rutaAlumnos);

    if (!file.exists()) {
        qWarning() << "🚨 El archivo 'alumnos.txt' no existe en " << rutaAlumnos << ". Creándolo.";
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "0001,alumno,1234,Estudiante Predeterminado,Alumno,,0.0,Ingeniería,Matemáticas,Física\n"; // Usuario predeterminado
            file.close();
        }
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        AlumnosUsers.clear();

        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            Usuario alumno = Usuario::fromText(line);

            if (!alumno.username.isEmpty()) {
                AlumnosUsers.append(alumno);
                qDebug() << "✅ Alumno cargado:" << alumno.toText();
            } else {
                qWarning() << "⚠ Error en línea:" << line;
            }
        }
        file.close();
    } else {
        qWarning() << "❌ No se pudo abrir el archivo en " << rutaAlumnos;
    }
}

void Alumnos::eliminarAlumno(const QString &nombre) {
    loadAlumnosUser();  // Cargar la lista actualizada de alumnos

    // 🔹 Filtrar la lista para eliminar el alumno
    auto it = std::remove_if(AlumnosUsers.begin(), AlumnosUsers.end(),

                             [&](const Usuario &alumno) { return alumno.nombre == nombre; });

    if (it != AlumnosUsers.end()) {
        AlumnosUsers.erase(it, AlumnosUsers.end());  // Eliminar el alumno de la lista
        saveAlumnosUser();  // Guardar la lista actualizada en el archivo
        qDebug() << "✅ Alumno eliminado con éxito:" << nombre;
    } else {
        qDebug() << "⚠ No se encontró el alumno a eliminar:" << nombre;
    }
}

void Alumnos::addAlumno(const Usuario &nuevoAlumno) {
    qDebug() << "🆕 Agregando nuevo alumno:" << nuevoAlumno.toText();

    // 🔹 Verificar si el usuario ya existe
    for (const Usuario &alumno : AlumnosUsers) {
        if (alumno.username == nuevoAlumno.username) {
            QMessageBox::warning(nullptr, "Error", "El usuario ya existe. Elija otro nombre de usuario.");
            return;
        }
    }

    // 🔹 Agregar y guardar en archivo
    AlumnosUsers.append(nuevoAlumno);
    saveAlumnosUser();

    qDebug() << "✅ Estado actual de AlumnosUsers:";
    for (const Usuario &user : AlumnosUsers) {
        qDebug() << user.toText();
    }
}

QList<Usuario> Alumnos::getAlumnosUsers() const {
    return AlumnosUsers;
}


void Alumnos::modificarAlumno(const QString &usuario, const Usuario &nuevoDatos) {
    loadAlumnosUser();  // Cargamos la lista actualizada

    for (Usuario &alumno : AlumnosUsers) {
        if (alumno.username == usuario) {
            alumno = nuevoDatos;  // 🔹 Modificamos los datos del alumno
            saveAlumnosUser();    // 🔹 Guardamos los cambios en el archivo
            QMessageBox::information(nullptr, "Éxito", "El alumno ha sido actualizado correctamente.");
            return;
        }
    }

    QMessageBox::warning(nullptr, "Error", "El usuario no existe.");
}
