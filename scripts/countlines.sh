#!/bin/bash

cloc --exclude-dir="CMakeFiles,_deps,thirdparty,.vs" ./srcs --include-ext=cpp,h,c --by-file
