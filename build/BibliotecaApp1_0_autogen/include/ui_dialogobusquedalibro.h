/********************************************************************************
** Form generated from reading UI file 'dialogobusquedalibro.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGOBUSQUEDALIBRO_H
#define UI_DIALOGOBUSQUEDALIBRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogoBusquedaLibro
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTituloPrincipal;
    QGridLayout *gridLayout;
    QLabel *labelTitulo;
    QLineEdit *lineEditTitulo;
    QLabel *labelAutor;
    QLineEdit *lineEditAutor;
    QLabel *labelEditorial;
    QLineEdit *lineEditEditorial;
    QLabel *labelPalabrasClave;
    QLineEdit *lineEditPalabrasClave;
    QHBoxLayout *horizontalLayoutBotones;
    QPushButton *btnBuscar;
    QPushButton *btnCancelar;
    QTableWidget *tableWidgetResultados;

    void setupUi(QDialog *DialogoBusquedaLibro)
    {
        if (DialogoBusquedaLibro->objectName().isEmpty())
            DialogoBusquedaLibro->setObjectName("DialogoBusquedaLibro");
        verticalLayout = new QVBoxLayout(DialogoBusquedaLibro);
        verticalLayout->setObjectName("verticalLayout");
        labelTituloPrincipal = new QLabel(DialogoBusquedaLibro);
        labelTituloPrincipal->setObjectName("labelTituloPrincipal");
        labelTituloPrincipal->setAlignment(Qt::AlignCenter);
        labelTituloPrincipal->setStyleSheet(QString::fromUtf8("font-weight: bold; font-size: 16pt;"));

        verticalLayout->addWidget(labelTituloPrincipal);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        labelTitulo = new QLabel(DialogoBusquedaLibro);
        labelTitulo->setObjectName("labelTitulo");

        gridLayout->addWidget(labelTitulo, 0, 0, 1, 1);

        lineEditTitulo = new QLineEdit(DialogoBusquedaLibro);
        lineEditTitulo->setObjectName("lineEditTitulo");

        gridLayout->addWidget(lineEditTitulo, 0, 1, 1, 1);

        labelAutor = new QLabel(DialogoBusquedaLibro);
        labelAutor->setObjectName("labelAutor");

        gridLayout->addWidget(labelAutor, 1, 0, 1, 1);

        lineEditAutor = new QLineEdit(DialogoBusquedaLibro);
        lineEditAutor->setObjectName("lineEditAutor");

        gridLayout->addWidget(lineEditAutor, 1, 1, 1, 1);

        labelEditorial = new QLabel(DialogoBusquedaLibro);
        labelEditorial->setObjectName("labelEditorial");

        gridLayout->addWidget(labelEditorial, 2, 0, 1, 1);

        lineEditEditorial = new QLineEdit(DialogoBusquedaLibro);
        lineEditEditorial->setObjectName("lineEditEditorial");

        gridLayout->addWidget(lineEditEditorial, 2, 1, 1, 1);

        labelPalabrasClave = new QLabel(DialogoBusquedaLibro);
        labelPalabrasClave->setObjectName("labelPalabrasClave");

        gridLayout->addWidget(labelPalabrasClave, 3, 0, 1, 1);

        lineEditPalabrasClave = new QLineEdit(DialogoBusquedaLibro);
        lineEditPalabrasClave->setObjectName("lineEditPalabrasClave");

        gridLayout->addWidget(lineEditPalabrasClave, 3, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayoutBotones = new QHBoxLayout();
        horizontalLayoutBotones->setObjectName("horizontalLayoutBotones");
        btnBuscar = new QPushButton(DialogoBusquedaLibro);
        btnBuscar->setObjectName("btnBuscar");

        horizontalLayoutBotones->addWidget(btnBuscar);

        btnCancelar = new QPushButton(DialogoBusquedaLibro);
        btnCancelar->setObjectName("btnCancelar");

        horizontalLayoutBotones->addWidget(btnCancelar);


        verticalLayout->addLayout(horizontalLayoutBotones);

        tableWidgetResultados = new QTableWidget(DialogoBusquedaLibro);
        if (tableWidgetResultados->columnCount() < 7)
            tableWidgetResultados->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetResultados->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetResultados->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetResultados->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetResultados->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetResultados->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetResultados->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetResultados->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidgetResultados->setObjectName("tableWidgetResultados");

        verticalLayout->addWidget(tableWidgetResultados);


        retranslateUi(DialogoBusquedaLibro);

        QMetaObject::connectSlotsByName(DialogoBusquedaLibro);
    } // setupUi

    void retranslateUi(QDialog *DialogoBusquedaLibro)
    {
        DialogoBusquedaLibro->setWindowTitle(QCoreApplication::translate("DialogoBusquedaLibro", "Buscar Libros", nullptr));
        labelTituloPrincipal->setText(QCoreApplication::translate("DialogoBusquedaLibro", "Buscar Libros", nullptr));
        labelTitulo->setText(QCoreApplication::translate("DialogoBusquedaLibro", "T\303\255tulo:", nullptr));
        labelAutor->setText(QCoreApplication::translate("DialogoBusquedaLibro", "Autor:", nullptr));
        labelEditorial->setText(QCoreApplication::translate("DialogoBusquedaLibro", "Editorial:", nullptr));
        labelPalabrasClave->setText(QCoreApplication::translate("DialogoBusquedaLibro", "Palabras clave:", nullptr));
        btnBuscar->setText(QCoreApplication::translate("DialogoBusquedaLibro", "Buscar", nullptr));
        btnCancelar->setText(QCoreApplication::translate("DialogoBusquedaLibro", "Cancelar", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetResultados->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DialogoBusquedaLibro", "ISBN", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetResultados->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DialogoBusquedaLibro", "T\303\255tulo", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetResultados->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DialogoBusquedaLibro", "Autor", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetResultados->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DialogoBusquedaLibro", "Editorial", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetResultados->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("DialogoBusquedaLibro", "Pa\303\255s", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetResultados->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("DialogoBusquedaLibro", "A\303\261o", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetResultados->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("DialogoBusquedaLibro", "Disponible", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogoBusquedaLibro: public Ui_DialogoBusquedaLibro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGOBUSQUEDALIBRO_H
