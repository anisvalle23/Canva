#include "registro.h"
#include "ui_registro.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include "maestros.h"
#include "alumnos.h"  // 🔹 Agregamos la inclusión de alumnos
#include "mainwindow.h"
#include <QListWidget>
#include <QListWidgetItem>
#include "clases.h"

Registro::Registro(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Registro) {

    ui->setupUi(this);  // ✅ Esto debe ejecutarse primero

    // 🔹 Inicializar los administradores después de `setupUi`
    maestrosManager = new Maestros(this);
    alumnosManager = new Alumnos(this);
    clasesManager = new Clases();
    // 🔹 Verificar que stackedWidget contiene todas las páginas esperadas
    qDebug() << "📌 Páginas en stackedWidget:" << ui->stackedWidget->count();

    // 🔹 Asegurar que `stackedWidget` está habilitado
    ui->stackedWidget->setEnabled(true);

    // 🔹 Cargar usuarios desde el archivo al iniciar
    loadRegistroUser();

    // 🔹 Agregar usuario predeterminado si la lista está vacía
    if (registroUsers.isEmpty()) {
        addDefaultRegistro();
        saveRegistroUser();
    }

    // 🔹 Cargar listas de maestros y alumnos
    cargarListaMaestros();
    cargarListaMaestrosEliminar();
    cargarListaAlumnos();
    cargarListaAlumnosEliminar();

    // 🔹 Verificar si `page_8` existe en `stackedWidget`
    bool foundPage8 = false;
    for (int i = 0; i < ui->stackedWidget->count(); ++i) {
        if (ui->stackedWidget->widget(i) == ui->page_8) {
            foundPage8 = true;
            break;
        }
    }

    if (!foundPage8) {
        qWarning() << "⚠ Error: page_8 no encontrada en stackedWidget.";
    } else {
        qDebug() << "✅ page_8 está correctamente en stackedWidget.";
    }

    // 🔹 Habilitar todos los botones por seguridad
    QList<QPushButton *> allButtons = findChildren<QPushButton *>();
    for (QPushButton *btn : allButtons) {
        btn->setEnabled(true);
    }
}

Registro::~Registro() {
    delete maestrosManager;  // 🔹 Eliminamos maestrosManager para liberar memoria
    delete alumnosManager;   // 🔹 Eliminamos alumnosManager
    delete clasesManager;
    delete ui;
}

void Registro::cargarListaAlumnos() {
    ui->listWidgetAlumnos->clear();  // Limpiar lista antes de cargar
    alumnosManager->loadAlumnosUser();  // Cargar alumnos desde el archivo

    const QList<Usuario> &alumnos = alumnosManager->getAlumnosUsers();
    qDebug() << "📂 Cargando lista de alumnos... Total:" << alumnos.size();

    if (alumnos.isEmpty()) {
        qWarning() << "🚨 No hay alumnos registrados.";
        return;
    }

    for (const Usuario &alumno : alumnos) {
        ui->listWidgetAlumnos->addItem(alumno.nombre);
        qDebug() << "✅ Alumno agregado a la lista: " << alumno.nombre;
    }

    qDebug() << "✅ Lista de alumnos cargada en listWidgetAlumnos.";
}
void Registro::cargarListaAlumnosEliminar() {
    ui->listWidgetEliminarAlumnos->clear();  // Limpia la lista antes de agregar elementos
    alumnosManager->loadAlumnosUser();  // Carga los datos desde el archivo

    for (const Usuario &alumno : alumnosManager->getAlumnosUsers()) {
        ui->listWidgetEliminarAlumnos->addItem(alumno.nombre);  // Agrega cada alumno al QListWidget
    }

    qDebug() << "✅ Lista de alumnos cargada en listWidgetEliminarAlumnos.";
}



void Registro::addDefaultRegistro() {
    Usuario defaultUser = {"0001", "admin", "1234", "Administrador", "Gestión", QString::number(0.0)}; // Conversión correcta
    registroUsers.append(defaultUser);
}


void Registro::saveRegistroUser() {
    QString filePath = "/Users/anavalle/Desktop/Estru Datos I/MiniCanva/registro.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "❌ No se pudo abrir el archivo 'registro.txt' para escritura.";
        return;
    }

    QTextStream out(&file);
    for (const Usuario &user : registroUsers) {
        out << user.toText() << "\n";
        qDebug() << "💾 Guardando en archivo: " << user.toText();
    }

    file.close();
    qDebug() << "✅ Archivo 'registro.txt' guardado correctamente con " << registroUsers.size() << " usuarios.";
}

