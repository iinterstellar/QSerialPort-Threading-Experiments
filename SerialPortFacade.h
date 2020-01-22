#pragma once
#include <QSerialPort> // QSerialPort && QObject
#include <QPointer>

/* Facade Design Pattern for QSerialPort. 
 *	- Designed to be used in a dedicated QThread via QObject::moveToThread
 * Slots:
 *	- After thread start, signal slot SerialPortFacade::open to attempt opening a serial port
 *	- Signal slot SerialPortFacade::close to close serial port and shutdown Qthread
 *	- Signal slot SerialPortFacade::write to write data to QSerialPort
 *	- Note: QSerialPort parameters in slot SerialPortFacade::open should be registered before signal slot connection via qRegisterMetaType<T>()
 * Signals:
 *	- Signal SerialPortFacade::error emitted when any QSerialPort error occurs along with error message
 *	- Signal SerialPortFacade::printReadData emitted when new data has been read from QSerialPort
 *	- Signal SerialPortFacade::connectionChange emitted when a connection change has occurred with serial device
 *	- Signal SerialPortFacade::endThread emitted at the end slot SerialPortFacade::close after close operations have been wrapped up
 * Note: QSerialPort is automatically closed upon any QSerialPort error encountered.
 * Example usage:
 *		QThread* thread = new QThread;
 *		SerialPortFacade* serial = new SerialPortFacade();
 *		// Serial Port behavior specific connections
 *		connect(this, &myObj::openSerialPort, serial, &SerialPortFacade::open);
 *		connect(this, &myObj::closeSerialPort, serial, &SerialPortFacade::close, Qt::ConnectionType::BlockingQueuedConnection); // Blocking guarantees serial port has a chance to wrap everything up. Negligible blocking cost
 *		connect(this, &myObj::writeToSerialPort, serial, &SerialPortFacade::write);
 *		connect(serial, &SerialPortFacade::printReadData, this, &myObj::print);
 *		connect(serial, &SerialPortFacade::connectionChange, this, &myObj::handleConnectionChange);
 *		// Sample Thread specific connections. Ordering matters here!
 *		connect(serial, &SerialPortFacade::endThread, thread, &QThread::quit, Qt::ConnectionType::DirectConnection); // DirectConnection forces the thread to quit instantly on signal emition
 *		connect(serial, &SerialPortFacade::endThread, serial, &SerialPortFacade::deleteLater);
 *		connect(thread, &QThread::finished, thread, &QThread::deleteLater);
 *		thread.start();
*/
class SerialPortFacade : public QObject
{
	Q_OBJECT

	public:
		SerialPortFacade();
		~SerialPortFacade();

	public slots:
		void open(
			const QString &portname, 
			const qint32 baudrate, 
			const QSerialPort::DataBits dbits, 
			const QSerialPort::Parity parity, 
			const QSerialPort::StopBits stopbits,
			const QSerialPort::FlowControl flow);
		void close();
		void write(const QByteArray& data);
	signals:
		void error(const QString& msg);
		void printReadData(const QByteArray& data);
		void connectionChange(const bool conn_status);
		void endThread();

	private slots:
		void handleError(const QSerialPort::SerialPortError error);
		void readData();

	private:
		QPointer<QSerialPort> m_serial = nullptr;
		bool m_connection_status = false;
		QString m_error_msg;
};
