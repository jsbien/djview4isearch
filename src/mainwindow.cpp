/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf
*   This software is subject to, and may be distributed under, the
*   GNU General Public License, either version 2 of the license,
*   or (at your option) any later version. The license should have
*   accompanied the software or you may obtain a copy of the license
*   from the Free Software Foundation at http://www.fsf.org .

*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
****************************************************************************/

#include "mainwindow.h"
#include "messagedialog.h"
#include "qdjvu.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	m_recentFiles(this)
{
	QApplication::instance()->setOrganizationName(m_applicationName);
	QApplication::instance()->setApplicationName(m_applicationName);
	ui.setupUi(this);
	m_recentFiles.plug(ui.actionFileRecent);
	connect(&m_recentFiles, SIGNAL(selected(QString)), this, SLOT(open(QString)));

	m_context = new QDjVuContext(m_applicationName.toLatin1(), this);
	m_document = new QDjVuDocument(this);

	setupActions();
	setWindowTitle(QString("%1 - %2").arg(tr("[Untitled]"))
													  .arg(m_applicationName));
	show();
	restoreSettings();

	if (QApplication::instance()->argc() > 1)
		open(QApplication::instance()->argv()[1]);

}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if (queryClose())
		saveSettings();
	else event->ignore();
}

bool MainWindow::queryClose()
{
	return true;
}

void MainWindow::restoreSettings()
{
	QSettings settings;
	resize(settings.value("Windows/MainWindow", size()).toSize());
}

void MainWindow::saveSettings()
{
	QSettings settings;
	settings.setValue("Windows/MainWindow", size());
}

void MainWindow::open(const QString &filename)
{
	/*** Open file. ***/
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	ui.djvuWidget->setDocument(0);
	if (m_document->setFileName(m_context, filename, true)) {
		ui.djvuWidget->setDocument(m_document);
		m_recentFiles.addFile(filename);
		setWindowTitle(QString("%1 - %2").arg(QFileInfo(filename).baseName())
							.arg(m_applicationName));
	}
	else MessageDialog::warning(tr("Cannot open file\n%1").arg(filename));
	QApplication::restoreOverrideCursor();
}

void MainWindow::selectFileToOpen()
{
	QString filename = MessageDialog::openFile(tr("DjVu files (*.djvu)"),
			tr("Open file"), "Files");
	if (!filename.isEmpty())
		open(filename);
}

void MainWindow::showAboutDialog()
{
	const QString VERSION = "0.1";
	QString about = tr("%1\n"
							 "Version %2\n(c) Michal Rudolf 2012")
			.arg(m_applicationName).arg(VERSION);
	QMessageBox::about(this, tr("About application"), about);
}





void MainWindow::setupActions()
{
	connect(ui.actionFileOpen, SIGNAL(triggered()), this,
			  SLOT(selectFileToOpen()));

	connect(ui.actionHelpAbout, SIGNAL(triggered()), this,
			  SLOT(showAboutDialog()));
}




const QString MainWindow::m_applicationName = QT_TR_NOOP("DjView-Poliqarp");