void Registro::loadRegistroUser() {
    QString filePath = "/Users/anavalle/Desktop/Estru Datos I/MiniCanva/registro.txt";
    QFile file(filePath);

    if (!file.exists()) {
        qWarning() << "🚨 El archivo 'registro.txt' NO existe en la ruta:" << filePath;
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "❌ No se pudo abrir el archivo para lectura.";
        return;
    }

    QTextStream in(&file);
    registroUsers.clear();  // Limpiar lista antes de cargar

    qDebug() << "📂 Cargando usuarios desde 'registro.txt'...";

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        qDebug() << "📄 Línea leída: " << line;

        if (line.isEmpty() || !line.contains(",")) {
            qWarning() << "⚠ Línea inválida o vacía: " << line;
            continue;
        }

        Usuario user = Usuario::fromText(line);
        if (!user.username.isEmpty() && !user.password.isEmpty()) {
            registroUsers.append(user);
            qDebug() << "✅ Usuario agregado: " << user.toText();
        } else {
            qWarning() << "⚠ Usuario inválido en línea: " << line;
        }
    }

    file.close();
    qDebug() << "✅ Total de usuarios cargados: " << registroUsers.size();
}


void Registro::cargarListaMaestrosEliminar() {
    ui->listWidget_2->clear();  // Limpiar lista antes de agregar elementos
    maestrosManager->loadMaestroUser();  // Cargar maestros desde el archivo

    const QList<Usuario> &maestros = maestrosManager->getMaestrosUsers();
    qDebug() << "📂 Cargando lista de maestros eliminables... Total:" << maestros.size();

    if (maestros.isEmpty()) {
        qWarning() << "🚨 No hay maestros registrados para eliminar.";
        return;
    }

    for (const Usuario &maestro : maestros) {
        ui->listWidget_2->addItem(maestro.nombre);
        qDebug() << "✅ Maestro agregado a la lista: " << maestro.nombre;
    }

    qDebug() << "✅ Lista de maestros cargada en listWidget_2.";
}


void Registro::on_CuentaButton_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_AlumnoButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_Cuenta1Button_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_alum1Button_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_nuevoAlumButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_4);
}


void Registro::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_CancelarButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_ModiAlumButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_5);
}


void Registro::on_pushButton_2_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_6_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_ElimAlumButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_7);
}


void Registro::on_CuentaButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_9);
}


void Registro::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_14_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_15_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_19_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_20_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_21_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_22_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_23_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_26_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_24_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_25_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_27_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_28_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_29_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_11_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_10);
}


void Registro::on_pushButton_31_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_32_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_33_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_12);
}


void Registro::on_pushButton_34_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_35_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_36_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_40_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_41_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_42_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_43_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_37_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_14);
}


void Registro::on_pushButton_45_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_46_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_47_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_48_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_49_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_50_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_51_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_52_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_54_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_55_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_56_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_57_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_58_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_59_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_60_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_4);
}


void Registro::on_pushButton_61_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_62_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_63_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_64_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_65_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_66_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_67_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_68_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_69_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_70_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_71_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_72_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_73_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_76_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_77_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_78_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_79_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_80_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_81_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_82_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_83_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_84_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_85_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_86_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_87_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_88_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_89_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_90_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_91_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_92_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_74_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_19);
}


void Registro::on_pushButton_75_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_20);
}


void Registro::on_pushButton_95_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_96_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_97_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_98_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_103_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_99_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_100_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_101_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_102_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_93_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_38_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_15);
}


void Registro::on_pushButton_39_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_17);
}


void Registro::on_pushButton_105_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_106_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}



    void Registro::on_pushButton_107_clicked()
    {
        qDebug() << "✅ Botón 107 presionado. Cambiando a page_8.";
        ui->stackedWidget->setCurrentWidget(ui->page_8);
        qDebug() << "📌 Página actual después del cambio:" << ui->stackedWidget->currentIndex();
    }




