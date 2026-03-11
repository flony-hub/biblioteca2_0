#include "mainwindow.h"
#include "ui_mainwindow.h"

// Includes completos para las clases que usas
#include "dialogolibro.h"
#include "dialogousuario.h"
#include "dialogoprestamo.h"
#include "dialogobusquedalibro.h"
#include "databasemanager.h"
#include "libro.h"
#include "usuario.h"
#include "prestamo.h"
#include <QMessageBox>
#include <QMenu>
#include <QPaintEvent>
#include <QPainter>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_dbManager(DatabaseManager::getInstance())
{
    ui->setupUi(this);

    // Inicialización de la base de datos
    if (!m_dbManager.openDatabase()) {
        QMessageBox::critical(this, "Error", "No se pudo abrir la base de datos");
        return;
    }

    if (!m_dbManager.createTables()) {
        QMessageBox::warning(this, "Advertencia", "Error al crear tablas");
    }

    // Configuración inicial
    configurarTablaLibros();
    configurarTablaUsuarios();
    configurarTablaPrestamos();
    actualizarTablaLibros();
    actualizarTablaUsuarios(); 
    actualizarTablaPrestamos();

    // Conexiones:
    connect(ui->tableWidgetLibros, &QTableWidget::cellDoubleClicked, [this](int row, int /*column*/){ editarLibro(row); });
    connect(ui->tableWidgetLibros, &QTableWidget::customContextMenuRequested, this, &MainWindow::mostrarMenuContextual);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::eliminarLibro);
    connect(ui->btnAgregarUsuario, &QPushButton::clicked, this, &MainWindow::on_btnAgregarUsuario_clicked);
    connect(ui->btnModificarUsuario, &QPushButton::clicked, this, &MainWindow::on_btnModificarUsuario_clicked);
    connect(ui->btnEliminarUsuario, &QPushButton::clicked, this, &MainWindow::on_btnEliminarUsuario_clicked);
    connect(ui->btnRegistrarDevolucion, &QPushButton::clicked, this, &MainWindow::on_btnRegistrarDevolucion_clicked);
    connect(ui->btnRealizarPrestamo, &QPushButton::clicked, this, &MainWindow::on_btnRealizarPrestamo_clicked);
    connect(ui->btnExportarUsuarios, &QPushButton::clicked, this, &MainWindow::exportarUsuarios);
    connect(ui->btnBuscarLibro, &QPushButton::clicked, this,[this](){abrirDialogoBusquedaLibro();});



}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    
    QPainter painter(this);
    painter.setOpacity(0.15); // Más transparente (rango 0.1 a 0.3)
    
    QPixmap watermark(":/images/logo_marca_agua.png");
    // Escala al 60% del tamaño menor (ancho o alto)
    int size = qMin(width(), height()) * 0.6;
    watermark = watermark.scaled(size, size, Qt::KeepAspectRatio);
    
    // Centrado
    int x = (width() - watermark.width()) / 2;
    int y = (height() - watermark.height()) / 2;
    painter.drawPixmap(x, y, watermark);
}

//---------------------------------------------------------------
//---------------------------------------------------------------
//libro


void MainWindow::configurarTablaLibros()
{
    ui->tableWidgetLibros->setColumnCount(5);
    ui->tableWidgetLibros->setHorizontalHeaderLabels({"ISBN", "Título", "Autor", "Año", "País"});
    ui->tableWidgetLibros->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetLibros->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetLibros->setContextMenuPolicy(Qt::CustomContextMenu);
}

void MainWindow::actualizarTablaLibros()
{
    ui->tableWidgetLibros->setRowCount(0);
    QList<Libro> libros = m_dbManager.obtenerTodosLibros();

    for (const Libro& libro : libros) {
        int row = ui->tableWidgetLibros->rowCount();
        ui->tableWidgetLibros->insertRow(row);

        ui->tableWidgetLibros->setItem(row, 0, new QTableWidgetItem(libro.isbn()));
        ui->tableWidgetLibros->setItem(row, 1, new QTableWidgetItem(libro.titulo()));
        ui->tableWidgetLibros->setItem(row, 2, new QTableWidgetItem(libro.autor()));
        ui->tableWidgetLibros->setItem(row, 3, new QTableWidgetItem(QString::number(libro.anio())));
        ui->tableWidgetLibros->setItem(row, 4, new QTableWidgetItem(libro.pais()));
    }
}

