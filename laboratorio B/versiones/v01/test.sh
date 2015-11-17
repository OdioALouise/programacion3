#!/usr/bin/env bash

# variables a editar
CASOS=(00 01 02 03 04 05)

ENTREGAR="Congreso.cpp"

ARCH_ENTREGA=EntregaB.tar.gz
LOG_ENTREGA=EntregaB.log

rm -f test/*.sal test/*.diff *.o Principal

g++ -Wall -Werror -o Principal $ENTREGAR Principal.cpp test_helper.cpp

for caso in ${CASOS[@]}; do \
    ./Principal < test/Caso$caso.in > test/Caso$caso.sal; \
    diff test/Caso$caso.out test/Caso$caso.sal > test/Caso$caso.diff; \
done

if [ "${#CASOS[@]}" -eq 0 ]; then
    echo No hay casos de prueba
else
    echo Debe haber ${#CASOS[@]} archivos .sal
    ls -lgG  test/*.sal
    echo
    echo Debe haber ${#CASOS[@]} archivos .diff de tamanio 0
    ls -lgG -o test/*.diff
fi

# Generar entregable
echo -n "Desea generar el archivo de entrega? (S/N): "
read entrega
if [ $entrega = "S" ] || [ $entrega = "s" ] ; then
    rm -f $ARCH_ENTREGA $LOG_ENTREGA
    echo
    echo "Modulos:"
    tar -zcvf $ARCH_ENTREGA $ENTREGAR
    echo
    echo "Archivo a entregar:"
    (ls -lgG $ARCH_ENTREGA; md5sum $ARCH_ENTREGA) | tee $LOG_ENTREGA
fi
