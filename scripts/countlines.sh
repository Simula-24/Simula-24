#!/bin/bash

cloc --exclude-dir="CMakeFiles,_deps,thirdparty,.vs" ./simula24 --include-ext=cpp,h,c --by-file
