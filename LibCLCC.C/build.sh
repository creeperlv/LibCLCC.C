#!/bin/sh

mkdir -p bin
mkdir -p bin/Examples

if [ -z "$CC" ];
then
  CC="cc"
fi

for item in Examples/*; do 
  if [ -f "$item" ]; then
    item_basename=$(basename "$item")
    dir_path=$(dirname "$item")
    base_name_no_ext="${item_basename%.*}"
    file_path_no_ext="$dir_path/$base_name_no_ext"
    COMPILE="$CC --std=c99 ./Source/*.c $item -o bin/$file_path_no_ext"
    echo "$COMPILE"
    $COMPILE
  fi
done
# find "Examples" -type f -print0 | while IFS= read -r -d '' file; do
    
# done
