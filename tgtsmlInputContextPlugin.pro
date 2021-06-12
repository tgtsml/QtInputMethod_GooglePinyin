TEMPLATE        = subdirs
SUBDIRS         = googlepinyin \
                  plugin \
                  demo

CONFIG          += ordered

plugin.depends  = googlepinyin
demo.depends = plugin
