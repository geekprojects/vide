
SUBDIRS=src tests

COPYRIGHT_LICENSE ?= GPL3
COPYRIGHT_HOLDER ?= Ian Parker <ian@geekprojects.com>
COPYRIGHT_YEAR ?= 2018
COPYRIGHT_SOFTWARE ?= Vide
COPYRIGHT_SOFTWARE_DESCRIPTION ?= Vi IDE
COPYRIGHT_OUTPUT_DIR ?= output
COPYRIGHT_WORD_WRAP ?= 100
COPYRIGHT_PATHS ?= src

add-copyright:
	copyright-header \
          --license $(COPYRIGHT_LICENSE)  \
          --add-path $(COPYRIGHT_PATHS) \
          --guess-extension \
          --copyright-holder '$(COPYRIGHT_HOLDER)' \
          --copyright-software '$(COPYRIGHT_SOFTWARE)' \
          --copyright-software-description '$(COPYRIGHT_SOFTWARE_DESCRIPTION)' \
          --copyright-year $(COPYRIGHT_YEAR) \
          --word-wrap $(COPYRIGHT_WORD_WRAP) \
          --output-dir $(COPYRIGHT_OUTPUT_DIR) \
          --syntax ../frontier/tools/syntax.yml

osxapp:
	appr.sh --executable src/vide/.libs/vide --app Vide.app --appname Vide --bundleid com.geekprojects.vide --version 0.0.1 --highdpi true

