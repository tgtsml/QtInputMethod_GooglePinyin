#ifndef TGTSMLPLATFORMINPUTCONTEXTPLUGIN_H
#define TGTSMLPLATFORMINPUTCONTEXTPLUGIN_H

#include <qpa/qplatforminputcontextplugin_p.h>
#include "tgtsmlplatforminputcontext.h"

class TgtsmlPlatformInputContextPlugin : public QPlatformInputContextPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformInputContextFactoryInterface_iid FILE "./res/tgtsml.json")

public:
    TgtsmlPlatformInputContext *create(const QString &key, const QStringList &paramlist);
};

#endif // TGTSMLPLATFORMINPUTCONTEXTPLUGIN_H
