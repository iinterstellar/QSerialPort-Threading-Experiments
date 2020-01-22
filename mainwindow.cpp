/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"

#include <QLabel>
#include <QMessageBox>

#ifdef _DEBUG
#include <QDebug>
#endif

//! [0]
MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	m_ui(new Ui::MainWindow),
	m_status(new QLabel),
	m_console(new Console),
	m_settings(new SettingsDialog),
	//! [1]
	m_serial(new QSerialPort(this)),
	//! [1]
	m_multithreadserial(nullptr),
	m_serialPortThread(nullptr)
{
//! [0]
    m_ui->setupUi(this);
    m_console->setEnabled(false);
    setCentralWidget(m_console);

    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    m_ui->actionQuit->setEnabled(true);
    m_ui->actionConfigure->setEnabled(true);

    m_ui->statusBar->addWidget(m_status);

    initActionsConnections();

    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);

//! [2]
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
//! [2]
    connect(m_console, &Console::getData, this, &MainWindow::writeData);
//! [3]
	// Registration necessary for Queued connections
	// From QT: "...make types available to non-template based functions, such as the queued signal and slot connections."
	qRegisterMetaType<QSerialPort::DataBits>();
	qRegisterMetaType<QSerialPort::Parity>();
	qRegisterMetaType<QSerialPort::StopBits>();
	qRegisterMetaType<QSerialPort::FlowControl>();
}
//! [3]

MainWindow::~MainWindow()
{
    delete m_settings;
    delete m_ui;
	emit closeSerialPort_MT(); // Shuts down Serial Port Thread if still running
}

//! [4]
void MainWindow::openSerialPort()
{
    const SettingsDialog::Settings p = m_settings->settings();
    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);

	if (p.multithreading) { // Case Multi-Threading Option enabled
		showStatusMessage(tr("Running Multi-Threading..."));
		if (m_serialPortThread == nullptr && m_multithreadserial == nullptr)
		{
			m_multithreadserial = new SerialPortFacade();
			m_serialPortThread = new QThread();
			m_multithreadserial->moveToThread(m_serialPortThread);
			initMultiThreadingConnections();
			m_serialPortThread->start();
			emit openSerialPort_MT(p.name, p.baudRate, p.dataBits, p.parity, p.stopBits, p.flowControl);
		}
		else // Error case, should never be reached
		{
			#ifdef _DEBUG
				qDebug() << "Error: Multi-threading members were not deallocated when open serial port was attempted.";
			#endif
			showStatusMessage(tr("Multi-Threading Open Serial Port error"));
		}
	}

	// Else default to Qt implementation
	else {
		showStatusMessage(tr("Default Qt implementation..."));
		if (m_serial->open(QIODevice::ReadWrite)) {
			m_console->setEnabled(true);
			m_console->setLocalEchoEnabled(p.localEchoEnabled);
			m_ui->actionConnect->setEnabled(false);
			m_ui->actionDisconnect->setEnabled(true);
			m_ui->actionConfigure->setEnabled(false);
			showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6, running Qt implementation...")
				.arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
				.arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
		}
		else {
			QMessageBox::critical(this, tr("Error"), m_serial->errorString());

			showStatusMessage(tr("Open error"));
		}
	}
    
}
//! [4]

//! [5]
void MainWindow::closeSerialPort()
{
	const SettingsDialog::Settings p = m_settings->settings();
	if (p.multithreading) {
		// Multithreading shutdown sequence
		m_console->setEnabled(false);
		m_ui->actionConnect->setEnabled(true);
		m_ui->actionDisconnect->setEnabled(false);
		m_ui->actionConfigure->setEnabled(true);
		showStatusMessage(tr("Disconnected"));

		// Signal shutdown thread sequence
		emit closeSerialPort_MT();
		if (m_serialPortThread.isNull() == false && m_serialPortThread->isRunning())	 // Case signal/slot mechanism failed to shutdown thread. Force shutdown (should never happen)
		{
			#ifdef _DEBUG
				qDebug() << "WARNING: SerialPort QThread was still running after emitting close serial port signal.";
			#endif 
			m_serialPortThread->quit();
			m_serialPortThread->wait();
		}
		const bool multi_serial_was_deallocated = m_multithreadserial.isNull(); // Just for debugging
		const bool multi_thread_was_deallocated = m_serialPortThread.isNull();
		if (multi_thread_was_deallocated == false)
			m_serialPortThread.clear(); // Deallocate QThread. During runtime use, deleateLater() will not have a chance to execute deallocation.
	}
	else { // Single thread Default implementation
		if (m_serial->isOpen())
			m_serial->close();
		m_console->setEnabled(false);
		m_ui->actionConnect->setEnabled(true);
		m_ui->actionDisconnect->setEnabled(false);
		m_ui->actionConfigure->setEnabled(true);
		showStatusMessage(tr("Disconnected"));
	}
}
//! [5]

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}