void MainWindow::on_btnAgregarLibro_clicked()
{
    DialogoLibro dialogo(this, DialogoLibro::Nuevo);
    if (dialogo.exec() == QDialog::Accepted) {
        Libro libro = dialogo.getLibro();
        if (m_dbManager.agregarLibro(libro)) {
            actualizarTablaLibros();
            QMessageBox::information(this, "Éxito", "Libro agregado correctamente");
        } else {
            QMessageBox::critical(this, "Error", "No se pudo agregar el libro");
        }
    }
}

void MainWindow::on_btnEditarLibro_clicked()
{
    // Implementación del modo búsqueda para edición
    DialogoLibro dialogoBusqueda(this, DialogoLibro::Buscar);
    if (dialogoBusqueda.exec() == QDialog::Accepted) {
        QString isbn = dialogoBusqueda.getIsbnBusqueda();
        if (!isbn.isEmpty()) {
            Libro libroActual = m_dbManager.obtenerLibro(isbn);
            if (libroActual.isbn().isEmpty()) {
                QMessageBox::warning(this, "Error", "No se encontró el libro con ISBN: " + isbn);
                return;
            }
            // Modo edición con los datos del libro
            DialogoLibro dialogoEdicion(this, DialogoLibro::Editar, &libroActual);
            if (dialogoEdicion.exec() == QDialog::Accepted) {
                Libro libroEditado = dialogoEdicion.getLibro();
                if (m_dbManager.actualizarLibro(libroEditado)) {
                    actualizarTablaLibros();
                    QMessageBox::information(this, "Éxito", "Libro actualizado correctamente");
                } else {
                    QMessageBox::critical(this, "Error", "Error al actualizar el libro");
                }
            }
        }
    }
}

void MainWindow::eliminarLibro()
{
    // 1. Diálogo para ingresar ISBN
    DialogoLibro dialogoBuscar(this, DialogoLibro::Buscar);
    if (dialogoBuscar.exec() != QDialog::Accepted)
        return;

    QString isbn = dialogoBuscar.getIsbnBusqueda();

    // 2. Obtener el libro
    Libro libro = m_dbManager.obtenerLibro(isbn);
    if (libro.isbn().isEmpty()) {
        QMessageBox::warning(this, "No encontrado", "No se encontró ningún libro con ese ISBN.");
        return;
    }

    // 3. Mostrar datos y confirmar eliminación
    QString detalles = QString("Título: %1\nAutor: %2\nEditorial: %3\nAño: %4\nPaís: %5\nISBN: %6")
                           .arg(libro.titulo())
                           .arg(libro.autor())
                           .arg(libro.editorial())
                           .arg(libro.anio())
                           .arg(libro.pais())
                           .arg(libro.isbn());

    int respuesta = QMessageBox::question(this, "Confirmar eliminación",
                                          "¿Está seguro de eliminar el siguiente libro?\n\n" + detalles,
                                          QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::Yes) {
        if (m_dbManager.eliminarLibro(libro.isbn())) {
            QMessageBox::information(this, "Éxito", "El libro fue eliminado correctamente.");
            actualizarTablaLibros(); // Asegurate de tener esta función
        } else {
            QMessageBox::critical(this, "Error", "No se pudo eliminar el libro.");
        }
    }
}


