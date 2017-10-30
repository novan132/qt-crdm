TEMPLATE = subdirs

SUBDIRS += \
    sdk-utilities \
    crdm-server

crdm-server.depends = sdk-utilities
