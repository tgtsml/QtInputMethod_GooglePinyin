TEMPLATE        = subdirs
SUBDIRS         = googlepinyin \
                  plugin \
                  TestDemo

CONFIG          += ordered

plugin.depends  = googlepinyin
TestDemo.depends = plugin
