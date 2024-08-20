target="$1"

if [ -z "$target" ]; then
    echo "Usage: ./zip.sh <file>"
    exit 1
fi
 
if [ ! -d "$target" ]; then
    echo "Error: $target is not a directory."
    exit 1
fi

parent_dir=$(dirname "$target")
target_name=$(basename "$target")
zip_file="$parent_dir/$target_name.zip"

cd "$target" || exit
zip -r "$zip_file" ./*

echo "Directory contents of $target have been zipped to $zip_file"