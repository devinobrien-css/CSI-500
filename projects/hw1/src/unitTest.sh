gcc consumerProducerParent.c -o consumerProducerParent
gcc producerConsumerChild.c -o producerConsumerChild

echo "-----------------------------------------------------------------------"
echo "TEST CASE 1: a large dataset"
./consumerProducerParent inputTestCase1.txt
echo "Expected:"
echo "chars -> 1504"
echo "words -> 200"
echo "lines -> 20"
echo "-----------------------------------------------------------------------"

echo 
echo

echo "-----------------------------------------------------------------------"
echo "TEST CASE 2: a small dataset"
./consumerProducerParent inputTestCase2.txt
echo "Expected:"
echo "chars -> 56"
echo "words -> 13"
echo "lines -> 3"

echo 
echo

echo "-----------------------------------------------------------------------"
echo "TEST CASE 3: the given dataset"
./consumerProducerParent editSource.txt
echo "Expected:"
echo "chars -> 141"
echo "words -> 25"
echo "lines -> 7"
echo "-----------------------------------------------------------------------"

echo 
echo



echo "-----------------------------------------------------------------------"
echo "TEST CASE 4: an extremely large dataset"
./consumerProducerParent inputTestCase3.txt
echo 
echo "Expected:"
echo "chars -> 13536"
echo "words -> 1794"
echo "lines -> 174"
echo "-----------------------------------------------------------------------"