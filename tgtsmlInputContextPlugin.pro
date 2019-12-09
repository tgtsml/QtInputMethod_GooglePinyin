TEMPLATE        = subdirs
SUBDIRS         = googlepinyin plugin testWindow

CONFIG          += ordered

testWindow.depends  = plugin
plugin.depends  = googlepinyin
