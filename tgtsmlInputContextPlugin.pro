TEMPLATE        = subdirs
SUBDIRS         = googlepinyin plugin

CONFIG          += ordered

testWindow.depends  = plugin
plugin.depends  = googlepinyin
