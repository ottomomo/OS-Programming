#!/bin/bash

# ${valores[*]}         # Muestra todos los valores de un array
# ${!valores[*]}        # Muestra todos los indices de un array
# ${#valores[*]}        # Devuelve el numero de valores en un array
# ${#valores[0]}        # Devuelve la longitud del indice 0
#bs =(1 128 512 1024 2048 2200 4096 5000)
bs[1]=1
bs[2]=128
bs[3]=512
bs[4]=1024
bs[5]=2048
bs[6]=2200
bs[7]=4096
bs[8]=5000

for index in ${bs[*]} ; do
	count=$(( 16*1024*1024 / index ))
	time dd if=/dev/zero of=salida bs= ${index} count= $count
done
