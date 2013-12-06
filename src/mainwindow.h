/****************************************************************************
*   Copyright (C) 2012-2013 by Michal Rudolf
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "recentfiles.h"
#include "djvulink.h"

class QDjVuContext;
class QDjVuDocument;

class HelpDialog;

class MainWindow : public QMainWindow
{
	  Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = 0);
private slots:
	 /** Show about information. */
	 void showAboutDialog();
	 /** Show default document. */
	 void showWelcomeDocument();
	 /** Handle zoom action. */
	 void zoomAction(QAction* data);
	 /** Handle rotate action. */
	 void rotateAction(QAction* data);
	 /** Close document. */
	 void closeDocument();
	 /** Export results. */
	 void exportResults();
	 /** Update status bar. */
	 void documentLoading(const DjVuLink &link);
	 /** Update status bar. */
	 void documentLoaded(const DjVuLink &link);
	 /** Configure. */
	 void configure();
	 /** Update corpus name. */
	 void setSource(const QString& title);
	 /** Display given HTML information in main panel. */
	 void showInformation(const QString &info);
	 /** Show logs. */
	 void showLogs();
	 /** Show page information. */
	 void showDocumentInformation();
	 /** Toggle help window. */
	 void toggleHelp();

	 // Index
	 /** Hide index-related action. */
	 void hideIndexActions();
	 /** Show index-related action. */
	 void showIndexActions();
	 /** Add index entry with selected region. */
	 void addIndexEntry();
	 /** Update index entry with selected region. */
	 void updateIndexEntry();
protected:
	 /** Confirm quitting. */
	 void closeEvent(QCloseEvent* event);

	 /** Connect actions. */
	 void setupActions();
	 /** Read configuration. */
	 void restoreSettings();
	 /** Save settings. */
	 void saveSettings();
	 /** Check if the data is saved. */
	 bool queryClose();
	 /** @return the name of application. */
	 QString applicationName() const;

	 HelpDialog* m_helpDialog;

	 Ui::MainWindow ui;
	 static const QString m_applicationName;
};

#endif // MAINWINDOW_H