//! [6]
void MainWindow::writeData(const QByteArray &data)
{
	const SettingsDialog::Settings p = m_settings->settings();
	if(!p.multithreading) // Disable default write when Multi-threading mode is enabled
		m_serial->write(data);
}
//! [6]

//! [7]
void MainWindow::readData()
{
    const QByteArray data = m_serial->readAll();
    m_console->putData(data);
}
//! [7]

//! [8]
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        closeSerialPort();
    }
}
//! [8]

void MainWindow::initActionsConnections()
{
    connect(m_ui->actionConnect, &QAction::triggered, this, &MainWindow::openSerialPort);
    connect(m_ui->actionDisconnect, &QAction::triggered, this, &MainWindow::closeSerialPort);
    connect(m_ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(m_ui->actionConfigure, &QAction::triggered, m_settings, &SettingsDialog::show);
    connect(m_ui->actionClear, &QAction::triggered, m_console, &Console::clear);
    connect(m_ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(m_ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::showStatusMessage(const QString &message)
{
    m_status->setText(message);
}

// Multi-Thread slot that handles Serial Port connection status changes. Updates GUI accordingly
void MainWindow::handleConnectionChange(const bool conn_status)
{
	static bool last_conn_status = false;
	if (last_conn_status != conn_status)
	{
		last_conn_status = conn_status;
		const SettingsDialog::Settings p = m_settings->settings();
		if (last_conn_status == true)
		{
			m_console->setEnabled(true);
			m_console->setLocalEchoEnabled(false); // TODO: Fix checkboxes. Need to add a 'Default' checkbox and let Local Echo be enabled for both modes
			m_ui->actionConnect->setEnabled(false);
			m_ui->actionDisconnect->setEnabled(true);
			m_ui->actionConfigure->setEnabled(false);
			showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6, running Multithreading implementation...")
				.arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
				.arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
		}
		else
		{
			closeSerialPort();
		}
	}
}

// Initializes Multi-Threading signal/slot connections
void MainWindow::initMultiThreadingConnections()
{
	// Serial Port behavior specific connections
	connect(this, &MainWindow::openSerialPort_MT, m_multithreadserial, &SerialPortFacade::open);
	connect(this, &MainWindow::closeSerialPort_MT, m_multithreadserial, &SerialPortFacade::close, Qt::ConnectionType::BlockingQueuedConnection); // Blocking guarantees serial port has a chance to wrap everything up. Negligible blocking cost
	connect(m_console, &Console::getData, m_multithreadserial, &SerialPortFacade::write);
	connect(m_multithreadserial, &SerialPortFacade::printReadData, m_console, &Console::putData);
	connect(m_multithreadserial, &SerialPortFacade::connectionChange, this, &MainWindow::handleConnectionChange);
	// Thread specific connections. Ordering matters here.
	connect(m_multithreadserial, &SerialPortFacade::endThread, m_serialPortThread, &QThread::quit, Qt::ConnectionType::DirectConnection); // DirectConnection forces the thread to quit instantly on signal emition
	connect(m_multithreadserial, &SerialPortFacade::endThread, m_multithreadserial, &SerialPortFacade::deleteLater);
	connect(m_serialPortThread, &QThread::finished, m_serialPortThread, &QThread::deleteLater);
}