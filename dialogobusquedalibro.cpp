#include "dialogobusquedalibro.h"
#include "ui_dialogobusquedalibro.h"
#include "databasemanager.h"

DialogoBusquedaLibro::DialogoBusquedaLibro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogoBusquedaLibro)
{
    ui->setupUi(this);

    // Conexiones
    connect(ui->btnBuscar, &QPushButton::clicked, this, &DialogoBusquedaLibro::buscarLibros);
    connect(ui->btnCancelar, &QPushButton::clicked, this, &DialogoBusquedaLibro::cerrarVentana);

    // Configurar la tabla
    ui->tableWidgetResultados->setColumnCount(7);
    QStringList headers = {"ISBN", "Título", "Autor", "Editorial", "País", "Año", "Disponible"};
    ui->tableWidgetResultados->setHorizontalHeaderLabels(headers);
}

DialogoBusquedaLibro::~DialogoBusquedaLibro()
{
    delete ui;
}

void DialogoBusquedaLibro::buscarLibros()
{
    QString titulo = ui->lineEditTitulo->text();
    QString autor = ui->lineEditAutor->text();
    QString editorial = ui->lineEditEditorial->text();
    QString palabrasClave = ui->lineEditPalabrasClave->text();

    QList<Libro> libros = DatabaseManager::getInstance().buscarLibros(titulo, autor, editorial, palabrasClave);
    cargarResultados(libros);
}

void DialogoBusquedaLibro::cerrarVentana()
{
    close();
}

void DialogoBusquedaLibro::cargarResultados(const QList<Libro> &libros)
{
    ui->tableWidgetResultados->setRowCount(0);
    for (const Libro& libro : libros) {
        int row = ui->tableWidgetResultados->rowCount();
        ui->tableWidgetResultados->insertRow(row);

        ui->tableWidgetResultados->setItem(row, 0, new QTableWidgetItem(libro.isbn()));
        ui->tableWidgetResultados->setItem(row, 1, new QTableWidgetItem(libro.titulo()));
        ui->tableWidgetResultados->setItem(row, 2, new QTableWidgetItem(libro.autor()));
        ui->tableWidgetResultados->setItem(row, 3, new QTableWidgetItem(libro.editorial()));
        ui->tableWidgetResultados->setItem(row, 4, new QTableWidgetItem(libro.pais()));
        ui->tableWidgetResultados->setItem(row, 5, new QTableWidgetItem(QString::number(libro.anio())));
        ui->tableWidgetResultados->setItem(row, 6, new QTableWidgetItem(libro.disponible() ? "Sí" : "No"));
    }
}