void MainWindow::editarLibro(int row)
{
    if (row < 0) return;

    QString isbn = ui->tableWidgetLibros->item(row, 0)->text();
    Libro libroActual = m_dbManager.obtenerLibro(isbn);
    if (libroActual.isbn().isEmpty()) {
        QMessageBox::warning(this, "Error", "No se pudo cargar el libro seleccionado");
        return;
    }
    DialogoLibro dialogo(this, DialogoLibro::Editar, &libroActual);
    if (dialogo.exec() == QDialog::Accepted) {
        Libro libroEditado = dialogo.getLibro();
        if (m_dbManager.actualizarLibro(libroEditado)) {
            actualizarTablaLibros();
            QMessageBox::information(this, "Éxito", "Libro actualizado correctamente");
        } else {
            QMessageBox::critical(this, "Error", "No se pudo actualizar el libro");
        }
    }
}

void MainWindow::mostrarMenuContextual(const QPoint &pos)
{
    QTableWidgetItem* item = ui->tableWidgetLibros->itemAt(pos);
    if (!item) return;

    QMenu menu;
    QAction* editarAction = menu.addAction("Editar libro");
    QAction* eliminarAction = menu.addAction("Eliminar libro");

    QAction* selectedAction = menu.exec(ui->tableWidgetLibros->viewport()->mapToGlobal(pos));
    if (selectedAction == editarAction) {
        editarLibro(item->row());
    } else if (selectedAction == eliminarAction) {
        eliminarLibro();
    }
}

void MainWindow::on_tableWidgetUsuarios_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    QMessageBox::information(this, "Cambio de celda",
                             QString("Celda actual: (%1, %2)\nCelda previa: (%3, %4)")
                                 .arg(currentRow).arg(currentColumn)
                                 .arg(previousRow).arg(previousColumn));
}


void MainWindow::abrirDialogoBusquedaLibro()
{
    DialogoBusquedaLibro dialogo(this);
    if (dialogo.exec() == QDialog::Accepted) {
        QString titulo = dialogo.findChild<QLineEdit*>("lineEditTitulo")->text().trimmed();
        QString autor = dialogo.findChild<QLineEdit*>("lineEditAutor")->text().trimmed();
        QString editorial = dialogo.findChild<QLineEdit*>("lineEditEditorial")->text().trimmed();
        QString palabrasClave = dialogo.findChild<QLineEdit*>("lineEditPalabrasClave")->text().trimmed();

        QList<Libro> resultados = m_dbManager.buscarLibros(titulo, autor, editorial, palabrasClave);

        QTableWidget* tabla = dialogo.findChild<QTableWidget*>("tableWidgetResultados");
        tabla->setRowCount(0);

        for (const Libro& libro : resultados) {
            int row = tabla->rowCount();
            tabla->insertRow(row);

            tabla->setItem(row, 0, new QTableWidgetItem(libro.isbn()));
            tabla->setItem(row, 1, new QTableWidgetItem(libro.titulo()));
            tabla->setItem(row, 2, new QTableWidgetItem(libro.autor()));
            tabla->setItem(row, 3, new QTableWidgetItem(libro.editorial()));
            tabla->setItem(row, 4, new QTableWidgetItem(libro.pais()));
            tabla->setItem(row, 5, new QTableWidgetItem(QString::number(libro.anio())));
            tabla->setItem(row, 6, new QTableWidgetItem(libro.disponible() ? "Sí" : "No"));
        }

        if (resultados.isEmpty()) {
            QMessageBox::information(this, "Sin resultados", "No se encontraron libros que coincidan con los criterios.");
        }
    }
}

//arranca Usuario
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------

