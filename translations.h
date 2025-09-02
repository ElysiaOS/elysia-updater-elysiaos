#ifndef TRANSLATIONS_H
#define TRANSLATIONS_H

#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QLocale>

class Translations {
public:
    static Translations& instance();
    
    QString get(const QString& key) const;
    void loadTranslations();

private:
    Translations();
    QMap<QString, QMap<QString, QString>> m_translations;
    QString m_currentLang;
    
    void addTranslation(const QString& lang, const QString& key, const QString& value);
};

#endif // TRANSLATIONS_H