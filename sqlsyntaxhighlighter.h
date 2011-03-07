#ifndef SQLSYNTAXHIGHLIGHTER_H
#define SQLSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextDocument>

class SQLSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit SQLSyntaxHighlighter(QTextDocument *document);

protected:
    enum State {
        NormalState = -1,
        InText,
        InComment
    };

    void highlightBlock(const QString &text);

private:
    QList<QString> greenParts;
    QList<QString> blueParts;

signals:

public slots:

};

#endif // SQLSYNTAXHIGHLIGHTER_H
