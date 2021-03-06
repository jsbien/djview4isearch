/****************************************************************************
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

#pragma once
#include "djvulink.h"
#include "djvuwidget.h"

/** This is a small class to handle QDjVu previews. */

class DjVuPreview : public DjVuWidget
{
	Q_OBJECT
public:
	explicit DjVuPreview(QWidget *parent = nullptr);
	void setData(const QVariant& data) {m_data = data;}
	QVariant data() const {return m_data;}
public slots:
	void configure();
protected:
	void focusInEvent(QFocusEvent *);
	void mouseDoubleClickEvent(QMouseEvent *);
	void mousePressEvent(QMouseEvent *event);
signals:
	void activated();
	void documentRequested(const DjVuLink& link);
private:
	QVariant m_data;
};

