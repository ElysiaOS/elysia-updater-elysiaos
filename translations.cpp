#include "translations.h"
#include <QtCore/QProcessEnvironment>
#include <QtCore/QLocale>
#include <QtCore/QDebug>

Translations::Translations() {
    loadTranslations();
}

Translations& Translations::instance() {
    static Translations instance;
    return instance;
}

void Translations::loadTranslations() {
    // Get the current locale from environment
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString lang = env.value("LANG", QLocale().name());
    
    // Extract just the language part (e.g., "en_US.UTF-8" -> "en")
    if (lang.contains('.')) {
        lang = lang.left(lang.indexOf('.'));
    }
    
    // If it's in format "en_US", take just the first part
    if (lang.contains('_')) {
        lang = lang.left(lang.indexOf('_'));
    }
    
    m_currentLang = lang.toLower();
    
    // English translations (default)
    addTranslation("en", "window_title", "Elysia Updater");
    addTranslation("en", "check_updates", "CHECK FOR UPDATES");
    addTranslation("en", "check_yay_updates", "CHECK YAY UPDATES");
    addTranslation("en", "check_elysia_updates", "CHECK ELYSIAOS UPDATES");
    addTranslation("en", "close", "CLOSE");
    addTranslation("en", "info", "Info");
    addTranslation("en", "syncing_database", "🔃 Syncing package database...");
    addTranslation("en", "checking_updates", "🔃 Syncing before checking for updates...");
    addTranslation("en", "checking_yay_updates", "🔃 Checking for AUR (yay) updates...\n");
    addTranslation("en", "checking_elysia_updates", "🔄 Checking for ElysiaOS updates using git-elyos.sh...\n");
    addTranslation("en", "system_up_to_date", "✅ System is up to date.");
    addTranslation("en", "aur_up_to_date", "✅ All AUR packages are up to date.");
    addTranslation("en", "updates_found", "🔧 %1 updates found:\n");
    addTranslation("en", "aur_updates_found", "🌟 %1 AUR updates found:\n");
    addTranslation("en", "update_only", "Update Only %1");
    addTranslation("en", "update_all", "Update All");
    addTranslation("en", "update_all_aur", "Update All AUR");
    addTranslation("en", "updating_package", "⏳ Updating %1...\n");
    addTranslation("en", "updating_aur_package", "⏳ Updating AUR package %1...\n");
    addTranslation("en", "updating_all", "⏳ Updating all packages...\n");
    addTranslation("en", "updating_all_aur", "⏳ Updating all AUR packages...\n");
    addTranslation("en", "update_finished", "✅ Update finished!\nReturning to menu...");
    addTranslation("en", "elysia_update_finished", "✅ ElysiaOS update check finished.\nReturning to menu...");
    
    // Spanish translations
    addTranslation("es", "window_title", "Actualizador de Elysia");
    addTranslation("es", "check_updates", "VERIFICAR ACTUALIZACIONES");
    addTranslation("es", "check_yay_updates", "VERIFICAR ACTUALIZACIONES YAY");
    addTranslation("es", "check_elysia_updates", "VERIFICAR ACTUALIZACIONES ELYSIAOS");
    addTranslation("es", "close", "CERRAR");
    addTranslation("es", "info", "Información");
    addTranslation("es", "syncing_database", "🔃 Sincronizando base de datos de paquetes...");
    addTranslation("es", "checking_updates", "🔃 Sincronizando antes de verificar actualizaciones...");
    addTranslation("es", "checking_yay_updates", "🔃 Verificando actualizaciones AUR (yay)...\n");
    addTranslation("es", "checking_elysia_updates", "🔄 Verificando actualizaciones de ElysiaOS usando git-elyos.sh...\n");
    addTranslation("es", "system_up_to_date", "✅ El sistema está actualizado.");
    addTranslation("es", "aur_up_to_date", "✅ Todos los paquetes AUR están actualizados.");
    addTranslation("es", "updates_found", "🔧 %1 actualizaciones encontradas:\n");
    addTranslation("es", "aur_updates_found", "🌟 %1 actualizaciones AUR encontradas:\n");
    addTranslation("es", "update_only", "Actualizar solo %1");
    addTranslation("es", "update_all", "Actualizar todo");
    addTranslation("es", "update_all_aur", "Actualizar todos los AUR");
    addTranslation("es", "updating_package", "⏳ Actualizando %1...\n");
    addTranslation("es", "updating_aur_package", "⏳ Actualizando paquete AUR %1...\n");
    addTranslation("es", "updating_all", "⏳ Actualizando todos los paquetes...\n");
    addTranslation("es", "updating_all_aur", "⏳ Actualizando todos los paquetes AUR...\n");
    addTranslation("es", "update_finished", "✅ Actualización finalizada!\nVolviendo al menú...");
    addTranslation("es", "elysia_update_finished", "✅ Verificación de actualizaciones de ElysiaOS finalizada.\nVolviendo al menú...");
    
    // French translations
    addTranslation("fr", "window_title", "Mise à jour Elysia");
    addTranslation("fr", "check_updates", "VÉRIFIER LES MISES À JOUR");
    addTranslation("fr", "check_yay_updates", "VÉRIFIER LES MISES À JOUR YAY");
    addTranslation("fr", "check_elysia_updates", "VÉRIFIER LES MISES À JOUR ELYSIAOS");
    addTranslation("fr", "close", "FERMER");
    addTranslation("fr", "info", "Info");
    addTranslation("fr", "syncing_database", "🔃 Synchronisation de la base de données des paquetes...");
    addTranslation("fr", "checking_updates", "🔃 Synchronisation avant de vérifier les mises à jour...");
    addTranslation("fr", "checking_yay_updates", "🔃 Vérification des mises à jour AUR (yay)...\n");
    addTranslation("fr", "checking_elysia_updates", "🔄 Vérification des mises à jour ElysiaOS avec git-elyos.sh...\n");
    addTranslation("fr", "system_up_to_date", "✅ Le système est à jour.");
    addTranslation("fr", "aur_up_to_date", "✅ Tous les paquets AUR sont à jour.");
    addTranslation("fr", "updates_found", "🔧 %1 mises à jour trouvées:\n");
    addTranslation("fr", "aur_updates_found", "🌟 %1 mises à jour AUR trouvées:\n");
    addTranslation("fr", "update_only", "Mettre à jour seulement %1");
    addTranslation("fr", "update_all", "Tout mettre à jour");
    addTranslation("fr", "update_all_aur", "Tout mettre à jour (AUR)");
    addTranslation("fr", "updating_package", "⏳ Mise à jour de %1...\n");
    addTranslation("fr", "updating_aur_package", "⏳ Mise à jour du paquet AUR %1...\n");
    addTranslation("fr", "updating_all", "⏳ Mise à jour de tous les paquets...\n");
    addTranslation("fr", "updating_all_aur", "⏳ Mise à jour de tous les paquets AUR...\n");
    addTranslation("fr", "update_finished", "✅ Mise à jour terminée!\nRetour au menu...");
    addTranslation("fr", "elysia_update_finished", "✅ Vérification des mises à jour ElysiaOS terminée.\nRetour au menu...");
    
    // German translations
    addTranslation("de", "window_title", "Elysia Updater");
    addTranslation("de", "check_updates", "AKTUALISIERUNGEN PRÜFEN");
    addTranslation("de", "check_yay_updates", "YAY-AKTUALISIERUNGEN PRÜFEN");
    addTranslation("de", "check_elysia_updates", "ELYSIAOS-AKTUALISIERUNGEN PRÜFEN");
    addTranslation("de", "close", "SCHLIEẞEN");
    addTranslation("de", "info", "Info");
    addTranslation("de", "syncing_database", "🔃 Paketdatenbank wird synchronisiert...");
    addTranslation("de", "checking_updates", "🔃 Synchronisierung vor der Suche nach Aktualisierungen...");
    addTranslation("de", "checking_yay_updates", "🔃 Suche nach AUR (yay) Aktualisierungen...\n");
    addTranslation("de", "checking_elysia_updates", "🔄 Suche nach ElysiaOS Aktualisierungen mit git-elyos.sh...\n");
    addTranslation("de", "system_up_to_date", "✅ System ist auf dem neuesten Stand.");
    addTranslation("de", "aur_up_to_date", "✅ Alle AUR-Pakete sind auf dem neuesten Stand.");
    addTranslation("de", "updates_found", "🔧 %1 Aktualisierungen gefunden:\n");
    addTranslation("de", "aur_updates_found", "🌟 %1 AUR-Aktualisierungen gefunden:\n");
    addTranslation("de", "update_only", "Nur %1 aktualisieren");
    addTranslation("de", "update_all", "Alle aktualisieren");
    addTranslation("de", "update_all_aur", "Alle AUR aktualisieren");
    addTranslation("de", "updating_package", "⏳ Aktualisiere %1...\n");
    addTranslation("de", "updating_aur_package", "⏳ Aktualisiere AUR-Paket %1...\n");
    addTranslation("de", "updating_all", "⏳ Alle Pakete werden aktualisiert...\n");
    addTranslation("de", "updating_all_aur", "⏳ Alle AUR-Pakete werden aktualisiert...\n");
    addTranslation("de", "update_finished", "✅ Aktualisierung abgeschlossen!\nZurück zum Menü...");
    addTranslation("de", "elysia_update_finished", "✅ ElysiaOS Aktualisierungsprüfung abgeschlossen.\nZurück zum Menü...");
    
    // Japanese translations
    addTranslation("ja", "window_title", "エリシア・アップデーター");
    addTranslation("ja", "check_updates", "アップデートを確認");
    addTranslation("ja", "check_yay_updates", "YAY アップデートを確認");
    addTranslation("ja", "check_elysia_updates", "エリシアOS アップデートを確認");
    addTranslation("ja", "close", "閉じる");
    addTranslation("ja", "info", "情報");
    addTranslation("ja", "syncing_database", "🔃 パッケージデータベースを同期中...");
    addTranslation("ja", "checking_updates", "🔃 アップデート確認前の同期中...");
    addTranslation("ja", "checking_yay_updates", "🔃 AUR (yay) アップデートを確認中...\n");
    addTranslation("ja", "checking_elysia_updates", "🔄 git-elyos.sh を使用してエリシアOSのアップデートを確認中...\n");
    addTranslation("ja", "system_up_to_date", "✅ システムは最新です。");
    addTranslation("ja", "aur_up_to_date", "✅ すべての AUR パッケージは最新です。");
    addTranslation("ja", "updates_found", "🔧 %1 件のアップデートが見つかりました:\n");
    addTranslation("ja", "aur_updates_found", "🌟 %1 件の AUR アップデートが見つかりました:\n");
    addTranslation("ja", "update_only", "%1 のみを更新");
    addTranslation("ja", "update_all", "すべてを更新");
    addTranslation("ja", "update_all_aur", "すべての AUR を更新");
    addTranslation("ja", "updating_package", "⏳ %1 を更新中...\n");
    addTranslation("ja", "updating_aur_package", "⏳ AUR パッケージ %1 を更新中...\n");
    addTranslation("ja", "updating_all", "⏳ すべてのパッケージを更新中...\n");
    addTranslation("ja", "updating_all_aur", "⏳ すべての AUR パッケージを更新中...\n");
    addTranslation("ja", "update_finished", "✅ 更新が完了しました!\nメニューに戻ります...");
    addTranslation("ja", "elysia_update_finished", "✅ エリシアOSのアップデート確認が完了しました。\nメニューに戻ります...");
    
    // Chinese translations
    addTranslation("zh", "window_title", "Elysia 更新程序");
    addTranslation("zh", "check_updates", "检查更新");
    addTranslation("zh", "check_yay_updates", "检查 YAY 更新");
    addTranslation("zh", "check_elysia_updates", "检查 ELYSIAOS 更新");
    addTranslation("zh", "close", "关闭");
    addTranslation("zh", "info", "信息");
    addTranslation("zh", "syncing_database", "🔃 正在同步包数据库...");
    addTranslation("zh", "checking_updates", "🔃 检查更新前正在同步...");
    addTranslation("zh", "checking_yay_updates", "🔃 正在检查 AUR (yay) 更新...\n");
    addTranslation("zh", "checking_elysia_updates", "🔄 正在使用 git-elyos.sh 检查 ElysiaOS 更新...\n");
    addTranslation("zh", "system_up_to_date", "✅ 系统已是最新。");
    addTranslation("zh", "aur_up_to_date", "✅ 所有 AUR 软件包都是最新的。");
    addTranslation("zh", "updates_found", "🔧 找到 %1 个更新:\n");
    addTranslation("zh", "aur_updates_found", "🌟 找到 %1 个 AUR 更新:\n");
    addTranslation("zh", "update_only", "仅更新 %1");
    addTranslation("zh", "update_all", "全部更新");
    addTranslation("zh", "update_all_aur", "更新所有 AUR");
    addTranslation("zh", "updating_package", "⏳ 正在更新 %1...\n");
    addTranslation("zh", "updating_aur_package", "⏳ 正在更新 AUR 软件包 %1...\n");
    addTranslation("zh", "updating_all", "⏳ 正在更新所有软件包...\n");
    addTranslation("zh", "updating_all_aur", "⏳ 正在更新所有 AUR 软件包...\n");
    addTranslation("zh", "update_finished", "✅ 更新完成!\n正在返回菜单...");
    addTranslation("zh", "elysia_update_finished", "✅ ElysiaOS 更新检查完成。\n正在返回菜单...");
    
    // Vietnamese translations
    addTranslation("vi", "window_title", "Trình Cập Nhật Elysia");
    addTranslation("vi", "check_updates", "KIỂM TRA CẬP NHẬT");
    addTranslation("vi", "check_yay_updates", "KIỂM TRA CẬP NHẬT YAY");
    addTranslation("vi", "check_elysia_updates", "KIỂM TRA CẬP NHẬT ELYSIAOS");
    addTranslation("vi", "close", "ĐÓNG");
    addTranslation("vi", "info", "Thông tin");
    addTranslation("vi", "syncing_database", "🔃 Đang đồng bộ cơ sở dữ liệu gói...");
    addTranslation("vi", "checking_updates", "🔃 Đang đồng bộ trước khi kiểm tra cập nhật...");
    addTranslation("vi", "checking_yay_updates", "🔃 Đang kiểm tra cập nhật AUR (yay)...\n");
    addTranslation("vi", "checking_elysia_updates", "🔄 Đang kiểm tra cập nhật ElysiaOS bằng git-elyos.sh...\n");
    addTranslation("vi", "system_up_to_date", "✅ Hệ thống đã được cập nhật.");
    addTranslation("vi", "aur_up_to_date", "✅ Tất cả các gói AUR đã được cập nhật.");
    addTranslation("vi", "updates_found", "🔧 Tìm thấy %1 cập nhật:\n");
    addTranslation("vi", "aur_updates_found", "🌟 Tìm thấy %1 cập nhật AUR:\n");
    addTranslation("vi", "update_only", "Chỉ cập nhật %1");
    addTranslation("vi", "update_all", "Cập nhật tất cả");
    addTranslation("vi", "update_all_aur", "Cập nhật tất cả AUR");
    addTranslation("vi", "updating_package", "⏳ Đang cập nhật %1...\n");
    addTranslation("vi", "updating_aur_package", "⏳ Đang cập nhật gói AUR %1...\n");
    addTranslation("vi", "updating_all", "⏳ Đang cập nhật tất cả các gói...\n");
    addTranslation("vi", "updating_all_aur", "⏳ Đang cập nhật tất cả các gói AUR...\n");
    addTranslation("vi", "update_finished", "✅ Cập nhật hoàn tất!\nQuay lại menu...");
    addTranslation("vi", "elysia_update_finished", "✅ Kiểm tra cập nhật ElysiaOS hoàn tất.\nQuay lại menu...");
    
    // Russian translations
    addTranslation("ru", "window_title", "Обновлятор Elysia");
    addTranslation("ru", "check_updates", "ПРОВЕРИТЬ ОБНОВЛЕНИЯ");
    addTranslation("ru", "check_yay_updates", "ПРОВЕРИТЬ ОБНОВЛЕНИЯ YAY");
    addTranslation("ru", "check_elysia_updates", "ПРОВЕРИТЬ ОБНОВЛЕНИЯ ELYSIAOS");
    addTranslation("ru", "close", "ЗАКРЫТЬ");
    addTranslation("ru", "info", "Информация");
    addTranslation("ru", "syncing_database", "🔃 Синхронизация базы данных пакетов...");
    addTranslation("ru", "checking_updates", "🔃 Синхронизация перед проверкой обновлений...");
    addTranslation("ru", "checking_yay_updates", "🔃 Проверка обновлений AUR (yay)...\n");
    addTranslation("ru", "checking_elysia_updates", "🔄 Проверка обновлений ElysiaOS с помощью git-elyos.sh...\n");
    addTranslation("ru", "system_up_to_date", "✅ Система актуальна.");
    addTranslation("ru", "aur_up_to_date", "✅ Все пакеты AUR актуальны.");
    addTranslation("ru", "updates_found", "🔧 Найдено %1 обновлений:\n");
    addTranslation("ru", "aur_updates_found", "🌟 Найдено %1 обновлений AUR:\n");
    addTranslation("ru", "update_only", "Обновить только %1");
    addTranslation("ru", "update_all", "Обновить все");
    addTranslation("ru", "update_all_aur", "Обновить все AUR");
    addTranslation("ru", "updating_package", "⏳ Обновление %1...\n");
    addTranslation("ru", "updating_aur_package", "⏳ Обновление пакета AUR %1...\n");
    addTranslation("ru", "updating_all", "⏳ Обновление всех пакетов...\n");
    addTranslation("ru", "updating_all_aur", "⏳ Обновление всех пакетов AUR...\n");
    addTranslation("ru", "update_finished", "✅ Обновление завершено!\nВозврат в меню...");
    addTranslation("ru", "elysia_update_finished", "✅ Проверка обновлений ElysiaOS завершена.\nВозврат в меню...");
    
    // Indonesian translations
    addTranslation("id", "window_title", "Pembaru Elysia");
    addTranslation("id", "check_updates", "PERIKSA PEMBARUAN");
    addTranslation("id", "check_yay_updates", "PERIKSA PEMBARUAN YAY");
    addTranslation("id", "check_elysia_updates", "PERIKSA PEMBARUAN ELYSIAOS");
    addTranslation("id", "close", "TUTUP");
    addTranslation("id", "info", "Info");
    addTranslation("id", "syncing_database", "🔃 Menyinkronkan database paket...");
    addTranslation("id", "checking_updates", "🔃 Menyinkronkan sebelum memeriksa pembaruan...");
    addTranslation("id", "checking_yay_updates", "🔃 Memeriksa pembaruan AUR (yay)...\n");
    addTranslation("id", "checking_elysia_updates", "🔄 Memeriksa pembaruan ElysiaOS menggunakan git-elyos.sh...\n");
    addTranslation("id", "system_up_to_date", "✅ Sistem sudah terbaru.");
    addTranslation("id", "aur_up_to_date", "✅ Semua paket AUR sudah terbaru.");
    addTranslation("id", "updates_found", "🔧 %1 pembaruan ditemukan:\n");
    addTranslation("id", "aur_updates_found", "🌟 %1 pembaruan AUR ditemukan:\n");
    addTranslation("id", "update_only", "Perbarui hanya %1");
    addTranslation("id", "update_all", "Perbarui semua");
    addTranslation("id", "update_all_aur", "Perbarui semua AUR");
    addTranslation("id", "updating_package", "⏳ Memperbarui %1...\n");
    addTranslation("id", "updating_aur_package", "⏳ Memperbarui paket AUR %1...\n");
    addTranslation("id", "updating_all", "⏳ Memperbarui semua paket...\n");
    addTranslation("id", "updating_all_aur", "⏳ Memperbarui semua paket AUR...\n");
    addTranslation("id", "update_finished", "✅ Pembaruan selesai!\nKembali ke menu...");
    addTranslation("id", "elysia_update_finished", "✅ Pemeriksaan pembaruan ElysiaOS selesai.\nKembali ke menu...");
}

void Translations::addTranslation(const QString& lang, const QString& key, const QString& value) {
    m_translations[lang][key] = value;
}

QString Translations::get(const QString& key) const {
    // Try to get translation for current language
    if (m_translations.contains(m_currentLang) && m_translations[m_currentLang].contains(key)) {
        return m_translations[m_currentLang][key];
    }
    
    // Fallback to English
    if (m_translations.contains("en") && m_translations["en"].contains(key)) {
        return m_translations["en"][key];
    }
    
    // If no translation found, return the key itself
    return key;
}