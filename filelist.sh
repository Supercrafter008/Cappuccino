#! /bin/bash

outFile="./src/resources/filelist.h"
count=0

for i in $(find ./data -type f  \( ! -printf "%f\n" \) | sort -f)
do
	files[count]=$i
	count=$((count+1))
done

echo "Generating filelist.h for $count files." >&2
cat <<EOF > $outFile
//This file was generated on build
#pragma once

struct ResourceFile
{
	const char          *filename;
	const unsigned char *File;
	const unsigned int  &FileSize;
};

EOF

for i in ${files[@]}
do
	filename=${i%.*}
	extension=${i##*.}
	echo '#include "'$filename'_'$extension'.h"' >> $outFile
done

echo '' >> $outFile
echo 'static ResourceFile ResourceList[] =' >> $outFile
echo '{' >> $outFile

for i in ${files[@]}
do
	filename=${i%.*}
	extension=${i##*.}
	echo -e '\t{"'$i'", '$filename'_'$extension', '$filename'_'$extension'_size},' >> $outFile
done

echo -e '\t{NULL, NULL, 0}' >> $outFile
echo '};' >> $outFile

echo '' >> $outFile
