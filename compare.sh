#! /bin/bash
g++ matrix_product.cpp -O3 -o direct
g++ matrix_product.cpp -O3 -DREORDER -o reorder

printf "without reorder\n"
time ./direct
printf "\nwith reorder\n"
time ./reorder

rm direct
rm reorder
