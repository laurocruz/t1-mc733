#!/bin/sh

echo "Gerando aqruivo para ser testado"
dd if=/dev/urandom of=test500MB.pt bs=1048576 count=500

echo "COMPILANDO"
make

echo "EXECUTANDO"
max=6
sumr=0
sumc=0
for i in `seq 2 $max`
do
    echo $i
	output=$(./aes test500MB.pt)

    real=$(echo $output | awk '{print $5'})
    cpu=$(echo $output | awk '{print $10'})
    
    sumr=$(echo $sumr + $real | bc)
    sumc=$(echo $sumc + $cpu | bc)
done

    sumr=$(echo "scale=8;$sumr/5.0" | bc)
    sumc=$(echo "scale=8;$sumc/5.0" | bc)

    sumr=$(echo "$sumr - $sumc" | bc)

    echo "MEDIA CPU = $sumc"
    echo "REAL - CPU = $sumr"

    perf stat -B ./aes test500MB.pt



