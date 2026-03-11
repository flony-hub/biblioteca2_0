/********************************************************************************
** Form generated from reading UI file 'dialogoprestamo.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGOPRESTAMO_H
#define UI_DIALOGOPRESTAMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogoPrestamo
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *labelISBN;
    QLineEdit *lineEditISBN;
    QLabel *labelDNI;
    QLineEdit *lineEditDNI;
    QLabel *labelFechaPrestamo;
    QDateEdit *dateEditPrestamo;
    QLabel *labelFechaDevolucion;
    QDateEdit *dateEditDevolucion;
    QPushButton *btnAceptar;

    void setupUi(QDialog *DialogoPrestamo)
    {
        if (DialogoPrestamo->objectName().isEmpty())
            DialogoPrestamo->setObjectName("DialogoPrestamo");
        DialogoPrestamo->resize(400, 250);
        verticalLayout = new QVBoxLayout(DialogoPrestamo);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        labelISBN = new QLabel(DialogoPrestamo);
        labelISBN->setObjectName("labelISBN");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelISBN);

        lineEditISBN = new QLineEdit(DialogoPrestamo);
        lineEditISBN->setObjectName("lineEditISBN");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEditISBN);

        labelDNI = new QLabel(DialogoPrestamo);
        labelDNI->setObjectName("labelDNI");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelDNI);

        lineEditDNI = new QLineEdit(DialogoPrestamo);
        lineEditDNI->setObjectName("lineEditDNI");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEditDNI);

        labelFechaPrestamo = new QLabel(DialogoPrestamo);
        labelFechaPrestamo->setObjectName("labelFechaPrestamo");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, labelFechaPrestamo);

        dateEditPrestamo = new QDateEdit(DialogoPrestamo);
        dateEditPrestamo->setObjectName("dateEditPrestamo");
        dateEditPrestamo->setCalendarPopup(true);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, dateEditPrestamo);

        labelFechaDevolucion = new QLabel(DialogoPrestamo);
        labelFechaDevolucion->setObjectName("labelFechaDevolucion");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, labelFechaDevolucion);

        dateEditDevolucion = new QDateEdit(DialogoPrestamo);
        dateEditDevolucion->setObjectName("dateEditDevolucion");
        dateEditDevolucion->setCalendarPopup(true);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, dateEditDevolucion);


        verticalLayout->addLayout(formLayout);

        btnAceptar = new QPushButton(DialogoPrestamo);
        btnAceptar->setObjectName("btnAceptar");

        verticalLayout->addWidget(btnAceptar, 0, Qt::AlignCenter);


        retranslateUi(DialogoPrestamo);

        QMetaObject::connectSlotsByName(DialogoPrestamo);
    } // setupUi

    void retranslateUi(QDialog *DialogoPrestamo)
    {
        DialogoPrestamo->setWindowTitle(QCoreApplication::translate("DialogoPrestamo", "Pr\303\251stamo", nullptr));
        labelISBN->setText(QCoreApplication::translate("DialogoPrestamo", "ISBN del Libro:", nullptr));
        labelDNI->setText(QCoreApplication::translate("DialogoPrestamo", "DNI del Usuario:", nullptr));
        labelFechaPrestamo->setText(QCoreApplication::translate("DialogoPrestamo", "Fecha de Pr\303\251stamo:", nullptr));
        labelFechaDevolucion->setText(QCoreApplication::translate("DialogoPrestamo", "Fecha de Devoluci\303\263n:", nullptr));
        btnAceptar->setText(QCoreApplication::translate("DialogoPrestamo", "Aceptar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogoPrestamo: public Ui_DialogoPrestamo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGOPRESTAMO_H
