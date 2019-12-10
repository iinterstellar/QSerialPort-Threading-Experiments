/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *parametersBox;
    QGridLayout *gridLayout_2;
    QLabel *baudRateLabel;
    QComboBox *baudRateBox;
    QLabel *dataBitsLabel;
    QComboBox *dataBitsBox;
    QLabel *parityLabel;
    QComboBox *parityBox;
    QLabel *stopBitsLabel;
    QComboBox *stopBitsBox;
    QLabel *flowControlLabel;
    QComboBox *flowControlBox;
    QGroupBox *selectBox;
    QGridLayout *gridLayout;
    QComboBox *serialPortInfoListBox;
    QLabel *descriptionLabel;
    QLabel *manufacturerLabel;
    QLabel *serialNumberLabel;
    QLabel *locationLabel;
    QLabel *vidLabel;
    QLabel *pidLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *applyButton;
    QGroupBox *additionalOptionsGroupBox;
    QVBoxLayout *verticalLayout;
    QCheckBox *localEchoCheckBox;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(281, 262);
        gridLayout_3 = new QGridLayout(SettingsDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        parametersBox = new QGroupBox(SettingsDialog);
        parametersBox->setObjectName(QString::fromUtf8("parametersBox"));
        gridLayout_2 = new QGridLayout(parametersBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        baudRateLabel = new QLabel(parametersBox);
        baudRateLabel->setObjectName(QString::fromUtf8("baudRateLabel"));

        gridLayout_2->addWidget(baudRateLabel, 0, 0, 1, 1);

        baudRateBox = new QComboBox(parametersBox);
        baudRateBox->setObjectName(QString::fromUtf8("baudRateBox"));

        gridLayout_2->addWidget(baudRateBox, 0, 1, 1, 1);

        dataBitsLabel = new QLabel(parametersBox);
        dataBitsLabel->setObjectName(QString::fromUtf8("dataBitsLabel"));

        gridLayout_2->addWidget(dataBitsLabel, 1, 0, 1, 1);

        dataBitsBox = new QComboBox(parametersBox);
        dataBitsBox->setObjectName(QString::fromUtf8("dataBitsBox"));

        gridLayout_2->addWidget(dataBitsBox, 1, 1, 1, 1);

        parityLabel = new QLabel(parametersBox);
        parityLabel->setObjectName(QString::fromUtf8("parityLabel"));

        gridLayout_2->addWidget(parityLabel, 2, 0, 1, 1);

        parityBox = new QComboBox(parametersBox);
        parityBox->setObjectName(QString::fromUtf8("parityBox"));

        gridLayout_2->addWidget(parityBox, 2, 1, 1, 1);

        stopBitsLabel = new QLabel(parametersBox);
        stopBitsLabel->setObjectName(QString::fromUtf8("stopBitsLabel"));

        gridLayout_2->addWidget(stopBitsLabel, 3, 0, 1, 1);

        stopBitsBox = new QComboBox(parametersBox);
        stopBitsBox->setObjectName(QString::fromUtf8("stopBitsBox"));

        gridLayout_2->addWidget(stopBitsBox, 3, 1, 1, 1);

        flowControlLabel = new QLabel(parametersBox);
        flowControlLabel->setObjectName(QString::fromUtf8("flowControlLabel"));

        gridLayout_2->addWidget(flowControlLabel, 4, 0, 1, 1);

        flowControlBox = new QComboBox(parametersBox);
        flowControlBox->setObjectName(QString::fromUtf8("flowControlBox"));

        gridLayout_2->addWidget(flowControlBox, 4, 1, 1, 1);


        gridLayout_3->addWidget(parametersBox, 0, 1, 1, 1);

        selectBox = new QGroupBox(SettingsDialog);
        selectBox->setObjectName(QString::fromUtf8("selectBox"));
        gridLayout = new QGridLayout(selectBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        serialPortInfoListBox = new QComboBox(selectBox);
        serialPortInfoListBox->setObjectName(QString::fromUtf8("serialPortInfoListBox"));

        gridLayout->addWidget(serialPortInfoListBox, 0, 0, 1, 1);

        descriptionLabel = new QLabel(selectBox);
        descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));

        gridLayout->addWidget(descriptionLabel, 1, 0, 1, 1);

        manufacturerLabel = new QLabel(selectBox);
        manufacturerLabel->setObjectName(QString::fromUtf8("manufacturerLabel"));

        gridLayout->addWidget(manufacturerLabel, 2, 0, 1, 1);

        serialNumberLabel = new QLabel(selectBox);
        serialNumberLabel->setObjectName(QString::fromUtf8("serialNumberLabel"));

        gridLayout->addWidget(serialNumberLabel, 3, 0, 1, 1);

        locationLabel = new QLabel(selectBox);
        locationLabel->setObjectName(QString::fromUtf8("locationLabel"));

        gridLayout->addWidget(locationLabel, 4, 0, 1, 1);

        vidLabel = new QLabel(selectBox);
        vidLabel->setObjectName(QString::fromUtf8("vidLabel"));

        gridLayout->addWidget(vidLabel, 5, 0, 1, 1);

        pidLabel = new QLabel(selectBox);
        pidLabel->setObjectName(QString::fromUtf8("pidLabel"));

        gridLayout->addWidget(pidLabel, 6, 0, 1, 1);


        gridLayout_3->addWidget(selectBox, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(96, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        applyButton = new QPushButton(SettingsDialog);
        applyButton->setObjectName(QString::fromUtf8("applyButton"));

        horizontalLayout->addWidget(applyButton);


        gridLayout_3->addLayout(horizontalLayout, 2, 0, 1, 2);

        additionalOptionsGroupBox = new QGroupBox(SettingsDialog);
        additionalOptionsGroupBox->setObjectName(QString::fromUtf8("additionalOptionsGroupBox"));
        verticalLayout = new QVBoxLayout(additionalOptionsGroupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        localEchoCheckBox = new QCheckBox(additionalOptionsGroupBox);
        localEchoCheckBox->setObjectName(QString::fromUtf8("localEchoCheckBox"));
        localEchoCheckBox->setChecked(true);

        verticalLayout->addWidget(localEchoCheckBox);


        gridLayout_3->addWidget(additionalOptionsGroupBox, 1, 0, 1, 2);


        retranslateUi(SettingsDialog);

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QCoreApplication::translate("SettingsDialog", "Settings", nullptr));
        parametersBox->setTitle(QCoreApplication::translate("SettingsDialog", "Select Parameters", nullptr));
        baudRateLabel->setText(QCoreApplication::translate("SettingsDialog", "BaudRate:", nullptr));
        dataBitsLabel->setText(QCoreApplication::translate("SettingsDialog", "Data bits:", nullptr));
        parityLabel->setText(QCoreApplication::translate("SettingsDialog", "Parity:", nullptr));
        stopBitsLabel->setText(QCoreApplication::translate("SettingsDialog", "Stop bits:", nullptr));
        flowControlLabel->setText(QCoreApplication::translate("SettingsDialog", "Flow control:", nullptr));
        selectBox->setTitle(QCoreApplication::translate("SettingsDialog", "Select Serial Port", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("SettingsDialog", "Description:", nullptr));
        manufacturerLabel->setText(QCoreApplication::translate("SettingsDialog", "Manufacturer:", nullptr));
        serialNumberLabel->setText(QCoreApplication::translate("SettingsDialog", "Serial number:", nullptr));
        locationLabel->setText(QCoreApplication::translate("SettingsDialog", "Location:", nullptr));
        vidLabel->setText(QCoreApplication::translate("SettingsDialog", "Vendor ID:", nullptr));
        pidLabel->setText(QCoreApplication::translate("SettingsDialog", "Product ID:", nullptr));
        applyButton->setText(QCoreApplication::translate("SettingsDialog", "Apply", nullptr));
        additionalOptionsGroupBox->setTitle(QCoreApplication::translate("SettingsDialog", "Additional options", nullptr));
        localEchoCheckBox->setText(QCoreApplication::translate("SettingsDialog", "Local echo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
