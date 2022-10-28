
gcc consumerProducerParent.c -o consumerProducerParent
gcc producerConsumerChild.c -o producerConsumerChild

echo "-----------------------------------------------------------------------"
echo "Executing Program:"
echo
./consumerProducerParent editSource.txt
echo
echo "Expected:"
echo "chars -> 141"
echo "words -> 25"
echo "lines -> 7"
echo "-----------------------------------------------------------------------"