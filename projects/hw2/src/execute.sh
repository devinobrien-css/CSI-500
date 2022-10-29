
gcc main.c ./layers/physical.c ./layers/data_link.c ./layers/application.c -o main

# clear files
echo | grep 'CLEAR' > ./bin/filename.binf
echo | grep 'CLEAR' > ./bin/filename.chck
echo | grep 'CLEAR' > ./bin/filename.done
echo | grep 'CLEAR' > ./bin/filename.outf
echo | grep 'CLEAR' > ./bin/filename.inpf

# execute program
echo "-----------------------------------------------------------------------"
echo "Executing Program:"
echo
echo "Input:"
echo "I am the contents of a file to be read, converted to bits, transferred, decoded, interpreted, and printed." 
echo
echo "I am the contents of a file to be read, converted to bits, transferred, decoded, interpreted, and printed." > bin/filename.inpf
echo "Result:"
./main
echo
echo "Expected:"
echo "I AM THE CONTENTS OF A FILE TO BE READ, CONVERTED TO BITS, TRANSFERRED, DECODED, INTERPRETED, AND PRINTED."
echo "-----------------------------------------------------------------------"