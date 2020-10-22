#!/bin/bash

MPOINT="./mount-point"
DIRTEMP="./temp"
VDISK="virtual-disk"
AUDITTOOL="./my-fsck-static-64"

FILE1="fuseLib.c"
FILE2="myFS.h"
FILE3="MyFileSystem.c"

if [ -d ./temp ]
then
	rm -R -f $DIRTEMP
	mkdir $DIRTEMP
fi

echo "Copying file 1"
cp ./src/$FILE1 $MPOINT/
cp ./src/$FILE1 $DIRTEMP/

echo 'Copying file 2' 
cp ./src/$FILE2 $MPOINT/
cp ./src/$FILE2 $DIRTEMP/

# Auditamos el disco
echo "Audit filesystem"
$AUDITTOOL $VDISK
# Auditamos el disco

# Comparamos los ficheros
echo 'Comparing file 1'
diff $DIRTEMP/$FILE1 $MPOINT/$FILE1
if [ $? -eq 0 ]
then
	echo "Correct"
else
	echo "Error: the files don't match"
fi

echo 'Comparing file 2'
diff $DIRTEMP/$FILE2 $MPOINT/$FILE2
if [ $? -eq 0 ]
then
	echo "Correct"
else
	echo "Error: the files don't match"
fi
# Comparamos los ficheros

# Truncamos el primer fichero en temporal
echo "Truncate file 1 to one less block in temporal directory"
truncate -os -1 $DIRTEMP/$FILE1
# Truncamos el primer fichero en temporal

# Truncamos el primer fichero en nuestro FS
echo "Truncate file 1 to one less block in mount point"
truncate -os -1 $MPOINT/$FILE1
# Truncamos el primer fichero en nuestro FS

# Auditamos el disco
$AUDITTOOL $VDISK
# Auditamos el disco

# Comparamos el primer fichero
echo 'Comparing file 1'
diff $DIRTEMP/$FILE1 $MPOINT/$FILE1
if [ $? -eq 0 ]
then
	echo "Correct"
else
	echo "Error: the files don't match"
fi
# Comparamos el primer fichero

# Añadimos un tercer fichero
echo 'Copying file 3' 
cp ./src/$FILE3 $MPOINT/
cp ./src/$FILE3 $DIRTEMP/

# Auditamos el disco
$AUDITTOOL $VDISK
# Auditamos el disco

# Comparamos el fichero nuevo
echo 'Comparing file 3'
diff .$DIRTEMP/$FILE3 $MPOINT/$FILE3
if [ $? -eq 0 ]
then
	echo "Correct"
else
	echo "Error: the files don't match"
fi
# Comparamos el fichero nuevo

# Truncamos el segundo fichero en nuesto FS
echo "Truncate file 2 to one more block in temporal directory"
truncate -os +1 $DIRTEMP/$FILE2
# Truncamos el segundo fichero en nuesto FS

# Truncamos el segundo fichero en nuesto TEMP
echo "Truncate file 2 to one more block in mount point"
truncate -os +1 $MPOINT/$FILE2
# Truncamos el segundo fichero en nuesto TEMP

# Auditamos el disco
$AUDITTOOL $VDISK
# Auditamos el disco

# Comparamos el segundo fichero
echo 'Comparing file 2'
diff $DIRTEMP/$FILE2 $MPOINT/$FILE2
if [ $? -eq 0 ]
then
	echo "Correct"
else
	echo "Error: the files don't match"
fi
# Comparamos el segundo fichero

exit 0