void Registro::on_pushButton_108_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_109_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_113_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_114_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_115_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_116_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_117_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_118_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_120_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_121_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_122_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_123_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_124_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_125_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_126_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_127_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_128_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_129_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_130_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_131_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_133_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void Registro::on_pushButton_134_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void Registro::on_pushButton_135_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_8);
}


void Registro::on_pushButton_136_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_13);
}


void Registro::on_pushButton_137_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_18);
}


void Registro::on_pushButton_138_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void Registro::on_pushButton_139_clicked()
{
      ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_140_clicked()
{
    this->close();  // Cierra la ventana actual (Registro)

    MainWindow *mainWindow = new MainWindow();  // Crear una nueva instancia de MainWindow
    mainWindow->show();  // Mostrar la pantalla de inicio de sesión
}


void Registro::on_pushButton_141_clicked()
{
      ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_142_clicked()
{
    this->close();  // Cierra la ventana actual (Registro)

    MainWindow *mainWindow = new MainWindow();  // Crear una nueva instancia de MainWindow
    mainWindow->show();  // Mostrar la pantalla de inicio de sesión
}


void Registro::on_pushButton_143_clicked()
{
      ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_145_clicked()
{
      ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_146_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_147_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_148_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_149_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_150_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_151_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_152_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_153_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_154_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_155_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_156_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_157_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_158_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_21);
}



void Registro::on_pushButton_159_clicked()
{
    this->close();  // Cierra la ventana actual (Registro)

    MainWindow *mainWindow = new MainWindow();  // Crear una nueva instancia de MainWindow
    mainWindow->show();  // Mostrar la pantalla de inicio de sesión
}

void Registro::on_pushButton_160_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_161_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_162_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_163_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_164_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_165_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_166_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_167_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_168_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_169_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_170_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_171_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_172_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_173_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_174_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_175_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_176_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_144_clicked()
{
    this->close();  // Cierra la ventana actual (Registro)

    MainWindow *mainWindow = new MainWindow();  // Crear una nueva instancia de MainWindow
    mainWindow->show();  // Mostrar la pantalla de inicio de sesión
}


void Registro::on_pushButton_177_clicked()
{
    this->close();  // Cierra la ventana actual (Registro)

    MainWindow *mainWindow = new MainWindow();  // Crear una nueva instancia de MainWindow
    mainWindow->show();  // Mostrar la pantalla de inicio de sesión
}


void Registro::on_pushButton_178_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_179_clicked()
{
    this->close();  // Cierra la ventana actual (Registro)

    MainWindow *mainWindow = new MainWindow();  // Crear una nueva instancia de MainWindow
    mainWindow->show();  // Mostrar la pantalla de inicio de sesión
}


void Registro::on_pushButton_180_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_181_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}


void Registro::on_pushButton_182_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_21);
}


void Registro::on_pushButton_183_clicked()
{
    this->close();

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}




void Registro::on_AgregarButton_clicked() {
    QString id = ui->inputID->text().trimmed();
    QString username = ui->inputUsuario->text().trimmed();
    QString password = ui->inputContrasena->text().trimmed();
    QString nombre = ui->inputNombre->text().trimmed();
    QString profesion = ui->comboProfesion->currentText().trimmed();
    QString sueldoStr = ui->inputSueldo->text().trimmed();

    if (id.isEmpty() || username.isEmpty() || password.isEmpty() ||
        nombre.isEmpty() || profesion.isEmpty() || sueldoStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios.");
        return;
    }

    bool ok;
    double sueldo = sueldoStr.toDouble(&ok);
    if (!ok || sueldo <= 0) {
        QMessageBox::warning(this, "Error", "El sueldo debe ser un número válido y mayor a 0.");
        return;
    }

    // 🔹 Cargar la lista de maestros antes de verificar duplicados
    maestrosManager->loadMaestroUser();

    for (const Usuario &maestro : maestrosManager->getMaestrosUsers()) {
        if (maestro.username == username) {
            QMessageBox::warning(this, "Error", "El usuario ya existe. Elija otro nombre de usuario.");
            return;
        }
    }

    // 🔹 Crear nuevo maestro con todos los datos
    Usuario nuevoMaestro = {id, username, password, nombre, profesion, QString::number(sueldo, 'f', 2)};

    maestrosManager->addMaestro(nuevoMaestro);
    maestrosManager->saveMaestroUser();

    QMessageBox::information(this, "Éxito", "El maestro ha sido agregado exitosamente.");
}