void MainWindow::configurarTablaUsuarios()
{
    ui->tableWidgetUsuarios->setColumnCount(4);
    ui->tableWidgetUsuarios->setHorizontalHeaderLabels({"DNI", "Nombre", "Email", "Teléfono", "Domicilio"});
    ui->tableWidgetUsuarios->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetUsuarios->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::actualizarTablaUsuarios()
{
    // Limpiar la tabla
    ui->tableWidgetUsuarios->setRowCount(0);

    // Obtener lista de usuarios desde la base de datos
    QList<Usuario> usuarios = m_dbManager.obtenerTodosUsuarios();

    for (const Usuario& usuario : usuarios) {
        int row = ui->tableWidgetUsuarios->rowCount();
        ui->tableWidgetUsuarios->insertRow(row);

        ui->tableWidgetUsuarios->setItem(row, 0, new QTableWidgetItem(usuario.dni()));
        ui->tableWidgetUsuarios->setItem(row, 1, new QTableWidgetItem(usuario.nombre()));
        ui->tableWidgetUsuarios->setItem(row, 2, new QTableWidgetItem(usuario.email()));
        ui->tableWidgetUsuarios->setItem(row, 3, new QTableWidgetItem(usuario.telefono()));
        ui->tableWidgetUsuarios->setItem(row, 4, new QTableWidgetItem(usuario.domicilio()));
    }
}

void MainWindow::on_btnAgregarUsuario_clicked()
{
    DialogoUsuario dialogo(this);
    if (dialogo.exec() == QDialog::Accepted) {
        // No necesitamos obtener el usuario, el diálogo ya lo guardó
        actualizarTablaUsuarios();
        QMessageBox::information(this, "Éxito", "Operación completada correctamente");
    }
}

void MainWindow::on_btnModificarUsuario_clicked()
{
    int row = ui->tableWidgetUsuarios->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un usuario para modificar");
        return;
    }

    QString dni = ui->tableWidgetUsuarios->item(row, 0)->text();
    
    // Crear diálogo y establecer el DNI directamente
    DialogoUsuario dialogo(this);
    dialogo.setWindowTitle("Modificar Usuario: " + dni);
    
    // Buscar automáticamente al usuario
    QLineEdit* dniEdit = dialogo.findChild<QLineEdit*>("lineEditDni");
    if (dniEdit) {
        dniEdit->setText(dni);
        QPushButton* btnBuscar = dialogo.findChild<QPushButton*>("btnBuscar");
        if (btnBuscar) {
            btnBuscar->click(); // Disparar la búsqueda automáticamente
        }
    }

    if (dialogo.exec() == QDialog::Accepted) {
        actualizarTablaUsuarios();
        QMessageBox::information(this, "Éxito", "Usuario actualizado correctamente");
    }
}


void MainWindow::on_btnEliminarUsuario_clicked()
{
    int row = ui->tableWidgetUsuarios->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un usuario para eliminar");
        return;
    }

    QString dni = ui->tableWidgetUsuarios->item(row, 0)->text();
    QMessageBox::StandardButton respuesta = QMessageBox::question(this, "Confirmar eliminación",
                                                                  QString("¿Está seguro de que desea eliminar al usuario con DNI %1?").arg(dni),
                                                                  QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::Yes) {
        if (m_dbManager.eliminarUsuario(dni)) {
            actualizarTablaUsuarios();
            QMessageBox::information(this, "Éxito", "Usuario eliminado correctamente");
        } else {
            QMessageBox::critical(this, "Error", "No se pudo eliminar al usuario");
        }
    }
}

void MainWindow::exportarUsuarios()
{
    QList<Usuario> usuarios = DatabaseManager::getInstance().obtenerTodosUsuarios();

    if (usuarios.isEmpty()) {
        QMessageBox::information(this, "Exportar", "No hay usuarios para exportar.");
        return;
    }

    QString nombreArchivo = QFileDialog::getSaveFileName(this, "Guardar como CSV", "", "Archivos CSV (*.csv)");

    if (nombreArchivo.isEmpty())
        return;

    QFile archivo(nombreArchivo);
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para escribir.");
        return;
    }

    QTextStream out(&archivo);
    out << "DNI,Nombre,Email,Teléfono, Domicilio\n";

    for (const Usuario& u : usuarios) {
        out << "\"" << u.dni() << "\","
            << "\"" << u.nombre().replace("\"", "\"\"") << "\","
            << "\"" << u.email().replace("\"", "\"\"") << "\","
            << "\"" << u.telefono().replace("\"", "\"\"") << "\"\n"
            << "\"" << u.domicilio().replace("\"", "\"\"") << "\"\n";
    }

    archivo.close();
    QMessageBox::information(this, "Éxito", "Usuarios exportados correctamente.");
}

