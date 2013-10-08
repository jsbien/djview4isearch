/****************************************************************************
*   Copyright (C) 2013 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef DICTIONARYINDEX_H
#define DICTIONARYINDEX_H

#include <QtCore>

class DictionaryIndex
{
public:
	DictionaryIndex();
	/** Open dictionary. */
	bool open(const QString& dictionary);
	/** Save dictionary. */
	bool save();
	/** Remove all items. */
	void clear();
	/** @return current filename. */
	QString filename() const {return m_filename;}
	/** @return list of items starting with given word. */
	QStringList find(const QString& words) const;
	/** Is dictionary index available. */
	bool isEmpty() const {return m_filename.isEmpty();}
	/** Check if dictionary was modified after reading. */
	bool isModified() const {return m_modified;}
	/** @return url of given word. */
	QUrl url(const QString& word) const;
	/** Hide given word. */
	void hide(const QString& entry);
	/** Set link for given word. */
	bool setLink(const QString& word, const QUrl& link);
	/** Add new word. */
	bool addWord(const QString&, const QUrl& link);
private:
	void addEntry(const QString& line);

	struct Entry {
		QString word;
		QUrl link;
		QString comment;
		Entry() {}
		Entry(const QString& w) {word = w.trimmed();}
		bool isVisible() const {return !comment.startsWith('!');}
		void hide() {if (isVisible()) comment.prepend('!');}
		QString formattedWord() const {return link.isValid() ? word : word + ' ';}
		QString toString();
		bool operator==(const Entry& e) {return e.word == word;}
	};

	QVector<Entry> m_entries;
	QString m_filename;
	bool m_modified;
};

#endif // DICTIONARYINDEX_H
