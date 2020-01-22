#include "SerialPortFacade.h"

// Constructor
SerialPortFacade::SerialPortFacade() :
	m_serial(new QSerialPort(this)),
	m_connection_status(false)
{
	connect(m_serial, &QSerialPort::errorOccurred, this, &SerialPortFacade::handleError);
	connect(m_serial, &QSerialPort::readyRead, this, &SerialPortFacade::readData);
}

// Destructor
SerialPortFacade::~SerialPortFacade() 
{
	if (m_serial != nullptr && m_serial->isOpen())
		m_serial->close();
	emit endThread();
}

// Public Slots
void SerialPortFacade::open(
	const QString& portname,
	const qint32 baudrate,
	const QSerialPort::DataBits dbits,
	const QSerialPort::Parity parity,
	const QSerialPort::StopBits stopbits,
	const QSerialPort::FlowControl flow)
{
	m_serial->setPortName(portname);
	m_serial->setBaudRate(baudrate);
	m_serial->setDataBits(dbits);
	m_serial->setParity(parity);
	m_serial->setStopBits(stopbits);
	m_serial->setFlowControl(flow);

	if (m_serial->open(QIODevice::ReadWrite)) {
		m_connection_status = true;
		emit connectionChange(m_connection_status);
	}
	else {
		m_error_msg = m_serial->errorString();
		// Print QSerialPort Open() error
		emit printReadData(m_error_msg.toLocal8Bit());
		// Send Thread shutdown signal
		emit endThread();
	}
}
void SerialPortFacade::close()
{
	if (m_serial->isOpen())
		m_serial->close();
	m_connection_status = false;
	// Notify GUI/user
	emit connectionChange(m_connection_status);
	// Send Thread shutdown signal
	emit endThread();
}
void SerialPortFacade::write(const QByteArray& data)
{
	m_serial->write(data);
}

// Private Slots
void SerialPortFacade::handleError(const QSerialPort::SerialPortError error)
{
	m_error_msg = m_serial->errorString();
	if (m_error_msg != "No error")
	{
		// Print Error Message
		emit printReadData(m_error_msg.toLocal8Bit());
		// Close Port
		close();
		// Emit error signal
		emit this->error(m_error_msg);
	}
}

void SerialPortFacade::readData()
{
	const QByteArray data = m_serial->readAll();
	emit printReadData(data);
}