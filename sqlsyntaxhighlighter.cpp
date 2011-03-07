#include "sqlsyntaxhighlighter.h"
#include <QDebug>
#include <QTextDocument>

SQLSyntaxHighlighter::SQLSyntaxHighlighter(QTextDocument *document) :
        QSyntaxHighlighter(document)
{
    blueParts = QList<QString>();
    blueParts.append("ALTER");
    blueParts.append("AND");
    blueParts.append("AS");
    blueParts.append("ASC");
    blueParts.append("BY");
    blueParts.append("DELETE");
    blueParts.append("DESC");
    blueParts.append("DROP");
    blueParts.append("FROM");
    blueParts.append("INNER");
    blueParts.append("INSERT");
    blueParts.append("IS");
    blueParts.append("JOIN");
    blueParts.append("LEFT");
    blueParts.append("NULL");
    blueParts.append("ON");
    blueParts.append("OR");
    blueParts.append("ORDER");
    blueParts.append("RIGHT");
    blueParts.append("SELECT");
    blueParts.append("WHERE");
    greenParts = QList<QString>();
    greenParts.append("*");
    greenParts.append("/");
    greenParts.append("+");
    greenParts.append("-");
    greenParts.append("%");
    greenParts.append("=");
    greenParts.append(";");
    greenParts.append("<");
    greenParts.append(">");
    greenParts.append("<=");
    greenParts.append(">=");
    greenParts.append("<>");
    greenParts.append("!=");

}

void SQLSyntaxHighlighter::highlightBlock(const QString &text)
{
    int i;
    int state = previousBlockState();
    int len = text.length();
    int pos = 0;
    QString part = text.toUpper();
    QString p;
    int pSize;
    QString previousLetter;
    QString quote = QString("'");
    QString scape = QString("\\");
    while (pos < len) {
        switch (state) {
            case NormalState:
                if (part.mid(pos,1) == quote) {
                    state = InText;
                    setFormat(pos, 1, Qt::red);

                    previousLetter=quote;
                }
                for (i = 0; i < blueParts.size(); i++) {
                    p = blueParts.at(i);
                    pSize = p.size();
                    QString previousChar = " ";
                    QString nextChar = " ";
                    if (pos>0) {
                        previousChar = part.mid(pos-1,1);
                    }
                    if (pos+pSize<part.size()) {
                        nextChar = part.mid(pos+pSize,1);
                    }
                    if (previousChar.count(QRegExp("\\s+"))==1 && nextChar.count(QRegExp("\\s+"))==1 && part.mid(pos,pSize) == p) {
                        setFormat(pos, pSize, Qt::blue);
                    }
                }
                for (i = 0; i < greenParts.size(); i++) {
                    p = greenParts.at(i);
                    pSize = p.size();
                    if (part.mid(pos,pSize) == p) {
                        setFormat(pos, pSize, Qt::darkGreen);
                    }
                }
                break;
            case InText:
                setFormat(pos, 1, Qt::red);
                p = text.mid(pos,1);
                if (previousLetter!=scape && p==quote) {
                    state = NormalState;
                }
                previousLetter = p;
                break;

        }
        pos++;
    }

    setCurrentBlockState(state);
}
