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

#include "entrylist.h"

EntryList::EntryList()
{
}

bool EntryList::open(const QString& filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly))
		return false;

	clear();
	QTextStream stream(&file);
	stream.setCodec("UTF-8");
	while (!stream.atEnd()) {
		Entry entry = Entry::parse(stream.readLine());
		if (entry.isValid()) {
			append(entry);
		}
	}
	m_filename = filename;
	return true;
}

bool EntryList::save(const QString& filename)
{
	const QString backup = filename + ".bak";
	if (QFile::exists(filename) && !m_backedUp.contains(filename)) {
		m_backedUp.insert(filename);
		if (QFile::exists(backup))
			QFile::remove(backup);
		QFile::rename(filename, backup);
	}

	QFile file(filename);
	if (file.open(QIODevice::WriteOnly)) {
		QTextStream stream(&file);
		stream.setCodec("UTF-8");
		QList<Entry> entries;
		for (int i = 0; i < count(); i++)
			if (!at(i).isDeleted())
				stream << at(i).toString();
		return true;
	}
	else {
		if (QFile::exists(backup))
			QFile::rename(backup, filename);
		return false;
	}
}

QSet<QString> EntryList::m_backedUp;