void Registro::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if (!item) {
        qWarning() << "⚠ Error: Item seleccionado es nulo.";
        return;
    }

    QString seleccionado = item->text().trimmed();
    qDebug() << "📌 Maestro seleccionado:" << seleccionado;

    // Buscar el maestro en la lista por su nombre
    bool encontrado = false;
    for (const Usuario &maestro : maestrosManager->getMaestrosUsers()) {
        if (seleccionado == maestro.nombre) {  // Comparación exacta con el nombre
            encontrado = true;

            // Llenar los campos con los datos del maestro seleccionado
            ui->inputID->setText(maestro.id);
            ui->inputUsuario->setText(maestro.username);
            ui->inputContrasena->setText(maestro.password);
            ui->inputNombre->setText(maestro.nombre);
            ui->comboProfesion->setCurrentText(maestro.profesion);
            ui->inputSueldo->setText(QString::number(maestro.sueldo, 'f', 2));

            qDebug() << "✅ Datos del maestro cargados en los campos de edición.";
            break;
        }
    }

    if (!encontrado) {
        qWarning() << "⚠ No se encontró el maestro seleccionado en la lista.";
    }
}

void Registro::cargarListaMaestros() {
    ui->listWidget->clear();  // Limpia la lista antes de agregar elementos
    maestrosManager->loadMaestroUser();  // Carga los datos desde el archivo

    const QList<Usuario> &maestros = maestrosManager->getMaestrosUsers();

    if (maestros.isEmpty()) {
        qWarning() << "🚨 No hay maestros registrados para mostrar.";
        return;
    }

    for (const Usuario &maestro : maestros) {
        ui->listWidget->addItem(maestro.nombre);  // Agrega cada maestro al QListWidget
    }

    qDebug() << "✅ Lista de maestros cargada en listWidget con" << maestros.size() << "elementos.";
}
void Registro::cargarListaClases() {
    ui->listWidgetClases->clear();  // Limpia la lista antes de actualizar

    if (!clasesManager) {
        qWarning() << "⚠ Error: clasesManager no está inicializado.";
        return;
    }

    clasesManager->loadClases();  // Carga los datos desde el archivo

    for (const Clase &clase : clasesManager->getClases()) {
        ui->listWidgetClases->addItem(clase.nombre);  // Agrega cada clase al QListWidget
    }

    qDebug() << "✅ Lista de clases cargada correctamente.";
}



void Registro::on_listWidget_itemDoubleClicked(QListWidgetItem *item) {
    if (!item) {
        qWarning() << "⚠ Error: No se seleccionó ningún maestro.";
        return;
    }

    QString nombreSeleccionado = item->text().trimmed();  // Obtener y limpiar el nombre seleccionado
    qDebug() << "📌 Doble clic en maestro:" << nombreSeleccionado;

    // 🔹 Buscar el maestro en la lista
    bool encontrado = false;
    for (const Usuario &maestro : maestrosManager->getMaestrosUsers()) {
        if (maestro.nombre == nombreSeleccionado) {
            encontrado = true;

            // 🔹 Llenar los campos con la información del maestro
            ui->inputID_2->setText(maestro.id);
            ui->inputNombre_2->setText(maestro.nombre);
            ui->comboProfesion_2->setCurrentText(maestro.profesion);
            ui->inputSueldo_2->setText(QString::number(maestro.sueldo, 'f', 2)); // Formato de 2 decimales
            ui->inputUsuario_2->setText(maestro.username);
            ui->inputContrasena_2->setText(maestro.password);

            // 🔹 Cambiar a la página de modificación del maestro (page_11)
            ui->stackedWidget->setCurrentWidget(ui->page_11);

            qDebug() << "✅ Maestro encontrado y cargado:" << maestro.nombre;
            break;
        }
    }

    if (!encontrado) {
        qWarning() << "⚠ No se encontró el maestro seleccionado en la lista.";
    }
}




