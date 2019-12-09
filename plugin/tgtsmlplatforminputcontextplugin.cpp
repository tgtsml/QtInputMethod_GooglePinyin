#include "tgtsmlplatforminputcontextplugin.h"

TgtsmlPlatformInputContext * TgtsmlPlatformInputContextPlugin::create(const QString &key, const QStringList &paramlist)
{
    Q_UNUSED(paramlist)

    if(key.compare("tgtsml",Qt::CaseInsensitive) == 0)
    {
        return new TgtsmlPlatformInputContext;
    }
    return nullptr;
}
