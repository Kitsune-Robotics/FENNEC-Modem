# A collection of shortcuts for building the docs

# Get vars
hash := $(shell git describe --abbrev=6 --always --tags --dirty)
builddate := $(shell date +"%m-%d-%y")
pwd = $(shell pwd)
builddir = $(pwd)/_build

# Sphinx defs
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = .

# General doc cleanup
clean:
	git clean -fdX

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(builddir)" $(SPHINXOPTS) $(O)

# Explicit sphinx doctypes.
latexpdf:
	@$(SPHINXBUILD) -M latexpdf "$(SOURCEDIR)" "$(builddir)" $(SPHINXOPTS) $(O)
html:
	@$(SPHINXBUILD) -M html "$(SOURCEDIR)" "$(builddir)" $(SPHINXOPTS) $(O)