void Registro::on_listWidgetEliminarAlumnos_itemDoubleClicked(QListWidgetItem *item)
{
    if (!item) return;  // Evita errores si no hay selección

    QString nombreSeleccionado = item->text().trimmed();  // Obtener el nombre del alumno seleccionado

    // 🔹 Confirmación de eliminación
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Eliminar Alumno",
                                  "¿Estás seguro de que deseas eliminar a " + nombreSeleccionado + "?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 🔹 Buscar y eliminar el alumno de la lista
        for (int i = 0; i < alumnosManager->getAlumnosUsers().size(); ++i) {
            if (alumnosManager->getAlumnosUsers()[i].nombre == nombreSeleccionado) {
                alumnosManager->eliminarAlumno(nombreSeleccionado);  // Elimina del archivo y lista
                cargarListaAlumnosEliminar();  // Recarga la lista de alumnos eliminables
                qDebug() << "✅ Alumno eliminado:" << nombreSeleccionado;
                return;
            }
        }

        QMessageBox::warning(this, "Error", "No se encontró el alumno seleccionado.");
    }
}


void Registro::on_AggButton_clicked()
{
    QString cuenta = ui->inputID_3->text().trimmed();
    QString nombre = ui->inputNombre_3->text().trimmed();
    QString carrera = ui->comboCarrera->currentText().trimmed();  // QComboBox
    QString clases = ui->comboClases->currentText().trimmed();    // QComboBox
    QString username = ui->inputUsuario_3->text().trimmed();
    QString password = ui->inputContrasena_3->text().trimmed();

    // 🔹 Validar que todos los campos estén llenos
    if (cuenta.isEmpty() || nombre.isEmpty() || carrera.isEmpty() ||
        clases.isEmpty() || username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios.");
        return;
    }

    // 🔹 Verificar que `alumnosManager` está inicializado correctamente
    if (!alumnosManager) {
        qWarning() << "⚠ Error: `alumnosManager` no ha sido inicializado.";
        return;
    }

    // 🔹 Cargar la lista de alumnos antes de verificar duplicados
    alumnosManager->loadAlumnosUser();

    for (const Usuario &alumno : alumnosManager->getAlumnosUsers()) {
        if (alumno.username == username) {
            QMessageBox::warning(this, "Error", "El usuario ya existe. Elija otro nombre de usuario.");
            return;
        }
    }

    // 🔹 Crear nuevo alumno con todos los datos
    Usuario nuevoAlumno = {cuenta, username, password, nombre, "Alumno", "", 0.0, carrera, clases};


    alumnosManager->addAlumno(nuevoAlumno);
    alumnosManager->saveAlumnosUser();

    QMessageBox::information(this, "Éxito", "El alumno ha sido agregado exitosamente.");

    // 🔹 Recargar la lista de alumnos en la interfaz
    cargarListaAlumnos();

}


void Registro::on_listWidgetAlumnos_itemDoubleClicked(QListWidgetItem *item)
{
    if (!item) {
        qWarning() << "⚠ Error: No se seleccionó ningún alumno.";
        return;
    }

    QString nombreSeleccionado = item->text().trimmed();  // Obtener y limpiar el nombre seleccionado
    qDebug() << "📌 Doble clic en alumno:" << nombreSeleccionado;

    // 🔹 Buscar el alumno en la lista
    bool encontrado = false;
    for (const Usuario &alumno : alumnosManager->getAlumnosUsers()) {
        if (alumno.nombre == nombreSeleccionado) {
            encontrado = true;

            // 🔹 Llenar los campos con la información del alumno
            ui->inputID_4->setText(alumno.id);
            ui->inputNombre_4->setText(alumno.nombre);
            ui->comboCarrera->setCurrentText(alumno.carrera);  // QComboBox
            ui->comboClases->setCurrentText(alumno.clases);    // QComboBox
            ui->inputUsuario_4->setText(alumno.username);
            ui->inputContrasena_4->setText(alumno.password);

            // 🔹 Cambiar a la página de modificación del alumno (page_Alumno)
            ui->stackedWidget->setCurrentWidget(ui->page_6);

            qDebug() << "✅ Alumno encontrado y cargado:" << alumno.nombre;
            break;
        }
    }

    if (!encontrado) {
        qWarning() << "⚠ No se encontró el alumno seleccionado en la lista.";
    }


}


