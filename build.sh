#!/usr/bin/env bash
# Fetch the latest version of the library
fetch() {
if [ -d "xxhash" ]; then return; fi
URL="https://github.com/Cyan4973/xxHash/archive/refs/heads/dev.zip"
ZIP="${URL##*/}"
DIR="xxHash-dev"
mkdir -p .build
cd .build

# Download the release
if [ ! -f "$ZIP" ]; then
  echo "Downloading $ZIP from $URL ..."
  curl -L "$URL" -o "$ZIP"
  echo ""
fi

# Unzip the release
if [ ! -d "$DIR" ]; then
  echo "Unzipping $ZIP to .build/$DIR ..."
  cp "$ZIP" "$ZIP.bak"
  unzip -q "$ZIP"
  rm "$ZIP"
  mv "$ZIP.bak" "$ZIP"
  echo ""
fi
cd ..

# Copy the libs to the package directory
echo "Copying libs to xxhash/ ..."
rm -rf xxhash
mkdir -p xxhash
cp -f ".build/$DIR"/*.c xxhash/
cp -f ".build/$DIR"/*.h xxhash/
echo ""
}


# Test the project
test() {
echo "Running 01-print-version.c ..."
clang -I. -o 01.exe examples/01-print-version.c  && ./01.exe && echo -e "\n"
echo "Running 02-simple-buffer.c ..."
clang -I. -o 02.exe examples/02-simple-buffer.c  && ./02.exe && echo -e "\n"
echo "Running 03-file-compress.c ..."
clang -I. -o 03.exe examples/03-file-compress.c
./03.exe examples/03-file-compress.c && echo -e "\n"
}


# Main script
if [[ "$1" == "test" ]]; then test
elif [[ "$1" == "fetch" ]]; then fetch
else echo "Usage: $0 {fetch|test}"; fi
