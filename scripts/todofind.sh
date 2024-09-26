
echo "# Todos" > todo.md
echo "|file|line|message|" >> todo.md
echo "|----|----|-------|" >> todo.md


 grep "todo" ./src -riIn --exclude-dir={thirdparty,.git,.vs,_deps} --include=*.{cpp,h} | \
 awk '{split($0, array, ":"); split($0, todoArray, "todo:|@todo:|TODO:|TODO"); print array[1], "|", array[2], "|", todoArray[2]; }' >> todo.md