// arranca prestamo
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
// arranca prestamo
void MainWindow::on_btnRealizarPrestamo_clicked()
{
    DialogoPrestamo dialogo(this);
    if (dialogo.exec() == QDialog::Accepted) {
        QString isbn = dialogo.getIsbnLibro();
        QString dni = dialogo.getDniUsuario();
        QDate fechaPrestamo = dialogo.getFechaPrestamo();
        QDate fechaDevolucion = dialogo.getFechaDevolucion();

        // Validar ISBN y DNI (ejemplo básico, puedes agregar más validaciones)
        if (isbn.isEmpty() || dni.isEmpty()) {
            QMessageBox::warning(this, "Error", "ISBN y DNI son obligatorios.");
            return;
        }

        // Validar que el libro exista y esté disponible (ejemplo)
        if (!DatabaseManager::getInstance().libroExiste(isbn)) {
            QMessageBox::warning(this, "Error", "El libro con ISBN " + isbn + " no existe.");
            return;
        }

        if (!DatabaseManager::getInstance().libroDisponible(isbn)) {
            QMessageBox::warning(this, "Error", "El libro con ISBN " + isbn + " no está disponible.");
            return;
        }

        // Validar que el usuario exista
        if (!DatabaseManager::getInstance().usuarioExiste(dni)) {
            QMessageBox::warning(this, "Error", "El usuario con DNI " + dni + " no existe.");
            return;
        }

        // Realizar el préstamo
        if (DatabaseManager::getInstance().realizarPrestamo(isbn, dni, fechaPrestamo, fechaDevolucion)) {
            QMessageBox::information(this, "Éxito", "Préstamo registrado correctamente");
            actualizarTablaPrestamos();
            actualizarTablaLibros(); // Para actualizar disponibilidad
        } else {
            QMessageBox::critical(this, "Error", "No se pudo registrar el préstamo");
        }
    }
}


void MainWindow::on_btnRegistrarDevolucion_clicked()
{
    int row = ui->tableWidgetPrestamos->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Advertencia", 
                           "Seleccione un préstamo para registrar devolución");
        return;
    }

    int idPrestamo = ui->tableWidgetPrestamos->item(row, 0)->text().toInt();
    QDate fechaDevolucion = QDate::currentDate();

    if (DatabaseManager::getInstance().finalizarPrestamo(idPrestamo, fechaDevolucion)) {
        QMessageBox::information(this, "Éxito", "Devolución registrada correctamente");
        actualizarTablaPrestamos();
        actualizarTablaLibros();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo registrar la devolución");
    }
}
void MainWindow::configurarTablaPrestamos()
{
    ui->tableWidgetPrestamos->setColumnCount(5);
    ui->tableWidgetPrestamos->setHorizontalHeaderLabels(
        {"ID", "ISBN Libro", "DNI Usuario", "Fecha Préstamo", "Fecha Devolución"});
    ui->tableWidgetPrestamos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetPrestamos->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::actualizarTablaPrestamos()
{
    ui->tableWidgetPrestamos->setRowCount(0);
    QList<Prestamo> prestamos = DatabaseManager::getInstance().obtenerTodosPrestamos();

    for (const Prestamo& prestamo : prestamos) {
        int row = ui->tableWidgetPrestamos->rowCount();
        ui->tableWidgetPrestamos->insertRow(row);

        ui->tableWidgetPrestamos->setItem(row, 0, new QTableWidgetItem(QString::number(prestamo.id())));
        ui->tableWidgetPrestamos->setItem(row, 1, new QTableWidgetItem(prestamo.isbnLibro()));
        ui->tableWidgetPrestamos->setItem(row, 2, new QTableWidgetItem(prestamo.dniUsuario()));
        ui->tableWidgetPrestamos->setItem(row, 3, new QTableWidgetItem(prestamo.fechaPrestamo().toString("yyyy-MM-dd")));
        ui->tableWidgetPrestamos->setItem(row, 4, new QTableWidgetItem(
            prestamo.fechaDevolucion().isValid() ? 
            prestamo.fechaDevolucion().toString("yyyy-MM-dd") : "Pendiente"));
    }
}
