/****************************************************************************
*   Copyright (C) 2012-2017 by Michal Rudolf <michal@rudolf.waw.pl>              *
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

#include "djvulink.h"


// Helper functions for Qt4 and Qt5 compatibility

typedef QPair<QString, QString> Item;
typedef QList<Item> QueryItems;

/** Extracts QueryItems from given url */
static QueryItems urlQueryItems(const QUrl &url)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	return QUrlQuery(url).queryItems();
#else
	return url.queryItems();
#endif
}

/** Sets Query component of url */
static void urlSetQueryItems(QUrl &url, const QueryItems &items)
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	QUrlQuery qitems;
	qitems.setQueryItems(items);
	url.setQuery(qitems);
#else
	url.setQueryItems(items);
#endif
}

/** Retrieves djvu-specific part of url */
static QueryItems getDjvuOpts(const QUrl &url) {
	QueryItems ret;
	bool djvuopts = false;
	foreach(const Item &parameter, urlQueryItems(url)) {
		if (parameter.first.compare("djvuopts", Qt::CaseInsensitive) == 0) {
			djvuopts = true;
		}
		else if (djvuopts)
			ret.append(parameter);
	}
	return ret;
}

/** Sets djvu argument, replacing existing value(s) or adding new */
static void setDjVuCgiArgument(QUrl &url, const QString &arg, const QString &val) {
	QueryItems parameters = urlQueryItems(url);
	bool djvuopts = false;
	bool found = false;
	for (QueryItems::Iterator it = parameters.begin(); it != parameters.end(); ++it) {
		if (it->first.compare("djvuopts", Qt::CaseInsensitive) == 0) {
			djvuopts = true;
		}
		else if (djvuopts && it->first.compare(arg) == 0) {
			if (found) {
				it = parameters.erase(it);
			} else {
				found = true;
				it->second = val;
			}
		}
	}
	if (!found) {
		parameters.append(qMakePair(arg, val));
	}
	urlSetQueryItems(url, parameters);
}


DjVuLink::DjVuLink()
{
}

QList<DjVuLink::Highlight> DjVuLink::highlights() const
{
	return m_highlights;
}

void DjVuLink::setLink(const QUrl &link)
{
	// Link example:
	// http://ebuw.uw.edu.pl/Content/234/directory.djvu?djvuopts&page=218&zoom=width&showposition=0.354,0.750&highlight=964,990,97,35#SW
	m_link = link;
	QColor defaultColor = QSettings().value("Display/highlight", "#ffff00").value<QColor>();
	m_highlights.clear();
	QPair<QString, QString> arg;
	foreach (arg, getDjvuOpts(link)) {
		if (arg.first == "page")
			m_page = qMax(0, arg.second.toInt() - 1);
		else if (arg.first == "highlight") {
			Highlight h;
			h.page = m_page;
			QStringList parts = arg.second.split(',');
			h.rect = QRect(QPoint(parts.value(0).toInt(), parts.value(1).toInt()),
								QSize(parts.value(2).toInt(), parts.value(3).toInt()));
			if (!parts.value(4).isEmpty())
				h.color = QString("#%1").arg(parts.value(4));
			else h.color = defaultColor;
			h.color.setAlpha(96);
			m_highlights.append(h);
		}
		else if (arg.first == "showposition") {
			m_position.setX(arg.second.section(QRegExp("[.,]"), 1, 1).toInt());
			m_position.setY(arg.second.section(QRegExp("[.,]"), 3, 3).toInt());
		}
	}
}

QUrl DjVuLink::colorRegionLink(const QRect& rect, int page) const
{
	QColor color = QSettings().value("Display/highlight", "#ffff00").value<QColor>();
	QUrl url = m_link;
	setDjVuCgiArgument(url, "highlight", QString("%1,%2,%3,%4,%5").arg(rect.left())
		.arg(rect.top()).arg(rect.width()).arg(rect.height())
		.arg(color.name().mid(1)));
	if (page >= 0) {
		setDjVuCgiArgument(url, "page", QString::number(page + 1));
	}
	return url;
}

QUrl DjVuLink::regionLink(const QRect& rect, int page) const
{
	QUrl url = m_link;
	setDjVuCgiArgument(url, "highlight", QString("%1,%2,%3,%4").arg(rect.left())
		.arg(rect.top()).arg(rect.width()).arg(rect.height()));
	if (page >= 0) {
		setDjVuCgiArgument(url, "page", QString::number(page + 1));
	}
	return url;
}

QUrl DjVuLink::link() const {
	return m_link;
}

QUrl DjVuLink::downloadLink() const
{
	QUrl newurl = m_link;
	QueryItems args;
	bool djvuopts = false;
	foreach(const Item &pair, urlQueryItems(m_link))
	{
		if (pair.first.toLower() == "djvuopts")
			djvuopts = true;
		else if (!djvuopts)
			args << pair;
	}
	urlSetQueryItems(newurl, args);
	return newurl;
}

QString DjVuLink::documentPath() const
{
	return m_link.scheme() + "://" + m_link.host() + m_link.path();
}

QString DjVuLink::toCsv(const QChar &separator) const
{
	if (!isValid())
		return QString();
	QStringList fields;
	fields << m_leftContext << m_match << m_rightMatch << m_rightContext << m_link.toString();
	for (int i = 0; i < fields.count(); i++)
		if (fields[i].contains(separator)) {
			fields[i].replace("\"", "\"\"");
			fields[i] = QString("\"%1\"").arg(fields[i]);
		}
	return fields.join(separator);
}