void Registro::on_pushButton_4_clicked() {
    // 🔹 Obtener los datos modificados del formulario
    QString cuenta = ui->inputID_4->text().trimmed();
    QString nombre = ui->inputNombre_4->text().trimmed();
    QString carrera = ui->comboCarrera->currentText().trimmed();  // QComboBox
    QString clases = ui->comboClases->currentText().trimmed();    // QComboBox
    QString username = ui->inputUsuario_4->text().trimmed();
    QString password = ui->inputContrasena_4->text().trimmed();

    // 🔹 Verificar que el usuario ingresó datos válidos
    if (cuenta.isEmpty() || nombre.isEmpty() || carrera.isEmpty() || username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos deben estar llenos.");
        return;
    }

    // 🔹 Crear el objeto `Usuario` con la información modificada
    Usuario alumnoModificado = {cuenta, username, password, nombre, "Alumno", "", 0.0, carrera, clases};

    // 🔹 Buscar al alumno en la lista
    bool encontrado = false;
    for (Usuario &alumno : alumnosManager->getAlumnosUsers()) {
        if (alumno.id == cuenta) { // Se busca por ID
            alumno = alumnoModificado; // Se actualizan los datos
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        QMessageBox::warning(this, "Error", "No se encontró al alumno en la lista.");
        return;
    }

    // 🔹 Guardar la lista actualizada en el archivo
    alumnosManager->saveAlumnosUser();

    // 🔹 Mostrar mensaje de éxito
    QMessageBox::information(this, "Éxito", "Los datos del alumno han sido modificados correctamente.");

    // // 🔹 Volver a la pantalla principal de alumnos
    // ui->stackedWidget->setCurrentWidget(ui->page_);
}




void Registro::on_listWidgetClases_itemDoubleClicked(QListWidgetItem *item)
{

}


void Registro::on_AgregarButton_2_clicked()
{
    // 🔹 Capturar valores de los campos
    QString id = ui->inputID_5->text().trimmed();
    QString nombre = ui->inputNombre_5->text().trimmed();
    QString hora = ui->comboBoxHora->currentText().trimmed();  // Ahora usa QComboBox
    QString periodo = ui->comboBoxPeriodo->currentText().trimmed();  // Ahora usa QComboBox

    // 🔹 Capturar valores numéricos desde QComboBox
    int uv = ui->comboBoxUV->currentText().toInt();
    int semestre = ui->comboBoxSemestre->currentText().toInt();
    int año = ui->comboBoxAnio->currentText().toInt();

    // 🔹 Debugging: Mostrar los valores capturados
    qDebug() << "Valores capturados:";
    qDebug() << "ID:" << id << ", Nombre:" << nombre << ", Hora:" << hora
             << ", UV:" << uv << ", Semestre:" << semestre
             << ", Periodo:" << periodo << ", Anio:" << año;

    // 🔹 Validar que los campos de texto no estén vacíos
    if (id.isEmpty() || nombre.isEmpty() || hora.isEmpty() || periodo.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios.");
        return;
    }

    // 🔹 Validar que los valores numéricos sean correctos
    if (uv <= 0 || semestre <= 0 || año <= 0) {
        QMessageBox::warning(this, "Error", "UV, Semestre y Año deben ser valores válidos y mayores a 0.");
        return;
    }

    // 🔹 Verificar que `clasesManager` esté inicializado
    if (!clasesManager) {
        qWarning() << "⚠ Error: `clasesManager` no ha sido inicializado.";
        return;
    }

    // 🔹 Crear objeto Clase
    Clase nuevaClase = {id, nombre, hora, uv, semestre, periodo, año};

    // 🔹 Agregar la nueva clase
    clasesManager->addClase(nuevaClase);
    clasesManager->saveClases();  // Guardar en el archivo

    // 🔹 Mostrar mensaje de éxito
    QMessageBox::information(this, "Éxito", "Clase agregada correctamente.");

    // 🔹 Limpiar los campos después de agregar la clase
    ui->inputID_5->clear();
    ui->inputNombre_5->clear();
    ui->comboBoxHora->setCurrentIndex(0);  // Reset a la primera opción
    ui->comboBoxUV->setCurrentIndex(0);
    ui->comboBoxSemestre->setCurrentIndex(0);
    ui->comboBoxPeriodo->setCurrentIndex(0);
    ui->comboBoxAnio->setCurrentIndex(0);

    // 🔹 Actualizar lista de clases en la UI
    cargarListaClases();
}


