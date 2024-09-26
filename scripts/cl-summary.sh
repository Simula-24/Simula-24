	#!/bin/bash

cloc --exclude-dir="CMakeFiles,_deps,thirdparty,.vs" ./src --include-ext=cpp,h,c,glsl
