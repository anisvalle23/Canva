#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <QString>
#include <QStringList>

struct Usuario {
    QString id;
    QString username;
    QString password;
    QString nombre;
    QString tipo;
    QString profesion;  // Solo para maestros
    double sueldo;      // Solo para maestros
    QString carrera;    // Solo para alumnos
    QString clases;     // Solo para alumnos

    // 🔹 Convertir una línea de texto a un Usuario
    static Usuario fromText(const QString &line) {
        QStringList fields = line.split(",");

        if (fields.size() == 8) {  // 📌 Caso Maestro (incluye sueldo y tipo)
            bool ok;
            double sueldo = fields[6].toDouble(&ok);
            if (!ok) sueldo = 0.0;  // Si la conversión falla, se asigna 0.0

            return {fields[0].trimmed(), fields[1].trimmed(), fields[2].trimmed(),
                    fields[3].trimmed(), "Maestro", fields[5].trimmed(), sueldo, "", ""};
        }

        else if (fields.size() == 7) {  // 📌 Caso Alumno (incluye tipo pero no sueldo)
            return {fields[0].trimmed(), fields[1].trimmed(), fields[2].trimmed(),
                    fields[3].trimmed(), "Alumno", "", 0.0, fields[5].trimmed(), fields[6].trimmed()};
        }

        else if (fields.size() == 6) {  // 📌 Caso Registro (Admin)
            return {fields[0].trimmed(), fields[1].trimmed(), fields[2].trimmed(),
                    fields[3].trimmed(), "Admin", fields[4].trimmed(), 0.0, "", ""};
        }

        return {"", "", "", "", "", "", 0.0, "", ""};  // Usuario vacío si el formato es inválido
    }

    // 🔹 Convertir un Usuario a una línea de texto (para guardar en el archivo)
    QString toText() const {
        if (tipo == "Maestro") {
            return id + "," + username + "," + password + "," + nombre + ","
                   + tipo + "," + profesion + "," + QString::number(sueldo, 'f', 2);
        }
        else if (tipo == "Alumno") {
            return id + "," + username + "," + password + "," + nombre + ","
                   + tipo + "," + carrera + "," + clases;
        }
        else if (tipo == "Admin") {
            return id + "," + username + "," + password + "," + nombre + ","
                   + tipo + "," + profesion;
        }
        return ""; // Devuelve cadena vacía si el tipo es inválido
    }
};

// 🔹 Nueva estructura para las Clases
struct Clase {
    QString id;
    QString nombre;
    QString hora;
    int uv;          // Unidades valorativas
    int semestre;
    QString periodo;
    int año;

    // 🔹 Convertir una línea de texto a un objeto Clase
    static Clase fromText(const QString &line) {
        QStringList fields = line.split(",");

        if (fields.size() == 7) {  // 📌 Verificamos que la línea tenga el formato correcto
            bool ok1, ok2, ok3;
            int uv = fields[3].toInt(&ok1);
            int semestre = fields[4].toInt(&ok2);
            int año = fields[6].toInt(&ok3);

            return {fields[0].trimmed(), fields[1].trimmed(), fields[2].trimmed(),
                    ok1 ? uv : 0, ok2 ? semestre : 0, fields[5].trimmed(), ok3 ? año : 0};
        }

        return {"", "", "", 0, 0, "", 0};  // 📌 Si hay error, devolvemos una clase vacía
    }

    // 🔹 Convertir una Clase a una línea de texto (para guardar en el archivo)
    QString toText() const {
        return id + "," + nombre + "," + hora + ","
               + QString::number(uv) + "," + QString::number(semestre) + ","
               + periodo + "," + QString::number(año);
    }
};

#endif // ESTRUCTURAS_H
