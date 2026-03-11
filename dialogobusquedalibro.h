#ifndef DIALOGOBUSQUEDALIBRO_H
#define DIALOGOBUSQUEDALIBRO_H

#include <QDialog>
#include "databasemanager.h"


namespace Ui {
class DialogoBusquedaLibro;
}

class DialogoBusquedaLibro : public QDialog
{
    Q_OBJECT

public:
    explicit DialogoBusquedaLibro(QWidget *parent = nullptr);
    ~DialogoBusquedaLibro();

private:
    Ui::DialogoBusquedaLibro *ui;
    void buscarLibros();
    void cerrarVentana();
    void cargarResultados(const QList<Libro>& libros);
};

#endif // DIALOGOBUSQUEDALIBRO_H

