TEMPLATE        = subdirs
SUBDIRS         = googlepinyin plugin window

CONFIG          += ordered

window.depends  = plugin
plugin.depends  = googlepinyin
