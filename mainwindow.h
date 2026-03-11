#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "dialogolibro.h"
#include "databasemanager.h"
#include "dialogousuario.h"
#include "dialogoprestamo.h"
#include "dialogobusquedalibro.h"

class Libro;       // Añadido porque se usa en actualizarTablaLibros()
class Usuario;     // Añadido porque se usa en actualizarTablaUsuarios()
class Prestamo;    // Añadido porque se usa en actualizarTablaPrestamos()

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void mostrarMenuContextual(const QPoint &pos);

    void on_btnAgregarLibro_clicked();
    void on_btnEditarLibro_clicked();
    void eliminarLibro();
    void on_btnAgregarUsuario_clicked();
    void on_btnModificarUsuario_clicked();
    void on_btnEliminarUsuario_clicked();
    void exportarUsuarios();
    void on_btnRealizarPrestamo_clicked();
    void on_btnRegistrarDevolucion_clicked();
    void on_tableWidgetUsuarios_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);


protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;
    DatabaseManager& m_dbManager;
    
    // Métodos privados
    void abrirDialogoBusquedaLibro();
    void configurarTablaLibros();
    void configurarTablaUsuarios();
    void actualizarTablaLibros();    // Necesita Libro
    void actualizarTablaUsuarios();  // Necesita Usuario
    void configurarTablaPrestamos();
    void actualizarTablaPrestamos(); // Necesita Prestamo
    void editarLibro(int row);       // Necesita Libro
};

#endif // MAINWINDOW_H
