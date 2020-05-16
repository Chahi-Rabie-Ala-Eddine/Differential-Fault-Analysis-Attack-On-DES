#!/bin/bash

declare -a array_files=( 
"bin" 
"obj" 
"obj/ANALYZER" 
"obj/ATTACK" 
"obj/DES" 
"obj/PRINTER" 
"obj/UTILS"  
)

mkdir ${array_files[@]} 2> /dev/null 

unset array[@]
