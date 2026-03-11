/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tabLibros;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidgetLibros;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAgregarLibro;
    QPushButton *btnEditarLibro;
    QPushButton *pushButton;
    QPushButton *btnBuscarLibro;
    QSpacerItem *horizontalSpacer;
    QWidget *tabUsuarios;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *tableWidgetUsuarios;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnAgregarUsuario;
    QPushButton *btnModificarUsuario;
    QPushButton *btnEliminarUsuario;
    QPushButton *btnExportarUsuarios;
    QWidget *tabPrestamos;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tableWidgetPrestamos;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnRealizarPrestamo;
    QPushButton *btnRegistrarDevolucion;
    QMenuBar *menubar;
    QMenu *menuArchivo;
    QMenu *menuAyuda;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabLibros = new QWidget();
        tabLibros->setObjectName("tabLibros");
        verticalLayout_2 = new QVBoxLayout(tabLibros);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tableWidgetLibros = new QTableWidget(tabLibros);
        tableWidgetLibros->setObjectName("tableWidgetLibros");
        tableWidgetLibros->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
        tableWidgetLibros->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout_2->addWidget(tableWidgetLibros);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnAgregarLibro = new QPushButton(tabLibros);
        btnAgregarLibro->setObjectName("btnAgregarLibro");

        horizontalLayout->addWidget(btnAgregarLibro);

        btnEditarLibro = new QPushButton(tabLibros);
        btnEditarLibro->setObjectName("btnEditarLibro");

        horizontalLayout->addWidget(btnEditarLibro);

        pushButton = new QPushButton(tabLibros);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        btnBuscarLibro = new QPushButton(tabLibros);
        btnBuscarLibro->setObjectName("btnBuscarLibro");

        horizontalLayout->addWidget(btnBuscarLibro);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        tabWidget->addTab(tabLibros, QString());
        tabUsuarios = new QWidget();
        tabUsuarios->setObjectName("tabUsuarios");
        verticalLayout_3 = new QVBoxLayout(tabUsuarios);
        verticalLayout_3->setObjectName("verticalLayout_3");
        tableWidgetUsuarios = new QTableWidget(tabUsuarios);
        tableWidgetUsuarios->setObjectName("tableWidgetUsuarios");
        tableWidgetUsuarios->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout_3->addWidget(tableWidgetUsuarios);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        btnAgregarUsuario = new QPushButton(tabUsuarios);
        btnAgregarUsuario->setObjectName("btnAgregarUsuario");

        horizontalLayout_2->addWidget(btnAgregarUsuario);

        btnModificarUsuario = new QPushButton(tabUsuarios);
        btnModificarUsuario->setObjectName("btnModificarUsuario");

        horizontalLayout_2->addWidget(btnModificarUsuario);

        btnEliminarUsuario = new QPushButton(tabUsuarios);
        btnEliminarUsuario->setObjectName("btnEliminarUsuario");

        horizontalLayout_2->addWidget(btnEliminarUsuario);

        btnExportarUsuarios = new QPushButton(tabUsuarios);
        btnExportarUsuarios->setObjectName("btnExportarUsuarios");

        horizontalLayout_2->addWidget(btnExportarUsuarios);


        verticalLayout_3->addLayout(horizontalLayout_2);

        tabWidget->addTab(tabUsuarios, QString());
        tabPrestamos = new QWidget();
        tabPrestamos->setObjectName("tabPrestamos");
        verticalLayout_4 = new QVBoxLayout(tabPrestamos);
        verticalLayout_4->setObjectName("verticalLayout_4");
        tableWidgetPrestamos = new QTableWidget(tabPrestamos);
        tableWidgetPrestamos->setObjectName("tableWidgetPrestamos");

        verticalLayout_4->addWidget(tableWidgetPrestamos);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        btnRealizarPrestamo = new QPushButton(tabPrestamos);
        btnRealizarPrestamo->setObjectName("btnRealizarPrestamo");

        horizontalLayout_3->addWidget(btnRealizarPrestamo);

        btnRegistrarDevolucion = new QPushButton(tabPrestamos);
        btnRegistrarDevolucion->setObjectName("btnRegistrarDevolucion");

        horizontalLayout_3->addWidget(btnRegistrarDevolucion);


        verticalLayout_4->addLayout(horizontalLayout_3);

        tabWidget->addTab(tabPrestamos, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuArchivo = new QMenu(menubar);
        menuArchivo->setObjectName("menuArchivo");
        menuAyuda = new QMenu(menubar);
        menuAyuda->setObjectName("menuAyuda");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuArchivo->menuAction());
        menubar->addAction(menuAyuda->menuAction());

        retranslateUi(MainWindow);
        QObject::connect(btnAgregarLibro, SIGNAL(clicked()), MainWindow, SLOT(on_btnAgregarLibro_clicked()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Sistema de Biblioteca", nullptr));
        btnAgregarLibro->setText(QCoreApplication::translate("MainWindow", "Agregar Libro", nullptr));
        btnEditarLibro->setText(QCoreApplication::translate("MainWindow", "Editar Libro", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Eliminar Libro", nullptr));
        btnBuscarLibro->setText(QCoreApplication::translate("MainWindow", "Buscar", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabLibros), QCoreApplication::translate("MainWindow", "Libros", nullptr));
        btnAgregarUsuario->setText(QCoreApplication::translate("MainWindow", "Agregar Usuario", nullptr));
        btnModificarUsuario->setText(QCoreApplication::translate("MainWindow", "Editar Usuario", nullptr));
        btnEliminarUsuario->setText(QCoreApplication::translate("MainWindow", "Eliminar Usuario", nullptr));
        btnExportarUsuarios->setText(QCoreApplication::translate("MainWindow", "&Exportar Usuarios", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabUsuarios), QCoreApplication::translate("MainWindow", "Usuarios", nullptr));
        btnRealizarPrestamo->setText(QCoreApplication::translate("MainWindow", "Realizar Pr\303\251stamo", nullptr));
        btnRegistrarDevolucion->setText(QCoreApplication::translate("MainWindow", "Registrar Devoluci\303\263n", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabPrestamos), QCoreApplication::translate("MainWindow", "Pr\303\251stamos", nullptr));
        menuArchivo->setTitle(QCoreApplication::translate("MainWindow", "Archivo", nullptr));
        menuAyuda->setTitle(QCoreApplication::translate("MainWindow", "Ayuda", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
